#include "Set.h"
#include <cmath>


Set::Set(size_t mp) : _bitField(mp), _maxPower(mp){
}

Set::Set(const Set& set) : _bitField(set._bitField), _maxPower(set._maxPower){
}

Set::Set(const BitField& bf)  : _bitField(bf), _maxPower(bf.GetLength()){
}

size_t Set::GetMaxPower(void) const{
    return _maxPower;
}

void Set::InsElem(uint64_t elem){ //Проверка нужна
    _bitField.SetBit(elem);
}

void Set::DelElem(uint64_t elem){ //Проверка нужна
    _bitField.ClrBit(elem);
}

bool Set::IsMember(uint64_t elem) const{
    return _bitField.GetBit(elem);
}

std::vector<uint64_t> Set::GetPrimary(){
    std::vector<uint64_t> res;
    res.push_back(1);
    Set tmp(*this);
    size_t n = tmp.GetMaxPower(); //static_cast<size_t> (sqrt(n))
    size_t i = 2;
    while(i <= static_cast<size_t> (sqrt(n))){
        if(tmp._bitField.GetBit(i)){
            for(size_t j = i+i; j < n; j +=i){
                tmp._bitField.ClrBit(j);
            }
        }
        if(tmp._bitField.GetBit(i)){
            res.push_back(i);
        }
        i++;
    }
    for(size_t i = static_cast<size_t> (sqrt(n)) + 1; i < n; i++){
        if(tmp._bitField.GetBit(i)){
            res.push_back(i);
        }
    }
    return res;
}


bool Set::operator==(const Set &s) const{
    return (s._bitField == _bitField);
}

bool Set::operator!= (const Set &s) const{
    return !(_bitField == s._bitField);
}
Set& Set::operator=(const Set &s){
    _maxPower = s._maxPower;
    _bitField = s._bitField;
    return *this;
}
Set Set::operator+ (const uint64_t Elem){
    Set res(*this);
    res.InsElem(Elem);
    return res;
}
                                  
Set Set::operator- (const uint64_t Elem){
    Set res(*this);
    res.DelElem(Elem);
    return res;
}
                                   
Set Set::operator+ (const Set &s){
    BitField tmp(this->_bitField | s._bitField);
    Set res(tmp);
    return res;
}
Set Set::operator* (const Set &s){
    BitField tmp(this->_bitField & s._bitField);
    Set res(tmp);
    return res;
}
Set Set::operator~ (){
    return Set(~_bitField);
}