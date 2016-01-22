
#include "HotLogChannel.h"

HotLogChannel::HotLogChannel(unsigned char id, std::string key, Type type, float min, float max, float accuracy) {
	m_id = id;
	m_key = key;
	m_type = type;
	m_min = min;
	m_max = max;
	m_accuracy = accuracy;
}

unsigned char HotLogChannel::GetID() const {
	return m_id;
}
std::string HotLogChannel::GetName() const {
	return m_key;
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

std::string HotLogChannel::DeclareLine() {
	std::ostringstream stream;

	/**
	 * 	Write ID
	 */
	stream << GetID() + " ";

	/**
	 * 	Write Name
	 */
	stream << GetName() + " ";

	/**
	 * 	Write Type
	 */
	switch(m_type) {
	case kTypeDouble:
		stream << "double " << m_min << " " << m_max << " " << m_accuracy;
		break;
	case kTypeBoolean:
		stream << "boolean";
		break;
	case kTypeState:
		stream << "state";
		break;
	}

	/**
	 * 	Line End
	 */
	stream << std::endl;

	return stream.str();
}

void HotLogChannel::WriteDate(HotLogFile* file) {
	if (!f_updated) {
		return;
	}

	switch (m_type) {
	case kTypeDouble:
		unsigned char d;
		d = (unsigned char)(255 * (d_value - m_min) / (m_max - m_min));
		file->SetData(GetID(), (char*) &d, sizeof(unsigned char));
		break;
	case kTypeBoolean:
		unsigned char b;
		b = (b_value) ? 1 : 0;
		file->SetData(GetID(), (char*) &b, sizeof(unsigned char));
		break;
	case kTypeState:
		unsigned char s = (unsigned char) s_value;
		file->SetData(GetID(), (char*) &s, sizeof(unsigned char));
		break;
	}
}
