#include "model/shapes/line.h"

namespace editor {
namespace model {

Line::Line(ShapeId id, const Point& start, const Point& end)
    : m_id(id), m_start(start), m_end(end) {}

ShapeId Line::id() const { return m_id; }

const Point& Line::start() const { return m_start; }

const Point& Line::end() const { return m_end; }

}  // namespace model
}  // namespace editor
