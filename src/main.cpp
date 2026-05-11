#include <memory>

#include "debug_log.h"
#include "model/document.h"
#include "model/shapes/ellipse.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

int main() {
    DEBUG_LOG("Application started");

    const editor::model::Point origin{ 0.0, 0.0 };
    const editor::model::Point point{ 10.0, 10.0 };

    editor::model::Document document;

    document.addShape(std::make_unique<editor::model::Line>(1, origin, point));
    document.addShape(std::make_unique<editor::model::Rectangle>(2, origin, 100.0, 50.0));
    document.addShape(std::make_unique<editor::model::Ellipse>(3, point, 20.0, 10.0));

    static_cast<void>(document);

    return 0;
}
