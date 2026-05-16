#ifndef VIEW_CONSOLE_DOCUMENT_VIEW_H
#define VIEW_CONSOLE_DOCUMENT_VIEW_H

#include "view/i_document_view.h"

namespace editor {
namespace view {

/**
 * @brief Консольное представление документа.
 * @ingroup view_group
 */
class ConsoleDocumentView final : public IDocumentView {
public:
    /**
     * @brief Выводит краткое состояние документа в стандартный вывод.
     * @param document Документ для отображения.
     */
    void render(const model::Document& document) const override;
};

}  // namespace view
}  // namespace editor

#endif  // VIEW_CONSOLE_DOCUMENT_VIEW_H
