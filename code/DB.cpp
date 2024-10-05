//
// Created by sasor on 29.09.2024.
//

#include "DB.h"
#include "BC_Errors.h"

DataBank::DataBank() {
    actualTable_ = nullptr;
}

void DataBank::createTable(const std::string& nameTable, std::uint8_t cntCol,
                 const std::vector<std::uint8_t>& typesCol,
                 const std::vector<std::string>& namesCol) {
    if(nameTable.size() > 50 or cntCol==0) throw BC_InvalidLength(nameTable);
    for(auto p: namesCol){
        if(p.size()>50) throw BC_InvalidLength(nameTable);
    }
    std::uint8_t cnt=cntCol;
    std::size_t cntNames=namesCol.size();
     for(auto p: typesCol){
         if(p<=11){
             --cnt;
             --cntNames;
             if(p==2) {++p;} // String
         } else {
             throw BC_InvalidCreateType(nameTable,typesCol);
         }
     }
    if( cnt != 0 and cntNames!=0 ) throw BC_InvalidCreateCntCol(nameTable,cntCol, typesCol.size(), namesCol.size());

    PartsOfTable_ now={{},cntCol, typesCol, namesCol,0};
    tables_[nameTable]=now;
    openTable(nameTable);
}

void DataBank::openTable(const std::string& nameTable) {
    if(auto it=tables_.find(nameTable); it==tables_.end()){
        throw BC_TableNotFound(nameTable);
    } else {
        closeTable();
        PartsOfTable_ now = it->second;
        actualTable_ = std::make_unique<Table_>(nameTable, now.idTable, now.cntCol, now.typesCol,
                                                now.namesCol,now.firstRow);
    }
}

void DataBank::closeTable() {
    actualTable_.reset(nullptr);
}

void DataBank::addRow(std::shared_ptr<std::uint8_t[]> val, std::size_t lenRow) {
    if(actualTable_.get()==nullptr){
        throw BC_TableNotOpen();
    }
    actualTable_->addRow(val, lenRow);
}

DataBank::Table_::Table_(const std::string& nameTable, BC_ID id, std::uint8_t cntCol, std::vector<std::uint8_t>& typesCol,
                         std::vector<std::string>& namesCol, type_id firstRow):
    id_(id), cntCol_(cntCol), typesCol_(typesCol), namesCol_(namesCol), nameTable_(nameTable)
{
    lenRow_=0;
    for(std::uint8_t i=0; i<cntCol_; ++i) {
        switch(typesCol_[i]) {
            case 0: {++lenRow_; break;} // Bool
            case 1: {++lenRow_; break;} // Char
            case 2: {
                lenRow_+=typesCol_[++i]; // Длина строки
                break;
            }// String
            case 3: {++lenRow_; break;} // Int8
            case 4: {lenRow_+=2; break;} // Int16
            case 5: {lenRow_+=4; break;} // Int32
            case 6: {lenRow_+=8; break;} // Int64
            case 7: {++lenRow_; break;} // Uint8
            case 8: {lenRow_+=2; break;} // Uint16
            case 9: {lenRow_+=4; break;} // Uint32
            case 10:{lenRow_+=8; break;} // Uint64
            case 11:{lenRow_+=6; break;} // DataTime
            default: throw BC_IvalidTypeCreateTable(id, typesCol[i]);
            }
    }
    if(firstRow != 0) {
        rows_=Papers_::download(firstRow, id_, lenRow_);
    }
}

void DataBank::Table_::addRow(std::shared_ptr<std::uint8_t[]> val, std::size_t lenRow) {
    if(lenRow!=lenRow_) { throw BC_InvalidLengthAddRow();}
    BC_ID id={};
    Papers_::upload(id, id_, val, lenRow);
    rows_[id]=val;
}