#include "controller/editor_controller.h"
#include "debug_log.h"

namespace {

void onNewDocument(editor::controller::EditorController& controller) {
    controller.createNewDocument();
}

void onCreateLine(editor::controller::EditorController& controller) {
    const editor::model::Point start{ 0.0, 0.0 };
    const editor::model::Point end{ 10.0, 10.0 };

    controller.createLine(start, end);
}

void onCreateRectangle(editor::controller::EditorController& controller) {
    const editor::model::Point top_left{ 0.0, 0.0 };

    controller.createRectangle(top_left, 100.0, 50.0);
}

void onCreateEllipse(editor::controller::EditorController& controller) {
    const editor::model::Point center{ 10.0, 10.0 };

    controller.createEllipse(center, 20.0, 10.0);
}

void onDeleteShape(editor::controller::EditorController& controller, editor::model::ShapeId id) {
    controller.removeShape(id);
}

}  // namespace

int main() {
    DEBUG_LOG("Application started");

    editor::controller::EditorController controller;

    onNewDocument(controller);
    onCreateLine(controller);
    onCreateRectangle(controller);
    onCreateEllipse(controller);
    onDeleteShape(controller, 2);

    return 0;
}
