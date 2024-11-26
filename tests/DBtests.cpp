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
            //Logs::debug(std::to_string(i).c_str());
        }
        EXPECT_EQ(db.getAll(), ss.str());
    }
}

TEST(DBtests, del) {
    cleanFile();
    IDer ider;
    DataBank db(ider);
    db.add("1", "1");
    db.add("2", "2");
    db.add("3", "3");
    db.add("4", "4");
    db.add("5", "5");
    db.add("6", "6");
    std::stringstream ss;
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.del(1);
    ss.str("");
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.del(6);
    ss.str("");
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.del(4);
    ss.str("");
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.del(3);
    ss.str("");
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
}

TEST(DBtests, update) {
    cleanFile();
    IDer ider;
    DataBank db(ider);
    db.add("1", "1");
    db.add("2", "2");
    db.add("3", "3");
    db.add("4", "4");
    db.add("5", "5");
    db.add("6", "6");
    std::stringstream ss;
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(1, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(2, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(3, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 3 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(4, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 3 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 4 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(5, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 3 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 4 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    db.update(6, "5", "5");
    ss.str("");
    ss<<"ID: 1 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 2 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 3 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 4 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 5 Value: 5" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
}

TEST(DBtests, getAllWhereName) {
    cleanFile();
    IDer ider;
    DataBank db(ider);
    db.add("1", "1");
    db.add("2", "2");
    db.add("1", "3");
    db.add("1", "4");
    db.add("5", "5");
    db.add("1", "6");
    std::stringstream ss;
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 1 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 1 Value: 4" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 1 Value: 6" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    ss.str("");
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 3 Name: 1 Value: 3" << std::endl;
    ss<<"ID: 4 Name: 1 Value: 4" << std::endl;
    ss<<"ID: 6 Name: 1 Value: 6" << std::endl;
    EXPECT_EQ(db.getAllWhereName("1"), ss.str());
}

TEST(DBtests, getAllWhereValue) {
    cleanFile();
    IDer ider;
    DataBank db(ider);
    db.add("1", "1");
    db.add("2", "2");
    db.add("3", "1");
    db.add("4", "1");
    db.add("5", "5");
    db.add("6", "1");
    std::stringstream ss;
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 2 Name: 2 Value: 2" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 1" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 1" << std::endl;
    ss<<"ID: 5 Name: 5 Value: 5" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 1" << std::endl;
    EXPECT_EQ(db.getAll(), ss.str());
    ss.str("");
    ss<<"ID: 1 Name: 1 Value: 1" << std::endl;
    ss<<"ID: 3 Name: 3 Value: 1" << std::endl;
    ss<<"ID: 4 Name: 4 Value: 1" << std::endl;
    ss<<"ID: 6 Name: 6 Value: 1" << std::endl;
    EXPECT_EQ(db.getAllWhereValue("1"), ss.str());
}