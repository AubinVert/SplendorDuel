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
    bool isClicked; // Track si la carte a été click
    const Card* card;
    QPixmap m_image;
    int indice_dans_tirage;
    bool est_reservee;

public:

    const int getIndice() const {return indice_dans_tirage;}
    void setIndice(int x) {indice_dans_tirage = x;}

    const bool getReservee() const {return est_reservee;}
    void setReservee(bool x) {est_reservee = x;}

    explicit Qt_carte(QWidget *parent = nullptr);

    void toggleClicked();
    void updateAppearance();
    void updateAppearance(const std::string& string);

    const Card* getCard() const {return card;}
    void setCard(const Card* j) {card = j;}

protected:
    void paintEvent(QPaintEvent *event) override;

signals:
    void carteClicked(Qt_carte *c);

public slots:
    void clickedEvent() {
        emit carteClicked(this);
    }
};

#endif // QT_VUE_CARTE_H
