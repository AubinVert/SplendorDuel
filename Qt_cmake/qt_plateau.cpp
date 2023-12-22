#include "qt_plateau.h"
#include "qt_vue_jeton.h"
#include "mainwindow.h"

Qt_Plateau::Handler Qt_Plateau::handler;

Qt_Plateau::~Qt_Plateau() {
    // Rien
}

Qt_Plateau::Qt_Plateau(QWidget *parent) : QWidget(parent) {
    layout = new QGridLayout(this);

    // Set the spacing to 8 pixels
    layout->setHorizontalSpacing(7);
    layout->setVerticalSpacing(18);

    // Calculate jeton size, taking into account the spacing
    const int jetonWidth = 64 * 0.75; // 4 gaps, 5 jetons
    const int jetonHeight = 64 * 0.75; // 4 gaps, 5 jetons

    // Setup the card grid
    for (int i = 0; i < NJETONS; ++i) {
        Qt_jeton *jeton = new Qt_jeton(this);
        jeton->setIndice(i);
        jeton->setStyleSheet("background: transparent;");
        jeton->setFixedSize(jetonWidth, jetonHeight); // Set fixed size to ensure they fit the grid
        layout->addWidget(jeton, i / 5, i % 5);
        jetons.push_back(jeton);
    }

    // Setup for privileges
    privilegesLayout = new QGridLayout(this);
    privilegesLayout->setHorizontalSpacing(4);  // Set the spacing between the privileges

    privilege1 = new Qt_jeton(this);
    privilege2 = new Qt_jeton(this);
    privilege3 = new Qt_jeton(this);

    // Set fixed size and style for privileges
    const int privilegeSize = 60 * 0.75;
    privilege1->setFixedSize(privilegeSize, privilegeSize);
    privilege1->setStyleSheet("background: transparent;");
    privilege2->setFixedSize(privilegeSize, privilegeSize);
    privilege2->setStyleSheet("background: transparent;");
    privilege3->setFixedSize(privilegeSize, privilegeSize);
    privilege3->setStyleSheet("background: transparent;");

    // Add the privileges to the layout in the same row but different columns
    privilegesLayout->addWidget(privilege1, 0, 0); // Row 0, Column 0
    privilegesLayout->addWidget(privilege2, 0, 1); // Row 0, Column 1
    privilegesLayout->addWidget(privilege3, 0, 2); // Row 0, Column 2

    // Now you need to add this layout to the main layout of the Qt_Plateau
    // Assuming 'layout' is the main layout of Qt_Plateau
    layout->addLayout(privilegesLayout, 5, 1, 1, 3); // Add the privilegesLayout to the bottom of the main grid

    // Disable stretching and set fixed size for the layout
    for (int i = 0; i < 5; ++i) {
        layout->setRowStretch(i, 0);
        layout->setColumnStretch(i, 0);
    }

    // Set fixed size for the Qt_Plateau based on the grid
    setFixedSize(371 * 0.75, 446 * 0.75);  // Adjust size based on number of rows, columns, and jeton size
}

void Qt_Plateau::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // Calculate the total size including jetons and spacing

    QPixmap backgroundPixmap("../src/Reste_detoure/Plateau.png");  // Load the background image

    // Stretch the pixmap to cover the area occupied by the jetons including the spacing
    QPixmap stretchedPixmap = backgroundPixmap.scaled(371 * 0.75, 446 * 0.75, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // Calculate the position to start drawing the background image to center it within the widget
    int x = (this->width() - stretchedPixmap.width()) / 2;
    int y = (this->height() - stretchedPixmap.height()) / 2;

    // Draw the stretched pixmap at the calculated position
    painter.drawPixmap(x, y, stretchedPixmap);

    QWidget::paintEvent(event); // Call the base class paint event
}

void Qt_Plateau::connectJetons() {
    for (int i = 0; i < NJETONS; i++){
        connect(this->jetons[i], &Qt_jeton::jetonClicked, &MainWindow::getMainWindow(), &MainWindow::jetonClicked);

    }
}
