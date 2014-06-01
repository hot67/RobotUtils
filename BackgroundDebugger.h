#ifndef BACKGROUNDDEBUGGER_H
#define BACKGROUNDDEBUGGER_H

#include "HotSubsystem.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sys/stat.h>

#define DEBUG_INTERVAL 500

using namespace std;

typedef struct {
    string id;
    double* value;
} NumData;

typedef struct {
    string id;
    string* value;
} StringData;

typedef struct {
    string id;
    FUNCPTR function;
} FuncData;

class BackgroundDebugger: public HotSubsystem
{
public:
    friend class HotSubsystemHandler;

    /**
     * @brief BackgroundDebugger: Class constructor
     * @param debugInterval: The interval to write debug data at (in ms).
     */
    BackgroundDebugger(double debugInterval=DEBUG_INTERVAL);
    ~BackgroundDebugger();

    // DEBUG FUNCTIONS ---------------------------------------------------------------------------
    /**
     * @brief AddNumber/String/Function: Adds a number/string to the debugger's watch list.
     * @param id: The identifier for the number/string. This is used to determine
     *            the filename to write to.
     * @param value: The pointer to the value to debug.
     */
    void AddNumber (string id, double* value);
    void AddString (string id, string* value);
    void AddFunction (string id, FUNCPTR function);

    /**
     * @brief LogData: manually save data to a file
     * @param id: The identifier of the value
     * @param value: The value to print to file
     */
    void LogData(string id, double value);
    void LogData(string id, string value);

    /**
     * @brief StartRun: Start the debugger. Creates a new folder
     *        containing all of the debug info from the run.
     */
    void StartRun();

    /**
     * @brief StopRun: Disables the debugger.
     */
    void StopRun() { f_running = false; }

    // CONFIGURATION FUNCTIONS ------------------------------------------------------------------
    /**
     * @brief SetManualLoggingName: Set the file to which
     *        LogData writes to data to
     * @param fName: File name to write manual log to (without the extension)
     */
    void SetManualLoggingName (string fName) { m_manualLog = fName+".txt"; }

    /**
     * @brief SetDebugInterval: Set the interval at which
     *        the debugger automatically writes data to file.
     * @param interval: The new interval for debugging in ms.
     */
    void SetDebugInterval (double interval) { m_debugInterval = interval; }

protected:
    void Update();
private:
    //User-defined debugging data
    vector<NumData> m_numList;
    vector<StringData> m_stringList;
    vector<FuncData> m_funcList;
    string m_tempMsg;
    string m_manualLog;

    ofstream m_fout (ios::app);
    double m_debugInterval;
    time_t lastDebugTime;

    bool f_running;
    int m_runNum;
};

#endif // BACKGROUNDDEBUGGER_H
