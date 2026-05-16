#include "model/document.h"

#include <algorithm>
#include <utility>

namespace editor {
namespace model {

bool Document::addShape(ShapePtr shape) {
    if (!shape || containsShape(shape->id())) {
        return false;
    }

    m_shapes.push_back(std::move(shape));
    return true;
}

bool Document::removeShape(ShapeId id) {
    const auto it = std::find_if(m_shapes.begin(), m_shapes.end(), [id](const ShapePtr& shape) {
        return shape->id() == id;
    });

    if (it == m_shapes.end()) {
        return false;
    }

    m_shapes.erase(it);
    return true;
}

const Document::Shapes& Document::shapes() const { return m_shapes; }

bool Document::empty() const { return m_shapes.empty(); }

std::size_t Document::shapeCount() const { return m_shapes.size(); }

ShapeId Document::nextAvailableShapeId() const {
    if (m_shapes.empty()) {
        return 0;
    }

    const auto it = std::max_element(m_shapes.begin(), m_shapes.end(), [](const ShapePtr& left, const ShapePtr& right) {
        return left->id() < right->id();
    });

    return (*it)->id() + 1;
}

bool Document::containsShape(ShapeId id) const {
    return std::any_of(m_shapes.begin(), m_shapes.end(), [id](const ShapePtr& shape) {
        return shape->id() == id;
    });
}

}  // namespace model
}  // namespace editor
