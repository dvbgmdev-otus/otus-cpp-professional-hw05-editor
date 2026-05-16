#include "controller/editor_controller.h"

#include "model/shapes/ellipse.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <memory>

namespace editor {
namespace controller {

EditorController::EditorController(io::IDocumentIO& document_io) : m_document_io(document_io), m_next_shape_id(0) {}

void EditorController::createNewDocument() {
    m_document = model::Document();
    m_next_shape_id = 0;
}

bool EditorController::importDocument(const std::string& path) {
    const auto result = m_document_io.importDocument(path, m_document);
    if (result) {
        m_next_shape_id = m_document.nextAvailableShapeId();
    }
    return result;
}

bool EditorController::exportDocument(const std::string& path) const {
    return m_document_io.exportDocument(m_document, path);
}

model::ShapeId EditorController::createLine(const model::Point& start, const model::Point& end) {
    const auto id = nextShapeId();
    m_document.addShape(std::make_unique<model::Line>(id, start, end));
    return id;
}

model::ShapeId EditorController::createRectangle(const model::Point& top_left, double width, double height) {
    const auto id = nextShapeId();
    m_document.addShape(std::make_unique<model::Rectangle>(id, top_left, width, height));
    return id;
}

model::ShapeId EditorController::createEllipse(const model::Point& center, double radius_x, double radius_y) {
    const auto id = nextShapeId();
    m_document.addShape(std::make_unique<model::Ellipse>(id, center, radius_x, radius_y));
    return id;
}

bool EditorController::removeShape(model::ShapeId id) {
    return m_document.removeShape(id);
}

const model::Document& EditorController::document() const {
    return m_document;
}

model::ShapeId EditorController::nextShapeId() {
    return m_next_shape_id++;
}

}  // namespace controller
}  // namespace editor
