#ifndef BACKGROUNDDEBUGGER_H
#define BACKGROUNDDEBUGGER_H

#include "HotSubsystem.h"
#include "WPILib.h"
#include <fstream>
#include <vector>
#include <ctime>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <cstdio>

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
     * @param clearContents: Clear the contents of existing debug folders.
     */
    BackgroundDebugger(double debugInterval=DEBUG_INTERVAL, bool clearContents=true);
    ~BackgroundDebugger();

    // DEBUG FUNCTIONS ---------------------------------------------------------------------------
    /**
     * @brief AddValue: Adds a number/string/function to the debugger's watch list.
     * @param id: The identifier for the number/string/function. This is used to determine
     *            the filename to write to.
     * @param value: The pointer to the value to debug.
     */
    void AddValue (string id, double* value);
    void AddValue (string id, string* value);
    void AddValue (string id, FUNCPTR function);

    /**
     * @brief SetTempMessage: Set a message to print out into all of the automatic
     *        debug files. This is useful for printing messages to show where the program
     *        is in its execution.
     * @param msg: The message to print.
     */
    void SetTempMessage (string msg) { m_tempMsg = msg; }

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
    void StopRun();

    // CONFIGURATION FUNCTIONS ------------------------------------------------------------------

    /**
     * @brief ClearContentsOnNewRun: Clear the contents of a folder
     *        from a previous run that shares the same name as the
     *        current run.
     * @param clear: Whether or not to clear out the contents of old
     *        folders
     */
    void ClearContentsOnNewRun (bool clear=true) { f_delContents = clear; }

    /**
     * @brief ResetRunNumber: Resets the run number.
     */
    void ResetRunNumber ();

    /**
     * @brief SetManualLoggingName: Set the file to which
     *        LogData writes to data to
     * @param fName: File name to write manual log to (without the extension)
     */
    void SetManualLoggingName (string fName) { m_manualLog = fName+"_manual.txt"; }

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

    ofstream* m_fout;
    double m_debugInterval;
    time_t m_lastDebugTime;
    time_t m_startTime;

    bool f_running;
    bool f_delContents;
    int m_runNum;
    string m_runPath;
};

#endif // BACKGROUNDDEBUGGER_H
