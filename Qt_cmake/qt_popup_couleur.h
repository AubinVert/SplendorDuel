#ifndef QT_POPUP_COULEUR_H
#define QT_POPUP_COULEUR_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "../classes/jeu.h"
#include "../classes/carte.h"

class popupCouleur : public QDialog {
    Q_OBJECT

public:
    explicit popupCouleur(QWidget *parent = nullptr);

    const int getNb() const {return nb;}
    const Color getColor() const {return c;}

    void setNb(int x) { nb = x;}
    void setColor(const Color& coul) { c = coul;}

private slots:
    void onSubmitClicked();

private:
    QComboBox *comboBox;
    QComboBox *comboBoxNb;

    Color c;
    int nb;

    QPushButton *submitButton;
};

#endif // QT_POPUP_COULEUR_H
