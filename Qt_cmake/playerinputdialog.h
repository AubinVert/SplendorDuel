#ifndef PLAYERINPUTDIALOG_H
#define PLAYERINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class PlayerInputDialog : public QDialog {
    Q_OBJECT

public:
    PlayerInputDialog(QWidget *parent = nullptr);

signals:
    void inputValuesSubmitted(QString name1, QString name2, QString choix1, QString choix2);

private slots:
    void onSubmitClicked();

private:
    QLineEdit *name1Edit;
    QLineEdit *name2Edit;
    QLineEdit *choix1Edit;
    QLineEdit *choix2Edit;
    QPushButton *submitButton;
    QPushButton *cancelButton;
};


#endif // PLAYERINPUTDIALOG_H
