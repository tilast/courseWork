#include "figure.h"

Figure::~Figure()
{
}

DrawStyle& Figure::getStyle() {
    return style;
}

const DrawStyle& Figure::getStyle() const {
    return style;
}
