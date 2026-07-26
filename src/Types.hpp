#pragma once

using Reg = uint8_t;

using Value8 = uint8_t;
using Value16 = uint16_t;

using Address = uint16_t;

enum class Register {
    A, B, C, D, E, F, H, L
};

enum class Instructions {
    ADD, SUB, ADC, SBC
};