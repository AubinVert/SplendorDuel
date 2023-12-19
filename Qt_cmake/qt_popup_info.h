#ifndef QT_POPUP_INFO_H
#define QT_POPUP_INFO_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class InfoDialog : public QDialog {
    Q_OBJECT

public:
    // Constructor with a message parameter
    explicit InfoDialog(const QString& message, QWidget *parent = nullptr) : QDialog(parent) {
        // Set up the dialog layout
        QVBoxLayout *layout = new QVBoxLayout(this);

        // Create a label to show the message
        QLabel *label = new QLabel(message, this);
        layout->addWidget(label);

        // Create an OK button
        QPushButton *okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);

        // Connect the OK button's clicked signal to the dialog's accept slot
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

        // Set the dialog layout
        setLayout(layout);
        connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    }
};

#endif // QT_POPUP_INFO_H
