#include "model/shapes/base_shape.h"

namespace editor {
namespace model {

BaseShape::BaseShape(ShapeId id) : m_id(id) {}

ShapeId BaseShape::id() const { return m_id; }

}  // namespace model
}  // namespace editor
