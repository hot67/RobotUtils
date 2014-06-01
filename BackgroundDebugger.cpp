#include "BackgroundDebugger.h"

BackgroundDebugger::BackgroundDebugger(double debugInterval) :
    HotSubsystem("BackgroundDebugger")
{
    m_debugInterval = debugInterval;
    m_manualLog = "manualLog.txt";
    m_fout = new ofstream (ios::app);

    f_running = false;
    m_runNum = 0;
    m_runPath = "DisabledLogs";

    if (!S_ISDIR(stat(m_runPath.c_str())))
    {
        mkdir(m_runPath.c_str());
        m_runPath += '/';
    }
    else if (m_delContents)
    {
        m_runPath += '/';

        struct dirent* curFile;
        DIR* folder;
        string filepath;

        folder = opendir(m_runPath.c_str());

        while (curFile = readdir(folder))
        {
            filepath = m_runPath+curFile->d_name;
            if (!filepath.compare((string)'.') && !filepath.compare((string)".."))
                remove(filepath);
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
    m_fout->open(m_runPath.c_str()+m_manualLog.c_str());

    if (m_fout->is_open())
    {
        (*m_fout)<<ctime(currentTime)<<' '<<id<<' '<<value;
        m_fout->close();
    }
}

void BackgroundDebugger::LogData(string id, string value)
{
    time_t currentTime;

    time(&currentTime);
    m_fout->open(m_runPath.c_str()+m_manualLog.c_str());

    if (m_fout->is_open())
    {
        (*m_fout)<<ctime(currentTime)<<' '<<id<<' '<<value;
        m_fout->close();
    }
}

void BackgroundDebugger::StartRun()
{
    m_runNum++;
    m_runPath = "Run"+m_runNum;

    if (!S_ISDIR(stat(m_runPath.c_str())))
    {
        mkdir(m_runPath.c_str());
        m_runPath += '/';
    }
    else if (m_delContents)
    {
        m_runPath += '/';

        struct dirent* curFile;
        DIR* folder;
        string filepath;

        folder = opendir(m_runPath.c_str());

        while (curFile = readdir(folder))
        {
            filepath = m_runPath+curFile->d_name;
            if (!filepath.compare((string)'.') && !filepath.compare((string)".."))
                remove(filepath);
        }
    }

    f_running = true;
}

void BackgroundDebugger::Update()
{

}
