#ifndef QT_TIRAGES_H
#define QT_TIRAGES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVector>
#include "qt_vue_carte.h"

class Qt_Tirages : public QWidget {
    Q_OBJECT

public:
    explicit Qt_Tirages(QWidget *parent = nullptr);

private:
    QHBoxLayout *tier1Layout;
    QHBoxLayout *tier2Layout;
    QHBoxLayout *tier3Layout;
    QHBoxLayout *royalLayout;
    QVector<Qt_carte*> tier1Cards;
    QVector<Qt_carte*> tier2Cards;
    QVector<Qt_carte*> tier3Cards;
    QVector<Qt_carte*> royalCards;
    QLabel *deckImage1;
    QLabel *deckImage2;
    QLabel *deckImage3;
    QLabel *royalCardsImage;

    void setupTierLayout(QHBoxLayout *&layout, QVector<Qt_carte*> &cards, int cardCount, QLabel *&deckImage);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }

};

#endif // QT_TIRAGES_H
