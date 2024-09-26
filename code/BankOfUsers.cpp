#include "BankOfUsers.h"
#include "BC_Errors.h"
#include "sha256.h"
#include <fstream>
#include <string>

inline void checkUsername(const std::string& username){
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

inline void checkPassword(const std::string& password){
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
    checkUsername(username);
    checkPassword(password);
    if(username.size() > 50 or password.size() > 50) throw BC_longUP();
    if(username.size() == 0 or username.size() < 4) throw BC_shortUP();
    std::string message;
    message.reserve(100);
    for(auto p: username) {message.push_back(p);}
    for(size_t i=username.size();i<50;++i){message.push_back(' ');}
    for(auto p: password) {message.push_back(p);}
    for(size_t i=password.size();i<50;++i){message.push_back(' ');}
    SHA256 hash;
    hash.update(message.c_str(), message.size());
    message = std::move(hash.hash());
    return message;
}

namespace BankOfUsers {
    void addUser(const std::string& username, const std::string& password) {
        std::string message = createMessage(username, password);
        std::fstream users;
        users.open("resources/users.txt", std::ios_base::out | std::ios_base::app);
        if(!users.is_open()){
            throw BC_CanNotOpenFile("users.txt");
        }
        std::fstream users_hash;
        users_hash.open("resources/users_hash",
                        std::ios_base::out |
                        std::ios_base::binary | std::ios_base::app);
        if(!users_hash.is_open()){
            users.close();
            throw BC_CanNotOpenFile("users_hash");
        }
        users.seekp(0,std::ios_base::end);
        users_hash.seekp(0,std::ios_base::end);
        users << ' ' << username;
        users.close();
        users_hash.write(message.c_str(), message.size());
        users_hash.close();
    }

    void deleteAllUsers(){
        std::fstream users;
        users.open("resources/users.txt", std::ios_base::out);
        if(!users.is_open()){
            throw BC_CanNotOpenFile("users.txt");
        }
        users.close();
        std::fstream users_hash;
        users_hash.open("resources/users_hash",std::ios_base::out);
        if(!users_hash.is_open()){
            throw BC_CanNotOpenFile("users_hash");
        }
        users_hash.close();
        addUser("admin", "admin");
    }

    bool checkUser(const std::string& username, const std::string& password){
        std::string message = createMessage(username, password);
        std::fstream users_hash;
        users_hash.open("resources/users_hash",std::ios_base::in | std::ios_base::binary);
        if(!users_hash.is_open()){
            throw BC_CanNotOpenFile("users_hash");
        }

        bool ok=false;
        std::string user;
        char ch;
        char tmp[65];
        tmp[64]='\0';
        while((ch=users_hash.peek())!=EOF and ch!='\n' and ch!='\r') {
            users_hash.read(tmp,64);
            user=std::move(tmp);
            if(user==message) {
                ok=true;
                break;
            }
        }
        users_hash.close();
        return ok;
    }

    bool checkName(const std::string& username){
        checkUsername(username);
        if(username.size() > 50) throw BC_longUP();
        if(username.size() == 0) throw BC_shortUP();
        std::fstream users;
        users.open("resources/users.txt", std::ios_base::in);
        if(!users.is_open()){
            throw BC_CanNotOpenFile("users.txt");
        }
        char ch;
        bool ok=false;
        std::string user;
        while((ch=users.peek())!=EOF and ch!='\n' and ch!='\r') {
            users >> user;
            if(user==username) {
                ok=true;
                break;
            }
        }
        users.close();
        return ok;
    }
}