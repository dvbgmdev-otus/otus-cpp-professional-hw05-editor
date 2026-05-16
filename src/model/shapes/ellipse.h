#ifndef MODEL_SHAPES_ELLIPSE_H
#define MODEL_SHAPES_ELLIPSE_H

#include "model/shapes/base_shape.h"
#include "model/shapes/point.h"

namespace editor {
namespace model {

/**
 * @brief Графический примитив эллипса.
 * @ingroup shapes_group
 */
class Ellipse final : public BaseShape {
public:
    /**
     * @brief Создает эллипс.
     * @param id Идентификатор примитива.
     * @param center Центр эллипса.
     * @param radius_x Радиус по горизонтальной оси.
     * @param radius_y Радиус по вертикальной оси.
     */
    Ellipse(ShapeId id, const Point& center, double radius_x, double radius_y);

    /**
     * @brief Передает эллипс visitor-объекту.
     * @param visitor Обработчик графических примитивов.
     */
    void accept(IShapeVisitor& visitor) const override;

    /**
     * @brief Возвращает центр эллипса.
     * @return Центр эллипса.
     */
    const Point& center() const;

    /**
     * @brief Возвращает радиус по горизонтальной оси.
     * @return Радиус по горизонтальной оси.
     */
    double radiusX() const;

    /**
     * @brief Возвращает радиус по вертикальной оси.
     * @return Радиус по вертикальной оси.
     */
    double radiusY() const;

private:
    /// Центр эллипса.
    Point m_center;
    /// Радиус по горизонтальной оси.
    double m_radius_x;
    /// Радиус по вертикальной оси.
    double m_radius_y;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_ELLIPSE_H
