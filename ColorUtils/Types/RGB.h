//
// Created by _Fedor_F on 05.03.2025.
//

#ifndef RGB_H
#define RGB_H
#include <cstddef>
#include <cstdint>
#include <functional>

namespace ColorUtils {
    class HEX;
    class XYZ;
    class LCh;
    class Lab;

    class RGB {
    public:
        union {
            struct {
                uint8_t R, G, B;
            };

            uint8_t components[3]{};
        };

        RGB();

        RGB(int R, int G, int B);

        explicit RGB(const Lab &lab);

        explicit RGB(const LCh &lch);

        explicit RGB(const XYZ &xyz);

        explicit RGB(const HEX &hex);

        bool operator==(const RGB &rgb) const;

        uint8_t &operator[](const std::size_t index) {
            return components[index];
        }
    };
} // ColorUtils
template<>
struct std::hash<ColorUtils::RGB> {
    std::size_t operator()(const ColorUtils::RGB &rgb) const noexcept {
        return std::hash<int>()(rgb.R << 16 | rgb.G << 8 | rgb.B);
    }
};

#endif //RGB_H
