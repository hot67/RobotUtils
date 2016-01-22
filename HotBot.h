#ifndef SRC_HOTBOT_H_
#define SRC_HOTBOT_H_

#include "WPILib.h"
#include "HotSubsystem.h"
#include "HotJoystick.h"

class HotSubsystem;

class HotBot : public IterativeRobot {
public:
	/******************************
	 * 	Structure
	 * 		In constructor,
	 * 		we do,
	 * 		1.	create all log files
	 *		In each robot,
	 *		1.	declare all non-subsystem components
	 *		2.	declare all log schema
	 *		3.	include all subsystems
	 *		4.	call start log to prepare logging
	 ******************************/
	HotBot(std::string dirPath = "/log/");
	virtual ~HotBot();

	/**
	 * 	Set Subsystem
	 * 		This function should be called only from Subsystem constructor
	 */
	void SetSubsystem(HotSubsystem* subsystem);

	/**
	 *	Getters
	 */
	HotLogSystem* GetLogSystem() const;

	/******************************
	 * 	Set Joysticks
	 ******************************/
	void SetDriver(unsigned int port);
	void SetOperator(unsigned int port);

	HotJoystick* GetDriver() const;
	HotJoystick* GetOperator() const;

	/******************************
	 * 	Loop Structure
	 ******************************/
	void RobotInit();
	void DisabledInit();
	void AutonomousInit();
	void TeleopInit();
	void TestInit();

	void DisabledPeriodic();
	void AutonomousPeriodic();
	void TeleopPeriodic();
	void TestPeriodic();

	/******************************
	 * 	Functions to be defined
	 * 		These function should be overwritten
	 * 		to define what robot should do in each period/initialization
	 ******************************/
	virtual void BeforeRobot();
	virtual void BeforeDisabled();
	virtual void BeforeAuton();
	virtual void BeforeTeleop();
	virtual void BeforeTest();

	virtual void DisabledPeriod();
	virtual void AutonPeriod();
	virtual void TeleopPeriod();
	virtual void TestPeriod();

	virtual void GeneralPeriod();

	/******************************
	 * 	For Log System
	 ******************************/
	/**
	 * 	Timeframe
	 * 		Define timeframe of log system
	 * 		Save timestamp and write it in data file
	 * 		Iterate through all channels and write their data if it is updated
	 */
	void Timeframe();

private:
	std::map<std::string, HotSubsystem*> m_subsystems;

	HotLogSystem* m_logSystem;

	HotLogger* m_logger;

	HotJoystick *m_driver, *m_operator;
};

#endif /* SRC_HOTBOT_H_ */
