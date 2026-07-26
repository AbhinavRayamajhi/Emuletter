#pragma once

#include "Types.hpp"

class Memory {

public:

    Value8 readByteMem(Address address);
    void writeByteMem(Address address, Value8 val);

private:

    Value8 cartridgeROMfixed[0x4000];
    Value8 cartridgeROMswitch[0x4000];
    Value8 VRAM[0x2000];
    Value8 externalRAM[0x2000];
    Value8 workRAM[0x2000];
    Value8 OAM[0x00A0];
    Value8 IOreg[0x0080];
    Value8 highRAM[0x007F];
    Value8 interruptEnable;

    Value8* addressToMemory(Address address);
};