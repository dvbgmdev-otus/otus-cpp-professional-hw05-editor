#ifndef MODEL_SHAPES_ELLIPSE_H
#define MODEL_SHAPES_ELLIPSE_H

#include "model/shapes/i_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Ellipse final : public IShape {
public:
    Ellipse(ShapeId id, const Point& center, double radius_x, double radius_y);
    ShapeId id() const override;
    const Point& center() const;
    double radiusX() const;
    double radiusY() const;

private:
    ShapeId m_id;
    Point m_center;
    double m_radius_x;
    double m_radius_y;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_ELLIPSE_H
