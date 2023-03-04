/**
 * @file HSLAPixel.cpp
 *
 * @author Lin Shihan <shihanl.21@intl.zju.edu.cn>
 * @version 1.0.000
 * @date Feb. 14, 2023
 */

#include "HSLAPixel.h"


cs225::HSLAPixel::HSLAPixel(): h(0), s(0), l(1), a(1) {}


cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance)
    : h(hue), s(saturation), l(luminance), a(1) {}


cs225::HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha)
    : h(hue), s(saturation), l(luminance), a(alpha) {}
