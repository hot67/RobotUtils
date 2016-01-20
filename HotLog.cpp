/*
 * HotLog.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#include "HotLog.h"

HotLog::HotLog(HotLog* parent, std::string name) {
	m_parent = parent;
	m_name = name;
	parent->SetChild(this);
}

void HotLog::SetChild(HotLog* child) {
	m_children[child->GetName()] = child;
}

std::string HotLog::GetName() const {
	return m_name;
}

std::string HotLog::GetFullName() const {
	return m_parent->GetFullName() + "." + m_name;
}

void HotLog::DefineBoolLog(std::string key) {
	m_channels[key] = new HotLogChannel(this, key, HotLogChannel::kTypeBoolean);
}

void HotLog::DefineDoubleLog(std::string key, float min, float max, float accuracy) {
	m_channels[key] = new HotLogChannel(this, key, HotLogChannel::kTypeDouble, min, max, accuracy);
}

void HotLog::DefineStateLog(std::string key) {
	m_channels[key] = new HotLogChannel(this, key, HotLogChannel::kTypeState);
}

void HotLog::Log(std::string key, bool value) {
	m_channels[key]->Set(value);
}

void HotLog::Log(std::string key, double value) {
	m_channels[key]->Set(value);
}

void HotLog::Log(std::string key, int value) {
	m_channels[key]->Set(value);
}

void HotLog::WriteData(std::ofstream* dataFile) {
	/**
	 * 	Write Channels
	 */
	for (std::map<std::string, HotLogChannel*>::iterator it = m_channels.begin(); it != m_channels.end(); it++) {
		it->second->WriteData(dataFile);
	}

	/**
	 * 	Write Children
	 */
	for (std::map<std::string, HotLog*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		it->second->WriteData(dataFile);
	}
}

void HotLog::WriteMeta(std::ofstream* metaFile) {
	/**
	 * 	Write Channels
	 */
	for (std::map<std::string, HotLogChannel*>::iterator it = m_channels.begin(); it != m_channels.end(); it++) {
		it->second->WriteMeta(metaFile);
	}

	/**
	 * 	Write Children
	 */
	for (std::map<std::string, HotLog*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		it->second->WriteMeta(metaFile);
	}
}

void HotLog::Log() {
	LogPeriod();

	for (std::map<std::string, HotLog*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		it->second->Log();
	}
}

unsigned char HotLog::NumberChannels(unsigned char index) {
	/**
	 * 	Number All Channels
	 */
	for (std::map<std::string, HotLogChannel*>::iterator it = m_channels.begin(); it != m_channels.end(); it++) {
		it->second->SetID(index++);
	}

	/**
	 * 	Number all sub loggers
	 */
	for (std::map<std::string, HotLog*>::iterator it = m_children.begin(); it != m_children.end(); it++) {
		index = it->second->NumberChannels(index);
	}

	return index;
}
