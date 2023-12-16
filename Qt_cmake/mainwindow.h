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


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void updateTopScore(int score);  // Méthode de mise à jour du score du haut
    void updateBottomScore(int score);  //  -- du bas

private slots:
    void showCards();
    void showJetons();
    //void renamePlayerX();
    //void renamePlayerY();
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
};

#endif // MAINWINDOW_H
