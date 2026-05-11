#ifndef MODEL_SHAPES_LINE_H
#define MODEL_SHAPES_LINE_H

#include "model/shapes/base_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

class Line final : public BaseShape {
public:
    Line(ShapeId id, const Point& start, const Point& end);
    const Point& start() const;
    const Point& end() const;

private:
    Point m_start;
    Point m_end;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_LINE_H
