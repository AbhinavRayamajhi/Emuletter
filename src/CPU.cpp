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

Value16 CPU::getVal16(Source16 source) {

    switch (source) {

    case Source16::AF:
        return (static_cast<uint16_t>(reg_A) << 8) | reg_F;

    case Source16::BC:
        return (static_cast<uint16_t>(reg_B) << 8) | reg_C;

    case Source16::DE:
        return (static_cast<uint16_t>(reg_D) << 8) | reg_E;

    case Source16::HL:
        return (static_cast<uint16_t>(reg_H) << 8) | reg_L;

    case Source16::SP:
        return reg_SP;

    default:
        assert(0 && "Invalid Register for Op");
        return 0;
    }
}

void CPU::setVal16(Source16 source, Value16 val) {

    switch (source) {

    case Source16::AF:
        reg_A = static_cast<uint8_t>(val >> 8);
        reg_F = static_cast<uint8_t>(val);
        break;

    case Source16::BC:
        reg_B = static_cast<uint8_t>(val >> 8);
        reg_C = static_cast<uint8_t>(val);
        break;

    case Source16::DE:
        reg_D = static_cast<uint8_t>(val >> 8);
        reg_E = static_cast<uint8_t>(val);
        break;

    case Source16::HL:
        reg_H = static_cast<uint8_t>(val >> 8);
        reg_L = static_cast<uint8_t>(val);
        break;

    case Source16::SP:
        reg_SP = val;
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

void CPU::ADD_HL(Source16 reg) {

    Value16 valToAdd = getVal16(reg);
    Value16 target = getVal16(Source16::HL);
    Value32 res = target + valToAdd;

    setSub(false);
    setHCarry((target & 0xFFF) + (valToAdd & 0xFFF) > 0xFFF);
    setCarry(res >= 65536);

    setVal16(Source16::HL, static_cast<Value16>(res));
}

void CPU::ADD_SP(SValue8 val) {

    setZero(false);
    setSub(false);

    Value8 uVal = static_cast<Value8>(val);

    setHCarry((reg_SP & 0xF) + (uVal & 0xF) > 0xF);
    setCarry((reg_SP & 0xFF) + (uVal & 0xFF) > 0xFF);

    reg_SP += val;
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

    SBC(RAM->readByteMem(address));
}

void CPU::INC(Source8 source) {

    Value8 res = getVal(source);

    setHCarry((res & 0xF) + 1 > 0xF);

    res++;
    setVal(source, res);

    setZero(res == 0);
    setSub(false);
}

void CPU::INC(Address address) {

    Value8 res = RAM->readByteMem(address);

    setHCarry((res & 0xF) + 1 > 0xF);

    res++;
    RAM->writeByteMem(address, res);

    setZero(res == 0);
    setSub(false);
}

void CPU::INC(Source16 source) {

    setVal16(source, getVal16(source) + 1);
}

void CPU::DEC(Source8 source) {

    Value8 res = getVal(source);
    
    setHCarry((res & 0xF) == 0);

    res--;
    setVal(source, res);

    setZero(res == 0);
    setSub(true);
}

void CPU::DEC(Address address) {

    Value8 res = RAM->readByteMem(address);
    
    setHCarry((res & 0xF) == 0);

    res--;
    RAM->writeByteMem(address, res);

    setZero(res == 0);
    setSub(true);
}

void CPU::DEC(Source16 source) {

    setVal16(source, getVal16(source) - 1);
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

    AND(RAM->readByteMem(address));
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

void CPU::OR(Address address) {

    OR(RAM->readByteMem(address));
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

void CPU::XOR(Address address) {

    XOR(RAM->readByteMem(address));
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

void CPU::CP(Address address) {

    CP(RAM->readByteMem(address));
}

void CPU::LD8(Source8 dest, Value8 val) {

    setVal(dest, val);
}

void CPU::LD8(Source8 dest, Source8 source) {

    setVal(dest, getVal(source));
}

void CPU::LD8(Source8 dest, Address address) {

    setVal(dest, RAM->readByteMem(address));
}

void CPU::LD8(Address address, Source8 source) {

    RAM->writeByteMem(address, getVal(source));
}

void CPU::LD8(Address address, Value8 val) {

    RAM->writeByteMem(address, val);
}