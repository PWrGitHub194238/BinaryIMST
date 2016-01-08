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
#include <cstddef>
#include <cstdio>

#include "../../include/exp/InputExceptions.hpp"
#include "../../include/log/bundle/Bundle.hpp"
#include "../../include/log/utils/LogUtils.hpp"
#include "../../include/structures/GraphIF.hpp"
#include "../../include/structures/GraphInclude.hpp"

class EdgeSetIF;
class VertexSetIF;

static const log4cxx::LoggerPtr logger(
		log4cxx::Logger::getLogger("InputUtils"));

GraphIF * InputUtils::readGraph(char const * filename, InputMode inputMode) {
	switch (inputMode) {
	case InputMode::RAM:
		return InputUtils::Impl::readGraphWithFileMappping(filename);
	default:
		return InputUtils::Impl::readGraphWithoutFileMappping(filename);
	}
	return nullptr;
}

GraphIF * InputUtils::Impl::readGraphWithoutFileMappping(
		char const * const filename) {
	GraphIF * graph { };
	VertexSetIF * vertexSet { };
	EdgeSetIF * edgeSet { };

	return graph;
}

GraphIF * InputUtils::Impl::readGraphWithFileMappping(
		char const * const filename) {
	GraphIF * graph { };

	std::size_t fileSize { };

	char buffer[InputUtils::Impl::MAX_CHARS_IN_LINE] { };

	boost::interprocess::file_mapping mappedFile(filename,
			boost::interprocess::read_only);

	boost::interprocess::mapped_region mappedRegionOfFile(mappedFile,
			boost::interprocess::read_only);

	fileSize = mappedRegionOfFile.get_size();

	boost::interprocess::bufferstream input_stream(
			static_cast<char*>(mappedRegionOfFile.get_address()), fileSize);

	while (!input_stream.eof()) {
		switch (input_stream.get()) {
		case InputUtils::Impl::COMMENT_LINE:
			INFO_NOARG(logger, BundleKey::IGNORING_COMMENT_LINE_WHILE_READING)
			input_stream.ignore(InputUtils::Impl::MAX_STREAM_SIZE, '\n');
			break;
		case InputUtils::Impl::PROBLEM_DEF_LINE:
			input_stream.getline(buffer, InputUtils::Impl::MAX_CHARS_IN_LINE);
			graph = InputUtils::Impl::createGraphFromBuffer(buffer);
			break;
		case InputUtils::Impl::ARC_DEF_LINE:
			input_stream.getline(buffer, InputUtils::Impl::MAX_CHARS_IN_LINE);
			InputUtils::Impl::addEdgeFromBuffer(buffer, graph);
			break;
		default:
			WARN_NOARG(logger,
					BundleKey::IGNORING_UNRECOGNISED_LINE_WHILE_READING)
			break;
		}
	}

	return graph;
}

GraphIF * InputUtils::Impl::createGraphFromBuffer(char * const buffer)
		throw (InputExceptions::InvalidProblemRead) {
	VertexCount vCount { };
	EdgeCount eCount { };
	if (sscanf(buffer, InputUtils::Impl::PROBLEM_DEF_LINE_PATTERN, &vCount,
			&eCount) != InputUtils::Impl::PROBLEM_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, BundleKey::INVALID_PROBLEM_LINE_READ)
		throw InputExceptions::InvalidProblemRead();
	}
	return new GraphImpl { vCount, eCount };
}

void InputUtils::Impl::addEdgeFromBuffer(char * const buffer,
		GraphIF * const graph) throw (InputExceptions::InvalidArcRead) {
	VertexIdx vertexU { };
	VertexIdx vertexV { };
	EdgeCost eCost { };
	if (sscanf(buffer, InputUtils::Impl::ARC_DEF_LINE_PATTERN, &vertexU,
			&vertexV, &eCost) != InputUtils::Impl::ARC_DEF_LINE_PATTERN_ARGS) {
		FATAL_NOARG(logger, BundleKey::INVALID_ARC_LINE_READ)
		throw InputExceptions::InvalidArcRead();
	}
	graph->addEdge(vertexU, vertexV, eCost);
}
