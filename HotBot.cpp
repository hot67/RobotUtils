#include "HotBot.h"

/******************************
 * 	Constructor
 ******************************/
HotBot::HotBot(std::string name, std::string dirPath) : HotLog(this, name) {
	m_name = name;
	m_timer = new Timer();

	/**
	 *	Log Files
	 */
	std::string path = dirPath + m_name + "-" + std::to_string((int)m_timer->GetFPGATimestamp());

	m_meta->open(path + ".meta", std::ios::out);
	m_data->open(path + ".data", std::ios::out|std::ios::binary);

	/**
	 * 	Start timer
	 */
	m_timer->Start();
}
HotBot::~HotBot() {}

/******************************
 * 	Get Name Infomation
 ******************************/
std::string HotBot::GetFullName() const {
	return m_name;
}

/******************************
 * 	Set subsystem
 * 		This function should only be called from subsystem constructor
 ******************************/
void HotBot::SetSubsystem(HotSubsystem* subsystem) {
	m_subsystems[subsystem->GetName()] = subsystem;
}

/******************************
 * 	Set Driver/Operator
 ******************************/
void HotBot::SetDriver(unsigned int port) {
	m_driver = new HotJoystick(this, "Driver", port);
}

void HotBot::SetOperator(unsigned int port) {
	m_operator = new HotJoystick(this, "Operator", port);
}

/******************************
 * 	Getter for Joysticks
 ******************************/
HotJoystick* HotBot::GetDriver() const {
	return m_driver;
}

HotJoystick* HotBot::GetOperator() const {
	return m_operator;
}

/******************************
 * 	Start Robot Routines
 ******************************/
void HotBot::RobotInit() {
	BeforeRobot();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeRobot();
	}
}

void HotBot::DisabledInit() {
	BeforeDisabled();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeDisabled();
	}
}

void HotBot::AutonomousInit() {
	BeforeAuton();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeAuton();
	}
}

void HotBot::TeleopInit() {
	BeforeTeleop();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeTeleop();
	}
}

void HotBot::TestInit() {
	BeforeTeleop();

	for (std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->BeforeTest();
	}
}

void HotBot::DisabledPeriodic() {
	DisabledPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->DisabledPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();

	Timeframe();
}

void HotBot::AutonomousPeriodic() {
	AutonPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->AutonPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();

	Timeframe();
}

void HotBot::TeleopPeriodic() {
	TeleopPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TeleopPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();

	Timeframe();
}

void HotBot::TestPeriodic() {
	TestPeriod();
	GeneralPeriod();

	for(std::map<std::string, HotSubsystem*>::iterator it = m_subsystems.begin(); it != m_subsystems.end(); it++) {
		it->second->TestPeriod();
		it->second->GeneralPeriod();
	}

	//	Log
	Log();

	Timeframe();
}

/******************************
 * 	To be Defined
 ******************************/
void HotBot::BeforeRobot() {}
void HotBot::BeforeDisabled() {}
void HotBot::BeforeAuton() {}
void HotBot::BeforeTeleop() {}
void HotBot::BeforeTest() {}

void HotBot::DisabledPeriod() {}
void HotBot::AutonPeriod() {}
void HotBot::TeleopPeriod() {}
void HotBot::TestPeriod() {}
void HotBot::GeneralPeriod() {}

/******************************
 * 	Start
 ******************************/
void HotBot::Start() {
	/**
	 * 	Start Log System
	 */
	StartLog();
}

/******************************
 * 	Start Log System
 ******************************/
void HotBot::StartLog() {
	/**
	 * 	Numbering All Channels
	 * 		Index start with ID
	 */
	NumberChannels(1);
}

/******************************
 * 	Time frame
 ******************************/
void HotBot::Timeframe() {
	int stamp = (int)(m_timer->Get() * 1000 + 0.5);

	/**
	 * 	Write Timestamp
	 */
	unsigned char id = 0;
	m_data->write((char*) &id, sizeof(char));
	m_data->write((char*) &stamp, sizeof(int));

	/**
	 *	Write Channels
	 */
	WriteData(m_data);
}
