#include "model/shapes/rectangle.h"

#include "model/shapes/i_shape_visitor.h"

namespace editor {
namespace model {

Rectangle::Rectangle(ShapeId id, const Point& top_left, double width, double height)  // NOLINT(bugprone-easily-swappable-parameters)
    : BaseShape(id), m_top_left(top_left), m_width(width), m_height(height) {}

void Rectangle::accept(IShapeVisitor& visitor) const {
    visitor.visit(*this);
}

const Point& Rectangle::topLeft() const { return m_top_left; }

double Rectangle::width() const { return m_width; }

double Rectangle::height() const { return m_height; }

}  // namespace model
}  // namespace editor
