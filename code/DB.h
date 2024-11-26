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
#include <memory>

class DataBank {
    IDer ider_;
    std::set<type_id> ids_;
    std::fstream file_;
    const std::size_t sizeMessage_=50+50+1024;
    std::string fileName_;

    std::shared_ptr<char[]> createMessage_(type_id id, const std::string& name,
                               const std::string& value) const;
public:
    explicit DataBank(IDer ider);

    void add(const std::string& name, const std::string& value);
    bool del(const type_id& id);
    bool update(const type_id& id,const std::string& newName, const std::string& newValue);
    std::string getAll();
    std::string getAllWhereName(const std::string& name);
    std::string getAllWhereValue(const std::string& value);
};

#endif // ! BC_DB_H_2024
