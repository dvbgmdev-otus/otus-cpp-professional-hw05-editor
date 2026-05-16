#ifndef CONTROLLER_EDITOR_CONTROLLER_H
#define CONTROLLER_EDITOR_CONTROLLER_H

#include "io/i_document_io.h"
#include "model/document.h"
#include "model/shapes/point.h"

#include <string>

namespace editor {
namespace controller {

/**
 * @brief Контроллер пользовательских сценариев редактора.
 * @ingroup controller_group
 *
 * Управляет текущим документом, создает графические примитивы и делегирует
 * импорт и экспорт документа объекту ввода-вывода.
 */
class EditorController {
public:
    /**
     * @brief Создает контроллер редактора.
     * @param document_io Сервис импорта и экспорта документов.
     */
    explicit EditorController(io::IDocumentIO& document_io);

    /**
     * @brief Создает новый пустой документ.
     */
    void createNewDocument();

    /**
     * @brief Импортирует документ из файла или другого источника.
     * @param path Путь к источнику данных.
     * @return true, если документ успешно импортирован; иначе false.
     */
    bool importDocument(const std::string& path);

    /**
     * @brief Экспортирует текущий документ.
     * @param path Путь к целевому файлу или ресурсу.
     * @return true, если документ успешно экспортирован; иначе false.
     */
    bool exportDocument(const std::string& path) const;

    /**
     * @brief Создает линию в текущем документе.
     * @param start Начальная точка линии.
     * @param end Конечная точка линии.
     * @return Идентификатор созданной линии.
     */
    model::ShapeId createLine(const model::Point& start, const model::Point& end);

    /**
     * @brief Создает прямоугольник в текущем документе.
     * @param top_left Левая верхняя точка прямоугольника.
     * @param width Ширина прямоугольника.
     * @param height Высота прямоугольника.
     * @return Идентификатор созданного прямоугольника.
     */
    model::ShapeId createRectangle(const model::Point& top_left, double width, double height);

    /**
     * @brief Создает эллипс в текущем документе.
     * @param center Центр эллипса.
     * @param radius_x Радиус по горизонтальной оси.
     * @param radius_y Радиус по вертикальной оси.
     * @return Идентификатор созданного эллипса.
     */
    model::ShapeId createEllipse(const model::Point& center, double radius_x, double radius_y);

    /**
     * @brief Удаляет графический примитив из текущего документа.
     * @param id Идентификатор удаляемого примитива.
     * @return true, если примитив найден и удален; иначе false.
     */
    bool removeShape(model::ShapeId id);

    /**
     * @brief Возвращает текущий документ.
     * @return Константная ссылка на текущий документ.
     */
    const model::Document& document() const;

private:
    /**
     * @brief Возвращает следующий идентификатор для нового примитива.
     * @return Идентификатор нового примитива.
     */
    model::ShapeId nextShapeId();

    /// Сервис импорта и экспорта документов.
    io::IDocumentIO& m_document_io;
    /// Текущий документ редактора.
    model::Document m_document;
    /// Следующий идентификатор для создаваемого примитива.
    model::ShapeId m_next_shape_id;
};

}  // namespace controller
}  // namespace editor

#endif  // CONTROLLER_EDITOR_CONTROLLER_H
