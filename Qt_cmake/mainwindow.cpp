#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    Qt_Plateau *plateau = new Qt_Plateau;
    Qt_Tirages *tirages = new Qt_Tirages;

    mainLayout->addWidget(plateau);
    mainLayout->addWidget(tirages);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    // Further setup for MainWindow, if needed
}
