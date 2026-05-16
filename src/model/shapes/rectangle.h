#ifndef MODEL_SHAPES_RECTANGLE_H
#define MODEL_SHAPES_RECTANGLE_H

#include "model/shapes/base_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

/**
 * @brief Графический примитив прямоугольника.
 * @ingroup shapes_group
 */
class Rectangle final : public BaseShape {
public:
    /**
     * @brief Создает прямоугольник.
     * @param id Идентификатор примитива.
     * @param top_left Левая верхняя точка прямоугольника.
     * @param width Ширина прямоугольника.
     * @param height Высота прямоугольника.
     */
    Rectangle(ShapeId id, const Point& top_left, double width, double height);  // NOLINT(bugprone-easily-swappable-parameters)

    /**
     * @brief Передает прямоугольник visitor-объекту.
     * @param visitor Обработчик графических примитивов.
     */
    void accept(IShapeVisitor& visitor) const override;

    /**
     * @brief Возвращает левую верхнюю точку прямоугольника.
     * @return Левая верхняя точка прямоугольника.
     */
    const Point& topLeft() const;

    /**
     * @brief Возвращает ширину прямоугольника.
     * @return Ширина прямоугольника.
     */
    double width() const;

    /**
     * @brief Возвращает высоту прямоугольника.
     * @return Высота прямоугольника.
     */
    double height() const;

private:
    /// Левая верхняя точка прямоугольника.
    Point m_top_left;
    /// Ширина прямоугольника.
    double m_width;
    /// Высота прямоугольника.
    double m_height;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_RECTANGLE_H
