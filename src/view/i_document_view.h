#ifndef VIEW_I_DOCUMENT_VIEW_H
#define VIEW_I_DOCUMENT_VIEW_H

#include "model/document.h"

namespace editor {
namespace view {

/**
 * @brief Интерфейс представления документа.
 * @ingroup view_group
 */
class IDocumentView {
public:
    virtual ~IDocumentView() = default;

    /**
     * @brief Отображает состояние документа.
     * @param document Документ для отображения.
     */
    virtual void render(const model::Document& document) const = 0;
};

}  // namespace view
}  // namespace editor

#endif  // VIEW_I_DOCUMENT_VIEW_H
