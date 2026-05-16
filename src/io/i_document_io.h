#ifndef IO_I_DOCUMENT_IO_H
#define IO_I_DOCUMENT_IO_H

#include "model/document.h"

#include <string>

namespace editor {
namespace io {

/**
 * @brief Интерфейс импорта и экспорта документа.
 * @ingroup io_group
 */
class IDocumentIO {
public:
    virtual ~IDocumentIO() = default;

    /**
     * @brief Загружает документ из внешнего источника.
     * @param path Путь к источнику данных.
     * @param document Документ, который будет заменен загруженными данными при успешном импорте.
     * @return true, если импорт выполнен успешно; иначе false.
     */
    virtual bool importDocument(const std::string& path, model::Document& document) const = 0;

    /**
     * @brief Сохраняет документ во внешний источник.
     * @param document Документ для сохранения.
     * @param path Путь к целевому файлу или ресурсу.
     * @return true, если экспорт выполнен успешно; иначе false.
     */
    virtual bool exportDocument(const model::Document& document, const std::string& path) const = 0;
};

}  // namespace io
}  // namespace editor

#endif  // IO_I_DOCUMENT_IO_H
