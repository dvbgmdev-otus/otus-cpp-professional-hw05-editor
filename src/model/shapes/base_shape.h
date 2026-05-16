#ifndef MODEL_SHAPES_BASE_SHAPE_H
#define MODEL_SHAPES_BASE_SHAPE_H

#include "model/shapes/i_shape.h"

namespace editor {
namespace model {

/**
 * @brief Базовая реализация примитива с идентификатором.
 * @ingroup shapes_group
 */
class BaseShape : public IShape {
public:
    /**
     * @brief Возвращает идентификатор примитива.
     * @return Идентификатор, заданный при создании примитива.
     */
    ShapeId id() const override;

protected:
    /**
     * @brief Создает базовую часть примитива.
     * @param id Идентификатор примитива.
     */
    explicit BaseShape(ShapeId id);

private:
    /// Идентификатор примитива.
    ShapeId m_id;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_BASE_SHAPE_H
