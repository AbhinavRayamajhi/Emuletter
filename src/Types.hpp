#pragma once

#include <cstdint>

using Reg8 = uint8_t;
using Reg16 = uint16_t;

using Value8 = uint8_t;
using Value16 = uint16_t;
using Value32 = uint32_t;

using SValue8 = int8_t;

using Address = uint16_t;

enum class Source8 {
    A, B, C, D, E, F, H, L
};

enum class Source16 {
    AF, BC, DE, HL, SP
};

