#include "qt_vue_carte.h"

/*Qt_carte::Qt_carte(const Card& carte, QWidget *parent)
    : QPushButton(parent), m_carte(carte) {
    connect(this, &QPushButton::clicked, this, &Qt_carte::onCarteClicked);
}*/

Qt_carte::Qt_carte(QWidget *parent) : QPushButton(parent) {
    connect(this, &QPushButton::clicked, this, &Qt_carte::onCarteClicked);
}

void Qt_carte::paintEvent(QPaintEvent *event) {
    // Q_UNUSED(event); // This macro marks the parameter as used to prevent a compiler warning

    QPainter painter(this);

    // Check if the button is down (clicked) and if yes, set the background to a darker color
    if (isDown()) {
        painter.fillRect(rect(), QColor(0, 0, 0, 50)); // Semi-transparent overlay when clicked
    }

    // Draw the image, ensuring we keep the alpha channel (transparency)
    if (!m_image.isNull()) {
        QPixmap scaledPixmap = m_image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRect pixmapRect((width() - scaledPixmap.width()) / 2, (height() - scaledPixmap.height()) / 2,
                         scaledPixmap.width(), scaledPixmap.height());
        painter.drawPixmap(pixmapRect.topLeft(), scaledPixmap);
    }
}

void Qt_carte::onCarteClicked() {
    emit carteClicked();
}

void Qt_carte::setImage(const QString &imagePath) {
    m_image.load(imagePath);
    update();  // Update the widget to trigger a repaint
}
