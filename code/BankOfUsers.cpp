#include "BankOfUsers.h"
#include "BC_Errors.h"
#include "sha256.h"
#include <fstream>
#include <string>

void checkUsername(const std::string& username){
    for(auto p: username){
        if( !(
                (p >= 'a' and p <= 'z') or
                (p >= 'A' and p <= 'Z') or
                (p >= '0' and p <= '9') or
                (p == '-' or p == '_')
                ) )
        {
            throw BC_InvalidUsername(username);
        }
    }
}

void checkPassword(const std::string& password){
    for(auto p: password) {
        if (!(
                (p >= 'a' and p <= 'z') or
                (p >= 'A' and p <= 'Z') or
                (p >= '0' and p <= '9') or
                (p == '-' or p == '_')
        )) {
            throw BC_InvalidPassword(password);
        }
    }
}

std::string createMessage(const std::string& username, const std::string& password) {
    message.reserve(100);
    for(auto p: username) {
        message.push_back(p);
    }
    for(size_t i=username.size();i<50;++i){
        message.push_back(' ');
    }
    for(auto p: password) {
        message.push_back(p);
    }
    for(size_t i=password.size();i<50;++i){
        message.push_back(' ');
    }
    return message;
}

namespace BankOfUsers {
    void addUser(const std::string& username, const std::string& password) {
        checkUsername(username);
        checkPassword(password);
        if(username.size() > 50 or password.size() > 50) throw BC_longUP();
        std::string message = createMessage(username, password);
        SHA256 hash;
        hash.update(message.c_str(), message.size());
        message = std::move(hash.hash());
        std::fstream users;
        users.open("users.txt", std::ios_base::out);
        if(!users.is_open()){
            throw BC_CanNotOpenFile("users.txt");
        }
        std::fstream users_hash;
        users_hash.open("users_hash.txt", std::ios_base::out | std::ios_base::binary);
        if(!users_hash.is_open()){
            users.close();
            throw BC_CanNotOpenFile("users_hash.txt");
        }
        users << username << std::endl;
        users.close();
        users_hash.write(message.c_str(), message.size());
    }


}