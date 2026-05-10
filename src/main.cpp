#include "debug_log.h"
#include "model/shapes/ellipse.h"
#include "model/shapes/line.h"
#include "model/shapes/rectangle.h"

int main() {
    DEBUG_LOG("Application started");

    const editor::model::Point origin{0.0, 0.0};
    const editor::model::Point point{10.0, 10.0};

    const editor::model::Line line(1, origin, point);
    const editor::model::Rectangle rectangle(2, origin, 100.0, 50.0);
    const editor::model::Ellipse ellipse(3, point, 20.0, 10.0);

    static_cast<void>(line);
    static_cast<void>(rectangle);
    static_cast<void>(ellipse);

    return 0;
}
