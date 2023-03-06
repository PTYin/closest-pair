#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include "RenderArea.h"

class MainWidget : public QWidget {
Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

    virtual ~MainWidget();

private:
    RenderArea *renderArea;
};

#endif // MAINWIDGET_H