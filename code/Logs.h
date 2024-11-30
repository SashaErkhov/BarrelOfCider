//server and client

#ifndef BC_LOGS_H
#define BC_LOGS_H

#include <string>

namespace Logs {
    void info(const char* message);
    void error(const char* message);
    void warning(const char* message);
    void debug(const char* message);
}

#endif // ! BC_LOGS_H
