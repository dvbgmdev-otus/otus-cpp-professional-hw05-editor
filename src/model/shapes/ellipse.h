#ifndef MODEL_SHAPES_ELLIPSE_H
#define MODEL_SHAPES_ELLIPSE_H

#include "model/shapes/i_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Ellipse final : public IShape {
public:
    Ellipse(ShapeId id, const Point& center, double radius_x, double radius_y)
        : m_id(id),
          m_center(center),
          m_radius_x(radius_x),
          m_radius_y(radius_y) {
    }

    ShapeId id() const override {
        return m_id;
    }

    const Point& center() const {
        return m_center;
    }

    double radiusX() const {
        return m_radius_x;
    }

    double radiusY() const {
        return m_radius_y;
    }

private:
    ShapeId m_id;
    Point m_center;
    double m_radius_x;
    double m_radius_y;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_ELLIPSE_H
