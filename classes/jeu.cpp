#include "jeu.h"
#include <string>
#include "joueur.h"



// condition pour savoir si le jeu est terminé à chaque tour on check ?


void Jeu::tour_suivant() {
    Strategy_player* temp = qui_joue;
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

/*
const int Jeu::choice(){

    int tmp = 0;
    bool fin_choix = 0;
    while (!fin_choix){
        try{
            cout<<"Pour prendre des jetons appuyez sur -> 1"<<endl;
            cout<<"Pour acheter une carte appuyez sur -> 2"<<endl;
            cout<<"Pour voir la liste des jetons possédés -> 3"<<endl;
            cout<<"choix :";
            cin>>tmp;

            if(tmp<1 or tmp>3){
                throw SplendorException("Il n'y a que 3 choix! Vous ne pouvez pas choisir autre chose que 1, 2 ou 3!\n");
            }

            fin_choix = 1;
        }catch(SplendorException& e){
            cout<<e.getInfos()<<"\n";
        }


    }

    switch (tmp) {
        case 1:
        {
            unsigned int nb = 0;

            cout<<"\n\nPlateau :"<<endl;
            Plateau::get_plateau().printTab();

            cout<<"Combien de jetons voulez-vous prendre ? : "<<endl;
            cout<<"choix :";
            cin>>nb;
            if(nb>3 || nb<=0){
                throw SplendorException("Nombre de jetons invalide");
            }
            if(nb > Plateau::get_plateau().getCurrentNb()){
                throw SplendorException("Il ne reste que "+std::to_string(Plateau::get_plateau().getCurrentNb())+" jetons sur le plateau! Vous ne pouvez pas en prendre plus!");
            }

            bool choix_ok = 0;
            while(!choix_ok){
                try{
                    std::vector<int> tmp_tab(0);
                    optional<Position> pos = nullopt;
                    int nb_or = 0;
                    int nb_perle = 0;

                    for(int i = 0; i<nb; i++){
                        unsigned int indice = 0;
                        cout<<"Veuillez renseigner l'indice du jeton "<<i<<" que vous voulez prendre : "<<endl;
                        cout<<"choix :";
                        cin>>indice;
                        if(Plateau::get_plateau().get_plateau_i(indice)==nullptr){//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                            throw SplendorException("Il n'y a pas de jeton à cet indice!\n");
                        }
                        if(indice>Jeton::getNbMaxJetons()){//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                            throw SplendorException("Il n'y a que "+std::to_string(Jeton::getNbMaxJetons())+" places sur le plateau\n");
                        }
                        if(Plateau::get_plateau().get_plateau_i(indice)->getColor()==Color::gold){
                            nb_or++;
                        }
                        if(Plateau::get_plateau().get_plateau_i(indice)->getColor()==Color::perle){
                            nb_perle++;
                        }
                        if((nb_or==1)&&(Jeu::getJeu().get_tour().getNbCartesReservees()>=3)){
                            throw SplendorException("Vous n'avez pas le droit de réserver une carte supplémentaire!");
                        }
                        if(nb_or==1 and nb>1){
                            throw SplendorException("Attention, on ne peut prendre qu'un seul jeton or!");
                        }
                        tmp_tab.push_back(indice);

                    }
                    //tri du vecteur par selection
                    int min = 0;
                    for(int j = 0;j<tmp_tab.size()-1;j++){
                        min = j;
                        for(int k = j+1; k<tmp_tab.size();k++){
                            if (tmp_tab[k]<tmp_tab[min]){
                                min = k;
                            }
                        }
                        if (min!=j){
                            int tmp2 = tmp_tab[min];
                            tmp_tab[min] = tmp_tab[j];
                            tmp_tab[j] = tmp2;
                        }
                    }
                    // vecteur trié
                    // cout<<"vecteur trié\n";


                    if (nb == 2){ // vérification de l'alignement pour 2 jetons
                        //cout<<"vérification pour 2 jetons\n";
                        const Jeton* jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[0]);
                        optional <Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1],jet1);
                        if(pos1==nullopt){
                            throw SplendorException("Jetons non-alignés\n");
                        }
                    }
                    if(nb==3){ // vérification de l'alignement pour 3 jetons
                        //cout<<"vérification pour 3 jetons\n";
                        const Jeton* jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[1]);
                        optional <Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[0],jet1);

                        const Jeton* jet2 = Plateau::get_plateau().get_plateau_i(tmp_tab[2]);
                        optional <Position> pos2 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1],jet2);

                        if((pos1!=pos2) || (pos1==nullopt) || (pos2==nullopt)){
                            throw SplendorException("Jetons non-alignés\n");
                        }
                    }
                    // on a vérifié l'alignement des jetons

                    if(nb_or==1){
                        Jeu::reservation_carte(Jeu::get_tour());
                    }
                    if(nb_perle == 2){ // obtention d'un privilège par l'adversaire si on pioche les 2 jetons perles en une fois
                        Jeu::getOpponent().obtainPrivilege();
                    }

                    if(nb==3){// obtention d'un privilège par l'adversaire si les 3 jetons sont de la même couleur
                        if((Plateau::get_plateau().get_plateau_i(tmp_tab[0])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor())
                        &&(Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[2])->getColor())){
                            Jeu::getOpponent().obtainPrivilege();
                        }
                    }
                    for(int i = 0; i<nb;i++){ // acquisition des jetons par le joueur
                        Jeu::get_tour().piocher_jeton(tmp_tab[i]);
                    }
                    choix_ok = 1;
                }catch(SplendorException& e){
                    cout<<e.getInfos()<<"\n";
                }
            }

            break;
        }

        case 2:

            // On demande s'il veut acheter une carte qu'il a réservé ou non
        {
            unsigned int choice = -1;

            if(qui_joue->getNbCartesReservees()!=0){


                while(choice != 1 && choice != 0){
                    cout<<"Voulez vous acheter une carte que vous avez réserver auparavant ? 1 pour oui /0 pour non"<<endl;
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
            break;
        }

        case 3:
        {
            // affichage des jetons du jouer !
            cout<<"Inventaire du joueur : "<<qui_joue->getName()<<endl;
            // afficher pour chaque type

            break;
        }
        default:break;


    }




}
*/

Strategy_player& Jeu::get_tour()  {
    return *qui_joue;
}

Jeu::Jeu() {

    // Création sac
    Sac::get_sac();

    // Création jetons. Ils sont mis dans le sac aussi
    int j = 1;
    for (int i = 0; i<4; i++) {
        auto* temp = new Jeton(j++, Color::bleu);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::rouge);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::vert);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::blanc);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<4; i++){
        auto* temp = new Jeton(j++, Color::noir);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<2; i++){
        auto* temp = new Jeton(j++, Color::perle);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }
    for (int i = 0; i<3; i++){
        auto* temp = new Jeton(j++, Color::gold);
        jetons.push_back(temp);
        Sac::get_sac().mettre_jeton_sac(temp);
    }

    // Construction plateau
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

    // Déstruction jetons
    for (auto & jeton : jetons){
        delete jeton;
    }
    jetons.clear();

    // Déstruction cartes royales
    for (auto & cartes_royale : cartes_royales){
        delete cartes_royale;
    }
    cartes_royales.clear();

    // Déstruction cartes joaillerie
    for (auto & it : cartes_joiallerie){
        delete it;
    }
    cartes_joiallerie.clear();

    // Déstruction privilèges
    for (auto & privilege : privileges){
        delete privilege;
    }
    privileges.clear();

    // Libération pioches
    delete p1;
    delete p2;
    delete p3;

    // Libère les tirages :
    delete tirage_1;
    delete tirage_2;
    delete tirage_3;

    // Déstruction sac
    Sac::libere_sac();

    // Déstruction plateau
    Plateau::libere_plateau();

    // Détruire joueur et ses privilèges et cartes royales
    delete qui_joue;
    delete adversaire;
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


void Jeu::setPlayers(){
    string choix1;
    cout<<"Le premier joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix1;

    string name1;
    if(choix1 == "J"){
        cout<<"Veuillez entrer son nom : ";
        cin>>name1;
        qui_joue = new Joueur(name1);
    }else{
        qui_joue = new IA();
    }

    string choix2;
    cout<<"Le second joueur est un joueur ou une IA [J/I]? \nChoix: "<<endl;
    cin>>choix2;

    string name2;
    if(choix1 == "J"){
        cout<<"Veuillez entrer son nom : ";
        cin>>name2;
        adversaire = new Joueur(name2);
    }else{
        adversaire = new IA();
    }
}


