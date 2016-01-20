/*
 * HotLogChannel.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#include "HotLogChannel.h"

HotLogChannel::HotLogChannel(HotLog* log, std::string key, Type type, float min, float max, float accuracy) {
	m_key = key;
	m_type = type;
	m_log = log;
	m_min = min;
	m_max = max;
	m_accuracy = accuracy;
}

std::string HotLogChannel::GetKey() {
	return m_key;
}

std::string HotLogChannel::GetFullKey() {
	return m_log->GetFullName() + "." + GetKey();
}

void HotLogChannel::SetID(unsigned char id) {
	m_id = id;
}

void HotLogChannel::Set(bool value) {
	if (m_type == kTypeBoolean && value != b_value) {
		b_value = value;
		f_updated = true;
	}
}

void HotLogChannel::Set(double value) {
	if (m_type == kTypeDouble && abs(d_value - value) > m_accuracy) {
		d_value = value;
		f_updated = true;
	}
}

void HotLogChannel::Set(int value) {
	if (m_type == kTypeState && value != s_value) {
		s_value = (unsigned char) value;
		f_updated = true;
	}
}

void HotLogChannel::WriteData(std::ofstream* dataFile) {
	if (f_updated) {
		//	Write ID
		dataFile->write((char*) &m_id, sizeof(unsigned char));

		switch(m_type) {
		case kTypeState:
			dataFile->write((char*) &s_value, sizeof(unsigned char));
			break;

		case kTypeDouble:
			unsigned char d_byte;
			d_byte = (unsigned char)(255 * (d_value - m_min) / (m_max - m_min) + 0.5);
			dataFile->write((char*) &d_byte, sizeof(unsigned char));
			break;

		case kTypeBoolean:
			unsigned char b_byte = (b_value) ? 1 : 0;
			dataFile->write((char*) &b_byte, sizeof(unsigned char));
			break;
		}
	}

	f_updated = false;
}

void HotLogChannel::WriteMeta(std::ofstream* metaFile) {
	/**
	 * 	Type
	 */
	std::string s_type;
	switch(m_type) {
	case kTypeState:
		s_type = "state";
		break;
	case kTypeDouble:
		s_type = "double";
		break;
	case kTypeBoolean:
		s_type = "boolean";
		break;
	}

	/**
	 * 	Write Meta
	 */
	*metaFile << std::to_string(m_id) << " " << m_key << " " << s_type << "\n";
}
