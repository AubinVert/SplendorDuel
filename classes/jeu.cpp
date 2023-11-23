#include "jeu.h"

// condition pour savoir si le jeu est terminé à chaque tour on check ?


void Jeu::tour_suivant() {
    Joueur* temp = qui_joue;
    qui_joue = adversaire;
    adversaire = temp;
    manche++;
}


const int Jeu::choice(){

     int tmp = 0;
    while (tmp != 1 && tmp != 2 && tmp != 3){
        cout<<"Pour prendre des jetons appuyez sur -> 1"<<endl;
        cout<<"Pour acheter une carte appuyez sur -> 2"<<endl;
        cout<<"Pour réserver une carte appuyez sur -> 3"<<endl;
        cout<<"choix :";
        cin>>tmp;
    }

    switch (tmp) {
        case 1:
        {
            unsigned int i = 0;
            // ici il faut cout le plateau
            cout<<"\n\nPlateau :"<<endl;
            cout<<Plateau::get_plateau<<endl;

            cout<<"Combien de jetons voulez-vous prendre ? : "<<endl;
            cout<<"choix :";
            cin>>i;
            if(i>3){
                throw("Vous ne pouvez pas prendre plus de 3 jetons");
            }
            for (int j = 0; j < i; ++j) {
                unsigned int k =0;
                cout<<"Veuillez renseigner l'indice du jeton que vous voulez prendre : "<<endl;
                cout<<"choix :";
                cin>>k;
                qui_joue->piocher_jeton(k);
            }
            break;
        }

        case 2:

            // comment désigner la bonne carte mtn ?


        case 3:

        {
            cout<<"\n\nTirage1 :"<<endl;
            cout<<*tirage_1<<endl;
            cout<<"\nTirage2 :"<<endl;
            cout<<*tirage_2<<endl;
            cout<<"\nTirage3 :"<<endl;
            cout<<*tirage_3<<endl;
            int choix = 0;
            while(choix != 1 && choix != 2 && choix != 3){
                cout<<"Dans quel tirage vous voulez réserver une carte ?"<<endl;
                cout<<"choix";
                cin>>choix;
            }
            switch (choix) {
                case 1:{
                    unsigned int indice = 0;
                    cout<<"Veuillez renseigner l'indice de la carte que vous voulez retirer ! "<<endl;
                    cout<<"choix : ";
                    cin>>indice;
                    qui_joue->reserver_carte(tirage_1, indice);
                    break;
                }case 2:{
                    unsigned int indice = 0;
                    cout<<"Veuillez renseigner l'indice de la carte que vous voulez retirer ! "<<endl;
                    cout<<"choix : ";
                    cin>>indice;
                    qui_joue->reserver_carte(tirage_2, indice);
                    break;
                }
                case 3:{
                    unsigned int indice = 0;
                    cout<<"Veuillez renseigner l'indice de la carte que vous voulez retirer ! "<<endl;
                    cout<<"choix : ";
                    cin>>indice;
                    qui_joue->reserver_carte(tirage_3, indice);
                    break;
                }

            }
        }



    }




}


 Joueur& Jeu::get_tour()  {
    return *qui_joue;
}

Joueur& Jeu::getOpponent()  {
    return *adversaire;
}

Jeu::Jeu() {
    // constructeur jetons (avec le sac)
    Sac::get_sac();
    Plateau::get_plateau();
    // construceur cartes
    cartes_joiallerie = initCartesJoaillerie();
    cartes_royales = initCartesRoyales();

    // constructeur privileges
    privileges = initPrivileges();

    // pioches :
    p1 = new Pioche(1);
    p2 = new Pioche(2);
    p3 = new Pioche(3);
    p1->InitPioches(p1, p2, p3, cartes_joiallerie);

    //std::cout<<p1->getPioche().size()<<endl;

    // tirages ?

    tirage_1 = new Tirage(1, 5, *p1);
    tirage_2 = new Tirage(2, 4, *p2);
    tirage_3 = new Tirage(3, 3, *p3);
    tirage_1->remplirTirage();
    tirage_2->remplirTirage();
    tirage_3->remplirTirage();


}

Jeu::Handler Jeu::handler;

Jeu::~Jeu(){
    Sac::libere_sac(); // détruit aussi jetons ?


    for (int i = 0; i < cartes_royales.size(); ++i) {
        delete cartes_royales[i];
    }
    for (int i = 0; i < cartes_joiallerie.size(); ++i) {
        delete cartes_joiallerie[i];
    }

    // libère les tirages :

    delete tirage_1;
    delete tirage_2;
    delete tirage_3;

    // reste à détruire privilèges, plateau ?

};

Jeu& Jeu::getJeu(){
    if (handler.instance == nullptr)  handler.instance = new Jeu;
    return *handler.instance;
}

void Jeu::libereJeu(){
    delete handler.instance;
    handler.instance = nullptr;
}

void Jeu::test() {
    if (handler.instance == nullptr) std::cout << "Test";
}