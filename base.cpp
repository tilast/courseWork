#include "base.h"

#include <cmath>
#include <iostream>

const Color Color::blackColor = Color(0., 0., 0.);
const Color Color::whiteColor = Color(1., 1., 1.);
const Color Color::grayColor = Color(.5, .5, .5);

Color::Color(   ColorChannel red, ColorChannel green, ColorChannel blue,
                ColorChannel alpha)
                : red(red), green(green), blue(blue), alpha(alpha)
                {}

DrawStyle::DrawStyle(Color lineColor, Color fillColor)
                : lineColor(lineColor), fillColor(fillColor)
                {}
