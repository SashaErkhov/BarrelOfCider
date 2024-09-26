#ifndef BC_ERRORS_2024
#define BC_ERRORS_2024

#include <string>
#include <iostream>

class BC_Error{
public:
    virtual std::string what() const = 0;
};

class BC_CanNotOpenFile : public BC_Error{
    std::string namefile;
public:
    explicit BC_CanNotOpenFile(std::string&& namefile): namefile(std::move(namefile)){}
    explicit BC_CanNotOpenFile(const std::string& namefile): namefile(namefile){}
    std::string what() const override{
        return "Can not open file: \"" + namefile + "\".";
    }
};

class BC_InvalidUsername : public BC_Error{
    std::string username;
public:
    explicit BC_InvalidUsername(const std::string& username): username(username){}
    explicit BC_InvalidUsername(std::string&& username): username(std::move(username)){}
    std::string what() const override{
        return "Invalid username: \"" + username + "\". "
        + R"(Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')";
    }
};

class BC_InvalidPassword : public BC_Error{
    std::string password;
public:
    explicit BC_InvalidPassword(const std::string& password): password(password){}
    explicit BC_InvalidPassword(std::string&& password): password(std::move(password)){}
    std::string what() const override {
        return "Invalid password: \"" + password + "\". " +
               R"(Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')";
    }
};

class BC_longUP: public BC_Error{
public:
    std::string what() const override{
        return "Username or password is too long";
    }
};



#endif