#ifndef MODEL_SHAPES_RECTANGLE_H
#define MODEL_SHAPES_RECTANGLE_H

#include "model/shapes/i_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Rectangle final : public IShape {
public:
    Rectangle(ShapeId id, const Point& top_left, double width, double height);
    ShapeId id() const override;
    const Point& topLeft() const;
    double width() const;
    double height() const;

private:
    ShapeId m_id;
    Point m_top_left;
    double m_width;
    double m_height;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_RECTANGLE_H
