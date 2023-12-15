#ifndef QT_JETONS_MAIN_H
#define QT_JETONS_MAIN_H
#include <QWidget>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>

class Qt_Jetons_Main : public QWidget {
    Q_OBJECT;

public:
    explicit Qt_Jetons_Main(QWidget *parent = nullptr);

private:
    QGridLayout *layout;
};


#endif // QT_JETONS_MAIN_H
