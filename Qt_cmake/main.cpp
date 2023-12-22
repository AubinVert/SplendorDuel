#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QString>
#include "mainwindow.h"
#include "../classes/jeu.h"
#include "../classes/joueur.h"
#include "qt_popup_info.h"
#include "qt_popup_yesno.h"
#include "main.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    InfoDialog info_dialog("Bienvenu dans le jeu Splendor Duel !");
    info_dialog.exec();

    popupYesNo yesno(nullptr, "Voulez vous commencer une nouvelle partie ou finir la dernière partie en cours (Oui/Non) ?");
    yesno.exec();
    char tmp = yesno.getUserChoice();

    if(tmp == 'Y'){
        gameFromScratch(argc, argv);
    }
    else {
        gameFromJson(argc, argv);
    }

    return app.exec();
}
