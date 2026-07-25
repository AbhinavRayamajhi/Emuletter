#include "CPU.hpp"

#include <cassert>

Value8 CPU::getVal8FromReg(Register target) {

    Value8 val = 0;

    switch (target) {

    case Register::A:
        val = reg_A;
        break;

    case Register::B:
        val = reg_B;
        break;

    case Register::C:
        val = reg_C;
        break;

    case Register::D:
        val = reg_D;
        break;

    case Register::E:
        val = reg_E;
        break;

    case Register::H:
        val = reg_H;
        break;
        
    case Register::L:
        val = reg_L;
        break;

    default:
        assert(0 && "Invalid Register for Op");
    }

    return val;
}

void CPU::setVal8ToReg(Register target, Value8 val) {


    switch (target) {

    case Register::A:
        reg_A = val;
        break;

    case Register::B:
        reg_B = val;
        break;

    case Register::C:
        reg_C = val;
        break;

    case Register::D:
        reg_D = val;
        break;

    case Register::E:
        reg_E = val;
        break;

    case Register::H:
        reg_H = val;
        break;
        
    case Register::L:
        reg_L = val;
        break;

    default:
        assert(0 && "Invalid Register for Op");
    }
}

void CPU::ADC(Register target) {

    Value8 val = getVal8FromReg(target);
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

    Value8 val = getVal8FromReg(target);
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

void CPU::INC(Register target) {

    Value8 val = getVal8FromReg(target);

    resetFlagSub();

    if ((val & 0xF) + 1 > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    setVal8ToReg(target, ++val);

    if (val == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::DEC(Register target) {

    Value8 val = getVal8FromReg(target);

    setFlagSub();

    if ((val & 0xF) == 0) setFlagHCarry();
    else resetFlagHCarry();

    setVal8ToReg(target, --val);

    if (val == 0) setFlagZero();
    else resetFlagZero();
}