#ifndef MODEL_DOCUMENT_H
#define MODEL_DOCUMENT_H

#include <cstddef>
#include <memory>
#include <vector>

#include "model/shapes/i_shape.h"

namespace editor {
namespace model {

class Document {
public:
    using ShapePtr = std::unique_ptr<IShape>;
    using Shapes = std::vector<ShapePtr>;

    bool addShape(ShapePtr shape);
    bool removeShape(ShapeId id);

    const Shapes& shapes() const;
    bool empty() const;
    std::size_t shapeCount() const;
    ShapeId nextAvailableShapeId() const;

private:
    bool containsShape(ShapeId id) const;

    Shapes m_shapes;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_DOCUMENT_H
