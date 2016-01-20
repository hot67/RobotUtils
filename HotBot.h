/*
 * HotBot.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#ifndef SRC_HOTBOT_H_
#define SRC_HOTBOT_H_

#include "WPILib.h"
#include "HotSubsystem.h"
#include "HotLog.h"
#include "HotJoystick.h"

class HotSubsystem;

class HotBot : public IterativeRobot, public HotLog {
public:
	/******************************
	 * 	Structure
	 ******************************/
	HotBot(std::string name);

	/**
	 * 	Set Subsystem
	 * 		This function should be called only from Subsystem constructor
	 */
	void SetSubsystem(HotSubsystem* subsystem);

	/**
	 * 	Get Full Name
	 */
	std::string GetFullName () { return m_name; }

	/******************************
	 * 	Set Joysticks
	 ******************************/
	void SetDriver(unsigned int port);
	void SetOperator(unsigned int port);

	HotJoystick* GetDriver();
	HotJoystick* GetOperator();

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
	virtual void RobotInitialization() {}
	virtual void DisabledInitialization() {}
	virtual void AutonInitialization() {}
	virtual void TeleopInitialization() {}
	virtual void TestInitialization() {}

	virtual void DisabledPeriod() {}
	virtual void AutonPeriod() {}
	virtual void TeleopPeriod() {}
	virtual void TestPeriod() {}


private:
	std::string m_name;
	std::map<std::string, HotSubsystem*> m_subsystems;

	HotJoystick *m_driver, *m_operator;
};

#endif /* SRC_HOTBOT_H_ */
