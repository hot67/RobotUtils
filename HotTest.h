/*
 * HotTest.h
 *
 *  Created on: Jan 24, 2016
 *      Author: Jin
 */

#ifndef SRC_ROBOTUTILS_HOTTEST_H_
#define SRC_ROBOTUTILS_HOTTEST_H_

/**
 * 	Configuration
 */
#define HOTTEST_LOCAL

#include <string>
#include <map>
#include <math.h>
#include <memory>

#ifdef HOTTEST_LOCAL
#include <iostream>
#else
#include "WPILib.h"
#endif
class HotTestFunc;

class HotTest {
public:
	/**
	 * 	Get Instance
	 */
	static HotTest* GetInstance();

	/******************************
	 * 	Test Status
	 ******************************/
	typedef enum {
		kGRN,
		kRED,
		kPRC
	} Status;

	/******************************
	 * 	Start / End Test
	 ******************************/
	HotTest();
	void End();

	/******************************
	 * 	Assign
	 ******************************/
	/**
	 * 	Simple Value Assign
	 */
	void Assign(std::string name, bool value, bool expect);
	void Assign(std::string name, int value, int expect);
	void Assign(std::string name, double value, double expect, double acc = 0.0);

	/**
	 * 	Inverse Assign
	 */
	void AssignN(std::string name, bool value, bool expect);
	void AssignN(std::string name, int value, int expect);
	void AssignN(std::string name, double value, double expect, double acc = 0.0);

	/**
	 * 	Detailed Assign
	 */
	void AssignTrue(std::string name, bool value);
	void AssignFalse(std::string name, bool value);
	void AssignNonZero(std::string name, int value);
	void AssignGreater(std::string name, double value, double decision);
	void AssignGreater(std::string name, int value, int decision);
	void AssignLess(std::string name, double value, double decision);
	void AssignLess(std::string name, int value, int decision);

	/**
	 * 	Program flow assign
	 */
	/**
	 * 	At the end of test, we check if the function has run
	 */
	void AssignRun(std::string name, HotTestFunc* func);
	void AssignRun(std::string name, std::string func);

	/**
	 * 	At the end of test, we check if the function has run
	 */
	void AssignNRun(std::string name, HotTestFunc* func);
	void AssignNRun(std::string name, std::string func);

	/**
	 * 	When Run(func) is called, we check if 'prev' has run
	 */
	void AssignRunAfter(std::string name, HotTestFunc* func, HotTestFunc* prev);
	void AssignRunAfter(std::string name, HotTestFunc* func, std::string prev);
	void AssignRunAfter(std::string name, std::string func, HotTestFunc* prev);
	void AssignRunAfter(std::string name, std::string func, std::string prev);

	/**
	 * 	When Run(func) is called, we check if 'post' has run
	 */
	void AssignRunBefore(std::string name, HotTestFunc* func, HotTestFunc* post);
	void AssignRunBefore(std::string name, HotTestFunc* func, std::string post);
	void AssignRunBefore(std::string name, std::string func, HotTestFunc* post);
	void AssignRunBefore(std::string name, std::string func, std::string post);

	/**
	 * 	Is Run(func) called?
	 */
	void AssignHasRun(std::string name, HotTestFunc* func);
	void AssignHasRun(std::string name, std::string func);

	/**
	 * 	Is Run(func) not called?
	 */
	void AssignNHasRun(std::string name, HotTestFunc* func);
	void AssignNHasRun(std::string name, std::string func);

	//	Tell name of function that should run certain number of times by this point
	void AssignHasRun(std::string name, HotTestFunc* func, int count);
	void AssignHasRun(std::string name, std::string func, int count);

	//	Tell name of function that should run more than certain number of times by this point
	void AssignHasRunMoreThan(std::string name, HotTestFunc* func, int count);
	void AssignHasRunMoreThan(std::string name, std::string func, int count);

	//	Tell name of function that should run no more than certain number of times by this point
	void AssignHasRunNoMoreThan(std::string name, HotTestFunc* func, int count);
	void AssignHasRunNoMoreThan(std::string name, std::string func, int count);

	//	Tell that function is running now
	void Run(HotTestFunc* name);
	void Run(std::string name);

	/**
	 * 	Write On Network Table
	 */
	void Result(std::string name, Status status, std::string value = "");



	/**
	 * 	Get Function
	 */
	HotTestFunc* GetFunc(std::string func);

private:
	/**
	 * 	Instance
	 */
	static HotTest* instance;

	/**
	 * 	To Display Result
	 */
#ifndef HOTTEST_LOCAL
	std::shared_ptr<NetworkTable> m_table;
#endif

	/**
	 * 	Summary
	 */
	int c_grn, c_red, c_prc;

	/**
	 *	List of Functions
	 */
	std::map<std::string, HotTestFunc*> m_funcs;
};

class HotTestFunc {
public:
	HotTestFunc(HotTest* test, std::string name);

	/**
	 * 	Get Name
	 */
	std::string GetName();

	/**
	 *	Set Condition
	 */
	void MustRun(std::string testName);
	void MustNotRun(std::string testName);
	void After(std::string testName, HotTestFunc* func);
	void Before(std::string testName, HotTestFunc* func);

	/**
	 * 	Is Must Run
	 */
	std::string MustRun();
	bool IsMustRun();
	std::string MustNotRun();
	bool IsMustNotRun();

	/**
	 * 	Set Run
	 */
	void Run();

	/**
	 *	Reset
	 */
	void Reset();

	/**
	 * 	Get Count
	 */
	int Count();

	/**
	 * 	Has Run
	 */
	bool HasRun();
private:
	/**
	 * 	Test
	 */
	HotTest* t;

	/**
	 * 	Name
	 */
	std::string m_name;

	/**
	 * 	Conditions
	 */
	std::string m_mustRun, m_mustNRun;
	std::map<std::string, HotTestFunc*> m_after, m_before;

	/**
	 * 	Count
	 */
	int m_count;
};
#endif /* SRC_ROBOTUTILS_HOTTEST_H_ */
