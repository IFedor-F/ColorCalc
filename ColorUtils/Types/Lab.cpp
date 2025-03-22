//
// Created by _Fedor_F on 05.03.2025.
//

#include "Lab.h"
#include "functional"
#include "LCh.h"
using namespace ColorUtils;

Lab::Lab(): L(), a(), b() {
}

Lab::Lab(const double L, const double a, const double b): L(L), a(a), b(b) {
}

bool Lab::operator==(const Lab &lab) const {
    return L == lab.L && a == lab.a && b == lab.b;
}

template<>
struct std::hash<Lab> {
    std::size_t operator()(const Lab &lab) const noexcept {
        return hash<double>()(lab.L) ^ (hash<double>()(lab.a) << 1) ^ (hash<double>()(lab.b) << 2);
    }
};
