//
// Created by _Fedor_F on 07.03.2025.
//

#ifndef HEX_H
#define HEX_H
#include <cstdint>
#include <string>


namespace ColorUtils {
    class XYZ;
    class LCh;
    class Lab;
    class RGB;

    class HEX {
        uint32_t value;

    public:
        HEX();

        explicit HEX(uint32_t value);

        explicit HEX(const Lab &lab);

        explicit HEX(const LCh &lch);

        explicit HEX(const XYZ &xyz);

        explicit HEX(const RGB &rgb);

        explicit HEX(const std::string &str);

        uint32_t toInt() const;

        std::string toHex() const;

        std::string toString() const;
    };
} // ColorUtils

#endif //HEX_H
