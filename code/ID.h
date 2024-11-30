//server and client

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
    type_id nextID() noexcept {return nextId_++;}
};

#endif // ! BC_ID_H