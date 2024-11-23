//
// Created by sasor on 29.09.2024.
//

#include "DB.h"
#include "BC_Errors.h"
#include "ID.h"
#include <sstream>
#include <memory>
#include "Logs.h"

std::string DataBank::createMessage_(type_id id, const std::string& name, const std::string& value) const{
    Logs::debug(std::to_string(name.size()).c_str());
    if(name.size() > 50 or value.size() > 1024){
        throw BC_longNameOrValueDB();
    }
    std::string message;
    message.reserve(sizeMessage_);
    for(auto p: std::to_string(id)) {message.push_back(p);}
    Logs::debug(message.c_str());
    for(size_t i=std::to_string(id).size(); i<50; ++i) {message.push_back(' ');}
    Logs::debug(message.c_str());
    for(auto p: name) {message.push_back(p);}
    Logs::debug(message.c_str());
    for(size_t i = name.size(); i<50; ++i) {message.push_back(' ');}
    Logs::debug(message.c_str());
    for(auto p: value) {message.push_back(p);}
    Logs::debug(message.c_str());
    for(size_t i = value.size(); i<1024; ++i) {message.push_back(' ');}
    Logs::debug(message.c_str());
    return message;
}

void DataBank::add(const std::string& name, const std::string& value){
    file_.open(fileName_, std::ios_base::app |
        std::ios_base::out | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    type_id id = ider_.nextID();
    std::string message = createMessage_(id, name, value);
    file_.seekp(0, std::ios_base::end);
    Logs::debug(std::to_string(message.size()).c_str());
    file_.write(message.c_str(), message.size());
    file_.close();
    ids_.insert(id);
}

std::string DataBank::getAll(){
    file_.open(fileName_, std::ios_base::in | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    file_.seekg(0, std::ios_base::beg);
    std::stringstream ss;
    std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
    std::string message;
    while(file_.peek() != EOF){
        file_.read(mes.get(), sizeMessage_);
        mes[sizeMessage_]='\0';
        message=std::string(mes.get());
        Logs::debug(message.c_str());
        Logs::debug(std::to_string(message.size()).c_str());
        size_t i;
        for(i=0; message[i]!=' '; ++i);
        ss << "ID: " << message.substr(0, i)
            << ' ';
        size_t len=0;
        for(i=50; message[i]!=' ' and len!=50; ++i, ++len);
        ss << "Name: " << message.substr(50, len)
            << ' ';
        for(i=100, len=0; message[i]!=' ' and len!=1024; ++i, ++len);
        ss << "Value: " << message.substr(100, len)
            << std::endl;
    }
    file_.close();
    return ss.str();
}

DataBank::DataBank(IDer ider): ider_(ider){
    fileName_= "resources/data_" + std::to_string(ider_.nextID()) + ".txt";
}