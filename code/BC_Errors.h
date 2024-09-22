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
    BC_CanNotOpenFile(std::string namefile): namefile(namefile){}
    override std::string what() const{
        return "Can not open file: \"" + namefile + "\"" + std::endl;
    }
};

class BC_InvalidUsername : public BC_Error{
    std::string username;
public:
    BC_InvalidUsername(std::string username): username(username){}
    override std::string what() const{
        return "Invalid username: \"" + username + "\"" + std::endl +
        "Please, use: \'a\'-\'z\' or \'A\'-\'Z\' or \'0\'-\'9\' or \'_\' or \'-\'" + std::endl;
    }
};

class BC_InvalidPassword : public BC_Error{
    std::string password;
public:
    BC_InvalidPassword(std::string password): password(password){}
    override std::string what() const {
        return "Invalid password: \"" + password + "\"" + std::endl +
               "Please, use: \'a\'-\'z\' or \'A\'-\'Z\' or \'0\'-\'9\' or \'_\' or \'-\'" + std::endl;
    }
};

class BC_longUP: public BC_Error{
public:
    override std::string what() const{
        return "Username or password is too long" + std::endl;
    }
};



#endif