//
// Created by _Fedor_F on 07.03.2025.
//

#ifndef HEX_H
#define HEX_H
#include <cstdint>
#include <string>
#include "functional"

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

        bool operator==(const HEX &hex) const;

        [[nodiscard]] uint32_t toInt() const;

        [[nodiscard]] std::string toHex() const;

        [[nodiscard]] std::string toString() const;
    };
} // ColorUtils

template<>
struct std::hash<ColorUtils::HEX> {
    std::size_t operator()(const ColorUtils::HEX &hex) const noexcept {
        return hash<uint32_t>()(hex.toInt());
    }
};
#endif //HEX_H
