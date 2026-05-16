#ifndef IO_FILE_DOCUMENT_IO_H
#define IO_FILE_DOCUMENT_IO_H

#include "io/i_document_io.h"

namespace editor {
namespace io {

/**
 * @brief Файловая реализация импорта и экспорта документа.
 * @ingroup io_group
 *
 * Использует демонстрационный текстовый формат, где каждая строка описывает
 * один графический примитив и его параметры.
 */
class FileDocumentIO final : public IDocumentIO {
public:
    /**
     * @brief Загружает документ из файла.
     * @param path Путь к входному файлу.
     * @param document Документ, который будет заменен содержимым файла при успешном импорте.
     * @return true, если файл прочитан и разобран успешно; иначе false.
     */
    bool importDocument(const std::string& path, model::Document& document) const override;

    /**
     * @brief Сохраняет документ в файл.
     * @param document Документ для сохранения.
     * @param path Путь к выходному файлу.
     * @return true, если файл записан успешно; иначе false.
     */
    bool exportDocument(const model::Document& document, const std::string& path) const override;
};

}  // namespace io
}  // namespace editor

#endif  // IO_FILE_DOCUMENT_IO_H
