/*
 * HotLogger.cpp
 *
 *  Created on: Jan 22, 2016
 *      Author: Jin
 */

#include <RobotUtils/HotLogger.h>

HotLogger::HotLogger(HotLogSystem* system, std::string name) {
	m_name = name;
	m_system = system;

	m_system->SetLogger(this);
}

HotLogger::HotLogger(HotLogger* parent, std::string name) {
	m_name = parent->GetName() + "." + name;
	m_system = parent->GetLogSystem();
	m_system->SetLogger(this);
}

HotLogger::~HotLogger() {}


/**
 * 	Getters
 */
std::string HotLogger::GetName() { return m_name; }

HotLogSystem* HotLogger::GetLogSystem() { return m_system; }

/**
 * 	Define Log Schema
 */
void HotLogger::DoubleSchema(std::string name, double min, double max, double acc) {
	m_system->SetDoubleChannel(GetName() + "." + name, min, max, acc);
}
void HotLogger::BooleanSchema(std::string name) {
	m_system->SetBooleanChannel(GetName() + "." + name);
}
void HotLogger::StateSchema(std::string name) {
	m_system->SetStateChannel(GetName() + "." + name);
}

/**
 * 	Write Log
 */
void HotLogger::WriteLog(std::string name, double value) {
	m_system->WriteLog(GetName() + "." + name, value);
}
void HotLogger::WriteLog(std::string name, bool value) {
	m_system->WriteLog(GetName() + "." + name, value);
}
void HotLogger::WriteLog(std::string name, int value) {
	m_system->WriteLog(GetName() + "." + name, value);
}

/**
 * 	Log Period
 */
void HotLogger::LogPeriod() {}
