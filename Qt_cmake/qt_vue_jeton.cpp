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

/*void Qt_jeton::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event);
    // Add any custom painting here if needed
}*/

/*void Qt_jeton::onJetonClicked() {
    emit jetonClicked(m_jeton); // Emit the signal with the jeton data
}*/
