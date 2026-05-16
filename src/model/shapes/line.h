#ifndef MODEL_SHAPES_LINE_H
#define MODEL_SHAPES_LINE_H

#include "model/shapes/base_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

/**
 * @brief Графический примитив линии.
 * @ingroup shapes_group
 */
class Line final : public BaseShape {
public:
    /**
     * @brief Создает линию.
     * @param id Идентификатор примитива.
     * @param start Начальная точка линии.
     * @param end Конечная точка линии.
     */
    Line(ShapeId id, const Point& start, const Point& end);

    /**
     * @brief Передает линию visitor-объекту.
     * @param visitor Обработчик графических примитивов.
     */
    void accept(IShapeVisitor& visitor) const override;

    /**
     * @brief Возвращает начальную точку линии.
     * @return Начальная точка линии.
     */
    const Point& start() const;

    /**
     * @brief Возвращает конечную точку линии.
     * @return Конечная точка линии.
     */
    const Point& end() const;

private:
    /// Начальная точка линии.
    Point m_start;
    /// Конечная точка линии.
    Point m_end;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_LINE_H
