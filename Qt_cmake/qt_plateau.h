#ifndef QT_PLATEAU_H
#define QT_PLATEAU_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "qt_vue_jeton.h"

#define NJETONS 25

class Qt_Plateau : public QWidget {
    Q_OBJECT;

public:
    Qt_Plateau(QWidget *parent = nullptr);
    const std::vector<Qt_jeton*>& getJetons() const {return jetons;}

private:
    QGridLayout *layout;
    QGridLayout *privilegesLayout;
    std::vector<Qt_jeton*> jetons;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }

    void paintEvent(QPaintEvent *event) override;

};


#endif // QT_PLATEAU_H
