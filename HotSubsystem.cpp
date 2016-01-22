
#include "HotSubsystem.h"

HotSubsystem::HotSubsystem(HotBot* bot, std::string name)
: HotLogger(bot->GetLogSystem(), name) {
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
 * 	To be Defined
 ******************************/
void HotSubsystem::BeforeRobot() {}
void HotSubsystem::BeforeDisabled() {}
void HotSubsystem::BeforeAuton() {}
void HotSubsystem::BeforeTeleop() {}
void HotSubsystem::BeforeTest() {}

void HotSubsystem::DisabledPeriod() {}
void HotSubsystem::AutonPeriod() {}
void HotSubsystem::TeleopPeriod() {}
void HotSubsystem::TestPeriod() {}
void HotSubsystem::GeneralPeriod() {}
