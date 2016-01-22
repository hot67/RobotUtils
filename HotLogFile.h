/*
 * HotLogFile.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#ifndef SRC_ROBOTUTILS_HOTLOGFILE_H_
#define SRC_ROBOTUTILS_HOTLOGFILE_H_

/**
 * 	Configure HOTLOG_CACHE_SIZE
 */
#ifndef HOTLOG_CACHE_SIZE
	#define HOTLOG_CACHE_SIZE 1024
#endif

#include <string>
#include <fstream>
#include "WPILib.h"

class HotLogFile {
public:
	HotLogFile(std::string dir);

	/**
	 *	Set Meta Declare Line
	 */
	void SetDeclareLine(std::string line);

	/**
	 * 	Set Data
	 */
	void SetData(unsigned char id, char* address, int size);

	/**
	 * 	Cache Byte
	 */
	void CacheByte(unsigned char byte);

	/**
	 * 	Start
	 */
	void Start();

	/**
	 * 	Write On File
	 */
	void WriteOnFile();

private:
	unsigned char m_cache[HOTLOG_CACHE_SIZE];
	int m_cacheIndex = 0;
	std::string m_dir;
	std::ofstream *m_data, *m_meta;
};

#endif /* SRC_ROBOTUTILS_HOTLOGFILE_H_ */
