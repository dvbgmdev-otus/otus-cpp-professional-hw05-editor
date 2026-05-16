#include "io/file_document_io.h"

#include "model/shapes/ellipse.h"
#include "model/shapes/i_shape_visitor.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <fstream>
#include <memory>
#include <string>

namespace editor {
namespace io {
namespace {

class ShapeExportVisitor final : public model::IShapeVisitor {
public:
    explicit ShapeExportVisitor(std::ostream& output) : m_output(output) {}

    void visit(const model::Line& line) override {
        m_output << "line " << line.id() << ' ' << line.start().x << ' ' << line.start().y << ' ' << line.end().x << ' '
                 << line.end().y << '\n';
    }

    void visit(const model::Rectangle& rectangle) override {
        m_output << "rectangle " << rectangle.id() << ' ' << rectangle.topLeft().x << ' ' << rectangle.topLeft().y << ' '
                 << rectangle.width() << ' ' << rectangle.height() << '\n';
    }

    void visit(const model::Ellipse& ellipse) override {
        m_output << "ellipse " << ellipse.id() << ' ' << ellipse.center().x << ' ' << ellipse.center().y << ' '
                 << ellipse.radiusX() << ' ' << ellipse.radiusY() << '\n';
    }

private:
    std::ostream& m_output;
};

bool importLine(std::istream& input, model::Document& document) {
    model::ShapeId id = 0;
    model::Point start{ 0.0, 0.0 };
    model::Point end{ 0.0, 0.0 };

    if (!(input >> id >> start.x >> start.y >> end.x >> end.y)) {
        return false;
    }

    return document.addShape(std::make_unique<model::Line>(id, start, end));
}

bool importRectangle(std::istream& input, model::Document& document) {
    model::ShapeId id = 0;
    model::Point top_left{ 0.0, 0.0 };
    double width = 0.0;
    double height = 0.0;

    if (!(input >> id >> top_left.x >> top_left.y >> width >> height)) {
        return false;
    }

    return document.addShape(std::make_unique<model::Rectangle>(id, top_left, width, height));
}

bool importEllipse(std::istream& input, model::Document& document) {
    model::ShapeId id = 0;
    model::Point center{ 0.0, 0.0 };
    double radius_x = 0.0;
    double radius_y = 0.0;

    if (!(input >> id >> center.x >> center.y >> radius_x >> radius_y)) {
        return false;
    }

    return document.addShape(std::make_unique<model::Ellipse>(id, center, radius_x, radius_y));
}

}  // namespace

bool FileDocumentIO::importDocument(const std::string& path, model::Document& document) const {
    std::ifstream input(path);
    if (!input) {
        return false;
    }

    model::Document imported_document;
    std::string shape_type;

    while (input >> shape_type) {
        if (shape_type == "line") {
            if (!importLine(input, imported_document)) {
                return false;
            }
        } else if (shape_type == "rectangle") {
            if (!importRectangle(input, imported_document)) {
                return false;
            }
        } else if (shape_type == "ellipse") {
            if (!importEllipse(input, imported_document)) {
                return false;
            }
        } else {
            return false;
        }
    }

    document = std::move(imported_document);
    return true;
}

bool FileDocumentIO::exportDocument(const model::Document& document, const std::string& path) const {
    std::ofstream output(path);
    if (!output) {
        return false;
    }

    ShapeExportVisitor visitor(output);
    for (const auto& shape : document.shapes()) {
        shape->accept(visitor);
    }

    return static_cast<bool>(output);
}

}  // namespace io
}  // namespace editor
