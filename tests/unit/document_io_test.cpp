/**
 * @file document_io_test.cpp
 * @brief Модульные тесты файлового импорта и экспорта документа.
 */

#include "io/file_document_io.h"
#include "model/shapes/ellipse.h"
#include "model/shapes/i_shape_visitor.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <cstdint>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>

namespace {

class DocumentIOTest : public ::testing::Test {
protected:
    std::string makePath(const std::string& file_name) const {
        std::ostringstream stream;
        stream << "/tmp/otus_editor_" << file_name << '_' << ::testing::UnitTest::GetInstance()->random_seed() << '_'
               << reinterpret_cast<std::uintptr_t>(this) << ".editor";
        return stream.str();
    }

    void writeFile(const std::string& path, const std::string& content) const {
        std::ofstream output(path);
        output << content;
    }

    std::string readFile(const std::string& path) const {
        std::ifstream input(path);
        std::ostringstream content;
        content << input.rdbuf();
        return content.str();
    }

    void rememberFile(const std::string& path) {
        m_paths.push_back(path);
    }

    void TearDown() override {
        for (const auto& path : m_paths) {
            std::remove(path.c_str());
        }
    }

    editor::io::FileDocumentIO document_io;

private:
    std::vector<std::string> m_paths;
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

std::unique_ptr<editor::model::Line> makeLine(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Line>(id, editor::model::Point{ 0.0, 0.0 }, editor::model::Point{ 10.0, 10.0 });
}

std::unique_ptr<editor::model::Rectangle> makeRectangle(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Rectangle>(id, editor::model::Point{ 1.0, 2.0 }, 100.0, 50.0);
}

std::unique_ptr<editor::model::Ellipse> makeEllipse(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Ellipse>(id, editor::model::Point{ 3.0, 4.0 }, 20.0, 10.0);
}

ShapeTypeCountingVisitor countShapeTypes(const editor::model::Document& document) {
    ShapeTypeCountingVisitor visitor;
    for (const auto& shape : document.shapes()) {
        shape->accept(visitor);
    }
    return visitor;
}

}  // namespace

#if (1)  // 1. Тесты экспорта документа

// 1.1. Экспорт пустого документа создает пустой файл.
TEST_F(DocumentIOTest, GivenEmptyDocument_WhenExportDocument_ThenCreatesEmptyFile) {
    const auto path = makePath("empty_export");
    rememberFile(path);
    const editor::model::Document document;

    const auto result = document_io.exportDocument(document, path);

    ASSERT_TRUE(result);
    EXPECT_EQ(readFile(path), "");
}

// 1.2. Экспорт документа с примитивами сохраняет все примитивы в текстовом формате.
TEST_F(DocumentIOTest, GivenDocumentWithShapes_WhenExportDocument_ThenWritesAllShapes) {
    const auto path = makePath("shapes_export");
    rememberFile(path);
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(0)));
    ASSERT_TRUE(document.addShape(makeRectangle(1)));
    ASSERT_TRUE(document.addShape(makeEllipse(2)));

    const auto result = document_io.exportDocument(document, path);

    ASSERT_TRUE(result);
    EXPECT_EQ(readFile(path), "line 0 0 0 10 10\nrectangle 1 1 2 100 50\nellipse 2 3 4 20 10\n");
}

#endif

#if (1)  // 2. Тесты импорта документа

// 2.1. Импорт пустого файла создает пустой документ.
TEST_F(DocumentIOTest, GivenEmptyFile_WhenImportDocument_ThenDocumentIsEmpty) {
    const auto path = makePath("empty_import");
    rememberFile(path);
    writeFile(path, "");
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(7)));

    const auto result = document_io.importDocument(path, document);

    ASSERT_TRUE(result);
    EXPECT_TRUE(document.empty());
    EXPECT_EQ(document.nextAvailableShapeId(), 0U);
}

// 2.2. Импорт файла с line восстанавливает линию.
TEST_F(DocumentIOTest, GivenLineRecord_WhenImportDocument_ThenRestoresLine) {
    const auto path = makePath("line_import");
    rememberFile(path);
    writeFile(path, "line 5 1 2 3 4\n");
    editor::model::Document document;

    const auto result = document_io.importDocument(path, document);

    ASSERT_TRUE(result);
    ASSERT_EQ(document.shapeCount(), 1U);
    const auto visitor = countShapeTypes(document);
    EXPECT_EQ(visitor.line_count, 1U);
    EXPECT_EQ(visitor.last_shape_id, 5U);
    EXPECT_EQ(document.nextAvailableShapeId(), 6U);
}

// 2.3. Импорт файла с несколькими примитивами восстанавливает все примитивы.
TEST_F(DocumentIOTest, GivenSeveralShapeRecords_WhenImportDocument_ThenRestoresAllShapes) {
    const auto path = makePath("several_import");
    rememberFile(path);
    writeFile(path, "line 0 0 0 10 10\nrectangle 1 1 2 100 50\nellipse 2 3 4 20 10\n");
    editor::model::Document document;

    const auto result = document_io.importDocument(path, document);

    ASSERT_TRUE(result);
    ASSERT_EQ(document.shapeCount(), 3U);
    const auto visitor = countShapeTypes(document);
    EXPECT_EQ(visitor.line_count, 1U);
    EXPECT_EQ(visitor.rectangle_count, 1U);
    EXPECT_EQ(visitor.ellipse_count, 1U);
    EXPECT_EQ(document.nextAvailableShapeId(), 3U);
}

#endif

#if (1)  // 3. Тесты ошибок импорта

// 3.1. Импорт несуществующего файла возвращает false и не меняет документ.
TEST_F(DocumentIOTest, GivenMissingFile_WhenImportDocument_ThenReturnsFalseAndKeepsDocument) {
    const auto path = makePath("missing_import");
    rememberFile(path);
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(4)));

    const auto result = document_io.importDocument(path, document);

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 4U);
}

// 3.2. Импорт неизвестного типа примитива возвращает false и не меняет документ.
TEST_F(DocumentIOTest, GivenUnknownShapeType_WhenImportDocument_ThenReturnsFalseAndKeepsDocument) {
    const auto path = makePath("unknown_type_import");
    rememberFile(path);
    writeFile(path, "triangle 1 0 0 10 10 5 5\n");
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(4)));

    const auto result = document_io.importDocument(path, document);

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 4U);
}

// 3.3. Импорт строки с неполными параметрами возвращает false и не меняет документ.
TEST_F(DocumentIOTest, GivenIncompleteShapeRecord_WhenImportDocument_ThenReturnsFalseAndKeepsDocument) {
    const auto path = makePath("incomplete_import");
    rememberFile(path);
    writeFile(path, "rectangle 1 0 0 100\n");
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(4)));

    const auto result = document_io.importDocument(path, document);

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 4U);
}

// 3.4. Импорт с дублирующимся идентификатором возвращает false и не меняет документ.
TEST_F(DocumentIOTest, GivenDuplicateShapeId_WhenImportDocument_ThenReturnsFalseAndKeepsDocument) {
    const auto path = makePath("duplicate_import");
    rememberFile(path);
    writeFile(path, "line 1 0 0 10 10\nrectangle 1 1 2 100 50\n");
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(4)));

    const auto result = document_io.importDocument(path, document);

    EXPECT_FALSE(result);
    EXPECT_EQ(document.shapeCount(), 1U);
    EXPECT_EQ(document.shapes().front()->id(), 4U);
}

#endif
