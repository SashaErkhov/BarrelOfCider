//client

#include "LexicalAnalysis.h"
#include <sstream>
#include <cstdint>
#include "ID.h"
#include <limits>

LexResult LexicalAnalysis::checkPassword(const std::string& password, std::string& log) noexcept {
    if(password==quitStr_) return LexResult::quit;
    if(password.empty()) {
        log = "Empty password";
        return LexResult::error;
    }
    if(password.size()<4) {
        log = "Password is too short";
        return LexResult::error;
    }
    if(password.size()>50) {
        log = "Password is too long";
        return LexResult::error;
    }
    for(auto p: password) {
        if (!(
                (p >= 'a' and p <= 'z') or
                (p >= 'A' and p <= 'Z') or
                (p >= '0' and p <= '9') or
                (p == '-' or p == '_')
        )) {
            log = R"(Invalid password. Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')";
            return LexResult::error;
        }
    }
    return LexResult::normal;
}

LexResult LexicalAnalysis::checkUsername(const std::string& username, std::string& log) noexcept {
    if(username.empty()) {
        log = "Empty username";
        return LexResult::error;
    }
    if(username.size()>50) {
        log = "Username is too long";
        return LexResult::error;
    }
    for(auto p: username){
        if( !(
                (p >= 'a' and p <= 'z') or
                (p >= 'A' and p <= 'Z') or
                (p >= '0' and p <= '9') or
                (p == '-' or p == '_')
        ) )
        {
            log = R"(Invalid username. Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')";
            return LexResult::error;
        }
    }
    return LexResult::normal;
}

LexResult LexicalAnalysis::checkBasic(const std::string& str, std::string& log) noexcept {
    if(str==quitStr_) return LexResult::quit;
    if(str.empty()) {
        log = "Empty command";
        return LexResult::error;
    }
    if(str.size() > 1200) {
        log = "Command is too long";
        return LexResult::error;
    }
    std::stringstream ss(str);
    std::string word;
    switch(str[0]) {
        case 'r': {
            ss >> word;
            if(checkUsername(word, log)==LexResult::error) {
                return LexResult::error;
            }
            ss>>word;
            if(checkPassword(word, log)==LexResult::error) {
                return LexResult::error;
            }
            if(ss>>word) {
                log = "Invalid command";
                return LexResult::error;
            }
            break;
        }
        case 'a': {
            ss >> word;
            if(checkName_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            ss>>word;
            if(checkValue_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            if(ss>>word) {
                log = "Invalid command";
                return LexResult::error;
            }
            break;
        }
        case 'd': {
            ss >> word;
            if(checkID_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            if(ss>>word) {
                log = "Invalid command";
                return LexResult::error;
            }
            break;
        }
        case 'u': {
            ss >> word;
            if(checkID_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            ss>>word;
            if(checkName_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            ss>>word;
            if(checkValue_(word, log)==LexResult::error) {
                return LexResult::error;
            }
            if(ss>>word) {
                log = "Invalid command";
                return LexResult::error;
            }
            break;
        }
        case 'g': {
            ss >> word;
            if(word=="all") {}
            else if(word=="name") {
                ss>>word;
                if(checkName_(word, log)==LexResult::error) {
                    return LexResult::error;
                }
            } else if(word=="value") {
                ss >> word;
                if(checkValue_(word, log)==LexResult::error) {
                    return LexResult::error;
                }
            } else {
                log = "Unknown command";
                return LexResult::error;
            }
            if(ss>>word) {
                log = "Invalid command";
                return LexResult::error;
            }
            break;
        }
        default: {
            log = "unknown command";
            return LexResult::error;
        }
    }
    return LexResult::normal;
}

LexResult LexicalAnalysis::checkName_(const std::string &name, std::string &log) {
    if(name.empty()) {
        log = "Empty name of record";
        return LexResult::error;
    }
    if(name.size()>50) {
        log = "Name of record is too long";
        return LexResult::error;
    }
    return LexResult::normal;
}

LexResult LexicalAnalysis::checkValue_(const std::string& value, std::string& log) {
    if(value.empty()) {
        log = "Empty value of record";
        return LexResult::error;
    }
    if(value.size()>1024) {
        log = "Value of record is too long";
        return LexResult::error;
    }
    return LexResult::normal;
}

LexResult LexicalAnalysis::checkID_(const std::string& id, std::string& log) {
    if(id.empty()) {
        log = "Empty ID of record";
        return LexResult::error;
    }
    for(auto p: id) {
        if( !(p>='0' and p<='9') )  {
            log = "Invalid ID of record";
            return LexResult::error;
        }
    }
    std::uint64_t idNum=std::atoll(id.c_str());
    if(idNum>std::numeric_limits<type_id>::max()) {
        log = "id is wrong";
        return LexResult::error;
    }
    return LexResult::normal;
}