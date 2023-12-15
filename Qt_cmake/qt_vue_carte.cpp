#include "qt_vue_carte.h"

/*Qt_carte::Qt_carte(const Card& carte, QWidget *parent)
    : QPushButton(parent), m_carte(carte) {
    connect(this, &QPushButton::clicked, this, &Qt_carte::onCarteClicked);
}*/

Qt_carte::Qt_carte(QWidget *parent) : QPushButton(parent) {
    // Default constructor can have default initialization if needed
    connect(this, &QPushButton::clicked, this, &Qt_carte::onCarteClicked);
}

/*void Qt_carte::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
    QPainter painter(this);
    // Custom painting code to represent the card
    // e.g., painter.drawText(), painter.drawPixmap() for images, etc.
}*/

void Qt_carte::onCarteClicked() {
    emit carteClicked();
}
