/**
 * @file bliterals.h
 * @brief Defines binary literals for C.
 *
 * All n-bit binary literals up to n=8 have unique macro definition.
 * Use function-like macros for n=16, n=32, and n=64.
 * These declarations may deprecate when C23 defines built-in binary literals.
 *
 * @author Yavuz Koroglu
 */
#ifndef PADKIT_BLITERALS_H
    #define PADKIT_BLITERALS_H /* Binary Literals (may become deprecated after C23) */
    #include <stdint.h>

    /**
     * @defgroup BinaryLiteralMacros Binary Literal Macros
     * @{
     */

    /**
     * @def B2(high,low)
     *   Takes two 8-bit binary values and concatenates them to obtain a 16-bit binary literal.
     */
    #define B2(high,low) \
        (((uint_fast16_t)high << 8U) | (uint_fast16_t)low)

    /**
     * @def B4(hh,h,ll,l)
     *   Takes four 8-bit binary values and concatenates them to obtain a 32-bit binary literal.
     */
    #define B4(hh,h,l,ll) \
        (((uint_fast32_t)B2(hh,h) << 16U) | (uint_fast32_t)B2(l,ll))

    /**
     * @def B8(hhhh,hhh,hh,h,l,ll,lll,llll)
     *   Takes eight 8-bit binary values and concatenates them to obtain a 64-bit binary literal.
     */
    #define B8(hhhh,hhh,hh,h,l,ll,lll,llll) \
        (((uint_fast64_t)B4(hhhh,hhh,hh,h) << 32U) | (uint_fast64_t)B4(l,ll,lll,llll))

    /**
     * @def B_0
     *   1'b0
     */
    #define B_0 0x0U
    /**
     * @def B_1
     *   1'b1
     */
    #define B_1 0x1U

    /**
     * @def B_00
     *   2'b00
     */
    #define B_00 0x0U
    /**
     * @def B_01
     *   2'b01
     */
    #define B_01 0x1U
    /**
     * @def B_10
     *   2'b10
     */
    #define B_10 0x2U
    /**
     * @def B_11
     *   2'b11
     */
    #define B_11 0x3U

    /**
     * @def B_000
     *   3'b000
     */
    #define B_000 0x0U
    /**
     * @def B_001
     *   3'b001
     */
    #define B_001 0x1U
    /**
     * @def B_010
     *   3'b010
     */
    #define B_010 0x2U
    /**
     * @def B_011
     *   3'b011
     */
    #define B_011 0x3U
    /**
     * @def B_100
     *   3'b100
     */
    #define B_100 0x4U
    /**
     * @def B_101
     *   3'b101
     */
    #define B_101 0x5U
    /**
     * @def B_110
     *   3'b110
     */
    #define B_110 0x6U
    /**
     * @def B_111
     *   3'b111
     */
    #define B_111 0x7U

    /**
     * @def B_0000
     *   4'b0000
     */
    #define B_0000 0x0U
    /**
     * @def B_0001
     *   4'b0001
     */
    #define B_0001 0x1U
    /**
     * @def B_0010
     *   4'b0010
     */
    #define B_0010 0x2U
    /**
     * @def B_0011
     *   4'b0011
     */
    #define B_0011 0x3U
    /**
     * @def B_0100
     *   4'b0100
     */
    #define B_0100 0x4U
    /**
     * @def B_0101
     *   4'b0101
     */
    #define B_0101 0x5U
    /**
     * @def B_0110
     *   4'b0110
     */
    #define B_0110 0x6U
    /**
     * @def B_0111
     *   4'b0111
     */
    #define B_0111 0x7U
    /**
     * @def B_1000
     *   4'b1000
     */
    #define B_1000 0x8U
    /**
     * @def B_1001
     *   4'b1001
     */
    #define B_1001 0x9U
    /**
     * @def B_1010
     *   4'b1010
     */
    #define B_1010 0xAU
    /**
     * @def B_1011
     *   4'b1011
     */
    #define B_1011 0xBU
    /**
     * @def B_1100
     *   4'b1100
     */
    #define B_1100 0xCU
    /**
     * @def B_1101
     *   4'b1101
     */
    #define B_1101 0xDU
    /**
     * @def B_1110
     *   4'b1110
     */
    #define B_1110 0xEU
    /**
     * @def B_1111
     *   4'b1111
     */
    #define B_1111 0xFU

    /**
     * @def B_00000
     *   5'b00000
     */
    #define B_00000 0x00U
    /**
     * @def B_00001
     *   5'b00001
     */
    #define B_00001 0x01U
    /**
     * @def B_00010
     *   5'b00010
     */
    #define B_00010 0x02U
    /**
     * @def B_00011
     *   5'b00011
     */
    #define B_00011 0x03U
    /**
     * @def B_00100
     *   5'b00100
     */
    #define B_00100 0x04U
    /**
     * @def B_00101
     *   5'b00101
     */
    #define B_00101 0x05U
    /**
     * @def B_00110
     *   5'b00110
     */
    #define B_00110 0x06U
    /**
     * @def B_00111
     *   5'b00111
     */
    #define B_00111 0x07U
    /**
     * @def B_01000
     *   5'b01000
     */
    #define B_01000 0x08U
    /**
     * @def B_01001
     *   5'b01001
     */
    #define B_01001 0x09U
    /**
     * @def B_01010
     *   5'b01010
     */
    #define B_01010 0x0AU
    /**
     * @def B_01011
     *   5'b01011
     */
    #define B_01011 0x0BU
    /**
     * @def B_01100
     *   5'b01100
     */
    #define B_01100 0x0CU
    /**
     * @def B_01101
     *   5'b01101
     */
    #define B_01101 0x0DU
    /**
     * @def B_01110
     *   5'b01110
     */
    #define B_01110 0x0EU
    /**
     * @def B_01111
     *   5'b01111
     */
    #define B_01111 0x0FU
    /**
     * @def B_10000
     *   5'b10000
     */
    #define B_10000 0x10U
    /**
     * @def B_10001
     *   5'b10001
     */
    #define B_10001 0x11U
    /**
     * @def B_10010
     *   5'b10010
     */
    #define B_10010 0x12U
    /**
     * @def B_10011
     *   5'b10011
     */
    #define B_10011 0x13U
    /**
     * @def B_10100
     *   5'b10100
     */
    #define B_10100 0x14U
    /**
     * @def B_10101
     *   5'b10101
     */
    #define B_10101 0x15U
    /**
     * @def B_10110
     *   5'b10110
     */
    #define B_10110 0x16U
    /**
     * @def B_10111
     *   5'b10111
     */
    #define B_10111 0x17U
    /**
     * @def B_11000
     *   5'b11000
     */
    #define B_11000 0x18U
    /**
     * @def B_11001
     *   5'b11001
     */
    #define B_11001 0x19U
    /**
     * @def B_11010
     *   5'b11010
     */
    #define B_11010 0x1AU
    /**
     * @def B_11011
     *   5'b11011
     */
    #define B_11011 0x1BU
    /**
     * @def B_11100
     *   5'b11100
     */
    #define B_11100 0x1CU
    /**
     * @def B_11101
     *   5'b11101
     */
    #define B_11101 0x1DU
    /**
     * @def B_11110
     *   5'b11110
     */
    #define B_11110 0x1EU
    /**
     * @def B_11111
     *   5'b11111
     */
    #define B_11111 0x1FU

    /**
     * @def B_000000
     *   6'b000000
     */
    #define B_000000 0x00U
    /**
     * @def B_000001
     *   6'b000001
     */
    #define B_000001 0x01U
    /**
     * @def B_000010
     *   6'b000010
     */
    #define B_000010 0x02U
    /**
     * @def B_000011
     *   6'b000011
     */
    #define B_000011 0x03U
    /**
     * @def B_000100
     *   6'b000100
     */
    #define B_000100 0x04U
    /**
     * @def B_000101
     *   6'b000101
     */
    #define B_000101 0x05U
    /**
     * @def B_000110
     *   6'b000110
     */
    #define B_000110 0x06U
    /**
     * @def B_000111
     *   6'b000111
     */
    #define B_000111 0x07U
    /**
     * @def B_001000
     *   6'b001000
     */
    #define B_001000 0x08U
    /**
     * @def B_001001
     *   6'b001001
     */
    #define B_001001 0x09U
    /**
     * @def B_001010
     *   6'b001010
     */
    #define B_001010 0x0AU
    /**
     * @def B_001011
     *   6'b001011
     */
    #define B_001011 0x0BU
    /**
     * @def B_001100
     *   6'b001100
     */
    #define B_001100 0x0CU
    /**
     * @def B_001101
     *   6'b001101
     */
    #define B_001101 0x0DU
    /**
     * @def B_001110
     *   6'b001110
     */
    #define B_001110 0x0EU
    /**
     * @def B_001111
     *   6'b001111
     */
    #define B_001111 0x0FU
    /**
     * @def B_010000
     *   6'b010000
     */
    #define B_010000 0x10U
    /**
     * @def B_010001
     *   6'b010001
     */
    #define B_010001 0x11U
    /**
     * @def B_010010
     *   6'b010010
     */
    #define B_010010 0x12U
    /**
     * @def B_010011
     *   6'b010011
     */
    #define B_010011 0x13U
    /**
     * @def B_010100
     *   6'b010100
     */
    #define B_010100 0x14U
    /**
     * @def B_010101
     *   6'b010101
     */
    #define B_010101 0x15U
    /**
     * @def B_010110
     *   6'b010110
     */
    #define B_010110 0x16U
    /**
     * @def B_010111
     *   6'b010111
     */
    #define B_010111 0x17U
    /**
     * @def B_011000
     *   6'b011000
     */
    #define B_011000 0x18U
    /**
     * @def B_011001
     *   6'b011001
     */
    #define B_011001 0x19U
    /**
     * @def B_011010
     *   6'b011010
     */
    #define B_011010 0x1AU
    /**
     * @def B_011011
     *   6'b011011
     */
    #define B_011011 0x1BU
    /**
     * @def B_011100
     *   6'b011100
     */
    #define B_011100 0x1CU
    /**
     * @def B_011101
     *   6'b011101
     */
    #define B_011101 0x1DU
    /**
     * @def B_011110
     *   6'b011110
     */
    #define B_011110 0x1EU
    /**
     * @def B_011111
     *   6'b011111
     */
    #define B_011111 0x1FU
    /**
     * @def B_100000
     *   6'b100000
     */
    #define B_100000 0x20U
    /**
     * @def B_100001
     *   6'b100001
     */
    #define B_100001 0x21U
    /**
     * @def B_100010
     *   6'b100010
     */
    #define B_100010 0x22U
    /**
     * @def B_100011
     *   6'b100011
     */
    #define B_100011 0x23U
    /**
     * @def B_100100
     *   6'b100100
     */
    #define B_100100 0x24U
    /**
     * @def B_100101
     *   6'b100101
     */
    #define B_100101 0x25U
    /**
     * @def B_100110
     *   6'b100110
     */
    #define B_100110 0x26U
    /**
     * @def B_100111
     *   6'b100111
     */
    #define B_100111 0x27U
    /**
     * @def B_101000
     *   6'b101000
     */
    #define B_101000 0x28U
    /**
     * @def B_101001
     *   6'b101001
     */
    #define B_101001 0x29U
    /**
     * @def B_101010
     *   6'b101010
     */
    #define B_101010 0x2AU
    /**
     * @def B_101011
     *   6'b101011
     */
    #define B_101011 0x2BU
    /**
     * @def B_101100
     *   6'b101100
     */
    #define B_101100 0x2CU
    /**
     * @def B_101101
     *   6'b101101
     */
    #define B_101101 0x2DU
    /**
     * @def B_101110
     *   6'b101110
     */
    #define B_101110 0x2EU
    /**
     * @def B_101111
     *   6'b101111
     */
    #define B_101111 0x2FU
    /**
     * @def B_110000
     *   6'b110000
     */
    #define B_110000 0x30U
    /**
     * @def B_110001
     *   6'b110001
     */
    #define B_110001 0x31U
    /**
     * @def B_110010
     *   6'b110010
     */
    #define B_110010 0x32U
    /**
     * @def B_110011
     *   6'b110011
     */
    #define B_110011 0x33U
    /**
     * @def B_110100
     *   6'b110100
     */
    #define B_110100 0x34U
    /**
     * @def B_110101
     *   6'b110101
     */
    #define B_110101 0x35U
    /**
     * @def B_110110
     *   6'b110110
     */
    #define B_110110 0x36U
    /**
     * @def B_110111
     *   6'b110111
     */
    #define B_110111 0x37U
    /**
     * @def B_111000
     *   6'b111000
     */
    #define B_111000 0x38U
    /**
     * @def B_111001
     *   6'b111001
     */
    #define B_111001 0x39U
    /**
     * @def B_111010
     *   6'b111010
     */
    #define B_111010 0x3AU
    /**
     * @def B_111011
     *   6'b111011
     */
    #define B_111011 0x3BU
    /**
     * @def B_111100
     *   6'b111100
     */
    #define B_111100 0x3CU
    /**
     * @def B_111101
     *   6'b111101
     */
    #define B_111101 0x3DU
    /**
     * @def B_111110
     *   6'b111110
     */
    #define B_111110 0x3EU
    /**
     * @def B_111111
     *   6'b111111
     */
    #define B_111111 0x3FU

    /**
     * @def B_0000000
     *   7'b0000000
     */
    #define B_0000000 0x00U
    /**
     * @def B_0000001
     *   7'b0000001
     */
    #define B_0000001 0x01U
    /**
     * @def B_0000010
     *   7'b0000010
     */
    #define B_0000010 0x02U
    /**
     * @def B_0000011
     *   7'b0000011
     */
    #define B_0000011 0x03U
    /**
     * @def B_0000100
     *   7'b0000100
     */
    #define B_0000100 0x04U
    /**
     * @def B_0000101
     *   7'b0000101
     */
    #define B_0000101 0x05U
    /**
     * @def B_0000110
     *   7'b0000110
     */
    #define B_0000110 0x06U
    /**
     * @def B_0000111
     *   7'b0000111
     */
    #define B_0000111 0x07U
    /**
     * @def B_0001000
     *   7'b0001000
     */
    #define B_0001000 0x08U
    /**
     * @def B_0001001
     *   7'b0001001
     */
    #define B_0001001 0x09U
    /**
     * @def B_0001010
     *   7'b0001010
     */
    #define B_0001010 0x0AU
    /**
     * @def B_0001011
     *   7'b0001011
     */
    #define B_0001011 0x0BU
    /**
     * @def B_0001100
     *   7'b0001100
     */
    #define B_0001100 0x0CU
    /**
     * @def B_0001101
     *   7'b0001101
     */
    #define B_0001101 0x0DU
    /**
     * @def B_0001110
     *   7'b0001110
     */
    #define B_0001110 0x0EU
    /**
     * @def B_0001111
     *   7'b0001111
     */
    #define B_0001111 0x0FU
    /**
     * @def B_0010000
     *   7'b0010000
     */
    #define B_0010000 0x10U
    /**
     * @def B_0010001
     *   7'b0010001
     */
    #define B_0010001 0x11U
    /**
     * @def B_0010010
     *   7'b0010010
     */
    #define B_0010010 0x12U
    /**
     * @def B_0010011
     *   7'b0010011
     */
    #define B_0010011 0x13U
    /**
     * @def B_0010100
     *   7'b0010100
     */
    #define B_0010100 0x14U
    /**
     * @def B_0010101
     *   7'b0010101
     */
    #define B_0010101 0x15U
    /**
     * @def B_0010110
     *   7'b0010110
     */
    #define B_0010110 0x16U
    /**
     * @def B_0010111
     *   7'b0010111
     */
    #define B_0010111 0x17U
    /**
     * @def B_0011000
     *   7'b0011000
     */
    #define B_0011000 0x18U
    /**
     * @def B_0011001
     *   7'b0011001
     */
    #define B_0011001 0x19U
    /**
     * @def B_0011010
     *   7'b0011010
     */
    #define B_0011010 0x1AU
    /**
     * @def B_0011011
     *   7'b0011011
     */
    #define B_0011011 0x1BU
    /**
     * @def B_0011100
     *   7'b0011100
     */
    #define B_0011100 0x1CU
    /**
     * @def B_0011101
     *   7'b0011101
     */
    #define B_0011101 0x1DU
    /**
     * @def B_0011110
     *   7'b0011110
     */
    #define B_0011110 0x1EU
    /**
     * @def B_0011111
     *   7'b0011111
     */
    #define B_0011111 0x1FU
    /**
     * @def B_0100000
     *   7'b0100000
     */
    #define B_0100000 0x20U
    /**
     * @def B_0100001
     *   7'b0100001
     */
    #define B_0100001 0x21U
    /**
     * @def B_0100010
     *   7'b0100010
     */
    #define B_0100010 0x22U
    /**
     * @def B_0100011
     *   7'b0100011
     */
    #define B_0100011 0x23U
    /**
     * @def B_0100100
     *   7'b0100100
     */
    #define B_0100100 0x24U
    /**
     * @def B_0100101
     *   7'b0100101
     */
    #define B_0100101 0x25U
    /**
     * @def B_0100110
     *   7'b0100110
     */
    #define B_0100110 0x26U
    /**
     * @def B_0100111
     *   7'b0100111
     */
    #define B_0100111 0x27U
    /**
     * @def B_0101000
     *   7'b0101000
     */
    #define B_0101000 0x28U
    /**
     * @def B_0101001
     *   7'b0101001
     */
    #define B_0101001 0x29U
    /**
     * @def B_0101010
     *   7'b0101010
     */
    #define B_0101010 0x2AU
    /**
     * @def B_0101011
     *   7'b0101011
     */
    #define B_0101011 0x2BU
    /**
     * @def B_0101100
     *   7'b0101100
     */
    #define B_0101100 0x2CU
    /**
     * @def B_0101101
     *   7'b0101101
     */
    #define B_0101101 0x2DU
    /**
     * @def B_0101110
     *   7'b0101110
     */
    #define B_0101110 0x2EU
    /**
     * @def B_0101111
     *   7'b0101111
     */
    #define B_0101111 0x2FU
    /**
     * @def B_0110000
     *   7'b0110000
     */
    #define B_0110000 0x30U
    /**
     * @def B_0110001
     *   7'b0110001
     */
    #define B_0110001 0x31U
    /**
     * @def B_0110010
     *   7'b0110010
     */
    #define B_0110010 0x32U
    /**
     * @def B_0110011
     *   7'b0110011
     */
    #define B_0110011 0x33U
    /**
     * @def B_0110100
     *   7'b0110100
     */
    #define B_0110100 0x34U
    /**
     * @def B_0110101
     *   7'b0110101
     */
    #define B_0110101 0x35U
    /**
     * @def B_0110110
     *   7'b0110110
     */
    #define B_0110110 0x36U
    /**
     * @def B_0110111
     *   7'b0110111
     */
    #define B_0110111 0x37U
    /**
     * @def B_0111000
     *   7'b0111000
     */
    #define B_0111000 0x38U
    /**
     * @def B_0111001
     *   7'b0111001
     */
    #define B_0111001 0x39U
    /**
     * @def B_0111010
     *   7'b0111010
     */
    #define B_0111010 0x3AU
    /**
     * @def B_0111011
     *   7'b0111011
     */
    #define B_0111011 0x3BU
    /**
     * @def B_0111100
     *   7'b0111100
     */
    #define B_0111100 0x3CU
    /**
     * @def B_0111101
     *   7'b0111101
     */
    #define B_0111101 0x3DU
    /**
     * @def B_0111110
     *   7'b0111110
     */
    #define B_0111110 0x3EU
    /**
     * @def B_0111111
     *   7'b0111111
     */
    #define B_0111111 0x3FU
    /**
     * @def B_1000000
     *   7'b1000000
     */
    #define B_1000000 0x40U
    /**
     * @def B_1000001
     *   7'b1000001
     */
    #define B_1000001 0x41U
    /**
     * @def B_1000010
     *   7'b1000010
     */
    #define B_1000010 0x42U
    /**
     * @def B_1000011
     *   7'b1000011
     */
    #define B_1000011 0x43U
    /**
     * @def B_1000100
     *   7'b1000100
     */
    #define B_1000100 0x44U
    /**
     * @def B_1000101
     *   7'b1000101
     */
    #define B_1000101 0x45U
    /**
     * @def B_1000110
     *   7'b1000110
     */
    #define B_1000110 0x46U
    /**
     * @def B_1000111
     *   7'b1000111
     */
    #define B_1000111 0x47U
    /**
     * @def B_1001000
     *   7'b1001000
     */
    #define B_1001000 0x48U
    /**
     * @def B_1001001
     *   7'b1001001
     */
    #define B_1001001 0x49U
    /**
     * @def B_1001010
     *   7'b1001010
     */
    #define B_1001010 0x4AU
    /**
     * @def B_1001011
     *   7'b1001011
     */
    #define B_1001011 0x4BU
    /**
     * @def B_1001100
     *   7'b1001100
     */
    #define B_1001100 0x4CU
    /**
     * @def B_1001101
     *   7'b1001101
     */
    #define B_1001101 0x4DU
    /**
     * @def B_1001110
     *   7'b1001110
     */
    #define B_1001110 0x4EU
    /**
     * @def B_1001111
     *   7'b1001111
     */
    #define B_1001111 0x4FU
    /**
     * @def B_1010000
     *   7'b1010000
     */
    #define B_1010000 0x50U
    /**
     * @def B_1010001
     *   7'b1010001
     */
    #define B_1010001 0x51U
    /**
     * @def B_1010010
     *   7'b1010010
     */
    #define B_1010010 0x52U
    /**
     * @def B_1010011
     *   7'b1010011
     */
    #define B_1010011 0x53U
    /**
     * @def B_1010100
     *   7'b1010100
     */
    #define B_1010100 0x54U
     /**
     * @def B_1010101
     *   7'b1010101
     */
    #define B_1010101 0x55U
    /**
     * @def B_1010110
     *   7'b1010110
     */
    #define B_1010110 0x56U
    /**
     * @def B_1010111
     *   7'b1010111
     */
    #define B_1010111 0x57U
    /**
     * @def B_1011000
     *   7'b1011000
     */
    #define B_1011000 0x58U
    /**
     * @def B_1011001
     *   7'b1011001
     */
    #define B_1011001 0x59U
    /**
     * @def B_1011010
     *   7'b1011010
     */
    #define B_1011010 0x5AU
    /**
     * @def B_1011011
     *   7'b1011011
     */
    #define B_1011011 0x5BU
    /**
     * @def B_1011100
     *   7'b1011100
     */
    #define B_1011100 0x5CU
    /**
     * @def B_1011101
     *   7'b1011101
     */
    #define B_1011101 0x5DU
    /**
     * @def B_1011110
     *   7'b1011110
     */
    #define B_1011110 0x5EU
    /**
     * @def B_1011111
     *   7'b1011111
     */
    #define B_1011111 0x5FU
    /**
     * @def B_1100000
     *   7'b1100000
     */
    #define B_1100000 0x60U
    /**
     * @def B_1100001
     *   7'b1100001
     */
    #define B_1100001 0x61U
    /**
     * @def B_1100010
     *   7'b1100010
     */
    #define B_1100010 0x62U
    /**
     * @def B_1100011
     *   7'b1100011
     */
    #define B_1100011 0x63U
    /**
     * @def B_1100100
     *   7'b1100100
     */
    #define B_1100100 0x64U
    /**
     * @def B_1100101
     *   7'b1100101
     */
    #define B_1100101 0x65U
    /**
     * @def B_1100110
     *   7'b1100110
     */
    #define B_1100110 0x66U
    /**
     * @def B_1100111
     *   7'b1100111
     */
    #define B_1100111 0x67U
    /**
     * @def B_1101000
     *   7'b1101000
     */
    #define B_1101000 0x68U
    /**
     * @def B_1101001
     *   7'b1101001
     */
    #define B_1101001 0x69U
    /**
     * @def B_1101010
     *   7'b1101010
     */
    #define B_1101010 0x6AU
    /**
     * @def B_1101011
     *   7'b1101011
     */
    #define B_1101011 0x6BU
    /**
     * @def B_1101100
     *   7'b1101100
     */
    #define B_1101100 0x6CU
    /**
     * @def B_1101101
     *   7'b1101101
     */
    #define B_1101101 0x6DU
    /**
     * @def B_1101110
     *   7'b1101110
     */
    #define B_1101110 0x6EU
    /**
     * @def B_1101111
     *   7'b1101111
     */
    #define B_1101111 0x6FU
    /**
     * @def B_1110000
     *   7'b1110000
     */
    #define B_1110000 0x70U
    /**
     * @def B_1110001
     *   7'b1110001
     */
    #define B_1110001 0x71U
    /**
     * @def B_1110010
     *   7'b1110010
     */
    #define B_1110010 0x72U
    /**
     * @def B_1110011
     *   7'b1110011
     */
    #define B_1110011 0x73U
    /**
     * @def B_1110100
     *   7'b1110100
     */
    #define B_1110100 0x74U
    /**
     * @def B_1110101
     *   7'b1110101
     */
    #define B_1110101 0x75U
    /**
     * @def B_1110110
     *   7'b1110110
     */
    #define B_1110110 0x76U
    /**
     * @def B_1110111
     *   7'b1110111
     */
    #define B_1110111 0x77U
    /**
     * @def B_1111000
     *   7'b1111000
     */
    #define B_1111000 0x78U
    /**
     * @def B_1111001
     *   7'b1111001
     */
    #define B_1111001 0x79U
    /**
     * @def B_1111010
     *   7'b1111010
     */
    #define B_1111010 0x7AU
    /**
     * @def B_1111011
     *   7'b1111011
     */
    #define B_1111011 0x7BU
    /**
     * @def B_1111100
     *   7'b1111100
     */
    #define B_1111100 0x7CU
    /**
     * @def B_1111101
     *   7'b1111101
     */
    #define B_1111101 0x7DU
    /**
     * @def B_1111110
     *   7'b1111110
     */
    #define B_1111110 0x7EU
    /**
     * @def B_1111111
     *   7'b1111111
     */
    #define B_1111111 0x7FU

    /**
     * @def B_00000000
     *   8'b00000000
     */
    #define B_00000000 0x00U
    /**
     * @def B_00000001
     *   8'b00000001
     */
    #define B_00000001 0x01U
    /**
     * @def B_00000010
     *   8'b00000010
     */
    #define B_00000010 0x02U
    /**
     * @def B_00000011
     *   8'b00000011
     */
    #define B_00000011 0x03U
    /**
     * @def B_00000100
     *   8'b00000100
     */
    #define B_00000100 0x04U
    /**
     * @def B_00000101
     *   8'b00000101
     */
    #define B_00000101 0x05U
    /**
     * @def B_00000110
     *   8'b00000110
     */
    #define B_00000110 0x06U
    /**
     * @def B_00000111
     *   8'b00000111
     */
    #define B_00000111 0x07U
    /**
     * @def B_00001000
     *   8'b00001000
     */
    #define B_00001000 0x08U
    /**
     * @def B_00001001
     *   8'b00001001
     */
    #define B_00001001 0x09U
    /**
     * @def B_00001010
     *   8'b00001010
     */
    #define B_00001010 0x0AU
    /**
     * @def B_00001011
     *   8'b00001011
     */
    #define B_00001011 0x0BU
    /**
     * @def B_00001100
     *   8'b00001100
     */
    #define B_00001100 0x0CU
    /**
     * @def B_00001101
     *   8'b00001101
     */
    #define B_00001101 0x0DU
    /**
     * @def B_00001110
     *   8'b00001110
     */
    #define B_00001110 0x0EU
    /**
     * @def B_00001111
     *   8'b00001111
     */
    #define B_00001111 0x0FU
    /**
     * @def B_00010000
     *   8'b00010000
     */
    #define B_00010000 0x10U
    /**
     * @def B_00010001
     *   8'b00010001
     */
    #define B_00010001 0x11U
    /**
     * @def B_00010010
     *   8'b00010010
     */
    #define B_00010010 0x12U
    /**
     * @def B_00010011
     *   8'b00010011
     */
    #define B_00010011 0x13U
    /**
     * @def B_00010100
     *   8'b00010100
     */
    #define B_00010100 0x14U
    /**
     * @def B_00010101
     *   8'b00010101
     */
    #define B_00010101 0x15U
    /**
     * @def B_00010110
     *   8'b00010110
     */
    #define B_00010110 0x16U
    /**
     * @def B_00010111
     *   8'b00010111
     */
    #define B_00010111 0x17U
    /**
     * @def B_00011000
     *   8'b00011000
     */
    #define B_00011000 0x18U
    /**
     * @def B_00011001
     *   8'b00011001
     */
    #define B_00011001 0x19U
    /**
     * @def B_00011010
     *   8'b00011010
     */
    #define B_00011010 0x1AU
    /**
     * @def B_00011011
     *   8'b00011011
     */
    #define B_00011011 0x1BU
    /**
     * @def B_00011100
     *   8'b00011100
     */
    #define B_00011100 0x1CU
    /**
     * @def B_00011101
     *   8'b00011101
     */
    #define B_00011101 0x1DU
    /**
     * @def B_00011110
     *   8'b00011110
     */
    #define B_00011110 0x1EU
    /**
     * @def B_00011111
     *   8'b00011111
     */
    #define B_00011111 0x1FU
    /**
     * @def B_00100000
     *   8'b00100000
     */
    #define B_00100000 0x20U
    /**
     * @def B_00100001
     *   8'b00100001
     */
    #define B_00100001 0x21U
    /**
     * @def B_00100010
     *   8'b00100010
     */
    #define B_00100010 0x22U
    /**
     * @def B_00100011
     *   8'b00100011
     */
    #define B_00100011 0x23U
    /**
     * @def B_00100100
     *   8'b00100100
     */
    #define B_00100100 0x24U
    /**
     * @def B_00100101
     *   8'b00100101
     */
    #define B_00100101 0x25U
    /**
     * @def B_00100110
     *   8'b00100110
     */
    #define B_00100110 0x26U
    /**
     * @def B_00100111
     *   8'b00100111
     */
    #define B_00100111 0x27U
    /**
     * @def B_00101000
     *   8'b00101000
     */
    #define B_00101000 0x28U
    /**
     * @def B_00101001
     *   8'b00101001
     */
    #define B_00101001 0x29U
    /**
     * @def B_00101010
     *   8'b00101010
     */
    #define B_00101010 0x2AU
    /**
     * @def B_00101011
     *   8'b00101011
     */
    #define B_00101011 0x2BU
    /**
     * @def B_00101100
     *   8'b00101100
     */
    #define B_00101100 0x2CU
    /**
     * @def B_00101101
     *   8'b00101101
     */
    #define B_00101101 0x2DU
    /**
     * @def B_00101110
     *   8'b00101110
     */
    #define B_00101110 0x2EU
    /**
     * @def B_00101111
     *   8'b00101111
     */
    #define B_00101111 0x2FU
    /**
     * @def B_00110000
     *   8'b00110000
     */
    #define B_00110000 0x30U
    /**
     * @def B_00110001
     *   8'b00110001
     */
    #define B_00110001 0x31U
    /**
     * @def B_00110010
     *   8'b00110010
     */
    #define B_00110010 0x32U
    /**
     * @def B_00110011
     *   8'b00110011
     */
    #define B_00110011 0x33U
    /**
     * @def B_00110100
     *   8'b00110100
     */
    #define B_00110100 0x34U
    /**
     * @def B_00110101
     *   8'b00110101
     */
    #define B_00110101 0x35U
    /**
     * @def B_00110110
     *   8'b00110110
     */
    #define B_00110110 0x36U
    /**
     * @def B_00110111
     *   8'b00110111
     */
    #define B_00110111 0x37U
    /**
     * @def B_00111000
     *   8'b00111000
     */
    #define B_00111000 0x38U
    /**
     * @def B_00111001
     *   8'b00111001
     */
    #define B_00111001 0x39U
    /**
     * @def B_00111010
     *   8'b00111010
     */
    #define B_00111010 0x3AU
    /**
     * @def B_00111011
     *   8'b00111011
     */
    #define B_00111011 0x3BU
    /**
     * @def B_00111100
     *   8'b00111100
     */
    #define B_00111100 0x3CU
    /**
     * @def B_00111101
     *   8'b00111101
     */
    #define B_00111101 0x3DU
    /**
     * @def B_00111110
     *   8'b00111110
     */
    #define B_00111110 0x3EU
    /**
     * @def B_00111111
     *   8'b00111111
     */
    #define B_00111111 0x3FU
    /**
     * @def B_01000000
     *   8'b01000000
     */
    #define B_01000000 0x40U
    /**
     * @def B_01000001
     *   8'b01000001
     */
    #define B_01000001 0x41U
    /**
     * @def B_01000010
     *   8'b01000010
     */
    #define B_01000010 0x42U
    /**
     * @def B_01000011
     *   8'b01000011
     */
    #define B_01000011 0x43U
    /**
     * @def B_01000100
     *   8'b01000100
     */
    #define B_01000100 0x44U
    /**
     * @def B_01000101
     *   8'b01000101
     */
    #define B_01000101 0x45U
    /**
     * @def B_01000110
     *   8'b01000110
     */
    #define B_01000110 0x46U
    /**
     * @def B_01000111
     *   8'b01000111
     */
    #define B_01000111 0x47U
    /**
     * @def B_01001000
     *   8'b01001000
     */
    #define B_01001000 0x48U
    /**
     * @def B_01001001
     *   8'b01001001
     */
    #define B_01001001 0x49U
    /**
     * @def B_01001010
     *   8'b01001010
     */
    #define B_01001010 0x4AU
    /**
     * @def B_01001011
     *   8'b01001011
     */
    #define B_01001011 0x4BU
    /**
     * @def B_01001100
     *   8'b01001100
     */
    #define B_01001100 0x4CU
    /**
     * @def B_01001101
     *   8'b01001101
     */
    #define B_01001101 0x4DU
    /**
     * @def B_01001110
     *   8'b01001110
     */
    #define B_01001110 0x4EU
    /**
     * @def B_01001111
     *   8'b01001111
     */
    #define B_01001111 0x4FU
    /**
     * @def B_01010000
     *   8'b01010000
     */
    #define B_01010000 0x50U
    /**
     * @def B_01010001
     *   8'b01010001
     */
    #define B_01010001 0x51U
    /**
     * @def B_01010010
     *   8'b01010010
     */
    #define B_01010010 0x52U
    /**
     * @def B_01010011
     *   8'b01010011
     */
    #define B_01010011 0x53U
    /**
     * @def B_01010100
     *   8'b01010100
     */
    #define B_01010100 0x54U
    /**
     * @def B_01010101
     *   8'b01010101
     */
    #define B_01010101 0x55U
    /**
     * @def B_01010110
     *   8'b01010110
     */
    #define B_01010110 0x56U
    /**
     * @def B_01010111
     *   8'b01010111
     */
    #define B_01010111 0x57U
    /**
     * @def B_01011000
     *   8'b01011000
     */
    #define B_01011000 0x58U
    /**
     * @def B_01011001
     *   8'b01011001
     */
    #define B_01011001 0x59U
    /**
     * @def B_01011010
     *   8'b01011010
     */
    #define B_01011010 0x5AU
    /**
     * @def B_01011011
     *   8'b01011011
     */
    #define B_01011011 0x5BU
    /**
     * @def B_01011100
     *   8'b01011100
     */
    #define B_01011100 0x5CU
    /**
     * @def B_01011101
     *   8'b01011101
     */
    #define B_01011101 0x5DU
    /**
     * @def B_01011110
     *   8'b01011110
     */
    #define B_01011110 0x5EU
    /**
     * @def B_01011111
     *   8'b01011111
     */
    #define B_01011111 0x5FU
    /**
     * @def B_01100000
     *   8'b01100000
     */
    #define B_01100000 0x60U
    /**
     * @def B_01100001
     *   8'b01100001
     */
    #define B_01100001 0x61U
    /**
     * @def B_01100010
     *   8'b01100010
     */
    #define B_01100010 0x62U
    /**
     * @def B_01100011
     *   8'b01100011
     */
    #define B_01100011 0x63U
    /**
     * @def B_01100100
     *   8'b01100100
     */
    #define B_01100100 0x64U
    /**
     * @def B_01100101
     *   8'b01100101
     */
    #define B_01100101 0x65U
    /**
     * @def B_01100110
     *   8'b01100110
     */
    #define B_01100110 0x66U
    /**
     * @def B_01100111
     *   8'b01100111
     */
    #define B_01100111 0x67U
    /**
     * @def B_01101000
     *   8'b01101000
     */
    #define B_01101000 0x68U
    /**
     * @def B_01101001
     *   8'b01101001
     */
    #define B_01101001 0x69U
    /**
     * @def B_01101010
     *   8'b01101010
     */
    #define B_01101010 0x6AU
    /**
     * @def B_01101011
     *   8'b01101011
     */
    #define B_01101011 0x6BU
    /**
     * @def B_01101100
     *   8'b01101100
     */
    #define B_01101100 0x6CU
    /**
     * @def B_01101101
     *   8'b01101101
     */
    #define B_01101101 0x6DU
    /**
     * @def B_01101110
     *   8'b01101110
     */
    #define B_01101110 0x6EU
    /**
     * @def B_01101111
     *   8'b01101111
     */
    #define B_01101111 0x6FU
    /**
     * @def B_01110000
     *   8'b01110000
     */
    #define B_01110000 0x70U
    /**
     * @def B_01110001
     *   8'b01110001
     */
    #define B_01110001 0x71U
    /**
     * @def B_01110010
     *   8'b01110010
     */
    #define B_01110010 0x72U
    /**
     * @def B_01110011
     *   8'b01110011
     */
    #define B_01110011 0x73U
    /**
     * @def B_01110100
     *   8'b01110100
     */
    #define B_01110100 0x74U
    /**
     * @def B_01110101
     *   8'b01110101
     */
    #define B_01110101 0x75U
    /**
     * @def B_01110110
     *   8'b01110110
     */
    #define B_01110110 0x76U
    /**
     * @def B_01110111
     *   8'b01110111
     */
    #define B_01110111 0x77U
    /**
     * @def B_01111000
     *   8'b01111000
     */
    #define B_01111000 0x78U
    /**
     * @def B_01111001
     *   8'b01111001
     */
    #define B_01111001 0x79U
    /**
     * @def B_01111010
     *   8'b01111010
     */
    #define B_01111010 0x7AU
    /**
     * @def B_01111011
     *   8'b01111011
     */
    #define B_01111011 0x7BU
    /**
     * @def B_01111100
     *   8'b01111100
     */
    #define B_01111100 0x7CU
    /**
     * @def B_01111101
     *   8'b01111101
     */
    #define B_01111101 0x7DU
    /**
     * @def B_01111110
     *   8'b01111110
     */
    #define B_01111110 0x7EU
    /**
     * @def B_01111111
     *   8'b01111111
     */
    #define B_01111111 0x7FU
    /**
     * @def B_10000000
     *   8'b10000000
     */
    #define B_10000000 0x80U
    /**
     * @def B_10000001
     *   8'b10000001
     */
    #define B_10000001 0x81U
    /**
     * @def B_10000010
     *   8'b10000010
     */
    #define B_10000010 0x82U
    /**
     * @def B_10000011
     *   8'b10000011
     */
    #define B_10000011 0x83U
    /**
     * @def B_10000100
     *   8'b10000100
     */
    #define B_10000100 0x84U
    /**
     * @def B_10000101
     *   8'b10000101
     */
    #define B_10000101 0x85U
    /**
     * @def B_10000110
     *   8'b10000110
     */
    #define B_10000110 0x86U
    /**
     * @def B_10000111
     *   8'b10000111
     */
    #define B_10000111 0x87U
    /**
     * @def B_10001000
     *   8'b10001000
     */
    #define B_10001000 0x88U
    /**
     * @def B_10001001
     *   8'b10001001
     */
    #define B_10001001 0x89U
    /**
     * @def B_10001010
     *   8'b10001010
     */
    #define B_10001010 0x8AU
    /**
     * @def B_10001011
     *   8'b10001011
     */
    #define B_10001011 0x8BU
    /**
     * @def B_10001100
     *   8'b10001100
     */
    #define B_10001100 0x8CU
    /**
     * @def B_10001101
     *   8'b10001101
     */
    #define B_10001101 0x8DU
    /**
     * @def B_10001110
     *   8'b10001110
     */
    #define B_10001110 0x8EU
    /**
     * @def B_10001111
     *   8'b10001111
     */
    #define B_10001111 0x8FU
    /**
     * @def B_10010000
     *   8'b10010000
     */
    #define B_10010000 0x90U
    /**
     * @def B_10010001
     *   8'b10010001
     */
    #define B_10010001 0x91U
    /**
     * @def B_10010010
     *   8'b10010010
     */
    #define B_10010010 0x92U
    /**
     * @def B_10010011
     *   8'b10010011
     */
    #define B_10010011 0x93U
    /**
     * @def B_10010100
     *   8'b10010100
     */
    #define B_10010100 0x94U
    /**
     * @def B_10010101
     *   8'b10010101
     */
    #define B_10010101 0x95U
    /**
     * @def B_10010110
     *   8'b10010110
     */
    #define B_10010110 0x96U
    /**
     * @def B_10010111
     *   8'b10010111
     */
    #define B_10010111 0x97U
    /**
     * @def B_10011000
     *   8'b10011000
     */
    #define B_10011000 0x98U
    /**
     * @def B_10011001
     *   8'b10011001
     */
    #define B_10011001 0x99U
    /**
     * @def B_10011010
     *   8'b10011010
     */
    #define B_10011010 0x9AU
    /**
     * @def B_10011011
     *   8'b10011011
     */
    #define B_10011011 0x9BU
    /**
     * @def B_10011100
     *   8'b10011100
     */
    #define B_10011100 0x9CU
    /**
     * @def B_10011101
     *   8'b10011101
     */
    #define B_10011101 0x9DU
    /**
     * @def B_10011110
     *   8'b10011110
     */
    #define B_10011110 0x9EU
    /**
     * @def B_10011111
     *   8'b10011111
     */
    #define B_10011111 0x9FU
    /**
     * @def B_10100000
     *   8'b10100000
     */
    #define B_10100000 0xA0U
    /**
     * @def B_10100001
     *   8'b10100001
     */
    #define B_10100001 0xA1U
    /**
     * @def B_10100010
     *   8'b10100010
     */
    #define B_10100010 0xA2U
    /**
     * @def B_10100011
     *   8'b10100011
     */
    #define B_10100011 0xA3U
    /**
     * @def B_10100100
     *   8'b10100100
     */
    #define B_10100100 0xA4U
    /**
     * @def B_10100101
     *   8'b10100101
     */
    #define B_10100101 0xA5U
    /**
     * @def B_10100110
     *   8'b10100110
     */
    #define B_10100110 0xA6U
    /**
     * @def B_10100111
     *   8'b10100111
     */
    #define B_10100111 0xA7U
    /**
     * @def B_10101000
     *   8'b10101000
     */
    #define B_10101000 0xA8U
    /**
     * @def B_10101001
     *   8'b10101001
     */
    #define B_10101001 0xA9U
    /**
     * @def B_10101010
     *   8'b10101010
     */
    #define B_10101010 0xAAU
    /**
     * @def B_10101011
     *   8'b10101011
     */
    #define B_10101011 0xABU
    /**
     * @def B_10101100
     *   8'b10101100
     */
    #define B_10101100 0xACU
    /**
     * @def B_10101101
     *   8'b10101101
     */
    #define B_10101101 0xADU
    /**
     * @def B_10101110
     *   8'b10101110
     */
    #define B_10101110 0xAEU
    /**
     * @def B_10101111
     *   8'b10101111
     */
    #define B_10101111 0xAFU
    /**
     * @def B_10110000
     *   8'b10110000
     */
    #define B_10110000 0xB0U
    /**
     * @def B_10110001
     *   8'b10110001
     */
    #define B_10110001 0xB1U
    /**
     * @def B_10110010
     *   8'b10110010
     */
    #define B_10110010 0xB2U
    /**
     * @def B_10110011
     *   8'b10110011
     */
    #define B_10110011 0xB3U
    /**
     * @def B_10110100
     *   8'b10110100
     */
    #define B_10110100 0xB4U
    /**
     * @def B_10110101
     *   8'b10110101
     */
    #define B_10110101 0xB5U
    /**
     * @def B_10110110
     *   8'b10110110
     */
    #define B_10110110 0xB6U
    /**
     * @def B_10110111
     *   8'b10110111
     */
    #define B_10110111 0xB7U
    /**
     * @def B_10111000
     *   8'b10111000
     */
    #define B_10111000 0xB8U
    /**
     * @def B_10111001
     *   8'b10111001
     */
    #define B_10111001 0xB9U
    /**
     * @def B_10111010
     *   8'b10111010
     */
    #define B_10111010 0xBAU
    /**
     * @def B_10111011
     *   8'b10111011
     */
    #define B_10111011 0xBBU
    /**
     * @def B_10111100
     *   8'b10111100
     */
    #define B_10111100 0xBCU
    /**
     * @def B_10111101
     *   8'b10111101
     */
    #define B_10111101 0xBDU
    /**
     * @def B_10111110
     *   8'b10111110
     */
    #define B_10111110 0xBEU
    /**
     * @def B_10111111
     *   8'b10111111
     */
    #define B_10111111 0xBFU
    /**
     * @def B_11000000
     *   8'b11000000
     */
    #define B_11000000 0xC0U
    /**
     * @def B_11000001
     *   8'b11000001
     */
    #define B_11000001 0xC1U
    /**
     * @def B_11000010
     *   8'b11000010
     */
    #define B_11000010 0xC2U
    /**
     * @def B_11000011
     *   8'b11000011
     */
    #define B_11000011 0xC3U
    /**
     * @def B_11000100
     *   8'b11000100
     */
    #define B_11000100 0xC4U
    /**
     * @def B_11000101
     *   8'b11000101
     */
    #define B_11000101 0xC5U
    /**
     * @def B_11000110
     *   8'b11000110
     */
    #define B_11000110 0xC6U
    /**
     * @def B_11000111
     *   8'b11000111
     */
    #define B_11000111 0xC7U
    /**
     * @def B_11001000
     *   8'b11001000
     */
    #define B_11001000 0xC8U
    /**
     * @def B_11001001
     *   8'b11001001
     */
    #define B_11001001 0xC9U
    /**
     * @def B_11001010
     *   8'b11001010
     */
    #define B_11001010 0xCAU
    /**
     * @def B_11001011
     *   8'b11001011
     */
    #define B_11001011 0xCBU
    /**
     * @def B_11001100
     *   8'b11001100
     */
    #define B_11001100 0xCCU
    /**
     * @def B_11001101
     *   8'b11001101
     */
    #define B_11001101 0xCDU
    /**
     * @def B_11001110
     *   8'b11001110
     */
    #define B_11001110 0xCEU
    /**
     * @def B_11001111
     *   8'b11001111
     */
    #define B_11001111 0xCFU
    /**
     * @def B_11010000
     *   8'b11010000
     */
    #define B_11010000 0xD0U
    /**
     * @def B_11010001
     *   8'b11010001
     */
    #define B_11010001 0xD1U
    /**
     * @def B_11010010
     *   8'b11010010
     */
    #define B_11010010 0xD2U
    /**
     * @def B_11010011
     *   8'b11010011
     */
    #define B_11010011 0xD3U
    /**
     * @def B_11010100
     *   8'b11010100
     */
    #define B_11010100 0xD4U
    /**
     * @def B_11010101
     *   8'b11010101
     */
    #define B_11010101 0xD5U
    /**
     * @def B_11010110
     *   8'b11010110
     */
    #define B_11010110 0xD6U
    /**
     * @def B_11010111
     *   8'b11010111
     */
    #define B_11010111 0xD7U
    /**
     * @def B_11011000
     *   8'b11011000
     */
    #define B_11011000 0xD8U
    /**
     * @def B_11011001
     *   8'b11011001
     */
    #define B_11011001 0xD9U
    /**
     * @def B_11011010
     *   8'b11011010
     */
    #define B_11011010 0xDAU
    /**
     * @def B_11011011
     *   8'b11011011
     */
    #define B_11011011 0xDBU
    /**
     * @def B_11011100
     *   8'b11011100
     */
    #define B_11011100 0xDCU
    /**
     * @def B_11011101
     *   8'b11011101
     */
    #define B_11011101 0xDDU
    /**
     * @def B_11011110
     *   8'b11011110
     */
    #define B_11011110 0xDEU
    /**
     * @def B_11011111
     *   8'b11011111
     */
    #define B_11011111 0xDFU
    /**
     * @def B_11100000
     *   8'b11100000
     */
    #define B_11100000 0xE0U
    /**
     * @def B_11100001
     *   8'b11100001
     */
    #define B_11100001 0xE1U
    /**
     * @def B_11100010
     *   8'b11100010
     */
    #define B_11100010 0xE2U
    /**
     * @def B_11100011
     *   8'b11100011
     */
    #define B_11100011 0xE3U
    /**
     * @def B_11100100
     *   8'b11100100
     */
    #define B_11100100 0xE4U
    /**
     * @def B_11100101
     *   8'b11100101
     */
    #define B_11100101 0xE5U
    /**
     * @def B_11100110
     *   8'b11100110
     */
    #define B_11100110 0xE6U
    /**
     * @def B_11100111
     *   8'b11100111
     */
    #define B_11100111 0xE7U
    /**
     * @def B_11101000
     *   8'b11101000
     */
    #define B_11101000 0xE8U
    /**
     * @def B_11101001
     *   8'b11101001
     */
    #define B_11101001 0xE9U
    /**
     * @def B_11101010
     *   8'b11101010
     */
    #define B_11101010 0xEAU
    /**
     * @def B_11101011
     *   8'b11101011
     */
    #define B_11101011 0xEBU
    /**
     * @def B_11101100
     *   8'b11101100
     */
    #define B_11101100 0xECU
    /**
     * @def B_11101001
     *   8'b11101101
     */
    #define B_11101101 0xEDU
    /**
     * @def B_11101110
     *   8'b11101110
     */
    #define B_11101110 0xEEU
    /**
     * @def B_11101111
     *   8'b11101111
     */
    #define B_11101111 0xEFU
    /**
     * @def B_11110000
     *   8'b11110000
     */
    #define B_11110000 0xF0U
    /**
     * @def B_11110001
     *   8'b11110001
     */
    #define B_11110001 0xF1U
    /**
     * @def B_11110010
     *   8'b11110010
     */
    #define B_11110010 0xF2U
    /**
     * @def B_11110011
     *   8'b11110011
     */
    #define B_11110011 0xF3U
    /**
     * @def B_11110100
     *   8'b11110100
     */
    #define B_11110100 0xF4U
    /**
     * @def B_11110101
     *   8'b11110101
     */
    #define B_11110101 0xF5U
    /**
     * @def B_11110110
     *   8'b11110110
     */
    #define B_11110110 0xF6U
    /**
     * @def B_11110111
     *   8'b11110111
     */
    #define B_11110111 0xF7U
    /**
     * @def B_11111000
     *   8'b11111000
     */
    #define B_11111000 0xF8U
    /**
     * @def B_11111001
     *   8'b11111001
     */
    #define B_11111001 0xF9U
    /**
     * @def B_11111010
     *   8'b11111010
     */
    #define B_11111010 0xFAU
    /**
     * @def B_11111011
     *   8'b11111011
     */
    #define B_11111011 0xFBU
    /**
     * @def B_11111100
     *   8'b11111100
     */
    #define B_11111100 0xFCU
    /**
     * @def B_11111101
     *   8'b11111101
     */
    #define B_11111101 0xFDU
    /**
     * @def B_11111110
     *   8'b11111110
     */
    #define B_11111110 0xFEU
    /**
     * @def B_11111111
     *   8'b11111111
     */
    #define B_11111111 0xFFU

    /**@}*/
#endif
