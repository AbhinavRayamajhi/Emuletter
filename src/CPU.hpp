#pragma once

#include <cstdint>

#include "Types.hpp"
#include "Memory.hpp"

class CPU {

public:

    // Each CPU needs a pointer to memory so no default construction
    CPU() = delete;
    CPU(Memory* mem) : RAM(mem) {}

    // 8 bit registers
    inline uint8_t getA()         { return reg_A; }
    inline void setA(uint8_t val) { reg_A = val; }

    inline uint8_t getB()         { return reg_B; }
    inline void setB(uint8_t val) { reg_B = val; }

    inline uint8_t getC()         { return reg_C; }
    inline void setC(uint8_t val) { reg_C = val; }

    inline uint8_t getD()         { return reg_D; }
    inline void setD(uint8_t val) { reg_D = val; }

    inline uint8_t getE()         { return reg_E; }
    inline void setE(uint8_t val) { reg_E = val; }

    inline uint8_t getF()         { return reg_F; }
    inline void setF(uint8_t val) { reg_F = val; }

    inline uint8_t getH()         { return reg_H; }
    inline void setH(uint8_t val) { reg_H = val; }

    inline uint8_t getL()         { return reg_L; }
    inline void setL(uint8_t val) { reg_L = val;  }

    // Combined virtual 16 bit registers
    inline uint16_t getAF() {
        return (static_cast<uint16_t>(reg_A) << 8) | reg_F;
    }
    inline void setAF(uint16_t val) {
        reg_A = static_cast<uint8_t>(val >> 8);
        reg_F = static_cast<uint8_t>(val);
    }

    inline uint16_t getBC() {
        return (static_cast<uint16_t>(reg_B) << 8) | reg_C;
    }
    inline void setBC(uint16_t val) { reg_B = static_cast<uint8_t>(val >> 8);
        reg_C = static_cast<uint8_t>(val);
    }

    inline uint16_t getDE() {
        return (static_cast<uint16_t>(reg_D) << 8) | reg_E;
    }
    inline void setDE(uint16_t val) {
        reg_D = static_cast<uint8_t>(val >> 8);
        reg_E = static_cast<uint8_t>(val);
    }

    inline uint16_t getHL() {
        return (static_cast<uint16_t>(reg_H) << 8) | reg_L;
    }
    inline void setHL(uint16_t val) {
        reg_H = static_cast<uint8_t>(val >> 8);
        reg_L = static_cast<uint8_t>(val);
    }

    // Flag register (F)
    inline bool flagZero()   { return reg_F & 0x80; }
    inline bool flagSub()    { return reg_F & 0x40; }
    inline bool flagHCarry() { return reg_F & 0x20; }
    inline bool flagCarry()  { return reg_F & 0x10; }

    inline void setFlagZero()   { reg_F |= 0x80; }
    inline void setFlagSub()    { reg_F |= 0x40; }
    inline void setFlagHCarry() { reg_F |= 0x20; }
    inline void setFlagCarry()  { reg_F |= 0x10; }

    inline void resetFlagZero()   { reg_F &= 0x7F; }
    inline void resetFlagSub()    { reg_F &= 0xBF; }
    inline void resetFlagHCarry() { reg_F &= 0xDF; }
    inline void resetFlagCarry()  { reg_F &= 0xEF; }
    
    // Instructions
    void ADC(Register reg);
    void SBC(Register reg);
    
    void ADD(Register reg);
    void SUB(Register reg);

    void INC(Register reg);
    void DEC(Register reg);

    void AND(Register reg);
    void OR(Register reg);
    void XOR(Register reg);
    void CP(Register reg);

    void ADC_HL();
    void SBC_HL();
    
    void ADD8_HL();
    void SUB8_HL();

    void AND_HL();
    void OR_HL();
    void XOR_HL();
    void CP_HL();

private:
    
    Reg reg_A = 0;
    Reg reg_B = 0;
    Reg reg_C = 0;
    Reg reg_D = 0;
    Reg reg_E = 0;
    Reg reg_F = 0;
    Reg reg_H = 0;
    Reg reg_L = 0;

    Memory* RAM;

    Reg* CPU::selectReg(Register target);

    template <bool isInc>
    void CPU::addTemplate8(Register reg);

    template <bool isDec>
    void CPU::subTemplate8(Register reg);

    template <BitWiseOp op>
    void CPU::bitwiseTemplate8(Register reg);
};