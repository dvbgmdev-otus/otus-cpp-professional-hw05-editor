/**
 * @file editor_controller_test.cpp
 * @brief Модульные тесты контроллера редактора.
 */

#include "controller/editor_controller.h"
#include "model/shapes/ellipse.h"
#include "model/shapes/i_shape_visitor.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <gtest/gtest.h>

#include <memory>
#include <string>

namespace {

class DocumentIOMock final : public editor::io::IDocumentIO {
public:
    bool importDocument(const std::string& path, editor::model::Document& document) const override {
        ++import_call_count;
        last_import_path = path;

        if (!import_result) {
            return false;
        }

        document = editor::model::Document();
        for (const auto id : imported_shape_ids) {
            document.addShape(std::make_unique<editor::model::Line>(
                id, editor::model::Point{ 0.0, 0.0 }, editor::model::Point{ 1.0, 1.0 }));
        }

        return true;
    }

    bool exportDocument(const editor::model::Document& document, const std::string& path) const override {
        ++export_call_count;
        last_export_path = path;
        exported_shape_count = document.shapeCount();
        return export_result;
    }

    bool import_result = true;
    bool export_result = true;
    std::vector<editor::model::ShapeId> imported_shape_ids;

    mutable std::size_t import_call_count = 0;
    mutable std::size_t export_call_count = 0;
    mutable std::size_t exported_shape_count = 0;
    mutable std::string last_import_path;
    mutable std::string last_export_path;
};

class ShapeTypeCountingVisitor final : public editor::model::IShapeVisitor {
public:
    void visit(const editor::model::Line& line) override {
        ++line_count;
        last_shape_id = line.id();
    }

    void visit(const editor::model::Rectangle& rectangle) override {
        ++rectangle_count;
        last_shape_id = rectangle.id();
    }

    void visit(const editor::model::Ellipse& ellipse) override {
        ++ellipse_count;
        last_shape_id = ellipse.id();
    }

    std::size_t line_count = 0;
    std::size_t rectangle_count = 0;
    std::size_t ellipse_count = 0;
    editor::model::ShapeId last_shape_id = 0;
};

ShapeTypeCountingVisitor countShapeTypes(const editor::model::Document& document) {
    ShapeTypeCountingVisitor visitor;
    for (const auto& shape : document.shapes()) {
        shape->accept(visitor);
    }
    return visitor;
}

}  // namespace

#if (1)  // 1. Тесты создания документа

// 1.1. createNewDocument очищает текущий документ.
TEST(EditorController, GivenDocumentWithShapes_WhenCreateNewDocument_ThenDocumentIsEmpty) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });

    controller.createNewDocument();

    EXPECT_TRUE(controller.document().empty());
    EXPECT_EQ(controller.document().shapeCount(), 0U);
}

// 1.2. createNewDocument сбрасывает генератор идентификаторов.
TEST(EditorController, GivenUsedShapeIds_WhenCreateNewDocument_ThenNextShapeIdStartsFromZero) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });
    controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);
    controller.createNewDocument();

    const auto id = controller.createEllipse({ 0.0, 0.0 }, 10.0, 20.0);

    EXPECT_EQ(id, 0U);
    EXPECT_EQ(controller.document().shapeCount(), 1U);
}

#endif

#if (1)  // 2. Тесты создания примитивов

// 2.1. createLine добавляет линию с идентификатором 0.
TEST(EditorController, GivenEmptyDocument_WhenCreateLine_ThenAddsLineWithIdZero) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);

    const auto id = controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });

    ASSERT_EQ(id, 0U);
    ASSERT_EQ(controller.document().shapeCount(), 1U);
    const auto visitor = countShapeTypes(controller.document());
    EXPECT_EQ(visitor.line_count, 1U);
    EXPECT_EQ(visitor.last_shape_id, 0U);
}

// 2.2. createRectangle добавляет прямоугольник со следующим идентификатором.
TEST(EditorController, GivenExistingShape_WhenCreateRectangle_ThenAddsRectangleWithNextId) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });

    const auto id = controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    ASSERT_EQ(id, 1U);
    ASSERT_EQ(controller.document().shapeCount(), 2U);
    const auto visitor = countShapeTypes(controller.document());
    EXPECT_EQ(visitor.line_count, 1U);
    EXPECT_EQ(visitor.rectangle_count, 1U);
}

// 2.3. createEllipse добавляет эллипс со следующим идентификатором.
TEST(EditorController, GivenExistingShapes_WhenCreateEllipse_ThenAddsEllipseWithNextId) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });
    controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    const auto id = controller.createEllipse({ 0.0, 0.0 }, 10.0, 20.0);

    ASSERT_EQ(id, 2U);
    ASSERT_EQ(controller.document().shapeCount(), 3U);
    const auto visitor = countShapeTypes(controller.document());
    EXPECT_EQ(visitor.line_count, 1U);
    EXPECT_EQ(visitor.rectangle_count, 1U);
    EXPECT_EQ(visitor.ellipse_count, 1U);
}

#endif

#if (1)  // 3. Тесты удаления примитивов

// 3.1. removeShape удаляет существующий примитив.
TEST(EditorController, GivenExistingShapeId_WhenRemoveShape_ThenShapeIsRemoved) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    const auto line_id = controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });
    controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    const auto result = controller.removeShape(line_id);

    EXPECT_TRUE(result);
    EXPECT_EQ(controller.document().shapeCount(), 1U);
}

// 3.2. removeShape возвращает false для неизвестного идентификатора.
TEST(EditorController, GivenUnknownShapeId_WhenRemoveShape_ThenReturnsFalse) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });

    const auto result = controller.removeShape(42);

    EXPECT_FALSE(result);
    EXPECT_EQ(controller.document().shapeCount(), 1U);
}

#endif

#if (1)  // 4. Тесты импорта и экспорта

// 4.1. exportDocument передает текущий документ в IO-сервис.
TEST(EditorController, GivenDocumentWithShapes_WhenExportDocument_ThenDelegatesToDocumentIO) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });
    controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    const auto result = controller.exportDocument("document.editor");

    EXPECT_TRUE(result);
    EXPECT_EQ(document_io.export_call_count, 1U);
    EXPECT_EQ(document_io.last_export_path, "document.editor");
    EXPECT_EQ(document_io.exported_shape_count, 2U);
}

// 4.2. importDocument заменяет текущий документ данными из IO-сервиса.
TEST(EditorController, GivenImportedDocument_WhenImportDocument_ThenReplacesCurrentDocument) {
    DocumentIOMock document_io;
    document_io.imported_shape_ids = { 3, 4 };
    editor::controller::EditorController controller(document_io);
    controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    const auto result = controller.importDocument("document.editor");

    EXPECT_TRUE(result);
    EXPECT_EQ(document_io.import_call_count, 1U);
    EXPECT_EQ(document_io.last_import_path, "document.editor");
    ASSERT_EQ(controller.document().shapeCount(), 2U);
    const auto visitor = countShapeTypes(controller.document());
    EXPECT_EQ(visitor.line_count, 2U);
}

// 4.3. importDocument продолжает генерацию идентификаторов после максимального импортированного.
TEST(EditorController, GivenImportedDocument_WhenCreateShape_ThenUsesNextAvailableShapeId) {
    DocumentIOMock document_io;
    document_io.imported_shape_ids = { 1, 5 };
    editor::controller::EditorController controller(document_io);
    ASSERT_TRUE(controller.importDocument("document.editor"));

    const auto id = controller.createEllipse({ 0.0, 0.0 }, 10.0, 20.0);

    EXPECT_EQ(id, 6U);
    EXPECT_EQ(controller.document().shapeCount(), 3U);
}

// 4.4. importDocument при ошибке не меняет текущий документ и генератор идентификаторов.
TEST(EditorController, GivenImportError_WhenImportDocument_ThenKeepsCurrentDocumentAndNextId) {
    DocumentIOMock document_io;
    editor::controller::EditorController controller(document_io);
    controller.createLine({ 0.0, 0.0 }, { 1.0, 1.0 });
    document_io.import_result = false;

    const auto result = controller.importDocument("broken.editor");
    const auto id = controller.createRectangle({ 0.0, 0.0 }, 10.0, 20.0);

    EXPECT_FALSE(result);
    EXPECT_EQ(id, 1U);
    EXPECT_EQ(controller.document().shapeCount(), 2U);
}

#endif
