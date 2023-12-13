#ifndef QT_PLATEAU_H
#define QT_PLATEAU_H

#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class Qt_Plateau : public QWidget {
    Q_OBJECT;

public:
    explicit Qt_Plateau(QWidget *parent = nullptr);

private:
    QGridLayout *layout;
    QHBoxLayout *privilegesLayout;
};


#endif // QT_PLATEAU_H
