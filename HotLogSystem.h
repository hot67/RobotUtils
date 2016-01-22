/*
 * HotLogSystem.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#ifndef SRC_ROBOTUTILS_HOTLOGSYSTEM_H_
#define SRC_ROBOTUTILS_HOTLOGSYSTEM_H_

#include <map>
#include <string>
#include "HotLogger.h"
#include "HotLogChannel.h"
#include "HotLogFile.h"

class HotLogger;
class HotLogChannel;

class HotLogSystem {
public:
	/**
	 * 	Constructor
	 */
	HotLogSystem(std::string dir);

	/**
	 * 	Set Logger
	 */
	void SetLogger(HotLogger* logger);

	/**
	 * 	Start Logging
	 * 		after this function is called, you may not set any more channels.
	 */
	void Start();

	/**
	 * 	Set Channel
	 */
	void SetDoubleChannel(std::string name, double min, double max, double acc);
	void SetBooleanChannel(std::string name);
	void SetStateChannel(std::string name);

	/**
	 * 	Write Log
	 */
	void WriteLog(std::string name, double value);
	void WriteLog(std::string name, bool value);
	void WriteLog(std::string name, int value);

	/**
	 * 	Run Log Period
	 */
	void LogPeriod();
private:
	/**
	 * 	Channel Id Index
	 * 		0 is saved for timestamp
	 */
	unsigned char m_index = 1;

	/**
	 * 	File
	 */
	HotLogFile* m_file;

	/**
	 * 	Loggers and channels
	 */
	std::map<std::string, HotLogger*> m_loggers;
	std::map<std::string, HotLogChannel*> m_channels;
};

#endif /* SRC_ROBOTUTILS_HOTLOGSYSTEM_H_ */
