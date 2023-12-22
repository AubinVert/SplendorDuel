#ifndef QT_CHOICEPOPUP_H
#define QT_CHOICEPOPUP_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>

class ChoiceDialog : public QDialog {
    Q_OBJECT

private:
    int userChoice = -1;

public:
    ChoiceDialog(int nb_choice, QWidget *parent = nullptr) : QDialog(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *text = new QLabel("Choix");
        text->setAlignment(Qt::AlignCenter);
        layout->addWidget(text);

        // Display options based on nb_choice
        int i = 1;
        if (nb_choice % 2 == 1) {
            QPushButton *btn = new QPushButton("Utiliser un privilège", this);
            connect(btn, &QPushButton::clicked, this, [this, i]() { onChoiceMade(i); });
            layout->addWidget(btn);
            i++;
        }
        if (nb_choice >= 2) {
            QPushButton *btn = new QPushButton("Remplir le plateau", this);
            connect(btn, &QPushButton::clicked, this, [this, i]() { onChoiceMade(i); });
            layout->addWidget(btn);
            i++;
        }

        // Actions optionnelles
        QPushButton *takeTokensBtn = new QPushButton("Prendre des jetons", this);
        connect(takeTokensBtn, &QPushButton::clicked, this, [this, i]() { onChoiceMade(i); });
        layout->addWidget(takeTokensBtn);
        i++;

        QPushButton *buyCardBtn = new QPushButton("Acheter une carte", this);
        connect(buyCardBtn, &QPushButton::clicked, this, [this, i]() { onChoiceMade(i); });
        layout->addWidget(buyCardBtn);
    }

    int getUserChoice() const { return userChoice; }

private slots:
    void onChoiceMade(int choice) {
        userChoice = choice;
        accept();
    }

};

#endif // QT_CHOICEPOPUP_H
