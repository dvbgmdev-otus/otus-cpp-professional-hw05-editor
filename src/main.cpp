#include "controller/editor_controller.h"
#include "debug_log.h"
#include "io/file_document_io.h"
#include "view/console_document_view.h"

#include <string>

namespace {

std::string getApplicationDirectory(const char* application_path) {
    const std::string path(application_path ? application_path : "");
    const auto separator_pos = path.find_last_of("/\\");

    if (separator_pos == std::string::npos) {
        return ".";
    }

    return path.substr(0, separator_pos);
}

std::string makeApplicationFilePath(const std::string& application_directory, const std::string& file_name) {
    return application_directory + "/" + file_name;
}

void onNewDocument(editor::controller::EditorController& controller) {
    controller.createNewDocument();
}

void onImportDocument(editor::controller::EditorController& controller, const std::string& path) {
    controller.importDocument(path);
}

void onExportDocument(editor::controller::EditorController& controller, const std::string& path) {
    controller.exportDocument(path);
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

void onRenderDocument(const editor::controller::EditorController& controller, const editor::view::IDocumentView& view) {
    view.render(controller.document());
}

}  // namespace

int main(int argc, char* argv[]) {
    DEBUG_LOG("Application started");

    static_cast<void>(argc);

    const auto application_directory = getApplicationDirectory(argv[0]);
    const auto input_path = makeApplicationFilePath(application_directory, "input.editor");
    const auto output_path = makeApplicationFilePath(application_directory, "output.editor");

    editor::io::FileDocumentIO document_io;
    editor::view::ConsoleDocumentView document_view;
    editor::controller::EditorController controller(document_io);

    onNewDocument(controller);
    onImportDocument(controller, input_path);
    onCreateLine(controller);
    onCreateRectangle(controller);
    onCreateEllipse(controller);
    onDeleteShape(controller, 2);
    onRenderDocument(controller, document_view);
    onExportDocument(controller, output_path);

    return 0;
}
