#include "model/shapes/ellipse.h"

#include "model/shapes/i_shape_visitor.h"

namespace editor {
namespace model {

Ellipse::Ellipse(ShapeId id, const Point& center, double radius_x, double radius_y)
    : BaseShape(id), m_center(center), m_radius_x(radius_x), m_radius_y(radius_y) {}

void Ellipse::accept(IShapeVisitor& visitor) const {
    visitor.visit(*this);
}

const Point& Ellipse::center() const { return m_center; }

double Ellipse::radiusX() const { return m_radius_x; }

double Ellipse::radiusY() const { return m_radius_y; }

}  // namespace model
}  // namespace editor
