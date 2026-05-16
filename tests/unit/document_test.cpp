/**
 * @file document_test.cpp
 * @brief Модульные тесты документа.
 */

#include "model/document.h"
#include "model/shapes/ellipse.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <gtest/gtest.h>

#include <memory>

namespace {

std::unique_ptr<editor::model::Line> makeLine(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Line>(id, editor::model::Point{ 0.0, 0.0 }, editor::model::Point{ 1.0, 1.0 });
}

std::unique_ptr<editor::model::Rectangle> makeRectangle(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Rectangle>(id, editor::model::Point{ 0.0, 0.0 }, 10.0, 20.0);
}

std::unique_ptr<editor::model::Ellipse> makeEllipse(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Ellipse>(id, editor::model::Point{ 0.0, 0.0 }, 10.0, 20.0);
}

}  // namespace

#if (1)  // 1. Тесты добавления примитивов

// 1.1. Новый документ пустой.
TEST(Document, GivenNewDocument_WhenStateRead_ThenItIsEmpty) {
    const editor::model::Document document;

    EXPECT_TRUE(document.empty());
    EXPECT_EQ(document.shapeCount(), 0U);
    EXPECT_EQ(document.nextAvailableShapeId(), 0U);
}

// 1.2. Документ принимает валидный примитив во владение.
TEST(Document, GivenValidShape_WhenAddShape_ThenShapeIsStored) {
    editor::model::Document document;

    const auto result = document.addShape(makeLine(3));

    ASSERT_TRUE(result);
    EXPECT_FALSE(document.empty());
    EXPECT_EQ(document.shapeCount(), 1U);
    ASSERT_EQ(document.shapes().size(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 3U);
}

// 1.3. Документ отклоняет пустой указатель.
TEST(Document, GivenNullShape_WhenAddShape_ThenShapeIsRejected) {
    editor::model::Document document;

    const auto result = document.addShape(nullptr);

    EXPECT_FALSE(result);
    EXPECT_TRUE(document.empty());
    EXPECT_EQ(document.shapeCount(), 0U);
}

// 1.4. Документ отклоняет примитив с уже существующим идентификатором.
TEST(Document, GivenDuplicateShapeId_WhenAddShape_ThenShapeIsRejected) {
    editor::model::Document document;

    ASSERT_TRUE(document.addShape(makeLine(5)));
    const auto result = document.addShape(makeRectangle(5));

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 5U);
}

#endif

#if (1)  // 2. Тесты удаления примитивов

// 2.1. Документ удаляет существующий примитив по идентификатору.
TEST(Document, GivenExistingShapeId_WhenRemoveShape_ThenShapeIsRemoved) {
    editor::model::Document document;

    ASSERT_TRUE(document.addShape(makeLine(1)));
    ASSERT_TRUE(document.addShape(makeRectangle(2)));

    const auto result = document.removeShape(1);

    ASSERT_TRUE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 2U);
}

// 2.2. Документ сообщает об ошибке при удалении неизвестного идентификатора.
TEST(Document, GivenUnknownShapeId_WhenRemoveShape_ThenDocumentIsNotChanged) {
    editor::model::Document document;

    ASSERT_TRUE(document.addShape(makeLine(1)));

    const auto result = document.removeShape(99);

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 1U);
}

#endif

#if (1)  // 3. Тесты вычисления следующего идентификатора

// 3.1. Документ возвращает следующий идентификатор после максимального существующего.
TEST(Document, GivenSeveralShapeIds_WhenNextAvailableShapeId_ThenReturnsMaxIdPlusOne) {
    editor::model::Document document;

    ASSERT_TRUE(document.addShape(makeLine(4)));
    ASSERT_TRUE(document.addShape(makeRectangle(1)));
    ASSERT_TRUE(document.addShape(makeEllipse(8)));

    EXPECT_EQ(document.nextAvailableShapeId(), 9U);
}

// 3.2. Документ не переиспользует удаленный идентификатор ниже максимального.
TEST(Document, GivenRemovedShape_WhenNextAvailableShapeId_ThenReturnsMaxIdPlusOne) {
    editor::model::Document document;

    ASSERT_TRUE(document.addShape(makeLine(1)));
    ASSERT_TRUE(document.addShape(makeRectangle(4)));
    ASSERT_TRUE(document.removeShape(1));

    EXPECT_EQ(document.nextAvailableShapeId(), 5U);
}

#endif
