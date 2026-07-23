#pragma once

#include <cstdint>

class CPU {

public:

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
    inline bool flagZero()      { return reg_F & 0x80; }
    inline bool flagSubtract()  { return reg_F & 0x40; }
    inline bool flagHalfCarry() { return reg_F & 0x20; }
    inline bool flagCarry()     { return reg_F & 0x10; }

private:
    
    uint8_t reg_A = 0;
    uint8_t reg_B = 0;
    uint8_t reg_C = 0;
    uint8_t reg_D = 0;
    uint8_t reg_E = 0;
    uint8_t reg_F = 0;
    uint8_t reg_H = 0;
    uint8_t reg_L = 0;
};