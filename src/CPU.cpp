#include "CPU.hpp"

#include <cassert>

Reg* CPU::selectReg(Register target) {


    switch (target) {

    case Register::A:
        return &reg_A;

    case Register::B:
        return &reg_B;

    case Register::C:
        return &reg_C;

    case Register::D:
        return &reg_D;

    case Register::E:
        return &reg_E;

    case Register::H:
        return &reg_H;
        
    case Register::L:
        return &reg_L;

    default:
        assert(0 && "Invalid Register for Op");
        return nullptr;
    }
}

void CPU::ADC(Register target) {

    Value8 val = *selectReg(target);
    bool carryIn = flagCarry();

    Value16 newVal = reg_A + val + carryIn;

    resetFlagSub();

    if ((reg_A & 0xF) + (val & 0xF) + carryIn > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    if (newVal >= 256) setFlagCarry();
    else resetFlagCarry();

    reg_A = static_cast<Value8>(newVal);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::SBC(Register target) {

    Value8 val = *selectReg(target);
    bool carryIn = flagCarry();

    setFlagSub();

    if ((val & 0xF) + carryIn > (reg_A & 0xF) ) setFlagHCarry();
    else resetFlagHCarry();

    if (val + carryIn > reg_A ) setFlagCarry();
    else resetFlagCarry();

    reg_A -= val + carryIn ;

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::ADD8(Register target) {

    resetFlagCarry();
    ADC(target);
}

void CPU::SUB8(Register target) {

    resetFlagCarry();
    SBC(target);
}

void CPU::INC8(Register target) {

    Reg* regToMod = selectReg(target);

    resetFlagSub();

    if ((*regToMod & 0xF) + 1 > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    *regToMod += 1;

    if (*regToMod == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::DEC8(Register target) {

    Reg* regToMod = selectReg(target);

    setFlagSub();

    if ((*regToMod & 0xF) == 0) setFlagHCarry();
    else resetFlagHCarry();

    *regToMod -= 1;

    if (*regToMod == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::AND(Register target) {

    reg_A &= *selectReg(target);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();

    resetFlagSub();
    setFlagHCarry();
    resetFlagCarry();
}

void CPU::OR(Register target) {

    reg_A |= *selectReg(target);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();

    resetFlagSub();
    resetFlagHCarry();
    resetFlagCarry();
}

void CPU::XOR(Register target) {

    reg_A ^= *selectReg(target);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();

    resetFlagSub();
    resetFlagHCarry();
    resetFlagCarry();
}

void CPU::CP(Register target) {

    Value8 val = *selectReg(target);

    if (reg_A == val) setFlagZero();
    else resetFlagZero();

    setFlagSub();

    if ((val & 0xF) > (reg_A & 0xF) ) setFlagHCarry();
    else resetFlagHCarry();

    if (val > reg_A ) setFlagCarry();
    else resetFlagCarry();
}
