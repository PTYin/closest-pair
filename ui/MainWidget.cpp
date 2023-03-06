#include "MainWidget.h"

// Constructor for main widget
MainWidget::MainWidget(QWidget *parent) :
        QWidget(parent) {
    auto *mainLayout = new QGridLayout(this);
    renderArea = new RenderArea(this);
    mainLayout->addWidget(renderArea, 0, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Closest pair of points"));
}

// Destructor
MainWidget::~MainWidget() {
    delete renderArea;
}