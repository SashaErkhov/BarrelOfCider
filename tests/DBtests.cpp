//
// Created by sasor on 22.11.2024.
//
#include <gtest/gtest.h>
#include "../code/DB.h"
#include "../code/Logs.h"

void cleanFile() {
    std::fstream file;
    file.open("resources/data_0.txt", std::ios_base::out);
    file.close();
}

TEST(DBtests, addAndGetAll) {
    {
        cleanFile();
        IDer ider;
        DataBank db(ider);
        db.add("1", "1");
        std::stringstream ss;
        ss << "ID: 1 Name: 1 Value: 1" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add("2","2");
        ss << "ID: 2 Name: 2 Value: 2" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add("3","3");
        ss << "ID: 3 Name: 3 Value: 3" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add("4","4");
        ss << "ID: 4 Name: 4 Value: 4" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add("5","5");
        ss << "ID: 5 Name: 5 Value: 5" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
    }
    {
        cleanFile();
        IDer ider;
        DataBank db(ider);
        std::string name;
        name.reserve(50);
        for(size_t i=0;i<50;++i) {name.push_back('1');}
        Logs::debug(name.c_str());
        Logs::debug(std::to_string(name.size()).c_str());
        db.add(name, "1");
        db.add(name, "2");
        db.add(name, "3");
        std::stringstream ss;
        ss<<"ID: 1 Name: "<<name<<" Value: 1" << std::endl;
        ss<<"ID: 2 Name: "<<name<<" Value: 2" << std::endl;
        ss<<"ID: 3 Name: "<<name<<" Value: 3" << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add("4", name);
        ss<<"ID: 4 Name: 4 Value: "<<name << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add(name, name);
        ss<<"ID: 5 Name: "<<name<<" Value: "<<name << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        std::string value;
        value.reserve(1024);
        for(size_t i=0;i<1024;++i) {value.push_back('1');}
        db.add("6", value);
        ss<<"ID: 6 Name: 6 Value: "<<value << std::endl;
        EXPECT_EQ(db.getAll(), ss.str());
        db.add(name, value);
        ss<<"ID: 7 Name: "<<name<<" Value: "<<value << std::endl;
        Logs::debug(ss.str().c_str());
        EXPECT_EQ(db.getAll(), ss.str());
    }
    {
        cleanFile();
        IDer ider;
        std::string value;
        value.reserve(1024);
        for(size_t i=0;i<1024;++i) {value.push_back('1');}
        std::string name;
        name.reserve(50);
        for(size_t i=0;i<50;++i) {name.push_back('1');}
        DataBank db(ider);
        std::stringstream ss;
        for(std::uint64_t i=1;i<102;++i) {
            db.add(name, value);
            ss<<"ID: "<<i<<" Name: "<<name<<" Value: "<<value << std::endl;
            EXPECT_EQ(db.getAll(), ss.str());
            //Logs::info(std::to_string(i).c_str());
        }
        EXPECT_EQ(db.getAll(), ss.str());
    }
}