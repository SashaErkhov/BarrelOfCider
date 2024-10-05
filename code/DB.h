//
// Created by sasor on 29.09.2024.
//

#ifndef BC_DB_H_2024
#define BC_DB_H_2024

#include <memory>
#include "ID.h"
#include <cstdint>
#include <string>
#include <map>
#include <vector>

class DataBank {

    class Table_;
    class Papers_;
    struct PartsOfTable_ {
        BC_ID idTable;
        std::uint8_t cntCol;
        std::vector<std::uint8_t> typesCol;
        std::vector<std::string> namesCol;
        type_id firstRow;// type_id объявлен в ID.h
    };

    std::map<std::string, PartsOfTable_> tables_;
    std::unique_ptr<Table_> actualTable_;

public:
    DataBank();
    void createTable(const std::string& nameTable, std::uint8_t cntCol,
                     const std::vector<std::uint8_t>& typesCol, const std::vector<std::string>& namesCol);
    void openTable(const std::string& nameTable);
    void closeTable();
    void addRow(std::shared_ptr<std::uint8_t[]> val, std::size_t lenRow);
    std::string getAllRows();
    std::string getAllRowsOfTable();
};

class DataBank::Table_ {
    std::string nameTable_;
    BC_ID id_;
    std::uint8_t cntCol_;
    std::vector<std::uint8_t> typesCol_;
    std::vector<std::string> namesCol_;
    std::size_t lenRow_;
    std::map<BC_ID, std::shared_ptr<std::uint8_t[]>> rows_;
public:
    Table_(const std::string& nameTable, BC_ID id, std::uint8_t cntCol, std::vector<std::uint8_t>& typesCol,
           std::vector<std::string>& namesCol, type_id firstRow);
    void addRow(std::shared_ptr<std::uint8_t[]> val, std::size_t lenRow);
};

class DataBank::Papers_ {
public:
    static std::map<BC_ID, std::shared_ptr<std::uint8_t[]>> download(
            type_id firstRow, BC_ID idTable, std::size_t lenRow);
    static void upload(BC_ID idRow, BC_ID idTable, std::shared_ptr<std::uint8_t[]> val,std::size_t lenRow);
};

#endif // ! BC_DB_H_2024
