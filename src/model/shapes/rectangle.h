#ifndef MODEL_SHAPES_RECTANGLE_H
#define MODEL_SHAPES_RECTANGLE_H

#include "model/shapes/base_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Rectangle final : public BaseShape {
public:
    Rectangle(ShapeId id, const Point& top_left, double width, double height);

    void accept(IShapeVisitor& visitor) const override;

    const Point& topLeft() const;
    double width() const;
    double height() const;

private:
    Point m_top_left;
    double m_width;
    double m_height;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_RECTANGLE_H
