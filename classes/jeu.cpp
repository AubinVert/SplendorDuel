#include "jeu.h"

// condition pour savoir si le jeu est terminé à chaque tour on check ?


void Jeu::tour_suivant() {
    Joueur* temp = qui_joue;
    qui_joue = adversaire;
    adversaire = temp;
    manche++;
    if(qui_joue->getNbCouronnes() == 10 || qui_joue->getNbPoints() == 20 ){
        est_termine = true;
    }

}

// condition d'arrêt

const bool Jeu::isFinished() {
    return est_termine;
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
            cout<<"\n\nPlateau :"<<endl;
            Plateau::get_plateau().print_tab();



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

            // On demande s'il veut acheter une carte qu'il a réserver ou non
        {
            unsigned int choice = -1;

            if(qui_joue->getNbCartesReservees()!=0){


                while(choice != 1 && choice != 0){
                    cout<<"Voulez vous acheter une carte que vous avez résever auparavant ? 1 pour oui /0 pour non"<<endl;
                    cout<<"choix";
                    cin>>choice;
                }
                if(choice==1){
                    //alors on doit lui print les cartes qu'il peut acheter (celles qu'il a déjà reservé)
                    vector<const JewelryCard*> reserved = qui_joue->getCartesReserved();
                    for (int i = 0; i < reserved.size(); ++i) {
                        cout<<"indice : "<<i<<" "<<*reserved[i]<<endl;
                    }
                    unsigned int indice;
                    cout<<"veuillez renseigner l'indice de la carte choisie : ";
                    cin>>indice;
                    qui_joue->buyCardFromReserve(indice);
                }else{
                    cout<<"\n\nTirage1 :"<<endl;
                    cout<<*tirage_1<<endl;
                    cout<<"\nTirage2 :"<<endl;
                    cout<<*tirage_2<<endl;
                    cout<<"\nTirage3 :"<<endl;
                    cout<<*tirage_3<<endl;
                    int choix = 0;
                    while(choix != 1 && choix != 2 && choix != 3){
                        cout<<"Dans quel tirage vous voulez acheter une carte ?"<<endl;
                        cout<<"choix";
                        cin>>choix;
                    }
                    switch (choix) {
                        case 1:{
                            unsigned int indice = 0;
                            cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                            cout<<"choix : ";
                            cin>>indice;
                            qui_joue->buyCard(tirage_1, indice);
                            break;
                        }case 2:{
                            unsigned int indice = 0;
                            cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                            cout<<"choix : ";
                            cin>>indice;
                            qui_joue->buyCard(tirage_2, indice);
                            break;
                        }
                        case 3:{
                            unsigned int indice = 0;
                            cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                            cout<<"choix : ";
                            cin>>indice;
                            qui_joue->buyCard(tirage_3, indice);
                            break;
                        }

                    }



                }


            }
            else{
                cout<<"\n\nTirage1 :"<<endl;
                cout<<*tirage_1<<endl;
                cout<<"\nTirage2 :"<<endl;
                cout<<*tirage_2<<endl;
                cout<<"\nTirage3 :"<<endl;
                cout<<*tirage_3<<endl;
                int choix = 0;
                while(choix != 1 && choix != 2 && choix != 3){
                    cout<<"Dans quel tirage vous voulez acheter une carte ?"<<endl;
                    cout<<"choix";
                    cin>>choix;
                }
                switch (choix) {
                    case 1:{
                        unsigned int indice = 0;
                        cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                        cout<<"choix : ";
                        cin>>indice;
                        qui_joue->buyCard(tirage_1, indice);
                        break;
                    }case 2:{
                        unsigned int indice = 0;
                        cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                        cout<<"choix : ";
                        cin>>indice;
                        qui_joue->buyCard(tirage_2, indice);
                        break;
                    }
                    case 3:{
                        unsigned int indice = 0;
                        cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                        cout<<"choix : ";
                        cin>>indice;
                        qui_joue->buyCard(tirage_3, indice);
                        break;
                    }

                }
            }
        }

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
    Plateau::get_plateau().remplir_plateau(Sac::get_sac());
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