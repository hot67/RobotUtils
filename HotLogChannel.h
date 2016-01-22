
#ifndef SRC_HOTLOGCHANNEL_H_
#define SRC_HOTLOGCHANNEL_H_

#include <fstream>
#include <string>
#include <sstream>
#include "HotLogger.h"
#include "HotLogFile.h"

class HotLogger;

class HotLogChannel {
public:
	/******************************
	 * 	Log Channel Type
	 ******************************/
	typedef enum {
		kTypeState,
		kTypeDouble,
		kTypeBoolean
	} Type;

	/******************************
	 * 	Constructor
	 * 		This function defines child-parent relationship to HotLog
	 ******************************/
	HotLogChannel(unsigned char id, std::string name, Type type, float min=0.0, float max=0.0, float accuracy=0.0);

	/******************************
	 * 	Getters
	 * 		Key is unique under the HotLog
	 * 		FullKey is unique among the entire system
	 ******************************/
	unsigned char GetID() const;
	std::string GetName() const;

	/******************************
	 * 	Set Value
	 ******************************/
	void Set(int value);
	void Set(double value);
	void Set(bool value);

	/******************************
	 * 	Write Declare Line
	 ******************************/
	std::string DeclareLine();

	/******************************
	 * 	Write Data
	 ******************************/
	void WriteDate(HotLogFile* file);

private:
	unsigned char m_id = 0;
	std::string m_key;
	Type m_type;

	//	For Double
	double m_min = 0.0, m_max = 0.0, m_accuracy = 0.0;

	//	Values
	unsigned char s_value = 0;
	double d_value = 0.0;
	bool b_value = false;

	//	Updated
	bool f_updated = true;
};

#endif /* SRC_HOTLOGCHANNEL_H_ */
