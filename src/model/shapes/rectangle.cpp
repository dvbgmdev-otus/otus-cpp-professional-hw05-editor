#include "model/shapes/rectangle.h"

namespace editor {
namespace model {

Rectangle::Rectangle(ShapeId id, const Point& top_left, double width, double height)
    : m_id(id), m_top_left(top_left), m_width(width), m_height(height) {}

ShapeId Rectangle::id() const { return m_id; }

const Point& Rectangle::topLeft() const { return m_top_left; }

double Rectangle::width() const { return m_width; }

double Rectangle::height() const { return m_height; }

}  // namespace model
}  // namespace editor
