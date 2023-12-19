#ifndef QT_VUE_JETON_H
#define QT_VUE_JETON_H

#include <QWidget>
#include <QResizeEvent>
#include <QPainter>
#include <QString>
#include <QStaticText>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QPushButton>
#include "../classes/jetons.h"


class Qt_jeton : public QPushButton {
    Q_OBJECT

private:
    bool isClicked; // Track si le jeton a été click
    const Jeton* jeton;
    int indice;

public:

    explicit Qt_jeton(QWidget *parent = nullptr);
    void toggleClicked(); // Method to change the clicked state
    void updateAppearance(); // Mise à jour image

    const Jeton* getJeton() const {return jeton;}
    void setJeton(const Jeton* j) {jeton = j;}

    const int getIndice() const {return indice;}
    void setIndice(int x) {indice = x;}


protected:
    void paintEvent(QPaintEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override; // Handle mouse press events

signals:
    void jetonClicked(Qt_jeton *j); // Signal à émettre si le jeton a été click

private slots:
    void clickedEvent() {
            emit jetonClicked(this);
    }

};


#endif // QT_VUE_JETON_H
