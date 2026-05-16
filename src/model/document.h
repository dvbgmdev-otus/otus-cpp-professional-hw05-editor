#ifndef MODEL_DOCUMENT_H
#define MODEL_DOCUMENT_H

#include <cstddef>
#include <memory>
#include <vector>

#include "model/shapes/i_shape.h"

namespace editor {
namespace model {

/**
 * @brief Модель документа векторного редактора.
 * @ingroup model_group
 *
 * Документ владеет набором графических примитивов и обеспечивает базовые
 * операции добавления, удаления и чтения состояния.
 */
class Document {
public:
    /// Указатель владения графическим примитивом.
    using ShapePtr = std::unique_ptr<IShape>;

    /// Контейнер графических примитивов документа.
    using Shapes = std::vector<ShapePtr>;

    /**
     * @brief Добавляет графический примитив в документ.
     * @param shape Примитив, который передается документу во владение.
     * @return true, если примитив добавлен; false для пустого указателя или дублирующегося идентификатора.
     */
    bool addShape(ShapePtr shape);

    /**
     * @brief Удаляет графический примитив по идентификатору.
     * @param id Идентификатор удаляемого примитива.
     * @return true, если примитив найден и удален; иначе false.
     */
    bool removeShape(ShapeId id);

    /**
     * @brief Возвращает все графические примитивы документа.
     * @return Константная ссылка на контейнер примитивов.
     */
    const Shapes& shapes() const;

    /**
     * @brief Проверяет, что документ не содержит примитивов.
     * @return true, если документ пуст; иначе false.
     */
    bool empty() const;

    /**
     * @brief Возвращает количество примитивов в документе.
     * @return Количество примитивов.
     */
    std::size_t shapeCount() const;

    /**
     * @brief Вычисляет следующий свободный идентификатор примитива.
     * @return Ноль для пустого документа или значение после максимального существующего идентификатора.
     */
    ShapeId nextAvailableShapeId() const;

private:
    /**
     * @brief Проверяет наличие примитива с заданным идентификатором.
     * @param id Идентификатор для поиска.
     * @return true, если примитив с таким идентификатором уже есть в документе.
     */
    bool containsShape(ShapeId id) const;

    /// Графические примитивы документа.
    Shapes m_shapes;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_DOCUMENT_H
