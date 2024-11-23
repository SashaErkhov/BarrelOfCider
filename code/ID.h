//
// Created by sasor on 29.09.2024.
//

#pragma once
#ifndef BC_ID_H
#define BC_ID_H

#include <cstdint>
#include <string>

#define type_id std::uint32_t

class IDer {
    type_id nextId_;
public:
    IDer(): nextId_(0){}
    type_id nextID() {return nextId_++;}
};

#endif // ! BC_ID_H