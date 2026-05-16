/**
 * @file shapes_test.cpp
 * @brief Модульные тесты графических примитивов.
 */

#include "model/shapes/ellipse.h"
#include "model/shapes/i_shape_visitor.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <gtest/gtest.h>

namespace {

class ShapeVisitorMock final : public editor::model::IShapeVisitor {
public:
    void visit(const editor::model::Line& line) override {
        visited_line_id = line.id();
    }

    void visit(const editor::model::Rectangle& rectangle) override {
        visited_rectangle_id = rectangle.id();
    }

    void visit(const editor::model::Ellipse& ellipse) override {
        visited_ellipse_id = ellipse.id();
    }

    editor::model::ShapeId visited_line_id = 0;
    editor::model::ShapeId visited_rectangle_id = 0;
    editor::model::ShapeId visited_ellipse_id = 0;
};

}  // namespace

#if (1)  // 1. Тесты примитива Line

// 1.1. Line хранит идентификатор и конечные точки.
TEST(LineShape, GivenConstructorArguments_WhenReadBack_ThenReturnsSameGeometry) {
    const editor::model::Point start{ 1.0, 2.0 };
    const editor::model::Point end{ 3.0, 4.0 };

    const editor::model::Line line(42, start, end);

    EXPECT_EQ(line.id(), 42);
    EXPECT_DOUBLE_EQ(line.start().x, start.x);
    EXPECT_DOUBLE_EQ(line.start().y, start.y);
    EXPECT_DOUBLE_EQ(line.end().x, end.x);
    EXPECT_DOUBLE_EQ(line.end().y, end.y);
}

// 1.2. Line передает себя visitor-объекту.
TEST(LineShape, GivenVisitor_WhenAcceptCalled_ThenVisitsLine) {
    const editor::model::Line line(7, { 0.0, 0.0 }, { 1.0, 1.0 });
    ShapeVisitorMock visitor;

    line.accept(visitor);

    EXPECT_EQ(visitor.visited_line_id, line.id());
}

#endif

#if (1)  // 2. Тесты примитива Rectangle

// 2.1. Rectangle хранит идентификатор, левую верхнюю точку, ширину и высоту.
TEST(RectangleShape, GivenConstructorArguments_WhenReadBack_ThenReturnsSameGeometry) {
    const editor::model::Point top_left{ 5.0, 6.0 };

    const editor::model::Rectangle rectangle(8, top_left, 100.0, 50.0);

    EXPECT_EQ(rectangle.id(), 8);
    EXPECT_DOUBLE_EQ(rectangle.topLeft().x, top_left.x);
    EXPECT_DOUBLE_EQ(rectangle.topLeft().y, top_left.y);
    EXPECT_DOUBLE_EQ(rectangle.width(), 100.0);
    EXPECT_DOUBLE_EQ(rectangle.height(), 50.0);
}

// 2.2. Rectangle передает себя visitor-объекту.
TEST(RectangleShape, GivenVisitor_WhenAcceptCalled_ThenVisitsRectangle) {
    const editor::model::Rectangle rectangle(9, { 0.0, 0.0 }, 10.0, 20.0);
    ShapeVisitorMock visitor;

    rectangle.accept(visitor);

    EXPECT_EQ(visitor.visited_rectangle_id, rectangle.id());
}

#endif

#if (1)  // 3. Тесты примитива Ellipse

// 3.1. Ellipse хранит идентификатор, центр и радиусы.
TEST(EllipseShape, GivenConstructorArguments_WhenReadBack_ThenReturnsSameGeometry) {
    const editor::model::Point center{ 7.0, 8.0 };

    const editor::model::Ellipse ellipse(10, center, 25.0, 15.0);

    EXPECT_EQ(ellipse.id(), 10);
    EXPECT_DOUBLE_EQ(ellipse.center().x, center.x);
    EXPECT_DOUBLE_EQ(ellipse.center().y, center.y);
    EXPECT_DOUBLE_EQ(ellipse.radiusX(), 25.0);
    EXPECT_DOUBLE_EQ(ellipse.radiusY(), 15.0);
}

// 3.2. Ellipse передает себя visitor-объекту.
TEST(EllipseShape, GivenVisitor_WhenAcceptCalled_ThenVisitsEllipse) {
    const editor::model::Ellipse ellipse(11, { 0.0, 0.0 }, 10.0, 20.0);
    ShapeVisitorMock visitor;

    ellipse.accept(visitor);

    EXPECT_EQ(visitor.visited_ellipse_id, ellipse.id());
}

#endif
