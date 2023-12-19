#include "qt_vue_carte.h"
#include <QDebug>

/*Qt_carte::Qt_carte(const Card& carte, QWidget *parent)
    : QPushButton(parent), m_carte(carte) {
    connect(this, &QPushButton::clicked, this, &Qt_carte::onCarteClicked);
}*/

Qt_carte::Qt_carte(QWidget *parent) : QPushButton(parent), isClicked(false), card(nullptr) {
    connect(this,SIGNAL(clicked()),this,SLOT(clickedEvent()));
}

void Qt_carte::paintEvent(QPaintEvent *event) {
    QPushButton::paintEvent(event); // Call base class paint event

    QPainter painter(this);
    if (isDown()) {
        painter.fillRect(rect(), QColor(128, 128, 128, 128)); // Grey out
    }

    painter.setRenderHint(QPainter::Antialiasing);

    // Set the brush to transparent
    painter.setBrush(Qt::transparent);

    /*// Draw the image, ensuring we keep the alpha channel (transparency)
    if (!m_image.isNull()) {
        QPixmap scaledPixmap = m_image.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QRect pixmapRect((width() - scaledPixmap.width()) / 2, (height() - scaledPixmap.height()) / 2,
                         scaledPixmap.width(), scaledPixmap.height());
        painter.drawPixmap(pixmapRect.topLeft(), scaledPixmap);
    }*/
}

void Qt_carte::updateAppearance() {
    if (card != nullptr) {
        qDebug() << card->getVisuel();
        QIcon icon(QPixmap(QString::fromStdString(card->getVisuel())));
        this->setIcon(icon);
        this->setIconSize(this->size()); // Adjust the size of the icon to fit the button
    }

    else {
        qDebug() << "prblm";
    }
    // Additional appearance updates...
}


void Qt_carte::updateAppearance(const std::string& string) {
    m_image = QPixmap(QString::fromStdString(string));
    setIcon(QIcon(m_image));
    setIconSize(size());
    update(); // Refresh the widget
}

void Qt_carte::toggleClicked() {
    isClicked = !isClicked;
    update();
}
