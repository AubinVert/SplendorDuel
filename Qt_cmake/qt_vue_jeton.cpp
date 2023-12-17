#include "qt_vue_jeton.h"

Qt_jeton::Qt_jeton(QWidget *parent) : QPushButton(parent), jeton(nullptr) {
    // Default initialization
    // updateAppearance();
    // connect(this, &QPushButton::clicked, this, &Qt_jeton::onJetonClicked);
}


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

void Qt_jeton::updateAppearance() {
    if (jeton != nullptr) {
        qDebug() << jeton->getVisuel();
        QIcon icon(QPixmap(QString::fromStdString(jeton->getVisuel())));
        this->setIcon(icon);
        this->setIconSize(this->size()); // Adjust the size of the icon to fit the button
    }
    // Additional appearance updates...
}
