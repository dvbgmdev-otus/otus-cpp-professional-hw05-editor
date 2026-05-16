#ifndef MODEL_SHAPES_POINT_H
#define MODEL_SHAPES_POINT_H

namespace editor {
namespace model {

/**
 * @brief Точка на двумерной плоскости.
 * @ingroup shapes_group
 */
struct Point {
    /// Координата по горизонтальной оси.
    double x;
    /// Координата по вертикальной оси.
    double y;
};

}  // namespace model
}  // namespace editor

#endif  // MODEL_SHAPES_POINT_H
