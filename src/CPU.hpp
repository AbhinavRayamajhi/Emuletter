#pragma once

#include "Types.hpp"
#include "Memory.hpp"

class CPU {

public:

    // Each CPU needs a pointer to memory so no default construction
    CPU() = delete;
    CPU(Memory* mem) : RAM(mem) {}

    // 8 bit registers
    Value8 getVal(Source8 source);
    void setVal(Source8 source, Value8 val);

    // 16 bit registers
    inline Value16 getPC() { return reg_PC; }
    inline void setPC(Value16 val) { reg_PC = val; }

    inline Value16 getSP() { return reg_SP; }
    inline void setSP(Value16 val) { reg_SP = val; }

    // Combined virtual 16 bit registers
    Value16 getVal16(Source16 source);
    void setVal16(Source16 source, Value16 val);

    // Flag register (F)
    inline bool flagZero()   { return reg_F & 0x80; }
    inline bool flagSub()    { return reg_F & 0x40; }
    inline bool flagHCarry() { return reg_F & 0x20; }
    inline bool flagCarry()  { return reg_F & 0x10; }

    inline void setZero(bool res) {
        if (res) reg_F |= 0x80;
        else reg_F &= 0x7F; 
    }

    inline void setSub(bool res) {
        if (res) reg_F |= 0x40;
        else reg_F &= 0xBF;
    }

    inline void setHCarry(bool res) {
        if (res) reg_F |= 0x20;
        else reg_F &= 0xDF; 
    }

    inline void setCarry(bool res) {
        if (res) reg_F |= 0x10;
        else reg_F &= 0xEF;
    }
    
    // Instructions 
    void ADD(Value8 valToAdd);
    void ADD(Source8 reg);
    void ADD(Address address);
    void ADD_HL(Source16 reg);
    void ADD_SP(SValue8 val);

    void ADC(Value8 valToAdd);
    void ADC(Source8 reg);
    void ADC(Address address);

    void SUB(Value8 valToSub);
    void SUB(Source8 reg);
    void SUB(Address address);

    void SBC(Value8 valToSub);
    void SBC(Source8 reg);
    void SBC(Address address);

    void INC(Source8 reg);
    void INC(Address address);
    void INC(Source16 source);

    void DEC(Source8 reg);
    void DEC(Address address);
    void DEC(Source16 source);

    void AND(Value8 val);
    void AND(Source8 reg);
    void AND(Address address);

    void OR(Value8 val);
    void OR(Source8 reg);
    void OR(Address address);

    void XOR(Value8 val);
    void XOR(Source8 reg);
    void XOR(Address address);

    void CP(Value8 val);
    void CP(Source8 reg);
    void CP(Address address);

    void LD8(Source8 dest, Value8 val);
    void LD8(Source8 dest, Source8 source);
    void LD8(Source8 dest, Address address);
    void LD8(Address address, Source8 source);
    void LD8(Address address, Value8 val);

private:
    
    Reg8 reg_A = 0;
    Reg8 reg_B = 0;
    Reg8 reg_C = 0;
    Reg8 reg_D = 0;
    Reg8 reg_E = 0;
    Reg8 reg_F = 0;
    Reg8 reg_H = 0;
    Reg8 reg_L = 0;

    Reg16 reg_PC = 0;
    Reg16 reg_SP = 0;

    Memory* RAM;
};