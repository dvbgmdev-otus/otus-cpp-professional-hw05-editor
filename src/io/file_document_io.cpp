#include "io/file_document_io.h"

#include <fstream>

namespace editor {
namespace io {

bool FileDocumentIO::importDocument(const std::string& path, model::Document& document) const {
    std::ifstream input(path);
    if (!input) {
        return false;
    }

    document = model::Document();
    return true;
}

bool FileDocumentIO::exportDocument(const model::Document& document, const std::string& path) const {
    std::ofstream output(path);
    if (!output) {
        return false;
    }

    output << "shapes: " << document.shapeCount() << '\n';
    return static_cast<bool>(output);
}

}  // namespace io
}  // namespace editor
