//
// Created by _Fedor_F on 05.03.2025.
//

#include "LCh.h"
using namespace ColorUtils;

LCh::LCh(): L(), C(), h() {
}

LCh::LCh(const double L, const double C, const double h): L(L), C(C), h(h) {
}

bool LCh::operator==(const LCh &lch) const {
    return L == lch.L && C == lch.C && h == lch.h;
}
