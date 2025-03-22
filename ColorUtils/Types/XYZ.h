//
// Created by _Fedor_F on 05.03.2025.
//

#ifndef XYZ_H
#define XYZ_H
#include <cstddef>

namespace ColorUtils {
    class HEX;
}

namespace ColorUtils {
    class LCh;
    class Lab;
    class RGB;

    class XYZ {
    public:
        union {
            struct {
                double X, Y, Z;
            };

            double components[3]{};
        };

        XYZ();

        XYZ(double X, double Y, double Z);

        explicit XYZ(const RGB &rgb);

        explicit XYZ(const Lab &lab);

        explicit XYZ(const LCh &lch);

        explicit XYZ(const HEX &hex);

        bool operator==(const XYZ &xyz) const;

        double &operator[](const std::size_t index) {
            return components[index];
        }
    };
} // ColorUtils
#endif //XYZ_H
