#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qt_tirages.h"
#include "qt_plateau.h"
#include "qt_jetons_bas.h"
#include "qt_jetons_main.h"
#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QInputDialog>
#include <QLineEdit>
#include <QLCDNumber>
#include <QDesktopServices>
#include <QUrl>

#include "popup_text.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void updateTopScore(int score);  // Méthode de mise à jour du score du haut
    void updateBottomScore(int score);  //  -- du bas

    void demanderNoms() {
        InputPopup *popup = new InputPopup(this);

        // Connect signals and slots if needed
        // For example, if you want to do something with the input after it's submitted

        popup->setModal(true); // Set the dialog to be modal
        popup->exec();         // Show the dialog modally

        // Code here will execute after the dialog is closed
        // You can process the input here if needed
    }

    void setTopPlayerName(const QString &name);
    void setBottomPlayerName(const QString &name);

private slots:
    void showCards();
    void showJetons();
    void remplirPlateau();
    void openWebLink();


private:
    QLabel *topScoreLabel;
    QLabel *bottomScoreLabel;
    QLCDNumber *topScoreDisplay;  // Top score display
    QLCDNumber *bottomScoreDisplay;  // Bottom score display
    QPushButton *remplirPlateauButton; // Remplir plateau
    QPushButton *viewCardsButtonBottom;
    QPushButton *viewJetonsButtonBottom;
    QPushButton *viewCardsButtonTop;
    QPushButton *viewJetonsButtonTop;

    QLabel *topPlayerNameLabel;
    QLabel *bottomPlayerNameLabel;
};

#endif // MAINWINDOW_H
