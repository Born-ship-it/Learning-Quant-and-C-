// ======================================================================
// shapes.cpp
// ======================================================================

#include "shapes.h"

double totalArea(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double sum = 0.0;
    for (const auto& s : shapes)
        sum += s->area();
    return sum;
}

void drawAll(const std::vector<std::unique_ptr<Shape>>& shapes, std::ostream& os) {
    for (const auto& s : shapes) {
        s->draw(os);
        os << '\n';
    }
}