#ifndef MAIN_H
#define MAIN_H

#ifndef LO21_SPLENDOR_DUEL_MAIN_H
#define LO21_SPLENDOR_DUEL_MAIN_H

#include <iostream>
#include "../classes/jeu.h"
#include "mainwindow.h"
#include <QThread>
#include <QApplication>

void toJson(){
    json j = Jeu::getJeu().toJson();
    std::string s = j.dump(2);
    std::ofstream file("../src/backup.json");
    file << s;
}


void gameFromScratch(int argc, char *argv[]){
    QApplication app(argc, argv);

    srand(static_cast<unsigned>(std::time(nullptr)));

    // Init le jeu
    Jeu::getJeu();

    MainWindow::getMainWindow().show();
    Qt_Plateau::getPlateau().connectJetons();
    MainWindow::getMainWindow().getTirages()->connectCartes();


    // Setup des noms
    MainWindow::getMainWindow().demanderNoms();
    MainWindow::getMainWindow().setTopPlayerName(QString::fromStdString(Jeu::getJeu().getCurrentPlayer().getName()));
    MainWindow::getMainWindow().setBottomPlayerName(QString::fromStdString(Jeu::getJeu().getOpponent().getName()));

    // Setup du plateau
    Jeu::getJeu().get_tour();
    MainWindow::getMainWindow().updatePlateau();
    MainWindow::getMainWindow().updateTirages();
    MainWindow::getMainWindow().updatePrivileges();

    unsigned int from_error =0;

    while (!Jeu::getJeu().isFinished()) {


        if(from_error == 0){
            Jeu::getJeu().get_tour();
            MainWindow::getMainWindow().setTopPlayerName(QString::fromStdString(Jeu::getJeu().getOpponent().getName()));
            MainWindow::getMainWindow().setBottomPlayerName(QString::fromStdString(Jeu::getJeu().getCurrentPlayer().getName()));
            // qDebug() << Jeu::getJeu().getCurrentPlayer().getName();
            MainWindow::getMainWindow().updateQuiJoue();

            /*
            cout<<"Etat des joueurs : "<<endl;
            Jeu::getJeu().getCurrentPlayer().print_player();
            cout<<"Bonus blanc"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::blanc)<<endl;
            cout<<"Bonus vert"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::vert)<<endl;
            cout<<"Bonus bleu"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::bleu)<<endl;
            cout<<"Bonus rouge"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::red)<<endl;
            cout<<"Bonus noir"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::noir)<<endl;
            cout<<"Bonus joker"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::joker)<<endl;
            cout<<endl;
            */

            // cout<<"Il y a "<<Sac::get_sac().get_nb_sac()<<" jetons dans le sac."<<endl;

            /*
            cout<<"\n\nPlateau :"<<endl;
            Plateau::get_plateau().printTab();

            cout<<"\n\nTirage1 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_1()<<endl;
            cout<<"\nTirage2 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_2()<<endl;
            cout<<"\nTirage3 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_3()<<endl;
            */


            // cout<<"c'est à "<<Jeu::getJeu().get_tour().getName()<<" de jouer ! "<<endl;
            // Faire un popup avec c'est à de jouer

            try{
                toJson();
            }catch (SplendorException &e){
                cout<<e.getInfos()<<endl;
                MainWindow::getMainWindow().triggerInfo(e.getInfos());
            }


        }
        try{
            // qDebug() << "DEBUT TRY";
            Jeu::getJeu().getCurrentPlayer().choice_qt();
            // update affichage

            Jeu::getJeu().getCurrentPlayer().verifJetons_qt();

            if(Jeu::getJeu().getCurrentPlayer().royaleCardEligibility()==1){
                Jeu::getJeu().getCurrentPlayer().selectionRoyalCard_qt();
            }


            Jeu::getJeu().tour_suivant();

            MainWindow::getMainWindow().updateScores();
            MainWindow::getMainWindow().updatePlateau();
            MainWindow::getMainWindow().updateTirages();
            MainWindow::getMainWindow().updatePrivileges();
            MainWindow::getMainWindow().update();
            // QThread::msleep(3000);

            from_error = 0;

        }catch(SplendorException& e){
            from_error = 1;
            cout<<"============= ACTION NON AUTORISÉE ================="<<endl;
            cout<< e.getInfos()<<endl;
        }

    }


    cout<<"=================== Partie terminée ==================="<<endl;
    cout<<"Nombre de manches : "<<Jeu::getJeu().getManche()<<endl;
    cout<<"Stats du gagnant:"<<endl;
    Jeu::getJeu().getCurrentPlayer().print_player();

    Jeu::libereJeu();

    app.exec();
}

void gameFromJson(){



    try{
        std::ifstream file("../src/backup.json");

        if (!file.is_open()) {
            std::cerr << "Failed to open the JSON file." << std::endl;
            throw SplendorException("Fichier non ouvert");
        }

        json data;
        file >> data;
        file.close();

        // si maximum de cartes atteint alors cartes générées en trop.
        // mauvaise gestion des cartes !

        if(data["est_termine"]){
            cout<<"vous ne pouvez pas reprendre une partie terminée !"<<endl;
            return;
        }

        Jeu::getJeu(data);


    }catch (SplendorException &e){
        cout<< e.getInfos()<<endl;
    }


    unsigned int from_error =0;

    while (!Jeu::getJeu().isFinished()) {


        if(from_error == 0){
            Jeu::getJeu().get_tour();

            cout<<"Etat des joueurs : "<<endl;
            Jeu::getJeu().getCurrentPlayer().print_player();
            cout<<"Bonus blanc"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::blanc)<<endl;
            cout<<"Bonus vert"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::vert)<<endl;
            cout<<"Bonus bleu"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::bleu)<<endl;
            cout<<"Bonus rouge"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::red)<<endl;
            cout<<"Bonus noir"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::noir)<<endl;
            cout<<"Bonus joker"<<Jeu::getJeu().getCurrentPlayer().calculateBonus(colorBonus::joker)<<endl;
            cout<<endl;

            cout<<"Il y a "<<Sac::get_sac().get_nb_sac()<<" jetons dans le sac."<<endl;

            cout<<"\n\nPlateau :"<<endl;
            Plateau::get_plateau().printTab();

            cout<<"\n\nTirage1 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_1()<<endl;
            cout<<"\nTirage2 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_2()<<endl;
            cout<<"\nTirage3 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_3()<<endl;



            cout<<"c'est à "<<Jeu::getJeu().get_tour().getName()<<" de jouer ! "<<endl;


            try{
                toJson();
            }catch (SplendorException &e){
                cout<<e.getInfos()<<endl;
            }



        }
        try{

            Jeu::getJeu().getCurrentPlayer().choice();
            Jeu::getJeu().getCurrentPlayer().verifJetons();
            if(Jeu::getJeu().getCurrentPlayer().royaleCardEligibility()==1){
                Jeu::getJeu().getCurrentPlayer().selectionRoyalCard();
            }
            Jeu::getJeu().tour_suivant();
            from_error = 0;

        }catch(SplendorException& e){
            from_error = 1;
            cout<<"============= ACTION NON AUTORISÉE ================="<<endl;
            cout<< e.getInfos()<<endl;
        }

    }

    cout<<"=================== Partie terminée ==================="<<endl;
    cout<<"Nombre de manches : "<<Jeu::getJeu().getManche()<<endl;
    cout<<"Stats du gagnant:"<<endl;
    Jeu::getJeu().getCurrentPlayer().print_player();

    Jeu::libereJeu();

}


#endif //LO21_SPLENDOR_DUEL_MAIN_H


#endif // MAIN_H
