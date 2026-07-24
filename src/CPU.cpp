#include "CPU.hpp"

#include <cassert>

void CPU::ADD_A(Register target) {

    Value8 res = 0;

    switch (target) {

    case Register::A:
        res = reg_A;
        break;

    case Register::B:
        res = reg_B;
        break;

    case Register::C:
        res = reg_C;
        break;

    case Register::D:
        res = reg_D;
        break;

    case Register::E:
        res = reg_E;
        break;

    case Register::H:
        res = reg_H;
        break;
        
    case Register::L:
        res = reg_L;
        break;

    case Register::HL:
        //TODO
        break;
    default:
        assert(0 && "Invalid Register for ADD op");
    }

    Value16 newVal = reg_A + res;

    resetFlagSub();

    if (newVal >= 256) setFlagCarry();
    else resetFlagCarry();

    if ((reg_A & 0xF) + (res & 0xF) > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    reg_A = static_cast<Value8>(newVal);

    if (reg_A == 0) setFlagZero();
    else resetFlagZero();
}