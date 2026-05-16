#ifndef CONTROLLER_EDITOR_CONTROLLER_H
#define CONTROLLER_EDITOR_CONTROLLER_H

#include "model/document.h"
#include "model/shapes/point.h"

namespace editor {
namespace controller {

class EditorController {
public:
    EditorController();

    void createNewDocument();

    model::ShapeId createLine(const model::Point& start, const model::Point& end);
    model::ShapeId createRectangle(const model::Point& top_left, double width, double height);
    model::ShapeId createEllipse(const model::Point& center, double radius_x, double radius_y);

    bool removeShape(model::ShapeId id);

    const model::Document& document() const;

private:
    model::ShapeId nextShapeId();

    model::Document m_document;
    model::ShapeId m_next_shape_id;
};

}  // namespace controller
}  // namespace editor

#endif  // CONTROLLER_EDITOR_CONTROLLER_H
