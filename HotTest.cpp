/*
 * HotTest.cpp
 *
 *  Created on: Jan 24, 2016
 *      Author: Jin
 */

#include "HotTest.h"

/**
 * 	Get Instance
 */
HotTest* HotTest::GetInstance() {
	static HotTest* m_instance;

	return (m_instance == NULL) ? m_instance = new HotTest() : m_instance;
}
/**
 * 	Test Control
 */
HotTest::HotTest() {
#ifndef HOTTEST_LOCAL
	m_table = NetworkTable::GetTable("HotTest");
#endif
	c_red = 0;
	c_grn = 0;
	c_prc = 0;
}

void HotTest::End() {
	for (std::map<std::string, HotTestFunc*>::iterator it = m_funcs.begin(); it != m_funcs.end(); it++) {
		if (it->second->IsMustRun()) {
			AssignHasRun(it->second->MustRun(), it->second);
		}
		if (it->second->IsMustNotRun()) {
			AssignNHasRun(it->second->MustNotRun(), it->second);
		}
	}
}

/**
 * 	Simple Value Assign
 */
void HotTest::Assign(std::string name, bool value, bool expect) {
	Result(name, (value == expect) ? kGRN : kRED);
}
void HotTest::Assign(std::string name, int value, int expect) {
	Result(name, (value == expect) ? kGRN : kRED);
}
void HotTest::Assign(std::string name, double value, double expect, double acc) {
	Result(name, (fabs(value-expect) <= acc) ? kGRN : kRED);
}

/**
 * 	Inverse Assign
 */
void HotTest::AssignN(std::string name, bool value, bool expect) {
	Result(name, (value != expect) ? kGRN : kRED);
}
void HotTest::AssignN(std::string name, int value, int expect) {
	Result(name, (value != expect) ? kGRN : kRED);
}
void HotTest::AssignN(std::string name, double value, double expect, double acc) {
	Result(name, (fabs(value-expect) >= acc) ? kGRN : kRED);
}

/**
 * 	Detailed Assign
 */
void HotTest::AssignTrue(std::string name, bool value) {
	Assign(name, value, true);
}
void HotTest::AssignFalse(std::string name, bool value) {
	Assign(name, value, false);
}
void HotTest::AssignNonZero(std::string name, int value) {
	AssignN(name, value, 0);
}
void HotTest::AssignGreater(std::string name, double value, double decision) {
	Result(name, (value > decision) ? kGRN : kRED);
}
void HotTest::AssignGreater(std::string name, int value, int decision) {
	Result(name, (value > decision) ? kGRN : kRED);
}
void HotTest::AssignLess(std::string name, double value, double decision) {
	Result(name, (value < decision) ? kGRN : kRED);
}
void HotTest::AssignLess(std::string name, int value, int decision) {
	Result(name, (value < decision) ? kGRN : kRED);
}

/**
 * 	Flow Test
 */
void HotTest::AssignRun(std::string name, HotTestFunc* func) {
	func->MustRun(name);
}
void HotTest::AssignRun(std::string name, std::string func) {
	AssignRun(name, GetFunc(func));
}

void HotTest::AssignNRun(std::string name, HotTestFunc* func) {
	func->MustNotRun(name);
}
void HotTest::AssignNRun(std::string name, std::string func) {
	AssignNRun(name, GetFunc(func));
}

void HotTest::AssignHasRun(std::string name, HotTestFunc* func) {
	Result(name, func->HasRun() ? kGRN : kRED);
}
void HotTest::AssignHasRun(std::string name, std::string func) {
	AssignHasRun(name, GetFunc(func));
}

void HotTest::AssignNHasRun(std::string name, HotTestFunc* func) {
	Result(name, func->HasRun() ? kRED : kGRN);
}
void HotTest::AssignNHasRun(std::string name, std::string func) {
	AssignNHasRun(name, GetFunc(func));
}


void HotTest::AssignHasRun(std::string name, HotTestFunc* func, int count) {
	Result(name, func->Count() == count ? kGRN : kRED);
}
void HotTest::AssignHasRun(std::string name, std::string func, int count) {
	AssignHasRun(name, GetFunc(func), count);
}

void HotTest::AssignRunAfter(std::string name, HotTestFunc* func, HotTestFunc* prev) {
	func->After(name, prev);
}
void HotTest::AssignRunAfter(std::string name, HotTestFunc* func, std::string prev) {
	AssignRunAfter(name, func, GetFunc(prev));
}
void HotTest::AssignRunAfter(std::string name, std::string func, HotTestFunc* prev) {
	AssignRunAfter(name, GetFunc(func), prev);
}
void HotTest::AssignRunAfter(std::string name, std::string func, std::string prev) {
	AssignRunAfter(name, GetFunc(func), GetFunc(prev));
}

void HotTest::AssignRunBefore(std::string name, HotTestFunc* func, HotTestFunc* prev) {
	func->Before(name, prev);
}
void HotTest::AssignRunBefore(std::string name, HotTestFunc* func, std::string prev) {
	AssignRunBefore(name, func, GetFunc(prev));
}
void HotTest::AssignRunBefore(std::string name, std::string func, HotTestFunc* prev) {
	AssignRunBefore(name, GetFunc(func), prev);
}
void HotTest::AssignRunBefore(std::string name, std::string func, std::string prev) {
	AssignRunBefore(name, GetFunc(func), GetFunc(prev));
}

void HotTest::AssignHasRunMoreThan(std::string name, HotTestFunc* func, int count) {

	AssignGreater(name, func->Count(), (int)count);
}
void HotTest::AssignHasRunMoreThan(std::string name, std::string func, int count) {
	AssignHasRunMoreThan(name, GetFunc(func), count);
}

void HotTest::AssignHasRunNoMoreThan(std::string name, HotTestFunc* func, int count) {
	AssignLess(name, func->Count(), count);
}
void HotTest::AssignHasRunNoMoreThan(std::string name, std::string func, int count) {
	AssignHasRunMoreThan(name, GetFunc(func), count);
}

void HotTest::Run(HotTestFunc* func) {
	func->Run();
}

void HotTest::Run(std::string func) {
	Run(GetFunc(func));
}

/**
 * 	Write On Network Table
 */
void HotTest::Result(std::string name, Status status, std::string value) {
#ifdef HOTTEST_LOCAL
	switch(status) {
	case kGRN:
		std::cout << "GRN " + name + " " + value << std::endl;
		c_grn++;
		break;
	case kRED:
		std::cout << "RED " + name + " " + value << std::endl;
		c_red++;
		break;
	case kPRC:
		std::cout << "PRC " + name + " " + value << std::endl;
		c_prc++;
		break;
	}
#else
	switch(status) {
	case kGRN:
		m_table->PutString(name, "GRN " + value);
		c_grn++;
		break;
	case kRED:
		m_table->PutString(name, "RED " + value);
		c_red++;
		break;
	case kPRC:
		m_table->PutString(name, "PRC " + value);
		c_prc++;
		break;
	}
#endif

}

/**
 * 	Get Function
 */
HotTestFunc* HotTest::GetFunc(std::string func) {
	// std::cout << "GET FUNC " << func << std::endl;
	for (std::map<std::string, HotTestFunc*>::iterator it = m_funcs.begin(); it != m_funcs.end(); it++) {
		if (it->first.compare(func) == 0) {
			return it->second;
		}
	}

	return m_funcs[func] = new HotTestFunc(this, func);
}

/******************************
 * 	Hot Test Function
 ******************************/
HotTestFunc::HotTestFunc(HotTest* test, std::string name) {
	t = test;
	m_name = name;
	m_mustRun = "";
	m_mustNRun = "";
	m_count = 0;
}
std::string HotTestFunc::GetName() {
	return m_name;
}
void HotTestFunc::MustRun(std::string testName) {
	m_mustRun = testName;
}
void HotTestFunc::MustNotRun(std::string testName) {
	m_mustNRun = testName;
}
void HotTestFunc::After(std::string testName, HotTestFunc* func) {
	m_after[testName] = func;
}
void HotTestFunc::Before(std::string testName, HotTestFunc* func) {
	m_before[testName] = func;
}

/**
 * 	Get Must Run
 */
std::string HotTestFunc::MustRun() {
	return m_mustRun;
}
bool HotTestFunc::IsMustRun() {
	return !m_mustRun.empty();
}
std::string HotTestFunc::MustNotRun() {
	return m_mustNRun;
}
bool HotTestFunc::IsMustNotRun() {
	return !m_mustNRun.empty();
}

/**
 * 	Set Run
 */
void HotTestFunc::Run() {
	m_count++;

	/**
	 * 	Check after
	 */
	for (std::map<std::string, HotTestFunc*>::iterator it = m_after.begin(); it != m_after.end(); it++) {
		t->AssignHasRun(it->first, it->second);
	}

	/**
	 * 	Check Before
	 */
	for (std::map<std::string, HotTestFunc*>::iterator it = m_before.begin(); it != m_before.end(); it++) {
		t->AssignNHasRun(it->first, it->second);
	}
}

int HotTestFunc::Count() {
	return m_count;
}

bool HotTestFunc::HasRun() {
	return m_count > 0;
}
