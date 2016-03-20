/*
 * IOUtils.cpp
 *
 *  Created on: 26 lut 2016
 *      Author: tomasz
 */

#include "../../include/utils/IOUtils.hpp"

#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/exceptions.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/streams/bufferstream.hpp>
#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "../../include/enums/GraphConstructMode.hpp"
#include "../../include/exp/IOExceptions.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogStringUtils.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/EdgeIF.hpp"
#include "../../include/structures/GraphInclude.hpp"
#include "../../include/structures/VertexInclude.hpp"
#include "../../include/typedefs/primitive.hpp"
#include "../../include/utils/enums/GraphVizEngine.hpp"
#include "../../include/utils/enums/InputFormat.hpp"
#include "../../include/utils/enums/InputMode.hpp"
#include "../../include/utils/enums/OutputFormat.hpp"
#include "../../include/utils/GraphVizUtils.hpp"
#include "../../include/utils/StringUtils.hpp"

class EdgeSetIF;
class VertexSetIF;

const static log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("utils.IOUtils"));

const unsigned short IOUtils::impl::MAX_CHARS_IN_LINE { 2
		* (std::numeric_limits<EdgeIdx>::digits10 + 1)
		+ (std::numeric_limits<EdgeCost>::digits10 + 1) + 3 };

const long IOUtils::impl::MAX_STREAM_SIZE {
		std::numeric_limits<std::streamsize>::max() };
const short IOUtils::impl::BUFFER_SIZE { 4096 };

const char IOUtils::impl::GR::COMMENT_LINE { 'c' };
constexpr unsigned short IOUtils::impl::GR::COMMENT_LINE_NUMERIC {
		IOUtils::impl::GR::COMMENT_LINE };
const char* IOUtils::impl::GR::COMMENT_LINE_PATTERN { "%*[^\n]\n" };
const unsigned short IOUtils::impl::GR::COMMENT_LINE_PATTERN_ARGS { 0 };

extern const char IOUtils::impl::GR::PROBLEM_DEF_LINE { 'p' };
extern const unsigned short IOUtils::impl::GR::PROBLEM_DEF_LINE_NUMERIC {
		IOUtils::impl::GR::PROBLEM_DEF_LINE };
extern const std::unique_ptr<char[]> IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" mst %VertexCount% %EdgeCount%") };
extern const unsigned short IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN_ARGS { 2 };

extern const char IOUtils::impl::GR::ARC_DEF_LINE { 'a' };
extern const unsigned short IOUtils::impl::GR::ARC_DEF_LINE_NUMERIC {
		IOUtils::impl::GR::ARC_DEF_LINE };
extern const std::unique_ptr<char[]> IOUtils::impl::GR::ARC_DEF_LINE_PATTERN {
		StringUtils::parseStringFormatSpecifiers(
				" %VertexIdx% %VertexIdx% %IOEdgeCost%") };
const unsigned short IOUtils::impl::GR::ARC_DEF_LINE_PATTERN_ARGS { 3 };

const char* IOUtils::impl::VA::VERTEX_LIST_KEY { "vl" };
const char* IOUtils::impl::VA::EDGE_LIST_KEY { "el" };
const char* IOUtils::impl::VA::EDGE_VERTEX_A_KEY { "vertexA" };
const char* IOUtils::impl::VA::EDGE_VERTEX_B_KEY { "vertexB" };
const char* IOUtils::impl::VA::EDGE_COST_KEY { "weight" };

const char* IOUtils::impl::DOT::GRAPH_DEF { "graph" };
const char* IOUtils::impl::DOT::DIR { "rankdir" };
const char* IOUtils::impl::DOT::LABEL { "label" };
const char* IOUtils::impl::DOT::WEIGHT { "weight" };
const char* IOUtils::impl::DOT::LEN { "len" };
const char* IOUtils::impl::DOT::EDGE_UNDIR { "--" };
const char* IOUtils::impl::DOT::ENDLN { ";" };

GraphIF * InputUtils::readGraph(char const * filename, InputFormat inputFormat,
		InputMode inputMode) throw (IOExceptions::FileNotFountException) {
	switch (inputMode) {
	case InputMode::RAM:
		return InputUtils::impl::RAM::readGraph(filename, inputFormat);
	default:
		return InputUtils::impl::HDD::readGraph(filename, inputFormat);
	}
	return nullptr;
}

GraphIF * InputUtils::impl::RAM::readGraph(char const * const filename,
		InputFormat inputFormat) throw (IOExceptions::FileNotFountException) {
	switch (inputFormat) {
	case InputFormat::VA:
		return InputUtils::impl::RAM::VA::readGraph(filename);
	default:
		return InputUtils::impl::RAM::GR::readGraph(filename);
	}
}

GraphIF * InputUtils::impl::RAM::VA::readGraph(char const * const filename)
		throw (IOExceptions::FileNotFountException) {
	GraphIF * graph { };

	std::size_t fileSize { };

	char* buffer { };

	rapidjson::Document jsonDoc { };
	rapidjson::Value::MemberIterator vertexList { };
	rapidjson::Value::MemberIterator edgeList { };
	rapidjson::Value::MemberIterator endValue { };
	rapidjson::Value::ConstMemberIterator it { };

	try {
		boost::interprocess::file_mapping mappedFile(filename,
				boost::interprocess::read_only);

		boost::interprocess::mapped_region mappedRegionOfFile(mappedFile,
				boost::interprocess::read_only);

		fileSize = mappedRegionOfFile.get_size();

		boost::interprocess::bufferstream input_stream(
				static_cast<char*>(mappedRegionOfFile.get_address()), fileSize);

		jsonDoc.Parse(input_stream.buffer().first);

		endValue = jsonDoc.MemberEnd();
		vertexList = jsonDoc.FindMember(IOUtils::impl::VA::VERTEX_LIST_KEY);
		if (vertexList != endValue) {
			edgeList = jsonDoc.FindMember(IOUtils::impl::VA::EDGE_LIST_KEY);
			if (edgeList != endValue) {
				graph = InputUtils::impl::RAM::VA::createGraph(
						vertexList->value, edgeList->value.MemberCount());
				it = edgeList->value.MemberEnd();
				for (rapidjson::Value::ConstMemberIterator itBegin =
						edgeList->value.MemberBegin(); itBegin != it;
						++itBegin) {
					InputUtils::impl::RAM::VA::addEdge(itBegin, graph);
				}
			}
		}

		INFO(logger, LogBundleKey::IOU_END_OF_READ, filename,
				LogStringUtils::graphDescription(graph, "\t").c_str());

		return graph;
	} catch (boost::interprocess::interprocess_exception& e) {
		throw IOExceptions::FileNotFountException(filename);
	}
}

GraphIF * InputUtils::impl::RAM::VA::createGraph(rapidjson::Value & vertexList,
		rapidjson::SizeType const numberOfEdges)
				throw (IOExceptions::InvalidProblemRead) {
	return InputUtils::impl::HDD::VA::createGraph(vertexList, numberOfEdges);
}

void InputUtils::impl::RAM::VA::addEdge(
		rapidjson::Value::ConstMemberIterator& edge, GraphIF * const graph)
				throw (IOExceptions::InvalidArcRead) {
	return InputUtils::impl::HDD::VA::addEdge(edge, graph);
}

GraphIF * InputUtils::impl::RAM::GR::readGraph(char const * const filename)
		throw (IOExceptions::FileNotFountException) {
	GraphIF * graph { };

	std::size_t fileSize { };

	char buffer[IOUtils::impl::BUFFER_SIZE] { };

	try {
		boost::interprocess::file_mapping mappedFile(filename,
				boost::interprocess::read_only);

		boost::interprocess::mapped_region mappedRegionOfFile(mappedFile,
				boost::interprocess::read_only);

		fileSize = mappedRegionOfFile.get_size();

		boost::interprocess::bufferstream input_stream(
				static_cast<char*>(mappedRegionOfFile.get_address()), fileSize);

		while (!input_stream.eof()) {
			switch (input_stream.get()) {
			case IOUtils::impl::GR::COMMENT_LINE_NUMERIC:
				INFO_NOARG(logger,
						LogBundleKey::IOU_IGNORING_COMMENT_LINE_WHILE_READING)
				;
				input_stream.ignore(IOUtils::impl::MAX_STREAM_SIZE, '\n');
				break;
			case IOUtils::impl::GR::PROBLEM_DEF_LINE_NUMERIC:
				input_stream.getline(buffer, IOUtils::impl::MAX_CHARS_IN_LINE);
				graph = InputUtils::impl::RAM::GR::createGraph(buffer);
				break;
			case IOUtils::impl::GR::ARC_DEF_LINE_NUMERIC:
				input_stream.getline(buffer, IOUtils::impl::MAX_CHARS_IN_LINE);
				InputUtils::impl::RAM::GR::addEdge(buffer, graph);
				break;
			default:
				WARN_NOARG(logger,
						LogBundleKey::IOU_IGNORING_UNRECOGNISED_LINE_WHILE_READING)
				;
				break;
			}
		}

		INFO(logger, LogBundleKey::IOU_END_OF_READ, filename,
				LogStringUtils::graphDescription(graph, "\t").c_str());

		return graph;
	} catch (boost::interprocess::interprocess_exception& e) {
		throw IOExceptions::FileNotFountException(filename);
	}
}

GraphIF * InputUtils::impl::RAM::GR::createGraph(char * const buffer)
		throw (IOExceptions::InvalidProblemRead) {
	VertexCount vCount { };
	EdgeCount eCount { };
	if (sscanf(buffer, IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN.get(),
			&vCount, &eCount)
			!= IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_PROBLEM_LINE_READ);
		throw IOExceptions::InvalidProblemRead();
	}
	INFO(logger, LogBundleKey::IOU_MST_PROBLEM_READ, vCount, eCount);
	return new GraphImpl { vCount, eCount,
			GraphConstructMode::AUTO_CONSTRUCT_VERTEX };
}

void InputUtils::impl::RAM::GR::addEdge(char * const buffer,
		GraphIF * const graph) throw (IOExceptions::InvalidArcRead) {
	VertexIdx vertexU { };
	VertexIdx vertexV { };
	EdgeCost eCost { };
	if (sscanf(buffer, IOUtils::impl::GR::ARC_DEF_LINE_PATTERN.get(), &vertexU,
			&vertexV, &eCost) != IOUtils::impl::GR::ARC_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_ARC_LINE_READ);
		throw IOExceptions::InvalidArcRead();
	}
	INFO(logger, LogBundleKey::IOU_ARC_DEF_READ, vertexU, vertexV, eCost);
	graph->addEdge(vertexU, vertexV, eCost);
}

GraphIF * InputUtils::impl::HDD::readGraph(char const * const filename,
		InputFormat inputFormat) throw (IOExceptions::FileNotFountException) {
	switch (inputFormat) {
	case InputFormat::VA:
		return InputUtils::impl::HDD::VA::readGraph(filename);
	default:
		return InputUtils::impl::HDD::GR::readGraph(filename);
	}
}

GraphIF * InputUtils::impl::HDD::VA::readGraph(char const * const filename)
		throw (IOExceptions::FileNotFountException) {
	GraphIF * graph { };
	FILE * dataFile = std::fopen(filename, "r");
	rapidjson::Document jsonDoc { };
	rapidjson::Value::MemberIterator vertexList { };
	rapidjson::Value::MemberIterator edgeList { };
	rapidjson::Value::MemberIterator endValue { };
	rapidjson::Value::ConstMemberIterator it { };
	char readBuffer[IOUtils::impl::BUFFER_SIZE] { };
	if (dataFile == NULL) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, filename);
		throw IOExceptions::FileNotFountException(filename);
	} else {
		TRACE(logger, LogBundleKey::IOU_START_READ_FILE_DATA, filename);
		rapidjson::FileReadStream is(dataFile, readBuffer, sizeof(readBuffer));
		jsonDoc.ParseStream(is);
		endValue = jsonDoc.MemberEnd();
		vertexList = jsonDoc.FindMember(IOUtils::impl::VA::VERTEX_LIST_KEY);
		if (vertexList != endValue) {
			edgeList = jsonDoc.FindMember(IOUtils::impl::VA::EDGE_LIST_KEY);
			if (edgeList != endValue) {
				graph = InputUtils::impl::HDD::VA::createGraph(
						vertexList->value, edgeList->value.MemberCount());
				it = edgeList->value.MemberEnd();
				for (rapidjson::Value::ConstMemberIterator itBegin =
						edgeList->value.MemberBegin(); itBegin != it;
						++itBegin) {
					InputUtils::impl::HDD::VA::addEdge(itBegin, graph);
				}
			}
		}
		fclose(dataFile);
		INFO(logger, LogBundleKey::IOU_END_OF_READ, filename,
				LogStringUtils::graphDescription(graph, "\t").c_str());
	}
	return graph;
}

GraphIF * InputUtils::impl::HDD::VA::createGraph(rapidjson::Value & vertexList,
		rapidjson::SizeType const numberOfEdges)
				throw (IOExceptions::InvalidProblemRead) {
	GraphIF* graph = new GraphImpl { vertexList.MemberCount(), numberOfEdges,
			GraphConstructMode::RESERVE_SPACE_ONLY };
	rapidjson::Value::ConstMemberIterator itEnd = vertexList.MemberEnd();
	for (rapidjson::Value::ConstMemberIterator itBegin =
			vertexList.MemberBegin(); itBegin != itEnd; ++itBegin) {
		graph->addVertex(
				new VertexImpl { (VertexIdx) std::atoll(
						itBegin->name.GetString()) });
	}
	return graph;
}

void InputUtils::impl::HDD::VA::addEdge(
		rapidjson::Value::ConstMemberIterator& edge, GraphIF * const graph)
				throw (IOExceptions::InvalidArcRead) {
	const rapidjson::Value& endValue = edge->value.MemberEnd()->value;
	const rapidjson::Value& vertexU = edge->value.FindMember(
			IOUtils::impl::VA::EDGE_VERTEX_A_KEY)->value;
	const rapidjson::Value& vertexV = edge->value.FindMember(
			IOUtils::impl::VA::EDGE_VERTEX_B_KEY)->value;
	const rapidjson::Value& edgeCost = edge->value.FindMember(
			IOUtils::impl::VA::EDGE_COST_KEY)->value;
	if (vertexU == endValue || vertexV == endValue || edgeCost == endValue) {
		throw IOExceptions::InvalidArcRead();
	} else {
		INFO(logger, LogBundleKey::IOU_ARC_DEF_READ,
				(VertexIdx ) vertexU.GetDouble(),
				(VertexIdx ) vertexV.GetDouble(),
				(EdgeCost ) edgeCost.GetUint());
		graph->addEdge((VertexIdx) vertexU.GetDouble(),
				(VertexIdx) vertexV.GetDouble(),
				(EdgeCost) edgeCost.GetDouble());
	}
}

GraphIF * InputUtils::impl::HDD::GR::readGraph(char const * const filename)
		throw (IOExceptions::FileNotFountException) {
	GraphIF * graph { };
	FILE * dataFile = std::fopen(filename, "r");
	if (dataFile == NULL) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, filename);
		throw IOExceptions::FileNotFountException(filename);
	} else {
		TRACE(logger, LogBundleKey::IOU_START_READ_FILE_DATA, filename);
		while (!feof(dataFile)) {
			switch (fgetc(dataFile)) {
			case IOUtils::impl::GR::COMMENT_LINE_NUMERIC:
				INFO_NOARG(logger,
						LogBundleKey::IOU_IGNORING_COMMENT_LINE_WHILE_READING)
				;
				if (fscanf(dataFile, IOUtils::impl::GR::COMMENT_LINE_PATTERN)
						!= IOUtils::impl::GR::COMMENT_LINE_PATTERN_ARGS) {
					WARN_NOARG(logger,
							LogBundleKey::IOU_IGNORING_UNRECOGNISED_LINE_WHILE_READING);
				}
				break;
			case IOUtils::impl::GR::PROBLEM_DEF_LINE_NUMERIC:
				graph = InputUtils::impl::HDD::GR::createGraph(dataFile);
				break;
			case IOUtils::impl::GR::ARC_DEF_LINE_NUMERIC:
				InputUtils::impl::HDD::GR::addEdge(dataFile, graph);
				break;
			}
		}
		INFO(logger, LogBundleKey::IOU_END_OF_READ, filename,
				LogStringUtils::graphDescription(graph, "\t").c_str());
		fclose(dataFile);
	}
	return graph;
}

GraphIF * InputUtils::impl::HDD::GR::createGraph(FILE * const dataFile)
		throw (IOExceptions::InvalidProblemRead) {
	VertexCount vCount { };
	EdgeCount eCount { };
	if (fscanf(dataFile, IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN.get(),
			&vCount, &eCount)
			!= IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_PROBLEM_LINE_READ);
		throw IOExceptions::InvalidProblemRead();
	}
	INFO(logger, LogBundleKey::IOU_MST_PROBLEM_READ, vCount, eCount);
	return new GraphImpl { vCount, eCount,
			GraphConstructMode::AUTO_CONSTRUCT_VERTEX };
}

void InputUtils::impl::HDD::GR::addEdge(FILE * const dataFile,
		GraphIF * const graph) throw (IOExceptions::InvalidArcRead) {
	VertexIdx vertexU { };
	VertexIdx vertexV { };
	EdgeCost eCost { };
	if (fscanf(dataFile, IOUtils::impl::GR::ARC_DEF_LINE_PATTERN.get(),
			&vertexU, &vertexV, &eCost)
			!= IOUtils::impl::GR::ARC_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_ARC_LINE_READ);
		throw IOExceptions::InvalidArcRead();
	}
	INFO(logger, LogBundleKey::IOU_ARC_DEF_READ, vertexU, vertexV, eCost);
	graph->addEdge(vertexU, vertexV, eCost);
}

void OutputUtils::exportGraph(GraphIF* const graph, char const * exportPath,
		OutputFormat const outputFormat, GraphVizEngine const layoutEngine,
		GraphVizUtils::GraphDimmention graphMaxWidth,
		GraphVizUtils::GraphDimmention graphMaxHeight)
				throw (IOExceptions::InvalidProblemWrite,
				IOExceptions::InvalidArcWrite) {
	switch (outputFormat) {
	case OutputFormat::GR:
		//TODO
		break;
	case OutputFormat::VA:
		OutputUtils::impl::VA::exportGraph(graph, exportPath, layoutEngine,
				graphMaxWidth, graphMaxHeight);
		break;
	case OutputFormat::DOT:
		// TODO
		break;
	default:
		break;
	}
}

void OutputUtils::exportGraph(GraphIF* const graph, char const * exportPath,
		OutputFormat const outputFormat)
				throw (IOExceptions::InvalidProblemWrite,
				IOExceptions::InvalidArcWrite) {
	switch (outputFormat) {
	case OutputFormat::GR:
		OutputUtils::impl::GR::exportGraph(graph, exportPath);
		break;
	case OutputFormat::VA:
		OutputUtils::impl::VA::exportGraph(graph, exportPath);
		break;
	case OutputFormat::DOT:
		OutputUtils::impl::DOT::exportGraph(graph, exportPath);
		break;
	default:
		break;
	}
}

void OutputUtils::impl::GR::exportGraph(GraphIF* const graph,
		char const * exportPath) throw (IOExceptions::InvalidProblemWrite,
				IOExceptions::InvalidArcWrite) {
	std::ofstream exportFile { };

	char buffer[IOUtils::impl::MAX_CHARS_IN_LINE] { };

	VertexCount vCount { };
	EdgeCount eCount { };
	EdgeIF * edge { };

	exportFile.open(exportPath);
	if (!exportFile.is_open()) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, exportPath);
	} else {
		TRACE(logger, LogBundleKey::IOU_START_WRITE_FILE_DATA, exportPath);
		exportFile << IOUtils::impl::GR::COMMENT_LINE << " "
				<< "9th DIMACS Implementation Challenge: Minimum Spanning Tree"
				<< std::endl;
		exportFile << IOUtils::impl::GR::COMMENT_LINE << " "
				<< "http://www.dis.uniroma1.it/~challenge9" << std::endl;
		exportFile << IOUtils::impl::GR::COMMENT_LINE << " " << exportPath
				<< std::endl;
		exportFile << IOUtils::impl::GR::COMMENT_LINE << std::endl;

		vCount = graph->getNumberOfVertices();
		eCount = graph->getNumberOfEdges();
		if (sprintf(buffer, IOUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN.get(),
				vCount, eCount) < 0) {
			FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_PROBLEM_LINE_WRITE);
			throw IOExceptions::InvalidProblemWrite();
		}
		exportFile << IOUtils::impl::GR::PROBLEM_DEF_LINE << buffer
				<< std::endl;

		INFO(logger, LogBundleKey::IOU_MST_PROBLEM_WRITE, vCount, eCount,
				exportPath);

		exportFile << IOUtils::impl::GR::COMMENT_LINE << " "
				<< "graph contains " << vCount << " nodes and " << eCount
				<< " arcs" << std::endl;
		exportFile << IOUtils::impl::GR::COMMENT_LINE << std::endl;

		graph->beginEdge();
		while (graph->hasNextEdge()) {
			edge = graph->nextEdge();
			if (sprintf(buffer, IOUtils::impl::GR::ARC_DEF_LINE_PATTERN.get(),
					edge->getSourceVertex()->getVertexIdx(),
					edge->getTargetVertex()->getVertexIdx(),
					edge->getEdgeCost()) < 0) {
				FATAL_NOARG(logger, LogBundleKey::IOU_INVALID_ARC_LINE_WRITE);
				throw IOExceptions::InvalidArcRead();
			}
			exportFile << IOUtils::impl::GR::ARC_DEF_LINE << buffer
					<< std::endl;

			INFO(logger, LogBundleKey::IOU_ARC_DEF_WRITE,
					LogStringUtils::edgeVisualization(edge, "\t").c_str());
		}
		exportFile.close();
		INFO(logger, LogBundleKey::IOU_END_OF_WRITE, exportPath,
				LogStringUtils::graphDescription(graph, "\t").c_str());
	}
}

void OutputUtils::impl::VA::exportGraph(GraphIF* const graph,
		char const * exportPath, GraphVizEngine const layoutEngine,
		GraphVizUtils::GraphDimmention graphMaxWidth,
		GraphVizUtils::GraphDimmention graphMaxHeight) {
	FILE* exportFile = fopen(exportPath, "w");

	char buffer[IOUtils::impl::MAX_CHARS_IN_LINE] { };

	rapidjson::Document jsonDoc;
	rapidjson::Document vertexJsonDoc;
	rapidjson::Document edgeJsonDoc;

	rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

	EdgeIF* edge { };
	EdgeCount edgeCounter { 0 };
	VertexIF* vertex { };

	if (exportFile == nullptr) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, exportPath);
	} else {
		rapidjson::FileWriteStream os(exportFile, buffer, sizeof(buffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);

		jsonDoc.SetObject();

		TRACE(logger, LogBundleKey::IOU_START_WRITE_FILE_DATA, exportPath);

		jsonDoc.AddMember("vl",
				OutputUtils::impl::VA::getVertexSetJson(allocator, graph,
						GraphVizUtils::getVerticesCoordinates(graph,
								layoutEngine, graphMaxWidth, graphMaxHeight)),
				allocator);

		jsonDoc.AddMember("el",
				OutputUtils::impl::VA::getEdgeSetJson(allocator, graph),
				allocator);

		INFO(logger, LogBundleKey::IOU_END_OF_WRITE, exportPath,
				LogStringUtils::graphDescription(graph, "\t").c_str());

		jsonDoc.Accept(writer);
		fclose(exportFile);
	}
}

rapidjson::Document OutputUtils::impl::VA::getVertexSetJson(
		rapidjson::Document::AllocatorType& allocator, GraphIF * const graph,
		GraphVizUtils::VerticesCoordinates verticesCoordinates) {
	rapidjson::Document vertexJsonDoc;
	VertexIF * vertex { };

	vertexJsonDoc.SetObject();

	graph->beginVertex();
	vertexJsonDoc.SetObject();
	while (graph->hasNextVertex()) {
		vertex = graph->nextVertex();
		rapidjson::Value key(std::to_string(vertex->getVertexIdx()).c_str(),
				allocator);
		vertexJsonDoc.AddMember(key,
				OutputUtils::impl::VA::getVertexJson(vertexJsonDoc, allocator,
						vertex, verticesCoordinates.at(vertex->getVertexIdx())),
				allocator);
		INFO(logger, LogBundleKey::IOU_VERTEX_DEF_WRITE,
				LogStringUtils::vertexVisualization(vertex, "\t").c_str());
	}
	return vertexJsonDoc;
}

rapidjson::Document OutputUtils::impl::VA::getVertexJson(
		rapidjson::Document& vertexJsonDoc,
		rapidjson::Document::AllocatorType& allocator, VertexIF * const vertex,
		GraphVizUtils::VertexCoordinates vertexCoordinates) {
	rapidjson::Document jsonDoc;
	rapidjson::Value text(std::to_string(vertex->getVertexIdx()).c_str(),
			allocator);
	jsonDoc.SetObject();
	jsonDoc.AddMember("cx", vertexCoordinates.first, allocator);
	jsonDoc.AddMember("cy", vertexCoordinates.second, allocator);
	jsonDoc.AddMember("text", text, allocator);
	jsonDoc.AddMember("state", "default", allocator);
	return jsonDoc;
}

void OutputUtils::impl::VA::exportGraph(GraphIF* const graph,
		char const * exportPath) {
	FILE* exportFile = fopen(exportPath, "w");

	char buffer[IOUtils::impl::MAX_CHARS_IN_LINE] { };

	rapidjson::Document jsonDoc;
	rapidjson::Document vertexJsonDoc;
	rapidjson::Document edgeJsonDoc;

	rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();

	EdgeIF* edge { };
	EdgeCount edgeCounter { 0 };
	VertexIF* vertex { };

	if (exportFile == nullptr) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, exportPath);
	} else {
		rapidjson::FileWriteStream os(exportFile, buffer, sizeof(buffer));
		rapidjson::Writer<rapidjson::FileWriteStream> writer(os);

		jsonDoc.SetObject();

		TRACE(logger, LogBundleKey::IOU_START_WRITE_FILE_DATA, exportPath);

		jsonDoc.AddMember("vl",
				OutputUtils::impl::VA::getVertexSetJson(allocator, graph),
				allocator);

		jsonDoc.AddMember("el",
				OutputUtils::impl::VA::getEdgeSetJson(allocator, graph),
				allocator);

		INFO(logger, LogBundleKey::IOU_END_OF_WRITE, exportPath,
				LogStringUtils::graphDescription(graph, "\t").c_str());

		jsonDoc.Accept(writer);
		fclose(exportFile);
	}
}

rapidjson::Document OutputUtils::impl::VA::getVertexSetJson(
		rapidjson::Document::AllocatorType& allocator, GraphIF * const graph) {
	rapidjson::Document vertexJsonDoc;
	VertexIF * vertex { };

	vertexJsonDoc.SetObject();

	graph->beginVertex();
	vertexJsonDoc.SetObject();
	while (graph->hasNextVertex()) {
		vertex = graph->nextVertex();
		rapidjson::Value key(std::to_string(vertex->getVertexIdx()).c_str(),
				allocator);
		vertexJsonDoc.AddMember(key,
				OutputUtils::impl::VA::getVertexJson(vertexJsonDoc, allocator,
						vertex), allocator);
		INFO(logger, LogBundleKey::IOU_VERTEX_DEF_WRITE,
				LogStringUtils::vertexVisualization(vertex, "\t").c_str());
	}
	return vertexJsonDoc;
}

rapidjson::Document OutputUtils::impl::VA::getEdgeSetJson(
		rapidjson::Document::AllocatorType& allocator, GraphIF * const graph) {
	rapidjson::Document edgeJsonDoc;
	EdgeIF * edge { };
	EdgeCount edgeCounter { 0 };

	edgeJsonDoc.SetObject();

	graph->beginEdge();
	edgeJsonDoc.SetObject();
	while (graph->hasNextEdge()) {
		edge = graph->nextEdge();
		rapidjson::Value key(std::to_string(edgeCounter++).c_str(), allocator);
		edgeJsonDoc.AddMember(key,
				OutputUtils::impl::VA::getEdgeJson(edgeJsonDoc, allocator,
						edge), allocator);
		INFO(logger, LogBundleKey::IOU_ARC_DEF_WRITE,
				LogStringUtils::edgeVisualization(edge, "\t").c_str());
	}
	return edgeJsonDoc;
}

rapidjson::Document OutputUtils::impl::VA::getVertexJson(
		rapidjson::Document& vertexJsonDoc,
		rapidjson::Document::AllocatorType& allocator,
		VertexIF * const vertex) {
	rapidjson::Document jsonDoc;
	rapidjson::Value text(std::to_string(vertex->getVertexIdx()).c_str(),
			allocator);
	jsonDoc.SetObject();
	jsonDoc.AddMember("cx", 0, allocator);
	jsonDoc.AddMember("cy", 0, allocator);
	jsonDoc.AddMember("text", text, allocator);
	jsonDoc.AddMember("state", "default", allocator);
	return jsonDoc;
}

rapidjson::Document OutputUtils::impl::VA::getEdgeJson(
		rapidjson::Document& vertexJsonDoc,
		rapidjson::Document::AllocatorType& allocator, EdgeIF * const edge) {
	rapidjson::Document jsonDoc;
	jsonDoc.SetObject();
	jsonDoc.AddMember("vertexA", edge->getSourceVertex()->getVertexIdx(),
			allocator);
	jsonDoc.AddMember("vertexB", edge->getTargetVertex()->getVertexIdx(),
			allocator);
	jsonDoc.AddMember("type", 0, allocator);
	jsonDoc.AddMember("weight", edge->getEdgeCost(), allocator);
	jsonDoc.AddMember("state", "default", allocator);
	jsonDoc.AddMember("displayWeight", true, allocator);
	jsonDoc.AddMember("animateHighlighed", false, allocator);
	return jsonDoc;
}

void OutputUtils::impl::DOT::exportGraph(GraphIF* const graph,
		char const * exportPath) {
	std::ofstream exportFile { };
	exportFile.open(exportPath);
	if (!exportFile.is_open()) {
		ERROR(logger, LogBundleKey::IOU_CANNOT_OPEN_FILE, exportPath);
	} else {
		TRACE(logger, LogBundleKey::IOU_START_WRITE_FILE_DATA, exportPath);
		OutputUtils::impl::DOT::exportGraphToStream(graph, exportFile);
		exportFile.close();
		INFO(logger, LogBundleKey::IOU_END_OF_WRITE, exportPath,
				LogStringUtils::graphDescription(graph, "\t").c_str());
	}
}

std::string OutputUtils::impl::DOT::exportGraph(GraphIF* const graph) {
	std::ostringstream oss { };

	TRACE_NOARG(logger, LogBundleKey::IOU_START_STREAM_WRITE_DATA);
	OutputUtils::impl::DOT::exportGraphToStream(graph, oss);
	TRACE_NOARG(logger, LogBundleKey::IOU_END_STREAM_WRITE);

	return oss.str();
}

void OutputUtils::impl::DOT::exportGraphToStream(GraphIF* const graph,
		std::ostream& stream) {
	VertexIF * vertex { };
	EdgeIF * edge { };
	EdgeCost edgeCost { };
	EdgeCost totalCost { graph->getTotalEdgeCost() };

	stream << IOUtils::impl::DOT::GRAPH_DEF << " G {" << std::endl;

	stream << "\t" << IOUtils::impl::DOT::DIR << "\t=\t" << "LR"
			<< IOUtils::impl::DOT::ENDLN << std::endl;

	graph->beginVertex();
	while (graph->hasNextVertex()) {
		vertex = graph->nextVertex();

		stream << "\t" << vertex->getVertexIdx() << "\t["
				<< IOUtils::impl::DOT::LABEL << "=\"" << vertex->getVertexIdx()
				<< "\"]" << IOUtils::impl::DOT::ENDLN << std::endl;

		INFO(logger, LogBundleKey::IOU_VERTEX_DEF_WRITE,
				LogStringUtils::vertexVisualization(vertex, "\t").c_str());
	}

	graph->beginEdge();
	while (graph->hasNextEdge()) {
		edge = graph->nextEdge();
		edgeCost = edge->getEdgeCost();

		stream << "\t" << edge->getSourceVertex()->getVertexIdx() << "\t"
				<< IOUtils::impl::DOT::EDGE_UNDIR << "\t"
				<< edge->getTargetVertex()->getVertexIdx() << "\t["
				<< IOUtils::impl::DOT::LABEL << "=\"" << edgeCost << "\",\t"
				<< IOUtils::impl::DOT::WEIGHT << "="
				<< 1 - (double) edgeCost / totalCost << ",\t"
				<< IOUtils::impl::DOT::LEN << "=" << edgeCost << "]"
				<< IOUtils::impl::DOT::ENDLN << std::endl;

		INFO(logger, LogBundleKey::IOU_ARC_DEF_WRITE,
				LogStringUtils::edgeVisualization(edge, "\t").c_str());
	}

	stream << "}" << std::flush;
}
