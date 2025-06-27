//
// Created by _Fedor_F on 05.03.2025.
//

#ifndef LAB_H
#define LAB_H
#include <cstddef>
#include "functional"

namespace ColorUtils {
    class HEX;
    class XYZ;
    class LCh;
    class RGB;

    class Lab {
    public:
        union {
            struct {
                double L, a, b;
            };

            double components[3]{};
        };

        Lab();

        Lab(double L, double a, double b);

        explicit Lab(const RGB &rgb);

        explicit Lab(const LCh &lch);

        explicit Lab(const XYZ &xyz);

        explicit Lab(const HEX &hex);

        bool operator==(const Lab &lab) const;

        double &operator[](const std::size_t index) {
            return components[index];
        }
    };
} // ColorUtils

template<>
struct std::hash<ColorUtils::Lab> {
    std::size_t operator()(const ColorUtils::Lab &lab) const noexcept {
        return hash<double>()(lab.L) ^ (hash<double>()(lab.a) << 1) ^ (hash<double>()(lab.b) << 2);
    }
};

#endif //LAB_H
