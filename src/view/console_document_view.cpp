#include "view/console_document_view.h"

#include <iostream>

namespace editor {
namespace view {

void ConsoleDocumentView::render(const model::Document& document) const {
    std::cout << "Document shapes: " << document.shapeCount() << '\n';
}

}  // namespace view
}  // namespace editor
