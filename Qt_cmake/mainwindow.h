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


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    void updateTopScore(int score);  // Method to update top score
    void updateBottomScore(int score);  // Method to update bottom score

private slots:
    void showCards();
    void showJetons();
    //void renamePlayerX();
    //void renamePlayerY();
    void remplirPlateau();


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
