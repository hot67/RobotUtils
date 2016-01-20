
#ifndef SRC_HOTLOG_H_
#define SRC_HOTLOG_H_

#include <fstream>
#include <string>
#include <map>

#include "HotLogChannel.h"
class HotLogChannel;

class HotLog {
public:
	/******************************
	 * 	Structure
	 ******************************/
	HotLog(HotLog* parent, std::string name);
	virtual ~HotLog() {};

	/**
	 * 	Set Child
	 */
	void SetChild(HotLog* child);

	/******************************
	 * 	Getters
	 ******************************/
	virtual std::string GetName() const;
	virtual std::string GetFullName() const;

	/******************************
	 * 	Define Log Schema
	 ******************************/
	void DefineBoolLog(std::string key);
	void DefineStateLog(std::string key);
	void DefineDoubleLog(std::string key, float min, float max, float accuracy);

	/******************************
	 * 	Set Log Value
	 ******************************/
	void Log(std::string key, bool value);
	void Log(std::string key, int value);
	void Log(std::string key, double value);

	/******************************
	 * 	Write Log
	 ******************************/
	void WriteData(std::ofstream* dataFile);
	void WriteMeta(std::ofstream* metaFile);

	/******************************
	 * 	Log Period
	 ******************************/
	virtual void LogPeriod () {};

	/******************************
	 * 	Log
	 * 		Run log period
	 ******************************/
	void Log();

	/******************************
	 * 	Number Channels
	 ******************************/
	unsigned char NumberChannels (unsigned char index);

private:
	HotLog *m_parent;
	std::string m_name;
	std::map<std::string, HotLog*> m_children;
	std::map<std::string, HotLogChannel*> m_channels;
};

#endif /* SRC_HOTLOG_H_ */
