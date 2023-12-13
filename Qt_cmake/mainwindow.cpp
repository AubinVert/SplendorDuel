#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    Plateau *plateau = new Plateau;
    Tirages *tirages = new Tirages;

    mainLayout->addWidget(plateau);
    mainLayout->addWidget(tirages);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    // Further setup for MainWindow, if needed
}
