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

void CPU::ADD_A(Register target) {

    Value8 val = getVal8FromReg(target);

    Value16 newVal = reg_A + val;

    resetFlagSub();

    if (newVal >= 256) setFlagCarry();
    else resetFlagCarry();

    if ((reg_A & 0xF) + (val & 0xF) > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    reg_A = static_cast<Value8>(newVal);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::SUB_A(Register target) {

    Value8 val = getVal8FromReg(target);

    setFlagSub();

    if (val > reg_A) setFlagCarry();
    else resetFlagCarry();

    if ((val & 0xF) > (reg_A & 0xF)) setFlagHCarry();
    else resetFlagHCarry();

    reg_A -= val;

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();
}