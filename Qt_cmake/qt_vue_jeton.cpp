#include "qt_vue_jeton.h"
#include "mainwindow.h"
#include <QCoreApplication>

Qt_jeton::Qt_jeton(QWidget *parent) : QPushButton(parent), jeton(nullptr) {
    // Default initialization
    // updateAppearance();
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
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

/*void Qt_jeton::mousePressEvent(QMouseEvent *event) {
    QPushButton::mousePressEvent(event); // Call base class handler
    toggleClicked();
    emit jetonClicked(this->jeton); // Emit the clicked signal
}*/

void Qt_jeton::updateAppearance() {
    if (jeton) {
        // qDebug() << jeton->getVisuel();
        QIcon icon(QPixmap(QString::fromStdString(jeton->getVisuel())));
        this->setIcon(icon);
        this->setIconSize(this->size()); // Adjust the size of the icon to fit the button
    }
    else {
        this->setIcon(QIcon()); // Set an empty QIcon when jeton is nullptr
        this->setIconSize(this->size()); // Adjust the size of the icon to fit the button
    }
    this->update();
    // Additional appearance updates...
}
