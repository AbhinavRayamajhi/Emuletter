#pragma once

using Value8 = uint8_t;
using Value16 = uint16_t;

enum class Register {
    A, B, C, D, E, F, H, L
};

enum class Instructions {
    ADD, SUB, ADC, SBC
};