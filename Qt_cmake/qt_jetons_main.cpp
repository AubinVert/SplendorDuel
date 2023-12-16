#include "qt_jetons_main.h"
#include "qt_vue_jeton.h"

Qt_Jetons_Main::Qt_Jetons_Main(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    // Setup the card grid
    for (int i = 0; i < 16; ++i) {
        Qt_jeton *label = new Qt_jeton();
        label->setMinimumSize(100, 100);  // Set minimum size to 50x50
        label->setDisabled(true);
        // label->setStyleSheet("border: 1px solid black;");
        layout->addWidget(label, i / 4, i % 4);
    }

    // Disable stretching and set fixed size for the layout
    for (int i = 0; i < 3; ++i) {
        layout->setRowStretch(i, 0);
        layout->setColumnStretch(i, 0);
    }

    // Additional setup, if needed
}
