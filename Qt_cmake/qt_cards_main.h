#ifndef QT_CARDS_MAIN_H
#define QT_CARDS_MAIN_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class Qt_cards_main : public QWidget {
    Q_OBJECT;

public:
    explicit Qt_cards_main(QWidget *parent = nullptr);
    void addCard();

private:
    QGridLayout *layout;


signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }


};

#endif // QT_CARDS_MAIN_H
