/*
 * HotLogger.h
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#ifndef SRC_ROBOTUTILS_HOTLOGGER_H_
#define SRC_ROBOTUTILS_HOTLOGGER_H_

#include <map>
#include <string>
#include "HotLogSystem.h"

class HotLogSystem;

class HotLogger {
public:
	/**
	 * 	As Base Logger
	 */
	HotLogger(HotLogSystem* system, std::string name);
	virtual ~HotLogger();

	/**
	 * 	As Child Logger
	 */
	HotLogger(HotLogger* parent, std::string name);

	/**
	 * 	Getters
	 */
	std::string GetName();
	HotLogSystem* GetLogSystem();

	/**
	 * 	To Define Log Schema
	 */
	void DoubleSchema(std::string name, double min, double max, double acc);
	void BooleanSchema(std::string name);
	void StateSchema(std::string name);

	/**
	 * 	Write Log
	 */
	void WriteLog(std::string name, double value);
	void WriteLog(std::string name, bool value);
	void WriteLog(std::string name, int value);

	/**
	 * 	Logging period
	 */
	virtual void LogPeriod();

private:
	std::string m_name;
	HotLogSystem* m_system;
};

#endif /* SRC_ROBOTUTILS_HOTLOGGER_H_ */
