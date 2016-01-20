/*
 * HotBot.cpp
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#include "HotBot.h"

HotBot::HotBot(std::string name) : HotLog(this, name) {
	m_name = name;
}

void HotBot::SetSubsystem(HotSubsystem* subsystem) {
	m_subsystems[subsystem->GetName()] = subsystem;
}

void HotBot::SetDriver(unsigned int port) {
	m_driver = new HotJoystick(this, "Driver", port);
}

void HotBot::SetOperator(unsigned int port) {
	m_operator = new HotJoystick(this, "Operator", port);
}

HotJoystick* HotBot::GetDriver() {
	return m_driver;
}

HotJoystick* HotBot::GetOperator() {
	return m_operator;
}

void HotBot::RobotInit() {
	RobotInitialization();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->RobotInit();
	}
}

void HotBot::DisabledInit() {
	DisabledInitialization();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->DisabledInit();
	}
}

void HotBot::AutonomousInit() {
	AutonInitialization();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->AutonInit();
	}
}

void HotBot::TeleopInit() {
	TeleopInitialization();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TeleopInit();
	}
}

void HotBot::TestInit() {
	TeleopInitialization();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TestInit();
	}
}

void HotBot::DisabledPeriodic() {
	DisabledPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->DisabledPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();
}

void HotBot::AutonomousPeriodic() {
	AutonPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->AutonPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();
}

void HotBot::TeleopPeriodic() {
	TeleopPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TeleopPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();
}

void HotBot::TestPeriodic() {
	TestPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TestPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();
}
