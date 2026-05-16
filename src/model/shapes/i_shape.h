#ifndef MODEL_SHAPES_I_SHAPE_H
#define MODEL_SHAPES_I_SHAPE_H

#include "model/shapes/shape_id.h"

namespace editor {
namespace model {

class IShapeVisitor;

/**
 * @brief Общий интерфейс графического примитива.
 * @ingroup shapes_group
 */
class IShape {
public:
    virtual ~IShape() = default;

    /**
     * @brief Возвращает идентификатор примитива.
     * @return Идентификатор примитива внутри документа.
     */
    virtual ShapeId id() const = 0;

    /**
     * @brief Передает примитив visitor-объекту.
     * @param visitor Обработчик конкретного типа примитива.
     */
    virtual void accept(IShapeVisitor& visitor) const = 0;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_I_SHAPE_H
