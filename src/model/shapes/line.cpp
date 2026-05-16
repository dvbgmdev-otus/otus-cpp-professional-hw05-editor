#include "model/shapes/line.h"

#include "model/shapes/i_shape_visitor.h"

namespace editor {
namespace model {

Line::Line(ShapeId id, const Point& start, const Point& end)
    : BaseShape(id), m_start(start), m_end(end) {}

void Line::accept(IShapeVisitor& visitor) const {
    visitor.visit(*this);
}

const Point& Line::start() const { return m_start; }

const Point& Line::end() const { return m_end; }

}  // namespace model
}  // namespace editor
