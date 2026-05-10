#ifndef MODEL_SHAPES_RECTANGLE_H
#define MODEL_SHAPES_RECTANGLE_H

#include "model/shapes/i_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Rectangle final : public IShape {
public:
    Rectangle(ShapeId id, const Point& top_left, double width, double height)
        : m_id(id),
          m_top_left(top_left),
          m_width(width),
          m_height(height) {
    }

    ShapeId id() const override {
        return m_id;
    }

    const Point& topLeft() const {
        return m_top_left;
    }

    double width() const {
        return m_width;
    }

    double height() const {
        return m_height;
    }

private:
    ShapeId m_id;
    Point m_top_left;
    double m_width;
    double m_height;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_RECTANGLE_H
