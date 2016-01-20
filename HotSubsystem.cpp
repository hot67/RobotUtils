/*
 * HotSubsystem.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#include "HotSubsystem.h"

HotSubsystem::HotSubsystem(HotBot* bot, std::string name)
: HotLog(bot, name) {
	m_bot = bot;
	m_name = name;

	//	Set as subsystem
	m_bot->SetSubsystem(this);
}

/******************************
 * 	Getters
 ******************************/
std::string HotSubsystem::GetName() const {
	return m_name;
}

HotBot* HotSubsystem::GetBot() const {
	return m_bot;
}
