#include "qt_vue_jeton.h"

/*Qt_jeton::Qt_jeton(const Jeton& j, QWidget *parent)
    : QPushButton(parent), m_jeton(j) {
    updateAppearance();
    connect(this, &QPushButton::clicked, this, &Qt_jeton::onJetonClicked);
}*/

Qt_jeton::Qt_jeton(QWidget *parent) : QPushButton(parent) {
    // Default initialization
    // updateAppearance();
    // connect(this, &QPushButton::clicked, this, &Qt_jeton::onJetonClicked);
}

/*void Qt_jeton::updateAppearance() {
    // Update the appearance of the jeton
    // For example, set the text or icon based on the jeton's properties
    setText(m_jeton.getName()); // Assuming Jeton has a getName() method
}*/

void Qt_jeton::toggleClicked() {
    isClicked = !isClicked;
    update(); // Repaint the jeton
}

void Qt_jeton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event); // Call base class paint event

    QPainter painter(this);
    if (isDown()) {
        painter.fillRect(rect(), QColor(128, 128, 128, 128)); // Grey out the jeton
    }
    // Add any custom painting here if needed
}

void Qt_jeton::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event); // Call base class handler
    toggleClicked();
    emit jetonClicked(); // Emit the clicked signal
}
