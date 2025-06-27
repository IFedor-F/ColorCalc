//
// Created by _Fedor_F on 05.03.2025.
//

#ifndef HSV_H
#define HSV_H
#include <cstddef>
#include <functional>

namespace ColorUtils {
    class HEX;
    class XYZ;
    class Lab;
    class RGB;

    class LCh {
    public:
        union {
            struct {
                double L, C, h;
            };

            double components[3]{};
        };

        LCh();

        LCh(double L, double C, double h);

        explicit LCh(const RGB &rgb);

        explicit LCh(const Lab &lab);

        explicit LCh(const XYZ &xyz);

        explicit LCh(const HEX &hex);

        bool operator==(const LCh &lch) const;

        double &operator[](const std::size_t index) {
            return components[index];
        }
    };
} // ColorUtils

template<>
struct std::hash<ColorUtils::LCh> {
    std::size_t operator()(const ColorUtils::LCh &lch) const noexcept {
        return hash<double>()(lch.L) ^ (hash<double>()(lch.C) << 1) ^ (hash<double>()(lch.h) << 2);
    }
};
#endif //HSV_H
