#ifndef MODEL_SHAPES_I_SHAPE_VISITOR_H
#define MODEL_SHAPES_I_SHAPE_VISITOR_H

namespace editor {
namespace model {

class Ellipse;
class Line;
class Rectangle;

class IShapeVisitor {
public:
    virtual ~IShapeVisitor() = default;

    virtual void visit(const Line& line) = 0;
    virtual void visit(const Rectangle& rectangle) = 0;
    virtual void visit(const Ellipse& ellipse) = 0;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_I_SHAPE_VISITOR_H
