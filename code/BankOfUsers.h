#ifndef BC_BANKOFUSERS_2024
#define BC_BANKOFUSERS_2024

#include <string>

namespace BankOfUsers {
    void addUser(const std::string& username, const std::string& password);
    void deleteAllUsers();
    bool checkUser(const std::string& username, const std::string& password);
    bool checkName(const std::string& username);
}

#endif