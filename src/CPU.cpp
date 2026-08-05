#include "CPU.hpp"

#include <cassert>

Value8 CPU::getVal(Source8 source) {

    switch (source) {

    case Source8::A:
        return reg_A;

    case Source8::B:
        return reg_B;

    case Source8::C:
        return reg_C;

    case Source8::D:
        return reg_D;

    case Source8::E:
        return reg_E;

    case Source8::H:
        return reg_H;
        
    case Source8::L:
        return reg_L;

    default:
        assert(0 && "Invalid Register for Op");
        return 0;
    }
}

void CPU::setVal(Source8 source, Value8 val) {

    switch (source) {

    case Source8::A:
        reg_A = val;
        break;

    case Source8::B:
        reg_B = val;
        break;

    case Source8::C:
        reg_C = val;
        break;

    case Source8::D:
        reg_D = val;
        break;

    case Source8::E:
        reg_E = val;
        break;

    case Source8::H:
        reg_H = val;
        break;

    case Source8::L:
        reg_L = val;
        break;

    default:
        assert(0 && "Invalid Register for Op");
    }
}

void CPU::ADD(Value8 valToAdd) {

    Value16 res = reg_A + valToAdd;

    setZero(res == 0);
    setSub(false);
    setHCarry((reg_A & 0xF) + (valToAdd & 0xF) > 0xF);
    setCarry(res >= 256);

    reg_A = static_cast<Value8>(res);
}

void CPU::ADD(Source8 source) {

    ADD(getVal(source));
}

void CPU::ADD(Address address) {

    ADD(RAM->readByteMem(address));
}

void CPU::ADC(Value8 valToAdd) {
    
    Value16 res = reg_A + valToAdd + flagCarry();

    setZero(res == 0);
    setSub(false);
    setHCarry((reg_A & 0xF) + (valToAdd & 0xF) + flagCarry() > 0xF);
    setCarry(res >= 256);

    reg_A = static_cast<Value8>(res);
}

void CPU::ADC(Source8 source) {

    ADC(getVal(source));
}

void CPU::ADC(Address address) {

    ADC(RAM->readByteMem(address));
}

void CPU::SUB(Value8 valToSub) {

    setSub(true);
    setHCarry((valToSub & 0xF) > (reg_A & 0xF));
    setCarry(valToSub > reg_A);

    reg_A -= valToSub;

    setZero(reg_A == 0);
}

void CPU::SUB(Source8 source) {
    
    SUB(getVal(source));
}

void CPU::SUB(Address address) {

    SUB(RAM->readByteMem(address));
}

void CPU::SBC(Value8 valToSub) {

    setSub(true);
    setHCarry((valToSub & 0xF) + flagCarry() > (reg_A & 0xF));
    setCarry(valToSub + flagCarry() > reg_A);

    reg_A -= valToSub + flagCarry();

    setZero(reg_A == 0);
}

void CPU::SBC(Source8 source) {

    SBC(getVal(source));
}

void CPU::SBC(Address address) {

    SUB(RAM->readByteMem(address));
}

void CPU::INC(Source8 source) {

    Value8 res = getVal(source);

    setHCarry((res & 0xF) + 1 > 0xF);

    res++;
    setVal(source, res);

    setZero(res == 0);
    setSub(false);
}

void CPU::DEC(Source8 source) {

    Value8 res = getVal(source);
    
    setHCarry((res & 0xF) == 0);

    res--;
    setVal(source, res);

    setZero(res == 0);
    setSub(true);
}

void CPU::AND(Value8 val) {

    reg_A &= val;

    setZero(reg_A == 0);
    setSub(false);
    setHCarry(true);
    setCarry(false);
}

void CPU::AND(Source8 source) {

    AND(getVal(source));
}

void CPU::AND(Address address) {

    AND(RAM->)
}

void CPU::OR(Value8 val) {

    reg_A |= val;

    setZero(reg_A == 0);
    setSub(false);
    setHCarry(false);
    setCarry(false);
}

void CPU::OR(Source8 source) {

    OR(getVal(source));
}

void CPU::XOR(Value8 val) {

    reg_A ^= val;

    setZero(reg_A == 0);
    setSub(false);
    setHCarry(false);
    setCarry(false);
}

void CPU::XOR(Source8 source) {

    XOR(getVal(source));
}

void CPU::CP(Value8 val) {

    setZero(reg_A == val);
    setSub(true);
    setHCarry((val & 0xF) > (reg_A & 0xF));
    setCarry(val > reg_A);
}

void CPU::CP(Source8 source) {

    CP(getVal(source));
}
