#ifndef PLATEAU_H
#define PLATEAU_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class Plateau : public QWidget {
    Q_OBJECT;

public:
    explicit Plateau(QWidget *parent = nullptr);

private:
    QGridLayout *layout;
    QHBoxLayout *privilegesLayout;
    // Additional private members for the privilege widgets, if needed
};


#endif // PLATEAU_H
