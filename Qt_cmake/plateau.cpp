#include "plateau.h"

Plateau::Plateau(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    // Setup the card grid
    for (int i = 0; i < 25; ++i) {
        QLabel *label = new QLabel(QString("Jeton %1").arg(i + 1));
        label->setStyleSheet("border: 1px solid black;");
        label->setMinimumSize(100, 100); // Set minimum size to 100x100 pixels
        layout->addWidget(label, i / 5, i % 5);
    }

    // Setup for privileges
    privilegesLayout = new QHBoxLayout();
    QLabel *privilege1 = new QLabel("Privilege 1");
    QLabel *privilege2 = new QLabel("Privilege 2");
    QLabel *privilege3 = new QLabel("Privilege 3");

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

    // Additional setup, if needed
}
