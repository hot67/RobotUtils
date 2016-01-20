/*
 * HotSubsystem.h
 *
 *  Created on: Jan 18, 2016
 *      Author: Jin
 */

#ifndef SRC_HOTSUBSYSTEM_H_
#define SRC_HOTSUBSYSTEM_H_

#include "HotBot.h"
#include "HotLog.h"
#include "HotJoystick.h"

class HotBot;

class HotSubsystem : public HotLog {
public:
	/******************************
	 * 	Constructor
	 * 		In this function, we connect subsystem and hot bot.
	 ******************************/
	HotSubsystem(HotBot* bot, std::string name);
	virtual ~HotSubsystem() {}

	/******************************
	 * 	Getter
	 ******************************/
	std::string GetName();
	HotBot* GetBot() { return m_bot; }

	/******************************
	 * 	Initialization
	 ******************************/
	virtual void RobotInit() {}
	virtual void DisabledInit() {}
	virtual void AutonInit() {}
	virtual void TeleopInit() {}
	virtual void TestInit() {}

	/******************************
	 *	Period
	 ******************************/
	virtual void DisabledPeriod() {}
	virtual void AutonPeriod() {}
	virtual void TeleopPeriod() {}
	virtual void TestPeriod() {}

	virtual void GeneralPeriod() {}
private:
	std::string m_name;
	HotBot* m_bot;
};

#endif /* SRC_HOTSUBSYSTEM_H_ */
