#ifndef CONTROLLER_EDITOR_CONTROLLER_H
#define CONTROLLER_EDITOR_CONTROLLER_H

#include "io/i_document_io.h"
#include "model/document.h"
#include "model/shapes/point.h"

#include <string>

namespace editor {
namespace controller {

class EditorController {
public:
    explicit EditorController(io::IDocumentIO& document_io);

    void createNewDocument();
    bool importDocument(const std::string& path);
    bool exportDocument(const std::string& path) const;

    model::ShapeId createLine(const model::Point& start, const model::Point& end);
    model::ShapeId createRectangle(const model::Point& top_left, double width, double height);
    model::ShapeId createEllipse(const model::Point& center, double radius_x, double radius_y);

    bool removeShape(model::ShapeId id);

    const model::Document& document() const;

private:
    model::ShapeId nextShapeId();

    io::IDocumentIO& m_document_io;
    model::Document m_document;
    model::ShapeId m_next_shape_id;
};

}  // namespace controller
}  // namespace editor

#endif  // CONTROLLER_EDITOR_CONTROLLER_H
