#ifndef QT_POPUP_YESNO_H
#define QT_POPUP_YESNO_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QString>

class popupYesNo : public QDialog {
    Q_OBJECT

private:
    char userChoice;  // To store the user's choice

public:
    popupYesNo(QWidget *parent = nullptr, const std::string& info = "") : QDialog(parent) {
        QVBoxLayout *layout = new QVBoxLayout(this);

        if (info != ""){
            QLabel *infolabel = new QLabel(QString::fromStdString(info), this);
            layout->addWidget(infolabel);
        }

        QLabel *text = new QLabel("Confirmez votre choix");
        layout->addWidget(text);

        QPushButton *yesBtn = new QPushButton("Oui", this);
        connect(yesBtn, &QPushButton::clicked, this, [this]() { onChoiceMade('Y'); });
        layout->addWidget(yesBtn);

        QPushButton *noBtn = new QPushButton("Non", this);
        connect(noBtn, &QPushButton::clicked, this, [this]() { onChoiceMade('N'); });
        layout->addWidget(noBtn);
    }

    int getUserChoice() const { return userChoice; }

private slots:
    void onChoiceMade(char choice) {
        userChoice = choice;
        accept();  // Close the dialog
    }

};

#endif // QT_POPUP_YESNO_H
