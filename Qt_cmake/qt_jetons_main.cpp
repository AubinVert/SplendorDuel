#include "qt_jetons_main.h"

Qt_Jetons_Main::Qt_Jetons_Main(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    // Setup the card grid
    for (int i = 0; i < 15; ++i) {
        QLabel *label = new QLabel(QString("Jeton %1").arg(i + 1));
        label->setStyleSheet("border: 1px solid black;");
        label->setFixedSize(100, 100); // Set minimum size to 100x100 pixels
        layout->addWidget(label, 0, i);
    }

    // Additional setup, if needed
}
