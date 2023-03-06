#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent)
        : QWidget(parent) {
    points = new QVector<QPoint>();
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

QSize RenderArea::minimumSizeHint() const {
    return {400, 400};
}

QSize RenderArea::sizeHint() const {
    return {800, 800};
}

RenderArea::~RenderArea() {
    delete points;
}

void RenderArea::mousePressEvent(QMouseEvent *event) {
    switch (event->button()) {
        case Qt::LeftButton:
            points->push_back(event->pos());
            update();
            break;
        case Qt::RightButton:
            finished = true;
            update();
            break;
        default:
            break;
    }
}

void RenderArea::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Space) {
        finished = false;
        points->clear();
        update();
    }
}

void RenderArea::paintEvent(QPaintEvent *event) {
    auto result = finished ? run<int>(*points, [](const auto &p) { return p.x(); }, [](const auto &p) { return p.y(); })
                           : make_pair(-1, -1);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, false);
    auto ordinary = QPen(Qt::black, 5.);
    auto answer = QPen(Qt::red, 10.);
    painter.setPen(ordinary);
    int index = 0;

    for (auto &point: *points) {
        bool isAnswer = finished && (index == result.first || index == result.second);
        painter.setPen(isAnswer ? answer : ordinary);
        painter.drawPoint(point);
        index++;
    }
}
