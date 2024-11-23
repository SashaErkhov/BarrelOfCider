//
// Created by sasor on 29.09.2024.
//

#pragma once
#ifndef BC_DB_H_2024
#define BC_DB_H_2024

#include <string>
#include "ID.h"
#include <set>
#include <fstream>

class DataBank {
    IDer ider_;
    std::set<type_id> ids_;
    std::fstream file_;
    const std::size_t sizeMessage_=50+50+1024;
    std::string fileName_;

    std::string createMessage_(type_id id, const std::string& name,
                               const std::string& value) const;
public:
    DataBank(IDer ider);

    //TODO оптимизировать add
    void add(const std::string& name, const std::string& value);
    void del(const type_id& id);
    void update(const type_id& id,const std::string& newName, const std::string& newValue);
    std::string getAll();
    std::string getAllWhereName(const std::string& name) const;
    std::string getAllWhereValue(const std::string& value) const;
};

#endif // ! BC_DB_H_2024
