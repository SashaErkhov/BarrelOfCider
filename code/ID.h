//
// Created by sasor on 29.09.2024.
//

#ifndef BC_ID_H
#define BC_ID_H

#include <cstdint>
#include <string>

#define type_id std::uint32_t

class BC_ID {
    static type_id next_id_;
    type_id val_;
public:
    BC_ID() : val_(next_id_++) {}
    BC_ID(const BC_ID& other) : val_(other.val_) {}
    BC_ID& operator=(const BC_ID& other) {
        val_ = other.val_;
        return *this;
    }
    BC_ID(BC_ID&& other) : val_(other.val_) {}
    BC_ID& operator=(BC_ID&& other) {
        val_ = other.val_;
        return *this;
    }
    type_id get() const {return val_;}
    
    bool operator==(const BC_ID& other) const { return this->val_ == other.val_;}
    bool operator!=(const BC_ID& other) const{ return this->val_ != other.val_;}
    bool operator<(const BC_ID& other) const{ return this->val_ < other.val_;}
    bool operator>(const BC_ID& other) const{ return this->val_ > other.val_;}
    bool operator<=(const BC_ID& other) const{ return this->val_ <= other.val_;}
    bool operator>=(const BC_ID& other) const{ return this->val_ >= other.val_;}

    friend std::string to_string(const BC_ID& val);
};
type_id BC_ID::next_id_ = 1;

std::string to_string(const BC_ID& val) {return std::to_string(val.val_);}

#endif //BC_ID_H
