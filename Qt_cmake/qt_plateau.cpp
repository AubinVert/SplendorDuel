#include "qt_plateau.h"
#include "qt_labelclick.h"

Qt_Plateau::Qt_Plateau(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);
    layout->setSpacing(0);

    // Setup the card grid
    for (int i = 0; i < 25; ++i) {
        Qt_LabelClick *label = new Qt_LabelClick(QString("Jeton %1").arg(i + 1), this);
        label->setFixedSize(100, 100); // Set minimum size to 100x100 pixels
        layout->addWidget(label, i / 5, i % 5);
    }

    // Setup for privileges
    privilegesLayout = new QHBoxLayout();
    Qt_LabelClick *privilege1 = new Qt_LabelClick("Privilege 1", this);
    Qt_LabelClick *privilege2 = new Qt_LabelClick("Privilege 2", this);
    Qt_LabelClick *privilege3 = new Qt_LabelClick("Privilege 3", this);

    // Set minimum size for privileges
    privilege1->setMinimumSize(100, 100);
    privilege2->setMinimumSize(100, 100);
    privilege3->setMinimumSize(100, 100);

    // Add the privileges to the layout
    privilegesLayout->addWidget(privilege1);
    privilegesLayout->addWidget(privilege2);
    privilegesLayout->addWidget(privilege3);

    // Ensure the privileges layout is at the bottom center
    layout->addLayout(privilegesLayout, 5, 1, 1, 3); // Adjust grid position as needed

    // Disable stretching and set fixed size for the layout
    for (int i = 0; i < 5; ++i) {
        layout->setRowStretch(i, 0);
        layout->setColumnStretch(i, 0);
    }

    // Set fixed size for the Qt_Plateau based on the grid
    setFixedSize(5 * 100, 6 * 100);  // Adjust size based on number of rows, columns, and jeton size
}
