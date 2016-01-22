/*
 * HotLogFile.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#include <RobotUtils/HotLogFile.h>

HotLogFile::HotLogFile(std::string dir) {
	m_dir = dir;
	m_meta = new std::ofstream();
	m_data = new std::ofstream();
	m_meta->open(dir + "meta.meta", std::ios::out);
}

void HotLogFile::SetDeclareLine(std::string line) {
	*m_meta << line;
}

void HotLogFile::SetData(unsigned char id, char* address, int size) {
	CacheByte(id);
	for (int i = 0; i < size; i++) {
		CacheByte(address[i]);
	}
}

void HotLogFile::CacheByte(unsigned char byte) {
	m_cache[m_cacheIndex++] = byte;

	if (m_cacheIndex == HOTLOG_CACHE_SIZE) {
		//	Open Meta File
		m_meta->open(m_dir + "data", std::ios::out|std::ios::binary);
		m_data->write((char*) m_cache, HOTLOG_CACHE_SIZE);
		m_meta->close();

		//	Reset Cache Index
		m_cacheIndex = 0;
	}
}
