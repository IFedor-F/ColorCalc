//
// Created by _Fedor_F on 05.03.2025.
//

#include "RGB.h"
using namespace ColorUtils;

RGB::RGB(): R(), G(), B() {
}

RGB::RGB(const int R, const int G, const int B): R(R), G(G), B(B) {
}

bool RGB::operator==(const RGB &rgb) const {
    return R == rgb.R && G == rgb.G && B == rgb.B;
}
