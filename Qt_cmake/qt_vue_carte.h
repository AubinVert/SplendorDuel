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
    const Card* card;
    QPixmap m_image;

public:
    explicit Qt_carte(QWidget *parent = nullptr);
    void updateAppearance();
    void updateAppearance(const std::string& string); // pour les pioches (qui ne changent pas)

    const Card* getCard() const {return card;}
    void setCard(const Card* j) {card = j;}

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void carteClicked();

public slots:
    void onCarteClicked();
};


#endif // QT_VUE_CARTE_H
