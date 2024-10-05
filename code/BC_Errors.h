#ifndef BC_ERRORS_2024
#define BC_ERRORS_2024

#include <string>
#include <iostream>
#include <cstdint>
#include <vector>
#include <sstream>
#include "ID.h"

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

class BC_shortUP: public BC_Error{
public:
    std::string what() const override {
        return "Usenrame or password is too short";
    }
};

class BC_InvalidCreateType : public BC_Error{
    std::string name;
    std::vector<std::uint8_t> types;
public:
    BC_InvalidCreateType(const std::string& name, const std::vector<std::uint8_t>& types): name(name), types(types){}
    BC_InvalidCreateType(std::string&& name, std::vector<std::uint8_t>&& types): name(std::move(name)), types(std::move(types)){}
    std::string what() const override {
        std::stringstream ss;
        ss << "Can not create \"" + name + "\". Vector of Types: ";
        for(auto type: types){
            ss << std::to_string(type) + " ";
        }
        return ss.str();
    }
};

class BC_InvalidCreateCntCol : public BC_Error{
    std::string name;
    std::uint8_t cnt;
    std::size_t type;
    std::size_t namesCol;
public:
    BC_InvalidCreateCntCol(const std::string& name, std::uint8_t cnt, std::size_t type, std::size_t namesCol):
    name(name), cnt(cnt), type(type), namesCol(namesCol){}
    std::string what() const override {
        return "Can not create \"" + name + "\". cntCol = "+std::to_string(cnt) +
        ", type = " + std::to_string(type) + ", namesCol = " + std::to_string(namesCol);
    }
};

class BC_InvalidLength : public BC_Error{
  std::string name;
public:
    BC_InvalidLength(const std::string& name): name(name){}
    BC_InvalidLength(std::string&& name): name(std::move(name)){}
    std::string what() const override {
        return "Can not create \"" + name + "\". Invalid length";
    }
};

class BC_TableNotFound : public BC_Error{
    std::string name;
public:
    BC_TableNotFound(const std::string& name): name(name){}
    BC_TableNotFound(std::string&& name): name(std::move(name)){}
    std::string what() const override {
        return "Table \"" + name + "\" not found.";
    }
};

class BC_TableNotOpen: public BC_Error{
public:
    BC_TableNotOpen() = default;
    std::string what() const override {
        return "Table not open.";
    }
};

class BC_InvalidLengthAddRow: public BC_Error {
public:
    BC_InvalidLengthAddRow() = default;
    std::string what() const override {
        return "Invalid length of row";
    }
};

class BC_IvalidTypeCreateTable: public BC_Error {
    BC_ID idTable;
    std::uint8_t type;
public:
    BC_IvalidTypeCreateTable(BC_ID idTable, std::uint8_t type) : idTable(idTable), type(type) {}
    std::string what() const override {
        return "Can not create table with id = " + std::to_string(idTable) +
               " and type = " + std::to_string(type);
    }
};


#endif // ! BC_ERRORS_2024