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

// General template for all 8 bit add operations
template <bool isInc>
void CPU::addTemplate8(Register reg) {

    Reg* targetReg;
    Value8 valToAdd;
    bool carryIn;

    if constexpr (isInc) targetReg = selectReg(reg);
    else targetReg = &reg_A;

    if constexpr (isInc) valToAdd = 1;
    else valToAdd = *selectReg(reg);

    if constexpr (isInc) carryIn = 0;
    else carryIn = flagCarry();

    Value16 newVal = *targetReg + valToAdd + carryIn;

    resetFlagSub();

    if ((*targetReg & 0xF) + (valToAdd & 0xF) + carryIn > 0xF) setFlagHCarry();
    else resetFlagHCarry();

    if constexpr (!isInc) {

        if (newVal >= 256) setFlagCarry();
        else resetFlagCarry();
    }

    *targetReg = static_cast<Value8>(newVal);

    if (*targetReg == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::ADC(Register reg) {

    addTemplate8<false>(reg);
}

void CPU::ADD(Register reg) {

    resetFlagCarry();
    addTemplate8<false>(reg);
}

void CPU::INC(Register reg) {

    addTemplate8<true>(reg);
}

template <bool isDec>
void CPU::subTemplate8(Register reg) {

    Reg* targetReg;
    Value8 valToSub;
    bool carryIn;

    if constexpr (isDec) targetReg = selectReg(reg);
    else targetReg = &reg_A;

    if constexpr (isDec) valToSub = 1;
    else valToSub = *selectReg(reg);

    if constexpr (isDec) carryIn = 0;
    else carryIn = flagCarry();

    setFlagSub();

    if ((valToSub & 0xF) + carryIn > (*targetReg & 0xF) ) setFlagHCarry();
    else resetFlagHCarry();

    if constexpr (!isDec) {

        if (valToSub + carryIn > *targetReg) setFlagCarry();
        else resetFlagCarry();
    }

    *targetReg -= valToSub + carryIn ;

    if (*targetReg == 0) setFlagZero();
    else resetFlagZero();
}

void CPU::SBC(Register reg) {

    subTemplate8<false>(reg);
}

void CPU::SUB(Register reg) {

    resetFlagCarry();
    subTemplate8<false>(reg);
}

void CPU::DEC(Register reg) {

    subTemplate8<true>(reg);
}

template <BitWiseOp op>
void CPU::bitwiseTemplate8(Register reg) {

    Reg* targetReg = selectReg(reg);

    if constexpr (op == BitWiseOp::AND) reg_A &= *targetReg;
    else if constexpr (op == BitWiseOp::OR) reg_A |= *targetReg;
    else if constexpr (op == BitWiseOp::XOR) reg_A ^= *targetReg;

    if constexpr (op == BitWiseOp::CP) {

        if (reg_A == *targetReg) setFlagZero();
        else resetFlagZero();

        setFlagSub();

        if ((*targetReg & 0xF) > (reg_A & 0xF) ) setFlagHCarry();
        else resetFlagHCarry();

        if (*targetReg > reg_A ) setFlagCarry();
        else resetFlagCarry();
    }
    else {

        if (reg_A == 0) setFlagZero();
        else resetFlagZero();

        resetFlagSub();
        resetFlagCarry();

        if constexpr (op == BitWiseOp::AND) setFlagHCarry();
        else resetFlagHCarry();
    }
}

void CPU::AND(Register reg) {

    bitwiseTemplate8<BitWiseOp::AND>(reg);
}

void CPU::OR(Register reg) {

    bitwiseTemplate8<BitWiseOp::OR>(reg);
}

void CPU::XOR(Register reg) {

   bitwiseTemplate8<BitWiseOp::XOR>(reg);
}

void CPU::CP(Register reg) {

    bitwiseTemplate8<BitWiseOp::CP>(reg);
}
