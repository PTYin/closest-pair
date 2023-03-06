//
// Created by Peter on 2023/3/5.
//

#ifndef QT_CLOSEST_PAIR_RENDERAREA_H
#define QT_CLOSEST_PAIR_RENDERAREA_H

#include <QtWidgets>
#include <QVector>
#include <QPoint>
#include "core.hpp"

class RenderArea : public QWidget {
Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);

    ~RenderArea() override;

    QSize minimumSizeHint() const override;

    QSize sizeHint() const override;

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

private:
    QVector<QPoint> *points;
    bool finished = false;
};

#endif //QT_CLOSEST_PAIR_RENDERAREA_H
