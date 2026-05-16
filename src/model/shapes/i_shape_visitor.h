#ifndef MODEL_SHAPES_I_SHAPE_VISITOR_H
#define MODEL_SHAPES_I_SHAPE_VISITOR_H

namespace editor {
namespace model {

class Ellipse;
class Line;
class Rectangle;

/**
 * @brief Интерфейс обработки конкретных типов графических примитивов.
 * @ingroup shapes_group
 */
class IShapeVisitor {
public:
    virtual ~IShapeVisitor() = default;

    /**
     * @brief Обрабатывает линию.
     * @param line Линия для обработки.
     */
    virtual void visit(const Line& line) = 0;

    /**
     * @brief Обрабатывает прямоугольник.
     * @param rectangle Прямоугольник для обработки.
     */
    virtual void visit(const Rectangle& rectangle) = 0;

    /**
     * @brief Обрабатывает эллипс.
     * @param ellipse Эллипс для обработки.
     */
    virtual void visit(const Ellipse& ellipse) = 0;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_I_SHAPE_VISITOR_H
