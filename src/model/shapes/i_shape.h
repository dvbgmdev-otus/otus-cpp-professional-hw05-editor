#ifndef MODEL_SHAPES_I_SHAPE_H
#define MODEL_SHAPES_I_SHAPE_H

#include "model/shapes/shape_id.h"

namespace editor {
namespace model {

class IShape {
public:
    virtual ~IShape() = default;
    virtual ShapeId id() const = 0;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_I_SHAPE_H
