//
// Created by _Fedor_F on 07.03.2025.
//

#include "HEX.h"

#include <algorithm>
#include <iomanip>
#include "functional"
using namespace ColorUtils;

HEX::HEX(const uint32_t value): value(value) {
}

HEX::HEX(): value(0) {
}

HEX::HEX(const std::string &str) {
    const auto it = std::ranges::find_if(str, [](const unsigned char ch) {
        return std::isxdigit(ch);
    });
    if (it != str.end()) {
        value = std::stoi(std::string(it, str.end()), nullptr, 16);
    } else {
        throw std::invalid_argument("Invalid Hexadecimal string");
    }
};

uint32_t HEX::toInt() const {
    return value;
};

std::string HEX::toHex() const {
    std::stringstream ss;
    ss << std::setw(6) << std::setfill('0') << std::hex << value;
    return ss.str();
};

std::string HEX::toString() const {
    std::stringstream ss;
    ss << "#" << std::setw(6) << std::setfill('0') << std::uppercase << std::hex << value;
    return ss.str();
}

bool HEX::operator==(const HEX &hex) const {
    return value == hex.value;
}

template<>
struct std::hash<HEX> {
    std::size_t operator()(const HEX &hex) const noexcept {
        return hash<uint32_t>()(hex.toInt());
    }
};
