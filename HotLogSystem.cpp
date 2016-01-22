/*
 * HotLogSystem.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#include <RobotUtils/HotLogSystem.h>

HotLogSystem::HotLogSystem(std::string dir) {
	m_file = new HotLogFile(dir);
}

void HotLogSystem::SetLogger(HotLogger* logger) {
	m_loggers[logger->GetName()] = logger;
}

/**
 * 	Start Logging
 */
void HotLogSystem::Start() {
	m_file->Start();
}

/**
 * 	Define Log Schema
 */
void HotLogSystem::SetDoubleChannel(std::string name, double min, double max, double acc) {
	HotLogChannel* ch = m_channels[name] = new HotLogChannel(m_index++, name, HotLogChannel::kTypeDouble, min, max, acc);
	m_file->SetDeclareLine(ch->DeclareLine());
}

void HotLogSystem::SetBooleanChannel(std::string name) {
	HotLogChannel* ch = m_channels[name] = new HotLogChannel(m_index++, name, HotLogChannel::kTypeBoolean);
	m_file->SetDeclareLine(ch->DeclareLine());
}

void HotLogSystem::SetStateChannel(std::string name) {
	HotLogChannel* ch = m_channels[name] = new HotLogChannel(m_index++, name, HotLogChannel::kTypeState);
	m_file->SetDeclareLine(ch->DeclareLine());
}

/**
 * 	Write Log
 */
void HotLogSystem::WriteLog(std::string name, double value) {
	m_channels[name]->Set(value);
}

void HotLogSystem::WriteLog(std::string name, bool value) {
	m_channels[name]->Set(value);
}

void HotLogSystem::WriteLog(std::string name, int value) {
	m_channels[name]->Set(value);
}

/**
 * 	Run Log Period
 */
void HotLogSystem::LogPeriod() {
	for (std::map<std::string, HotLogger*>::iterator it = m_loggers.begin(); it != m_loggers.end(); it++) {
		it->second->LogPeriod();
	}

	/**
	 * 	Write Data to cache/file
	 */
	//	ToDo: Write Timestamp

	for (std::map<std::string, HotLogChannel*>::iterator it = m_channels.begin(); it != m_channels.end(); it++) {
		it->second->WriteDate(m_file);
	}
}
