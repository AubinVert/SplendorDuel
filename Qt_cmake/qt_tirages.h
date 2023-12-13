#ifndef QT_TIRAGES_H
#define QT_TIRAGES_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QVector>

class Qt_Tirages : public QWidget {
    Q_OBJECT

public:
    explicit Qt_Tirages(QWidget *parent = nullptr);

private:
    QHBoxLayout *tier1Layout;
    QHBoxLayout *tier2Layout;
    QHBoxLayout *tier3Layout;
    QVector<QLabel*> tier1Cards;
    QVector<QLabel*> tier2Cards;
    QVector<QLabel*> tier3Cards;
    QLabel *deckImage1;
    QLabel *deckImage2;
    QLabel *deckImage3;

    void setupTierLayout(QHBoxLayout *&layout, QVector<QLabel*> &cards, int cardCount, QLabel *&deckImage);
};

#endif // QT_TIRAGES_H
