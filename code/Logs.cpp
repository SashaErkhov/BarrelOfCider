//
// Created by sasor on 20.11.2024.
//

#include "Logs.h"
#include <fstream>
#include <iostream>
#include <ctime>

inline const char* getDateTime() {
    time_t ttime = time(0);
    tm *gmt_time = gmtime(&ttime);
    char* dt = asctime(gmt_time);
    dt[24]='\0';
    return dt;
}

inline void saveToConsole(const char* type, const char* message) {
    std::cout<<getDateTime()<<" ["<<type<<"] "<<message<<std::endl;
}

inline bool saveToFile(const char* type, const char* message) {
    std::fstream file;
    file.open("resources/logs.txt", std::ios_base::app | std::ios_base::out);
    if(!file.is_open()) {
        saveToConsole("ERROR", "Can't open file in Logs::saveToFile");
        return false;
    }
    file<<getDateTime()<<" ["<<type<<"] "<<message<<std::endl;
    file.close();
    return true;
}

namespace Logs {
    void info(const char* message) {
        saveToConsole("INFO", message);
        saveToFile("INFO", message);
    }
    void error(const char* message) {
        saveToConsole("ERROR", message);
        saveToFile("ERROR", message);
    }
    void warning(const char* message) {
        saveToConsole("WARNING", message);
        saveToFile("WARNING", message);
    }
    void debug(const char* message) {
        //saveToConsole("DEBUG", message);
    }
}