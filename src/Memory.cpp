#include "Memory.hpp"

#include <cassert>

Value8* Memory::addressToMemory(Address address) {

    if (address < 0x4000) {

        return &cartridgeROMfixed[address];
    }
    else if (address < 0x8000) {

        return &cartridgeROMswitch[address - 0x4000];
    }
    else if (address < 0xA000) {

        return &VRAM[address - 0x8000];
    }
    else if (address < 0xC000) {

        return &externalRAM[address - 0xA000];
    }
    else if (address < 0xE000) {

        return &workRAM[address - 0XC000];
    }
    else if (address < 0xFE00) {

        return &workRAM[address - 0xE000];
    }
    else if (address < 0xFEA0) {

        return &OAM[address - 0xFE00];
    }
    else if (address < 0xFF00) {

        return nullptr;
    }
    else if (address < 0xFF80) {

        return &IOreg[address - 0xFF00];
    }
    else if (address < 0xFFFF) {

        return &highRAM[address - 0xFF80];
    }
    else if (address == 0xFFFF) {

        return &interruptEnable;
    }

    assert(0 && "Invalid address");
    return nullptr;
}


// nullptr handles both access to invalid section of memory and invalid address
Value8 Memory::readByteMem(Address address) {

    Value8* mem = addressToMemory(address);
    if (mem == nullptr) return 0;
    return *mem;
}

void Memory::writeByteMem(Address address, Value8 val) {

    Value8* mem = addressToMemory(address);
    if (mem == nullptr) return;
    *mem = val;
}