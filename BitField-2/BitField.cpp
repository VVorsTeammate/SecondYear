#include "BitField.h"
#include "cstring"

BitField::BitField(size_t len = 10) {
    _sizeBit = len;
    _memSize = (len / (8 * sizeof(uint16_t))) + (len % (8 * sizeof(uint16_t)) != 0);
    _mem = new uint16_t[_memSize];
    std::memset(_mem, 0, _memSize);
}

BitField::BitField(const BitField& tmp) {
    _sizeBit = tmp._sizeBit;
    _memSize = tmp._memSize;
    _mem = new uint16_t[_memSize];
    std::memcpy(_mem, tmp._mem, _memSize * sizeof(uint16_t));
}

BitField& BitField::operator=(const BitField& tmp){
    if (_sizeBit != tmp._sizeBit){
        delete [] _mem;
        _sizeBit = tmp._sizeBit;
        _memSize = tmp._memSize;
        _mem = new uint16_t[_memSize];
    }
    std::memcpy(_mem, tmp._mem, _memSize * sizeof(uint16_t));
    return *this;
}

uint16_t BitField::GetMask(size_t n) const {
    return 1 << (n % (8 * sizeof(uint16_t)));
}

void BitField::SetBit(size_t n) {
    _mem[GetMemIndex(n)] |= GetMask(n);
}

size_t BitField::GetMemIndex(size_t n) const {
    if (n >= _sizeBit)
        throw "Bit out of range!";
    return n / (8 * sizeof(uint16_t));
}

uint8_t BitField::GetBit(size_t n) const {
    // if (n >= _sizeBit){
    //     throw "PSHNH Bit out of range";
    // }
    return ((_mem[GetMemIndex(n)] & GetMask(n)) != 0);
}

void BitField::ClrBit(size_t n){
    _mem[GetMemIndex(n)] &= ~GetMask(n);
}

BitField BitField::operator|(const BitField& tmp){ //размеры битовых полей могут быть разными
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] = _mem[i] | tmp._mem[i];;
    }
    return B;
}

BitField BitField::operator&(const BitField& tmp){ //размеры битовых полей могут быть разными
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] &= tmp._mem[i];
    }
    return B;
}

BitField BitField::operator^(const BitField& tmp){ //размеры битовых полей могут быть разными
    BitField B(*this);
    for (size_t i=0; i < _memSize; i++){
        B._mem[i] ^= tmp._mem[i];
    }
    return B;
}

bool BitField::operator==(const BitField& tmp) const{
    for(size_t i = 0; i < _memSize; i++){
        if(_mem[i] != tmp._mem[i]){
            return false;
        }
    }
    return true;
}

BitField BitField::operator~(){ //размеры битовых полей могут быть разными
    BitField copy(*this);
    for (size_t i=0; i < _sizeBit; i++){
        if (GetBit(i)){
            copy.ClrBit(i);
        }
        else{
            copy.SetBit(i);
        }
    }
    return copy;
}