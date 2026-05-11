#ifndef MODEL_SHAPES_BASE_SHAPE_H
#define MODEL_SHAPES_BASE_SHAPE_H

#include "model/shapes/i_shape.h"

namespace editor {
namespace model {

class BaseShape : public IShape {
public:
    ShapeId id() const override;

protected:
    explicit BaseShape(ShapeId id);

private:
    ShapeId m_id;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_BASE_SHAPE_H
