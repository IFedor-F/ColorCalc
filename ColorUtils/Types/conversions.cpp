//
// Created by _Fedor_F on 05.03.2025.
//

#include <cmath>

#include "HEX.h"
#include "RGB.h"
#include "Lab.h"
#include "LCh.h"
#include "XYZ.h"

using namespace ColorUtils;

static double gamma_correction(const double c) {
    if (c <= 0.04045)
        return c / 12.92;
    return pow((c + 0.055) / 1.055, 2.4);
}

static double inverse_gamma_correction(const double c) {
    return c <= 0.0031308 ? 12.92 * c : 1.055 * pow(c, 1.0 / 2.4) - 0.055;
}

// Function to apply the CIE 1931 standard transformation to the XYZ values
// This function is part of the conversion from XYZ to Lab
static double F(const double t) {
    if (t > 0.008856)
        return pow(t, 1.0 / 3.0); // If t is greater than 0.008856, use cube root transformation
    return (903.3 * t + 16.0) / 116.0; // Otherwise, apply the linear transformation
}

static double inverse_F(const double t) {
    return t > 6.0 / 29.0 ? t * t * t : (t - 16.0 / 116.0) / 7.787;
}

static unsigned char clamp2rgb(double value) {
    if (value < 0.0) value = 0.0;
    if (value > 1.0) value = 1.0;
    return static_cast<unsigned char>(round(value * 255.0));
}


RGB::RGB(const XYZ &xyz) {
    //XYZ . linear RGB (sRGB)
    const double r = xyz.X * 3.2406 + xyz.Y * -1.5372 + xyz.Z * -0.4986;
    const double g = xyz.X * -0.9689 + xyz.Y * 1.8758 + xyz.Z * 0.0415;
    const double b = xyz.X * 0.0557 + xyz.Y * -0.2040 + xyz.Z * 1.0570;

    R = clamp2rgb(inverse_gamma_correction(r));
    G = clamp2rgb(inverse_gamma_correction(g));
    B = clamp2rgb(inverse_gamma_correction(b));
}

XYZ::XYZ(const Lab &lab) {
    const double fy = (lab.L + 16.0) / 116.0;
    const double fx = fy + lab.a / 500.0;
    const double fz = fy - lab.b / 200.0;

    X = inverse_F(fx) * 0.95047;
    Y = inverse_F(fy) * 1.00000;
    Z = inverse_F(fz) * 1.08883;
}


RGB::RGB(const Lab &lab): RGB(XYZ(lab)) {
}


LCh::LCh(const Lab &lab) {
    L = lab.L;
    C = hypot(lab.a, lab.b);
    h = atan2(lab.b, lab.a) * (180.0 / M_PI);
    h = h < 0 ? h + 360.0 : h;
}

XYZ::XYZ(const RGB &rgb) {
    // Apply gamma correction to each RGB component (normalize to [0, 1] ranges)
    const double r = gamma_correction(rgb.R / 255.0); // Red component
    const double g = gamma_correction(rgb.G / 255.0); // Green component
    const double b = gamma_correction(rgb.B / 255.0); // Blue component

    // Linear transformation from RGB to XYZ color space using standard sRGB-to-XYZ matrix
    X = r * 0.4124 + g * 0.3576 + b * 0.1805;
    Y = r * 0.2126 + g * 0.7152 + b * 0.0722;
    Z = r * 0.0193 + g * 0.1192 + b * 0.9505;
}


// The XYZ values are normalized to the D65 illuminant and then converted to Lab
Lab::Lab(const XYZ &xyz) {
    // Normalize XYZ values by the D65 reference white
    const double x = xyz.X / 0.95047;
    const double y = xyz.Y / 1.00000;
    const double z = xyz.Z / 1.08883;

    L = 116 * F(y) - 16; // lightness
    a = 500 * (F(x) - F(y)); // green to red
    b = 200 * (F(y) - F(z)); // blue to yellow
}


Lab::Lab(const RGB &rgb): Lab(XYZ(rgb)) {
}

LCh::LCh(const RGB &rgb): LCh(Lab(rgb)) {
}

Lab::Lab(const LCh &lch) {
    const double h_rad = lch.h * (M_PI / 180.0);
    L = lch.L;
    a = lch.C * cos(h_rad);
    b = lch.C * sin(h_rad);
}


LCh::LCh(const XYZ &xyz): LCh(Lab(xyz)) {
}

XYZ::XYZ(const LCh &lch): XYZ(Lab(lch)) {
}

RGB::RGB(const LCh &lch): RGB(XYZ(lch)) {
}

RGB::RGB(const HEX &hex) {
    R = (hex.toInt() & 0x00ff0000) >> 16;
    G = (hex.toInt() & 0x0000ff00) >> 8;
    B = hex.toInt() & 0x0000ff;
}

HEX::HEX(const RGB &rgb) {
    value = rgb.R << 16 | rgb.G << 8 | rgb.B;
}

HEX::HEX(const Lab &lab): HEX(RGB(lab)) {
}

HEX::HEX(const LCh &lch): HEX(RGB(lch)) {
}

HEX::HEX(const XYZ &xyz): HEX(RGB(xyz)) {
}

Lab::Lab(const HEX &hex): Lab(RGB(hex)) {
}

LCh::LCh(const HEX &hex): LCh(RGB(hex)) {
}

XYZ::XYZ(const HEX &hex): XYZ(RGB(hex)) {
}
