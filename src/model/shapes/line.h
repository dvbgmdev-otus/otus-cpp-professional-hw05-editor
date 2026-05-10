#ifndef MODEL_SHAPES_LINE_H
#define MODEL_SHAPES_LINE_H

#include "model/shapes/i_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Line final : public IShape {
public:
    Line(ShapeId id, const Point& start, const Point& end)
        : m_id(id),
          m_start(start),
          m_end(end) {
    }

    ShapeId id() const override {
        return m_id;
    }

    const Point& start() const {
        return m_start;
    }

    const Point& end() const {
        return m_end;
    }

private:
    ShapeId m_id;
    Point m_start;
    Point m_end;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_LINE_H
