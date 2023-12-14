#ifndef QT_PLATEAU_H
#define QT_PLATEAU_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class Qt_Plateau : public QWidget {
    Q_OBJECT;

public:
    Qt_Plateau(QWidget *parent = nullptr);

private:
    QGridLayout *layout;
    QHBoxLayout *privilegesLayout;

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override {
        emit clicked();
    }


};


#endif // QT_PLATEAU_H
