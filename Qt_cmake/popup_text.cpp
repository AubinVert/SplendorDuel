#include "popup_text.h"
#include "../classes/jeu.h"
#include <QLabel>

InputPopup::InputPopup(QWidget *parent) : QDialog(parent) {
    jeu = &Jeu::getJeu();

    QLabel *nameLabel1 = new QLabel("Player 1 Name:", this);
    lineEdit1 = new QLineEdit(this);

    QLabel *nameLabel2 = new QLabel("Player 2 Name:", this);
    lineEdit2 = new QLineEdit(this);

    QLabel *typeLabel1 = new QLabel("Player 1 Type:", this);
    comboBox1 = new QComboBox(this);
    comboBox1->addItem("IA");
    comboBox1->addItem("Joueur");

    QLabel *typeLabel2 = new QLabel("Player 2 Type:", this);
    comboBox2 = new QComboBox(this);
    comboBox2->addItem("IA");
    comboBox2->addItem("Joueur");

    submitButton = new QPushButton("Submit", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(nameLabel1);
    layout->addWidget(lineEdit1);
    layout->addWidget(typeLabel1);
    layout->addWidget(comboBox1);
    layout->addWidget(nameLabel2);
    layout->addWidget(lineEdit2);
    layout->addWidget(typeLabel2);
    layout->addWidget(comboBox2);
    layout->addWidget(submitButton);

    setWindowTitle("Player Settings");

    connect(submitButton, &QPushButton::clicked, this, &InputPopup::onSubmitClicked);
}

void InputPopup::onSubmitClicked() {
    // Convert QStrings to std::string and store them in lvalue strings
    std::string stdName1 = lineEdit1->text().toStdString();
    std::string stdName2 = lineEdit2->text().toStdString();
    std::string stdType1 = comboBox1->currentText().toStdString();
    std::string stdType2 = comboBox2->currentText().toStdString();

    // Now pass these std::string objects to the setPlayers method
    jeu->setPlayers(stdName1, stdName2, stdType1, stdType2);

    // Close the dialog
    accept();
}
