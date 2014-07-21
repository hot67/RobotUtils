#include "csvwriter.h"

CSVWriter::CSVWriter (const char* fname, int cols)
{
   if (fname != "")
      m_fout.open(fname);
   m_cols = cols;
   m_curCol = 0;
}

CSVWriter::~CSVWriter()
{
   if (is_open())
      close();
}

void CSVWriter::open(const char *fname)
{
    if (is_open())
        close();

    m_fout.open(fname,ios::ate);
}

bool CSVWriter::writeCell(string str)
{
   if (!is_open())
       return false;
   else
   {
       if (str.find(' '))
           m_fout<<'\"'<<str<<"\", ";
       else
           m_fout<<str<<", ";

       m_curCol++;

       if (m_curCol == m_cols && m_cols != 0)
           newRow();

       return true;
   }
}

bool CSVWriter::writeCell(float data)
{
    string buf;

    sprintf(buf.data(), "%f", data);

    return writeCell(buf);
}

bool CSVWriter::writeCell(bool data)
{
    if (data)
        return writeCell("true");
    else
        return writeCell("false");
}

void CSVWriter::newRow()
{
    m_fout<<endl;
    m_curCol = 0;
}
