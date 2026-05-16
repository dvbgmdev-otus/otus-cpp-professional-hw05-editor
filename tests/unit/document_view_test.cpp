/**
 * @file document_view_test.cpp
 * @brief Модульные тесты консольного представления документа.
 */

#include "model/document.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"
#include "view/console_document_view.h"

#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <sstream>

namespace {

class CoutCapture {
public:
    CoutCapture() : m_old_buffer(std::cout.rdbuf(m_stream.rdbuf())) {}

    ~CoutCapture() {
        std::cout.rdbuf(m_old_buffer);
    }

    std::string str() const {
        return m_stream.str();
    }

private:
    std::ostringstream m_stream;
    std::streambuf* m_old_buffer;
};

std::unique_ptr<editor::model::Line> makeLine(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Line>(id, editor::model::Point{ 0.0, 0.0 }, editor::model::Point{ 1.0, 1.0 });
}

std::unique_ptr<editor::model::Rectangle> makeRectangle(editor::model::ShapeId id) {
    return std::make_unique<editor::model::Rectangle>(id, editor::model::Point{ 0.0, 0.0 }, 10.0, 20.0);
}

}  // namespace

#if (1)  // 1. Тесты вывода количества примитивов

// 1.1. ConsoleDocumentView выводит ноль для пустого документа.
TEST(ConsoleDocumentView, GivenEmptyDocument_WhenRender_ThenPrintsZeroShapes) {
    const editor::model::Document document;
    const editor::view::ConsoleDocumentView view;
    CoutCapture capture;

    view.render(document);

    EXPECT_EQ(capture.str(), "Document shapes: 0\n");
}

// 1.2. ConsoleDocumentView выводит количество примитивов в документе.
TEST(ConsoleDocumentView, GivenDocumentWithShapes_WhenRender_ThenPrintsShapeCount) {
    editor::model::Document document;
    ASSERT_TRUE(document.addShape(makeLine(0)));
    ASSERT_TRUE(document.addShape(makeRectangle(1)));
    const editor::view::ConsoleDocumentView view;
    CoutCapture capture;

    view.render(document);

    EXPECT_EQ(capture.str(), "Document shapes: 2\n");
}

#endif
