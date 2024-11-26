//
// Created by sasor on 29.09.2024.
//

#include "DB.h"
#include "BC_Errors.h"
#include "ID.h"
#include <sstream>
#include <memory>
#include "Logs.h"

std::shared_ptr<char[]> DataBank::createMessage_(const type_id id, const std::string& name, const std::string& value) const{
    if(name.size() > 50 or value.size() > 1024){
        throw BC_longNameOrValueDB();
    }
    std::shared_ptr<char[]> message(new char[sizeMessage_+1]);
    std::string sID = std::to_string(id);
    for(size_t i = 0; i < sID.size(); i++){message[i] = sID[i];}
    for(size_t i = sID.size(); i < 50; ++i) {message[i] = ' ';}
    for(size_t i=50; i < (50+name.size()); ++i) {message[i] = name[i-50];}
    for(size_t i=50+name.size(); i < (100); ++i) {message[i] = ' ';}
    for(size_t i=100; i < (100+value.size()); ++i) {message[i] = value[i-100];}
    for(size_t i=100+value.size(); i < sizeMessage_; ++i) {message[i] = ' ';}
    message[sizeMessage_]='\0';
    return message;
}

void DataBank::add(const std::string& name, const std::string& value){
    file_.open(fileName_, std::ios_base::app |
        std::ios_base::out | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    type_id id = ider_.nextID();
    std::shared_ptr message= createMessage_(id, name, value);
    file_.seekp(0, std::ios_base::end);
    file_.write(message.get(), sizeMessage_);
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

bool DataBank::del(const type_id& id) {
    if(ids_.find(id) == ids_.end()) return false;
    std::string specName = "resources/del_"+std::to_string(id)+".txt";

    //copy
    {
        std::fstream file;
        file.open(fileName_, std::ios_base::in | std::ios_base::binary);
        if(!file.is_open()){
            throw BC_CanNotOpenFile(fileName_);
        }
        file.seekg(0, std::ios_base::beg);
        std::fstream specFile;
        specFile.open(specName, std::ios_base::out | std::ios_base::binary);
        if(!specFile.is_open()){
            throw BC_CanNotOpenFile(specName);
        }
        specFile.seekp(0, std::ios_base::beg);
        std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
        mes[sizeMessage_]='\0';
        while(file.peek() != EOF){
            file.read(mes.get(), sizeMessage_);
            specFile.write(mes.get(), sizeMessage_);
        }
        file.close();
        specFile.close();
    }

    std::fstream specFile;
    specFile.open(specName, std::ios_base::in | std::ios_base::binary);
    if(!specFile.is_open()){
        throw BC_CanNotOpenFile(specName);
    }
    file_.open(fileName_, std::ios_base::out | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    file_.seekp(0, std::ios_base::beg);
    specFile.seekg(0, std::ios_base::beg);
    std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
    std::string message;
    std::string idStr=std::to_string(id);
    while(specFile.peek() != EOF) {
        specFile.read(mes.get(), sizeMessage_);
        mes[sizeMessage_] = '\0';
        message = std::string(mes.get());
        size_t i;
        for(i=0; message[i]!=' '; ++i);
        if(message.substr(0, i) == idStr) {
            continue;
        } else {
            file_.write(mes.get(), sizeMessage_);
        }
    }
    file_.close();
    specFile.close();
#if __linux__
    std::system(("rm -rf " + specName).c_str());//Linux
#else
    //TODO Нормально сделать удаление
    //std::system(("del \"" + specName+"\"").c_str());//Windows
    specFile.open(specName, std::ios_base::out);
    if(!specFile.is_open()){
        throw BC_CanNotOpenFile(specName);
    }
    specFile.close();
    Logs::warning("Bad file deleter, del_*.txt");
#endif
    return true;
}

bool DataBank::update(const type_id& id,const std::string& newName, const std::string& newValue) {
    if(ids_.find(id) == ids_.end()) return false;
    std::string specName = "resources/upd_"+std::to_string(id)+".txt";

    //copy
    {
        std::fstream file;
        file.open(fileName_, std::ios_base::in | std::ios_base::binary);
        if(!file.is_open()){
            throw BC_CanNotOpenFile(fileName_);
        }
        file.seekg(0, std::ios_base::beg);
        std::fstream specFile;
        specFile.open(specName, std::ios_base::out | std::ios_base::binary);
        if(!specFile.is_open()){
            throw BC_CanNotOpenFile(specName);
        }
        specFile.seekp(0, std::ios_base::beg);
        std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
        mes[sizeMessage_]='\0';
        while(file.peek() != EOF){
            file.read(mes.get(), sizeMessage_);
            specFile.write(mes.get(), sizeMessage_);
        }
        file.close();
        specFile.close();
    }

    std::fstream specFile;
    specFile.open(specName, std::ios_base::in | std::ios_base::binary);
    if(!specFile.is_open()){
        throw BC_CanNotOpenFile(specName);
    }
    file_.open(fileName_, std::ios_base::out | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    file_.seekp(0, std::ios_base::beg);
    specFile.seekg(0, std::ios_base::beg);
    std::shared_ptr<char[]> mes(new char[sizeMessage_+1]);
    std::string message;
    std::string idStr=std::to_string(id);
    while(specFile.peek() != EOF) {
        specFile.read(mes.get(), sizeMessage_);
        mes[sizeMessage_] = '\0';
        message = std::string(mes.get());
        size_t i;
        for(i=0; message[i]!=' '; ++i);
        if(message.substr(0, i) == idStr) {
            mes = createMessage_(id, newName, newValue);
            file_.write(mes.get(), sizeMessage_);
        } else {
            file_.write(mes.get(), sizeMessage_);
        }
    }
    file_.close();
    specFile.close();
#if __linux__
    std::system(("rm -rf " + specName).c_str());//Linux
#else
    //TODO Нормально сделать удаление
    //std::system(("del \"" + specName+"\"").c_str());//Windows
    specFile.open(specName, std::ios_base::out);
    if(!specFile.is_open()){
        throw BC_CanNotOpenFile(specName);
    }
    specFile.close();
    Logs::warning("Bad file deleter, upd_*.txt");
#endif
    return true;
}

std::string DataBank::getAllWhereName(const std::string& name){
    file_.open(fileName_, std::ios_base::in | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    file_.seekg(0, std::ios_base::beg);
    std::stringstream ss;
    std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
    std::string message;
    std::string ID;
    std::string Name;
    while(file_.peek() != EOF){
        file_.read(mes.get(), sizeMessage_);
        mes[sizeMessage_]='\0';
        message=std::string(mes.get());
        size_t i;
        for(i=0; message[i]!=' '; ++i);
        ID=message.substr(0, i);
        size_t len=0;
        for(i=50; message[i]!=' ' and len!=50; ++i, ++len);
        Name=message.substr(50, len);
        if(Name == name) {
            ss<<"ID: "<<ID<<" Name: "<<Name<<" ";
            for(i=100, len=0; message[i]!=' ' and len!=1024; ++i, ++len);
            ss << "Value: " << message.substr(100, len)
               << std::endl;
        }
    }
    file_.close();
    return ss.str();
}

std::string DataBank::getAllWhereValue(const std::string& value) {
    file_.open(fileName_, std::ios_base::in | std::ios_base::binary);
    if(!file_.is_open()){
        throw BC_CanNotOpenFile(fileName_);
    }
    file_.seekg(0, std::ios_base::beg);
    std::stringstream ss;
    std::unique_ptr<char[]> mes(new char[sizeMessage_+1]);
    std::string message;
    std::string ID;
    std::string Name;
    std::string Value;
    while(file_.peek() != EOF){
        file_.read(mes.get(), sizeMessage_);
        mes[sizeMessage_]='\0';
        message=std::string(mes.get());
        size_t i;
        for(i=0; message[i]!=' '; ++i);
        ID=message.substr(0, i);
        size_t len=0;
        for(i=50; message[i]!=' ' and len!=50; ++i, ++len);
        Name=message.substr(50, len);
        for(i=100, len=0; message[i]!=' ' and len!=1024; ++i, ++len);
        Value=message.substr(100, len);
        if(Value == value) {
            ss<<"ID: "<<ID<<" Name: "<<Name<<
            " Value: " << Value << std::endl;
        }
    }
    file_.close();
    return ss.str();
}