#ifndef QT_VUE_CARTE_H
#define QT_VUE_CARTE_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../classes/carte.h"


class Qt_carte : public QPushButton {
    Q_OBJECT

private:
    Card* m_carte;
    QPixmap m_image;  // Image

public:
    explicit Qt_carte(QWidget *parent = nullptr);
    void setImage(const QString &imagePath);  // Méthode pour mettre l'image

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void carteClicked();

public slots:
    void onCarteClicked();
};


#endif // QT_VUE_CARTE_H
