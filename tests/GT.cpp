#include <string>
#include <iostream>
#include "DB.h"

int main()
{
    std::fstream file;
    file.open("resources/data_0.txt", std::ios_base::out);
    file.close();
    IDer ider;
    DataBank db(ider);
    db.add("1", "1");
    db.add("2", "2");
    db.add("3", "3");
    db.add("4", "4");
    db.add("5", "5");
    std::cout << db.getAll();
    return 0;
}