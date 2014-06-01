#include "BackgroundDebugger.h"

BackgroundDebugger::BackgroundDebugger(double debugInterval, bool clearContents) :
    HotSubsystem("BackgroundDebugger")
{
    Preferences* prefs;

    prefs = Preferences::GetInstance();

    m_debugInterval = debugInterval;
    m_manualLog = "manualLog.txt";
    m_fout = new ofstream;

    f_running = false;
    f_delContents = clearContents;
    m_runNum = prefs->GetInt("DebugRun");
    m_runPath = "DisabledLogs";

    if (!S_ISDIR(stat(m_runPath.c_str())))
    {
        mkdir(m_runPath.c_str());
        m_runPath += '/';
    }
    else
    {
        m_runPath += '/';

        struct dirent* curFile;
        DIR* folder;
        string filepath;

        folder = opendir(m_runPath.c_str());

        while (curFile = readdir(folder))
        {
            if (strcmp(curFile->d_name,".") != 0 && strcmp(curFile->d_name,"..") != 0)
            {
                filepath = m_runPath+curFile->d_name;

                m_fout->open(filepath.c_str(), ios::app);

                if (m_fout->is_open())
                    (*m_fout)<<"**REBOOT**"<<endl;
            }
        }
    }
}

BackgroundDebugger::~BackgroundDebugger()
{
    if (m_fout->is_open())
        m_fout->close();
}

void BackgroundDebugger::AddValue(string id, FUNCPTR function)
{
    FuncData funcData;

    funcData.id = id;
    funcData.function = function;

    m_funcList.push_back(funcData);
}

void BackgroundDebugger::AddValue(string id, double *value)
{
    NumData numData;

    numData.id = id;
    numData.value = value;

    m_numList.push_back(numData);
}

void BackgroundDebugger::AddValue(string id, string *value)
{
    StringData stringData;

    stringData.id = id;
    stringData.value = value;

    m_numList.push_back(stringData);
}

void BackgroundDebugger::LogData(string id, double value)
{
    time_t currentTime;

    time(&currentTime);
    m_fout->open(m_runPath.c_str()+m_manualLog.c_str(), ios::app);

    if (m_fout->is_open())
    {
        (*m_fout)<<ctime(currentTime)<<' '<<id<<' '<<value<<endl;
        m_fout->close();
    }
}

void BackgroundDebugger::LogData(string id, string value)
{
    time_t currentTime;

    time(&currentTime);
    m_fout->open(m_runPath.c_str()+m_manualLog.c_str(), ios::app);

    if (m_fout->is_open())
    {
        (*m_fout)<<ctime(currentTime)<<' '<<id<<' '<<value<<endl;
        m_fout->close();
    }
}

void BackgroundDebugger::ResetRunNumber()
{
    if (!f_running)
        m_runNum = 0;
}

void BackgroundDebugger::StartRun()
{
    m_runNum++;
    m_runPath = "Run"+m_runNum;

    time(&m_startTime);

    if (!S_ISDIR(stat(m_runPath.c_str())))
    {
        mkdir(m_runPath.c_str());
        m_runPath += '/';
    }
    else if (f_delContents)
    {
        m_runPath += '/';

        struct dirent* curFile;
        DIR* folder;
        string filepath;

        folder = opendir(m_runPath.c_str());

        while (curFile = readdir(folder))
        {
            if (strcmp(curFile->d_name, ".") != 0 && strcmp(curFile->d_name, ".."))
            {
                filepath = m_runPath+curFile->d_name;
                remove(filepath.c_str());
            }
        }
    }

    f_running = true;
}

void BackgroundDebugger::StopRun()
{
    Preferences* prefs;

    prefs = Preferences::GetInstance();

    prefs->PutInt("DebugRun",m_runNum);
    prefs->Save();

    f_running = false;
    m_runPath = "DisabledLogs/";
}

void BackgroundDebugger::Update()
{
    if (f_running)
    {
        int x;
        string message;

        message = m_tempMsg;

        if ((difftime(time(NULL),m_lastDebugTime)*1000.0) > m_debugInterval)
        {
            //Numbers
            for (x = 0; x < m_numList.size(); x++)
            {
                m_fout->open(m_runPath.c_str()+m_numList[x].id.c_str()+".txt", ios::app);

                if (m_fout->is_open())
                {
                    if (message != "")
                        (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, **"<<message<<"**"<<endl;

                    (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, "<<(*m_numList[x].value)<<endl;
                    m_fout->close();
                }
            }

            //Strings
            {
                for (x = 0; x < m_stringList.size(); x++)
                {
                    m_fout->open(m_runPath.c_str()+m_stringList[x].id.c_str()+".txt", ios::app);

                    if (m_fout->is_open())
                    {
                        if (message != "")
                            (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, **"<<message<<"**"<<endl;

                        (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, "<<(*m_stringList[x].value)<<endl;
                        m_fout->close();
                    }
                }
            }

            //Functions
            {
                for (x = 0; x < m_funcList.size(); x++)
                {
                    m_fout->open(m_runPath.c_str()+m_funcList[x].id.c_str()+".txt", ios::app);

                    if (m_fout->is_open())
                    {
                        if (message != "")
                            (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, **"<<message<<"**"<<endl;

                        (*m_fout)<<difftime(time(NULL),m_startTime)<<"s, "<<(m_funcList[x].function())<<endl;
                        m_fout->close();
                    }
                }
            }

            time(&m_lastDebugTime);
            if (m_tempMsg.compare(message) == 0)
                m_tempMsg = "";
        }
    }
}
