#ifndef QT_POPUP_JOKER_H
#define QT_POPUP_JOKER_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "../classes/jeu.h"
#include "../classes/carte.h"

class popupJoker : public QDialog {
    Q_OBJECT

public:
    explicit popupJoker(QWidget *parent = nullptr);

    const colorBonus getColor() const {return c;}
    void setColor(const colorBonus& coul) { c = coul;}

private slots:
    void onSubmitClicked();

private:
    QComboBox *comboBox;

    colorBonus c;

    QPushButton *submitButton;
};

#endif // QT_POPUP_JOKER_H
