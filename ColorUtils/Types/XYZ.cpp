//
// Created by _Fedor_F on 05.03.2025.
//

#include "XYZ.h"
#include "functional"
using namespace ColorUtils;

XYZ::XYZ(): X(), Y(), Z() {
}

XYZ::XYZ(const double X, const double Y, const double Z): X(X), Y(Y), Z(Z) {
}
bool XYZ::operator==(const XYZ &xyz) const {
    return X == xyz.X && Y == xyz.Y && Z == xyz.Z;
}

template<>
struct std::hash<XYZ> {
    std::size_t operator()(const XYZ &xyz) const noexcept {
        return hash<double>()(xyz.X) ^ (hash<double>()(xyz.Y) << 1) ^ (hash<double>()(xyz.Z) << 2);
    }
};
