
#include "HotSubsystem.h"

HotSubsystem::HotSubsystem(HotBot* bot, std::string name)
: HotLog(bot, name) {
	m_bot = bot;
	m_name = name;

	//	Set as subsystem
	m_bot->SetSubsystem(this);
}

HotSubsystem::~HotSubsystem() {}

/******************************
 * 	Getters
 ******************************/
std::string HotSubsystem::GetName() const {
	return m_name;
}

HotBot* HotSubsystem::GetBot() const {
	return m_bot;
}

HotJoystick* HotSubsystem::GetDriver() const {
	return GetBot()->GetDriver();
}

HotJoystick* HotSubsystem::GetOperator() const {
	return GetBot()->GetOperator();
}

/******************************
 * 	Functions to be defined
 ******************************/
void HotSubsystem::RobotInit() {}
void HotSubsystem::DisabledInit() {}
void HotSubsystem::AutonInit() {}
void HotSubsystem::TeleopInit() {}
void HotSubsystem::TestInit() {}
void HotSubsystem::DisabledPeriod() {}
void HotSubsystem::AutonPeriod() {}
void HotSubsystem::TeleopPeriod() {}
void HotSubsystem::TestPeriod() {}
void HotSubsystem::GeneralPeriod() {}
