//
// Created by _Fedor_F on 05.03.2025.
//

#ifndef HSV_H
#define HSV_H
#include <cstddef>

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

        double &operator[](const std::size_t index) {
            return components[index];
        }
    };
} // ColorUtils

#endif //HSV_H
