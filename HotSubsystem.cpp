#include "HotSubsystem.h"

HotSubsystemHandler::HotSubsystemHandler()
{
	m_task = new Task("HotSubsystemHandler", (FUNCPTR)(Run));
	m_task->Start();
}

void HotSubsystemHandler::Add(HotSubsystem subsystem)
{
	m_subsystems.push_back(subsystem);
}

int HotSubsystemHandler::Run()
{
	while (f_running)
	{
		if (f_enabled)
		{
			/***** Periodic *****/
			if (f_runPeriodic)
			{
				for (unsigned int i = 0; i < m_subsystems.size(); i++)
				{
					m_subsystems[i].Periodic();
				}
			}
			
			/***** Print Data *****/
			if (f_runPrintData)
			{
				for (unsigned int i = 0; i < m_subsystems.size(); i++)
				{
					m_subsystems[i].PrintData();
				}
			}
			
			Wait(0.002);
		}
		else
		{
			Wait(0.05);
		}
	}
	
	return 0;
}
