#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qt_tirages.h"
#include "qt_plateau.h"
#include "../classes/jetons.h"
#include "qt_choicepopup.h"
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
#include "qt_popup_yesno.h"
#include "qt_popup_info.h"
#include "qt_popup_tirageoupioche.h"
#include "qt_vue_jeton.h"



#define RIEN "../src/rien.png"


class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QLabel* topRoyal1;
    QLabel* topRoyal2;

    QLabel* bottomRoyal1;
    QLabel* bottomRoyal2;

    QLabel* topPrivileges;
    QLabel* bottomPrivileges;

    QLCDNumber *topScoreDisplay;
    QLCDNumber *bottomScoreDisplay;

    QPushButton *viewCardsButtonBottom;
    QPushButton *viewJetonsButtonBottom;
    QPushButton *viewReservedCardsButtonBottom;

    QPushButton *viewCardsButtonTop;
    QPushButton *viewJetonsButtonTop;
    QPushButton *viewReservedCardsButtonTop;

    QLabel *topPlayerNameLabel;
    QLabel *bottomPlayerNameLabel;

    QEventLoop wait_for_action_jeton;
    QEventLoop wait_for_action_carte;

    Qt_Plateau* plateau;
    Qt_Tirages* tirages;

    QLabel* quijoue;

    Jeu* jeu;

    bool buyingCard;
    bool stealingJeton;

    struct Handler {
        MainWindow * instance = nullptr;
        ~Handler() {
            delete instance;
            instance = nullptr;
        }
    };

    static Handler handler;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    MainWindow (const MainWindow&) = delete;
    MainWindow& operator=(const MainWindow&) = delete;

    int indice_jeton_click;
    Qt_carte* derniere_carte_click;

    bool discarding;

    QDialog* current_dialog;

public:

    const bool getDiscarding() const { return discarding;}
    void setDiscarding(bool x) {discarding = x;}

    void setBuyingCard(bool x) {buyingCard = x;}
    const bool getBuyingCard() {return buyingCard;}

    void setStealingJeton(bool x) {stealingJeton = x;}
    const bool getStealingJeton() {return stealingJeton;}

    void updateQuiJoue();

    QEventLoop* getCarteWaitLoop() {return &wait_for_action_carte;}
    QEventLoop* getJetonWaitLoop() {return &wait_for_action_jeton;}

    int getIndiceJetonClick() const {return indice_jeton_click;}
    void setIndiceJetonClick(int x) {indice_jeton_click = x;}

    Qt_carte* getDerniereCarteClick() const {return derniere_carte_click;}
    void setDerniereCarteClick(Qt_carte* c) {derniere_carte_click = c;}

    void updateTopScore(int score);  // Méthode de mise à jour du score du haut
    void updateBottomScore(int score);  //  -- du bas

    void updateScores(){
        int s1 = Jeu::getJeu().getCurrentPlayer().getNbPoints();
        bottomScoreDisplay->display(s1);
        int s2 = Jeu::getJeu().getOpponent().getNbPoints();
        topScoreDisplay->display(s2);
    }

    void demanderNoms() {
        InputPopup *popup = new InputPopup(this);
        popup->setModal(true);
        popup->exec();
    }

    void setTopPlayerName(const QString &name);
    void setBottomPlayerName(const QString &name);

    void updatePlateau();
    void updateTirages();
    void updatePrivileges();

    static MainWindow& getMainWindow(){
        if (handler.instance == nullptr)  handler.instance = new MainWindow();
        return *handler.instance;
    }

    void freeMainWindow(){
        delete handler.instance;
        handler.instance = nullptr;
    }

    void deactivateButtons();
    void activateJetons();
    void activateForReserve();
    void activateForBuy();
    void activateForRoyalCard();

    Qt_Tirages* getTirages() const {return tirages;}

    void activateJetonColor(const Color& c);

    void acceptCurrentDialog(){
        if (current_dialog != nullptr){
            current_dialog->accept();
            current_dialog = nullptr;
        }
    }

    void setCurrentDialog(QDialog* d) {current_dialog = d;}

private slots:
    void showBoughtCardsTop();
    void showReservedCardsTop();
    void showJetonsTop();

    void showBoughtCardsBottom();
    void showReservedCardsBottom();
    void showJetonsBottom();

    void YesNo(char* choice, const std::string& string);
    void remplirPlateau();
    void openWebLink();
    void nextAction(int* tmp, Joueur* j);
    void showInfo(const string& string);
    void colorChoice(Color *c, int *nb);
    void colorJoker(colorBonus *b);
    void showStats();
    void showStatsPlayers();

public slots:
    void jetonClicked(Qt_jeton*);
    void carteClicked(Qt_carte*);

signals:
    void triggerNextAction(int* tmp, Joueur* j);
    void triggerYesNo(char* choice, const std::string& string = "");
    void triggerInfo(const string& string);
    void triggercolorChoice(Color* c, int *nb);
    void triggercolorJoker(colorBonus *b);
    void jetonActionDone();
    void carteActionDone();

};

#endif // MAINWINDOW_H
