//
// Created by _Fedor_F on 05.03.2025.
//

#include "LCh.h"
#include "functional"
using namespace ColorUtils;

LCh::LCh(): L(), C(), h() {
}

LCh::LCh(const double L, const double C, const double h): L(L), C(C), h(h) {
}

bool LCh::operator==(const LCh &lch) const {
    return L == lch.L && C == lch.C && h == lch.h;
}

template<>
struct std::hash<LCh> {
    std::size_t operator()(const LCh &lch) const noexcept {
        return hash<double>()(lch.L) ^ (hash<double>()(lch.C) << 1) ^ (hash<double>()(lch.h) << 2);
    }
};
