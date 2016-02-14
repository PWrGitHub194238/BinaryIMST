/*
 * InputUtils.cpp
 *
 *  Created on: 2 sty 2016
 *      Author: tomasz
 */

#include "../../include/utils/InputUtils.hpp"

#include <boost/interprocess/detail/os_file_functions.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/streams/bufferstream.hpp>
#include <log4cxx/helpers/messagebuffer.h>
#include <log4cxx/logger.h>
#include <rapidjson/filereadstream.h>
#include <cstddef>
#include <cstdlib>

#include "../../include/enums/GraphConstructMode.hpp"
#include "../../include/exp/InputExceptions.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/GraphInclude.hpp"
#include "../../include/structures/VertexInclude.hpp"

class EdgeSetIF;
class VertexSetIF;

static const log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("InputUtils"));

GraphIF * InputUtils::readGraph(char const * filename, InputFormat inputFormat,
		InputMode inputMode) {
	switch (inputMode) {
	case InputMode::RAM:
		return InputUtils::impl::RAM::readGraph(filename, inputFormat);
	default:
		return InputUtils::impl::HDD::readGraph(filename, inputFormat);
	}
	return nullptr;
}

GraphIF * InputUtils::impl::RAM::readGraph(char const * const filename,
		InputFormat inputFormat) {
	switch (inputFormat) {
	case InputFormat::VA:
		return InputUtils::impl::RAM::VA::readGraph(filename);
	default:
		return InputUtils::impl::RAM::GR::readGraph(filename);
	}
}

GraphIF * InputUtils::impl::RAM::VA::readGraph(char const * const filename) {
	GraphIF * graph { };
	return graph;
}

GraphIF * InputUtils::impl::RAM::GR::readGraph(char const * const filename) {
	GraphIF * graph { };

	std::size_t fileSize { };

	char buffer[InputUtils::impl::BUFFER_SIZE] { };

	boost::interprocess::file_mapping mappedFile(filename,
			boost::interprocess::read_only);

	boost::interprocess::mapped_region mappedRegionOfFile(mappedFile,
			boost::interprocess::read_only);

	fileSize = mappedRegionOfFile.get_size();

	boost::interprocess::bufferstream input_stream(
			static_cast<char*>(mappedRegionOfFile.get_address()), fileSize);

	while (!input_stream.eof()) {
		switch (input_stream.get()) {
		case InputUtils::impl::GR::COMMENT_LINE:
			INFO_NOARG(logger,
					LogBundleKey::IGNORING_COMMENT_LINE_WHILE_READING)
			;
			input_stream.ignore(InputUtils::impl::MAX_STREAM_SIZE, '\n');
			break;
		case InputUtils::impl::GR::PROBLEM_DEF_LINE:
			input_stream.getline(buffer, InputUtils::impl::MAX_CHARS_IN_LINE);
			graph = InputUtils::impl::RAM::GR::createGraph(buffer);
			break;
		case InputUtils::impl::GR::ARC_DEF_LINE:
			input_stream.getline(buffer, InputUtils::impl::MAX_CHARS_IN_LINE);
			InputUtils::impl::RAM::GR::addEdge(buffer, graph);
			break;
		default:
			WARN_NOARG(logger,
					LogBundleKey::IGNORING_UNRECOGNISED_LINE_WHILE_READING)
			;
			break;
		}
	}

	return graph;
}

GraphIF * InputUtils::impl::RAM::GR::createGraph(char * const buffer)
		throw (InputExceptions::InvalidProblemRead) {
	VertexCount vCount { };
	EdgeCount eCount { };
	if (sscanf(buffer, InputUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN.get(),
			&vCount, &eCount)
			!= InputUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::INVALID_PROBLEM_LINE_READ);
		throw InputExceptions::InvalidProblemRead();
	}
	INFO(logger, LogBundleKey::MST_PROBLEM_READ, vCount, eCount);
	return new GraphImpl { vCount, eCount,
			GraphConstructMode::AUTO_CONSTRUCT_VERTEX };
}

void InputUtils::impl::RAM::GR::addEdge(char * const buffer,
		GraphIF * const graph) throw (InputExceptions::InvalidArcRead) {
	VertexIdx vertexU { };
	VertexIdx vertexV { };
	EdgeCost eCost { };
	if (sscanf(buffer, InputUtils::impl::GR::ARC_DEF_LINE_PATTERN.get(),
			&vertexU, &vertexV, &eCost)
			!= InputUtils::impl::GR::ARC_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::INVALID_ARC_LINE_READ);
		throw InputExceptions::InvalidArcRead();
	}
	INFO(logger, LogBundleKey::ARC_DEF_READ, vertexU, vertexV, eCost);
	graph->addEdge(vertexU, vertexV, eCost);
}

GraphIF * InputUtils::impl::HDD::readGraph(char const * const filename,
		InputFormat inputFormat) {
	switch (inputFormat) {
	case InputFormat::VA:
		return InputUtils::impl::HDD::VA::readGraph(filename);
	default:
		return InputUtils::impl::HDD::GR::readGraph(filename);
	}
}

GraphIF * InputUtils::impl::HDD::VA::readGraph(char const * const filename) {
	GraphIF * graph { };
	FILE * dataFile = std::fopen(filename, "r");
	rapidjson::Document jsonDoc { };
	rapidjson::Value vertexList { };
	rapidjson::Value edgeList { };
	rapidjson::Value endValue { };
	rapidjson::Value::ConstMemberIterator it { };
	char readBuffer[InputUtils::impl::BUFFER_SIZE] { };
	if (dataFile == NULL) {
		ERROR(logger, LogBundleKey::CANNOT_OPEN_FILE, filename);
	} else {
		TRACE(logger, LogBundleKey::START_READ_FILE_DATA, filename);
		rapidjson::FileReadStream is(dataFile, readBuffer, sizeof(readBuffer));
		jsonDoc.ParseStream(is);
		endValue = jsonDoc.MemberEnd()->value;
		vertexList =
				jsonDoc.FindMember(InputUtils::impl::VA::VERTEX_LIST_KEY)->value;
		if (vertexList != endValue) {
			edgeList =
					jsonDoc.FindMember(InputUtils::impl::VA::EDGE_LIST_KEY)->value;
			if (edgeList != endValue) {
				graph = InputUtils::impl::HDD::VA::createGraph(vertexList,
						edgeList.MemberCount());
				it = edgeList.MemberEnd();
				for (rapidjson::Value::ConstMemberIterator itBegin =
						edgeList.MemberBegin(); itBegin != it; ++itBegin) {
					InputUtils::impl::HDD::VA::addEdge(itBegin, graph);
				}
			}
		}
	}
	return graph;
}

GraphIF * InputUtils::impl::HDD::VA::createGraph(rapidjson::Value & vertexList,
		rapidjson::SizeType const numberOfEdges)
				throw (InputExceptions::InvalidProblemRead) {
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
				throw (InputExceptions::InvalidArcRead) {

	const rapidjson::Value& endValue = edge->value.MemberEnd()->value;
	const rapidjson::Value& vertexU = edge->value.FindMember(
			InputUtils::impl::VA::EDGE_VERTEX_A_KEY)->value;
	const rapidjson::Value& vertexV = edge->value.FindMember(
			InputUtils::impl::VA::EDGE_VERTEX_B_KEY)->value;
	const rapidjson::Value& edgeCost = edge->value.FindMember(
			InputUtils::impl::VA::EDGE_COST_KEY)->value;
	if (vertexU == endValue || vertexV == endValue || edgeCost == endValue) {
		throw InputExceptions::InvalidArcRead();
	} else {
		INFO(logger, LogBundleKey::ARC_DEF_READ, (VertexIdx ) vertexU.GetUint(),
				(VertexIdx ) vertexV.GetUint(), (EdgeCost ) edgeCost.GetUint());
		graph->addEdge((VertexIdx) vertexU.GetUint(),
				(VertexIdx) vertexV.GetUint(), (EdgeCost) edgeCost.GetUint());
	}
}

GraphIF * InputUtils::impl::HDD::GR::readGraph(char const * const filename) {
	GraphIF * graph { };
	FILE * dataFile = std::fopen(filename, "r");
	if (dataFile == NULL) {
		ERROR(logger, LogBundleKey::CANNOT_OPEN_FILE, filename);
	} else {
		TRACE(logger, LogBundleKey::START_READ_FILE_DATA, filename);
		while (!feof(dataFile)) {
			switch (fgetc(dataFile)) {
			case InputUtils::impl::GR::COMMENT_LINE:
				INFO_NOARG(logger,
						LogBundleKey::IGNORING_COMMENT_LINE_WHILE_READING)
				;
				if (fscanf(dataFile, InputUtils::impl::GR::COMMENT_LINE_PATTERN)
						!= InputUtils::impl::GR::COMMENT_LINE_PATTERN_ARGS) {
					WARN_NOARG(logger,
							LogBundleKey::IGNORING_UNRECOGNISED_LINE_WHILE_READING);
				}
				break;
			case InputUtils::impl::GR::PROBLEM_DEF_LINE:
				graph = InputUtils::impl::HDD::GR::createGraph(dataFile);
				break;
			case InputUtils::impl::GR::ARC_DEF_LINE:
				InputUtils::impl::HDD::GR::addEdge(dataFile, graph);
				break;
			}
		}
		fclose(dataFile);
	}
	return graph;
}

GraphIF * InputUtils::impl::HDD::GR::createGraph(FILE * const dataFile)
		throw (InputExceptions::InvalidProblemRead) {
	VertexCount vCount { };
	EdgeCount eCount { };
	if (fscanf(dataFile, InputUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN.get(),
			&vCount, &eCount)
			!= InputUtils::impl::GR::PROBLEM_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::INVALID_PROBLEM_LINE_READ);
		throw InputExceptions::InvalidProblemRead();
	}
	INFO(logger, LogBundleKey::MST_PROBLEM_READ, vCount, eCount);
	return new GraphImpl { vCount, eCount,
			GraphConstructMode::AUTO_CONSTRUCT_VERTEX };
}

void InputUtils::impl::HDD::GR::addEdge(FILE * const dataFile,
		GraphIF * const graph) throw (InputExceptions::InvalidArcRead) {
	VertexIdx vertexU { };
	VertexIdx vertexV { };
	EdgeCost eCost { };
	if (fscanf(dataFile, InputUtils::impl::GR::ARC_DEF_LINE_PATTERN.get(),
			&vertexU, &vertexV, &eCost)
			!= InputUtils::impl::GR::ARC_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, LogBundleKey::INVALID_ARC_LINE_READ);
		throw InputExceptions::InvalidArcRead();
	}
	INFO(logger, LogBundleKey::ARC_DEF_READ, vertexU, vertexV, eCost);
	graph->addEdge(vertexU, vertexV, eCost);
}

