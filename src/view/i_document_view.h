#ifndef VIEW_I_DOCUMENT_VIEW_H
#define VIEW_I_DOCUMENT_VIEW_H

#include "model/document.h"

namespace editor {
namespace view {

class IDocumentView {
public:
    virtual ~IDocumentView() = default;

    virtual void render(const model::Document& document) const = 0;
};

}  // namespace view
}  // namespace editor

#endif  // VIEW_I_DOCUMENT_VIEW_H
