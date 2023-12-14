#include "joueur.h"
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;
/******************** Fonctions utilitaires ********************/
int positiveOrNull(int x) {
    if (x < 0) return 0;
    return x;
}
/******************** Fonctions utilitaires ********************/



/******************** Strategy_player ********************/

// constructeur destructeur
Strategy_player::Strategy_player(const string &nom) : nb_points(0), nb_cartes_j(0), nb_cartes_r(0), nb_courones(0), nb_privileges(0),nom(nom), nb_jetons(0){}

Strategy_player::~Strategy_player(){
    // Déstruction cartes royales
    for (auto & cartes_royale : cartes_royale){
        delete cartes_royale;
    }
    cartes_royale.clear();

    // Déstruction privilèges
    for (auto & privilege : privileges){
        delete privilege;
    }
    privileges.clear();
}

//méthode utilitaire pour les classes filles

// Calculer le nb de jetons du joueur d'une couleur donnée
int Strategy_player::calculateBonus(enum colorBonus bonus){
    int res = 0;
    //cout<<cartes_joaillerie_achetees.size()<<endl;
    for (auto c: cartes_joaillerie_achetees){
        if ((*c).getBonus() == bonus){
            res += (*c).getNbBonus();
        }
    }
    return res;
}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Strategy_player::nbJeton(const Color& couleur) const {
    int res = 0;
    for (auto j = jetons.begin(); j != jetons.end(); ++j){
        if ((*j)->getColor() == couleur) res++;
    }
    return res;
}

// Supprimer val jetons de la main du joueur et remettre dans le sac
void Strategy_player::withdrawJetons(const Color& c, int val) {
    cout<<"\nSuppression des jetons "+ toString(c) <<":";
    int tmp = val;
    std::vector<int> tmp_tab(0);
    for(int k=0;k< jetons.size(); k++){
        if((jetons[k]->getColor() == c) && (tmp != 0)){
            tmp_tab.push_back(k);
            tmp--;

        }
    }
    cout<<" Vecteur : ";
    for(int i = 0; i<tmp_tab.size();i++){
        cout<<tmp_tab[i]<<" ";
    }

    if(tmp > 0){
        throw SplendorException("Pas assez de jetons "+ toString(c) +" pour en supprimer plus ! ");
    }
    for(int j = val-1 ;j>=0;j--){ //erreur!
        Sac::get_sac().mettre_jeton_sac(jetons[tmp_tab[j]]);
        jetons.erase(jetons.begin() + tmp_tab[j]);
        nb_jetons--;
    }
    cout<<"\nJetons restants dans la main du joueur:"<<endl;
    for (auto j : jetons){
        cout<<*j<<endl;
    }

}

void Strategy_player::reserver_carte(Tirage *t, const int indice){
    //reservation d'une carte d'un tirage
    unsigned int count =0;
    for (int i = 0; i < jetons.size(); ++i) {
        if(jetons[i]->getColor() == Color::gold) count++;
    }
    if(count == 0){
        throw SplendorException("Le joueur n'a pas de jeton or en sa possession!");
    }
    const JewelryCard& tmp =  t->getCarte(indice);
    // la fonction getCarte retire déjà la carte du tirage en question
    cartes_joaiellerie_reservees.push_back(&tmp);
    nb_cartes_j_reservees++;
    t->remplirTirage();
}

void Strategy_player::reserver_carte(Pioche *p) {
    //reservation de la carte au dessus de la pioche
    unsigned int count =0;
    for (int i = 0; i < jetons.size(); ++i) {
        if(jetons[i]->getColor() == Color::gold) count++;
    }
    if(count == 0){
        throw SplendorException("Le joueur n'a pas de jeton or en sa possession!");
    }
    const JewelryCard& tmp = p->getCarte();
    cartes_joaiellerie_reservees.push_back(&tmp);
    nb_cartes_j_reservees++;

}

void Strategy_player::piocher_jeton( int i) {

    if(i>24 || i<0){
        throw SplendorException("Indice du plateau non valide ! ");
    }

    const Jeton* tmp = Plateau::get_plateau().get_plateau_i(i);
    if(tmp == nullptr){
        throw SplendorException("Jeton déjà pris !");
    }
    jetons.push_back(tmp);
    Plateau::get_plateau().set_plateau_i(i,nullptr);
    Plateau::get_plateau().setCurrentNb(Plateau::get_plateau().getCurrentNb()-1);
    std::cout << "Jeton acquis; nombre de jetons restants sur le plateau : " << Plateau::get_plateau().getCurrentNb() << std::endl;
    nb_jetons++;



}

void Strategy_player::obtainRoyaleCard(unsigned int i) {
    // on prend une carte dans le jeu
    if(i>Jeu::getJeu().getCartesRoyales().size()){
        throw SplendorException("Carte non disponible");
    }
    //if (royaleCardEligibility() == false) throw SplendorException("Pas eligible.");
    const RoyalCard& tmp = Jeu::getJeu().pullCarteRoyale(i);
    cartes_royale.push_back(&tmp);
    // ENLEVER DU jeu
    nb_cartes_r++;
    nb_points += tmp.getPrestige();
}

bool Strategy_player::royaleCardEligibility() {
    if (nb_courones >= 3 and nb_courones < 6 and nb_cartes_r == 0){
        return true;
    }

    else if (nb_courones >= 6 and nb_cartes_r == 1){
        return true;
    }

    else {
        return false;
    }
}

void Strategy_player::obtainPrivilege() {
    // on va chercher dans le tirage des privilège un privilège. (du plateau ou alors de ton adversaire ? )
    // d'abord je regarde s'il y a des privilèges dans le jeu :

    if(nb_privileges==Privilege::get_max_instance()) {
        throw SplendorException("Vous avez déjà le nombre maximum autorisé de privilège!");
    }
    if(Jeu::getJeu().getNbPrivilege()==0){
        //si l'adversaire a tous les privilèges
        if(this == &Jeu::getJeu().getCurrentPlayer()){
            //si le joueur qui obtient le privilège est celui dont c'est le tour, on prend à l'opponent
            Jeu::getJeu().getOpponent().retirerPrivilege();
        }else{ // si c'est l'adversaire de clui dont c'est le tour, on retire le privilège à celui qui est en train de jouer
            Jeu::getJeu().getCurrentPlayer().retirerPrivilege();
        }
    }
    if(Jeu::getJeu().getNbPrivilege()==0) {
        throw SplendorException("Plus de privilège!");
    }
    privileges.push_back(Jeu::getJeu().getPrivilege());
    nb_privileges++;


}

void Strategy_player::retirerPrivilege(){
    if(nb_privileges==0){
        throw SplendorException("Vous ne pouvez pas retirer de privilège au joueur");
    }
    Jeu::getJeu().setPrivilege(*privileges[0]);
    privileges.erase(privileges.begin());
    nb_privileges--;



}

void Strategy_player::remplissagePlateau(){
    Jeu::getJeu().remplirPlateau();
    Jeu::getJeu().getOpponent().obtainPrivilege();
    Plateau::get_plateau().printTab();
}

// méthode utilitaire pour le main
bool Strategy_player::victoryConditions() {
    if(nb_courones >= 10)
        return true;
    if(nb_points >= 20)
        return true;

    //test sur les couleurs, si le joueur possède 10 points pour des cartes dont le bonus est de même couleurs, alors le joueur gagne
    int points_blanc = 0;
    int points_bleu = 0;
    int points_rouge = 0;
    int points_vert = 0;
    int points_noir = 0;
    for(auto card: cartes_joaillerie_achetees){
        optional<colorBonus> bonus = (*card).getBonus();
        if(bonus != nullopt){
            if(bonus == colorBonus::blanc) points_blanc += card->getPrestige();
            if(bonus == colorBonus::bleu) points_bleu += card->getPrestige();
            if(bonus == colorBonus::red) points_rouge += card->getPrestige();
            if(bonus == colorBonus::vert) points_vert += card->getPrestige();
            if(bonus == colorBonus::noir) points_noir += card->getPrestige();
        }
    }
    if(points_blanc>=10 || points_bleu>=10 || points_noir>=10 || points_rouge>=10 || points_vert>=10){
        return true;
    }

    // on renvoie false si rien n'est bon!

    return false;
}

void Strategy_player::print_player() {
    cout<<"Joueur : "<<nom<<endl;
    cout<<"Nombre de privilèges : "<<nb_privileges<<endl;
    cout<<"Nombre de points : "<<nb_points<<endl;
    cout<<"Nombre de couronnes : "<<nb_courones<<endl;
    cout<<"Cartes joailleries possédées : "<<endl;
    for(auto card: cartes_joaillerie_achetees){
        cout<<*card<<endl;
    }
    cout<<"---------------------------------------"<<endl;
    cout<<"Cartes joailleries reservées : "<<endl;
    for(auto card : cartes_joaiellerie_reservees){
         cout<<*card<<endl;
    }
    cout<<"---------------------------------------"<<endl;
    cout<<"Cartes royales :"<<endl;
    for(auto card : cartes_royale){
        cout<<*card<<endl;
    }
    cout<<"---------------------------------------"<<endl;
    cout<<"Jetons possédés : "<<endl;
    for(auto jet: jetons){
        cout<<*jet<<endl;
    }
}

int Strategy_player::getOptionalChoices(){
    /***Convention***
    Cette méthode renvoie:
     - 0 si le joueur ou l'ia ne peut rien faire
     - 1 si le joueur ou l'ia ne peut qu'utiliser un privilège,
     - 2 si le joueur ou l'ia ne peut que remplir le plateau,
     - 3 si le joueur ou l'ia peut faire les deux.
    ****************/
    int nb_choices = 0;
    if (Jeu::getJeu().getCurrentPlayer().getNbPrivileges() > 0){
        nb_choices+=1;
    }
    if (Plateau::get_plateau().getCurrentNb() < Jeton::getNbMaxJetons() and Sac::get_sac().get_nb_sac() > 0){
        nb_choices+=2;
    }
    return nb_choices;
}




/******************** Joueur ********************/

//constructeur et destructeur
Joueur::Joueur(const string & nom) : Strategy_player(nom){}

Joueur::~Joueur(){
    // Déstruction cartes royales
    for (auto cartes_royale : cartes_royale){
        delete cartes_royale;
    }
    cartes_royale.clear();

    // Déstruction privilèges
    for (auto privilege : privileges){
        delete privilege;
    }
    privileges.clear();
}

// Méthodes polymorphiques
void Joueur::choice(){
    int tmp = 0;
    bool fin_choix = 0;
    int nb_choice = 0;
    while (!fin_choix){
        try{
            nb_choice = getOptionalChoices(); // bien vérifier la convention sur le retour dans la définition de la méthode
            int i = 1;
            cout<<"Actions optionnelles disponibles:"<<endl;
            if(nb_choice%2 == 1){
                cout<<"Utiliser un privilège-> "<<i++<<endl;
            }
            if(nb_choice>=2){
                cout<<"Remplir le plateau -> "<<i++<<endl;
            }
            cout<<"Actions obligatoire:"<<endl;
            cout<<"Pour prendre des jetons appuyez sur -> "<<i++<<endl;
            cout<<"Pour acheter une carte appuyez sur -> "<<i++<<endl;
            cout<<"choix :";
            cin>>tmp;

            if(tmp<1 or tmp>i+1){
                throw SplendorException("Il n'y a que"+ to_string(i)+" choix! Vous ne pouvez pas choisir autre chose!\n");
            }
            string info;
            cout<<"Validez-vous votre choix? [Y/N]"<<endl;
            cin>>info;
            if(info=="N"){
                cout<<"Vous n'avez pas validé , vous devez recommencer voter choix!";
                throw SplendorException("");
            }


            switch (nb_choice) { // l'affichage et donc le choix dépend de la valeur de retour des choix optionnels
                case (0): { // aucun choix optionnel possible
                    switch (tmp) {
                        case 1: {
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 2: {
                            achat_carte();
                            fin_choix = 1;

                            break;
                        }
//                        case 3: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default: // on continue jusqu'à ce que l'utilisateur choisisse une entrée valide!
                            break;
                    }
                    break;
                }
                case (1): { // seulement possible d'utiliser un privilège
                    switch (tmp) {
                        case 1: {
                            utilisationPrivilege();
                            break;
                        }
                        case 2: {
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 3: {
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 4: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }
                case (2): { // seulement possible de remplir le plateau
                    switch (tmp) {
                        case 1: { // remplissage plateau
                            remplissagePlateau();
                            break;
                        }
                        case 2: {
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 3: {
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 4: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }
                case (3): { // deux choix optionnels possibles
                    switch (tmp) {
                        case 1: {
                            utilisationPrivilege();
                            break;
                        }
                        case 2: { // remplissage plateau
                            remplissagePlateau();
                            break;
                        }
                        case 3: {
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 4: {
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 5: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }default: break;
            }

        }catch(SplendorException& e){
            cout<<e.getInfos()<<"\n";
        }
    }

}

void Joueur::utilisationPrivilege(){
    if (nb_privileges<=0)
        throw SplendorException("Vous n'avez pas de privilège!");
    unsigned int indice;
    cout << "Quel jeton voulez-vous piocher ? " << endl;
    cout << "indice : ";
    cin >> indice;
    Jeu::getJeu().get_tour().piocher_jeton(indice);
    retirerPrivilege();
}

void Joueur::selection_jetons() {
    bool nb_ok=0;
    bool choix_ok = 0;
    if(Plateau::get_plateau().onlyGold() and Jeu::getJeu().get_tour().getNbCartesReservees() >= 3)
        throw SplendorException("Pas possible de piocher: il ne reste que des jetons or et vous ne pouvez plus réserver de carte!");
    while(!choix_ok){
        try{
            std::vector<int> tmp_tab(0);
            optional<Position> pos = nullopt;
            int nb_or = 0;
            int nb_perle = 0;
            string validation;
            while(validation!="Y"){
                while(tmp_tab.size()<3) {
                    unsigned int indice = 0;
                    cout << "Veuillez renseigner l'indice du jeton " << tmp_tab.size() << " que vous voulez prendre ";
                    if (tmp_tab.size()>0){ // ajout de la possibilité de s'arrêter
                        cout<<"-1 pour arrêter la sélection de jetons";
                    }
                    cout<<" :"<<endl;
                    cout << "choix :";
                    cin >> indice;
                    if (indice == -1){
                        break;
                    }
                    if (Plateau::get_plateau().get_plateau_i(indice) ==nullptr) {//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                        nb_or = 0;
                        nb_perle = 0;
                        tmp_tab.clear();
                        throw SplendorException("Il n'y a pas de jeton à cet indice!\n");
                    }
                    if (indice >Jeton::getNbMaxJetons()) {//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                        nb_or = 0;
                        nb_perle = 0;
                        tmp_tab.clear();
                        throw SplendorException("Il n'y a que " + std::to_string(Jeton::getNbMaxJetons()) + " places sur le plateau\n");
                    }
                    if (Plateau::get_plateau().get_plateau_i(indice)->getColor() == Color::gold) {
                        nb_or++;
                    }
                    if (Plateau::get_plateau().get_plateau_i(indice)->getColor() == Color::perle) {
                        nb_perle++;
                    }
                    if ((nb_or == 1) && (Jeu::getJeu().get_tour().getNbCartesReservees() >= 3)) {
                        nb_or = 0;
                        nb_perle = 0;
                        tmp_tab.clear();
                        throw SplendorException("Vous n'avez pas le droit de réserver une carte supplémentaire!");
                    }
                    if (nb_or == 1 and tmp_tab.size() > 1) {
                        nb_or = 0;
                        nb_perle = 0;
                        tmp_tab.clear();
                        throw SplendorException("Attention, on ne peut prendre un jeton or seulement tout seul!");
                    }
                    tmp_tab.push_back(indice);
                }
                cout<<"Validez-vous votre sélection? [Y/N] ";
                cin>>validation;
                if(validation != "Y"){//on recommence le choix des jetons
                    tmp_tab.clear();
                    nb_or = 0;
                    nb_perle = 0;
                    cout<<"\n Vous allez recommencer le choix des jetons: "<<endl;
                    cout<<"Tableau"<<endl;
//                    for(int test = 0; test<tmp_tab.size();test++){
//                        cout<<tmp_tab[test]<<" - ";
//                    }
                }
            }

            //tri du vecteur par selection
            int min = 0;
            for (int j = 0; j < tmp_tab.size() - 1; j++) {
                min = j;
                for (int k = j + 1; k < tmp_tab.size(); k++) {
                    if (tmp_tab[k] < tmp_tab[min]) {
                        min = k;
                    }
                }
                if (min != j) {
                    int tmp2 = tmp_tab[min];
                    tmp_tab[min] = tmp_tab[j];
                    tmp_tab[j] = tmp2;
                }
            }
            // vecteur trié
            // cout<<"vecteur trié\n";


            if (tmp_tab.size() == 2) { // vérification de l'alignement pour 2 jetons
                //cout<<"vérification pour 2 jetons\n";
                const Jeton *jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[0]);
                optional<Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1], jet1);
                if (pos1 == nullopt) {
                    throw SplendorException("Jetons non-alignés\n");
                }
            }
            if (tmp_tab.size() == 3) { // vérification de l'alignement pour 3 jetons
                //cout<<"vérification pour 3 jetons\n";
                const Jeton *jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[1]);
                optional<Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[0], jet1);

                const Jeton *jet2 = Plateau::get_plateau().get_plateau_i(tmp_tab[2]);
                optional<Position> pos2 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1], jet2);

                if ((pos1 != pos2) || (pos1 == nullopt) || (pos2 == nullopt)) {
                    throw SplendorException("Jetons non-alignés\n");
                }
            }

            // on a vérifié l'alignement des jetons
            if(nb_perle == 2){ // obtention d'un privilège par l'adversaire si on pioche les 2 jetons perles en une fois
                Jeu::getJeu().getOpponent().obtainPrivilege();
            }

            if(tmp_tab.size()==3){// obtention d'un privilège par l'adversaire si les 3 jetons sont de la même couleur
                if((Plateau::get_plateau().get_plateau_i(tmp_tab[0])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor())
                   &&(Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[2])->getColor())){
                    Jeu::getJeu().getOpponent().obtainPrivilege();
                }
            }
            for(int i = 0; i<tmp_tab.size();i++){ // acquisition des jetons par le joueur
                Jeu::getJeu().getCurrentPlayer().piocher_jeton(tmp_tab[i]);
            }
            if(nb_or==1){
                reservation_carte();
            }
            choix_ok = 1;
        }catch(SplendorException& e){
            cout<<e.getInfos()<<"\n";
        }
    }
}

void Joueur::reservation_carte() {
    cout << "\n\nTirage1 :" << endl;
    cout << *Jeu::getJeu().get_tirage_1() << endl;
    cout << "\nTirage2 :" << endl;
    cout << *Jeu::getJeu().get_tirage_2() << endl;
    cout << "\nTirage3 :" << endl;
    cout << *Jeu::getJeu().get_tirage_3() << endl;
    string tirageOuPioche;
    cout << "\nSouhaitez-vous réserver une carte dans un tirage ou la première carte d'une pioche? [T/P]"<<endl;
    cin>>tirageOuPioche;
    if(tirageOuPioche != "P"){
        //Le joueur choisit de réserver la carte sur un tirage
        int choix = 0;
        while (choix != 1 && choix != 2 && choix != 3) {
            cout << "Dans quel tirage vous voulez réserver une carte ?" << endl;
            cout << "choix";
            cin >> choix;
        }
        switch (choix) {
            case 1: {
                unsigned int indice = 0;
                cout << "Veuillez renseigner l'indice de la carte que vous voulez retirer ! " << endl;
                cout << "choix : ";
                cin >> indice;
                reserver_carte(Jeu::getJeu().get_tirage_1(), indice);
                break;
            }
            case 2: {
                unsigned int indice = 0;
                cout << "Veuillez renseigner l'indice de la carte que vous voulez retirer ! " << endl;
                cout << "choix : ";
                cin >> indice;
                reserver_carte(Jeu::getJeu().get_tirage_2(), indice);
                break;
            }
            case 3: {
                unsigned int indice = 0;
                cout << "Veuillez renseigner l'indice de la carte que vous voulez retirer ! " << endl;
                cout << "choix : ";
                cin >> indice;
                reserver_carte(Jeu::getJeu().get_tirage_3(), indice);
                break;
            }
        }
    }else{
        int choix = 0;
        cout<<"Sur quelle pioche souhaitez-vous réserver la carte? "<<endl;
        cout<<"choix: ";
        cin>>choix;
        while (choix != 1 && choix != 2 && choix != 3) {
            cout << "Sur quelle pioche voulez-vous réserver une carte ?" << endl;
            cout << "choix";
            cin >> choix;
        }
        reserver_carte(Jeu::getJeu().getPioche(choix));
    }
}

void Joueur::achat_carte(){
    unsigned int choice = -1;
    if(Jeu::getJeu().getCurrentPlayer().getNbCartesReservees()!=0){


        while(choice != 1 && choice != 0){
            cout<<"Voulez vous acheter une carte que vous avez réserver auparavant ? 1 pour oui /0 pour non"<<endl;
            cout<<"choix";
            cin>>choice;
        }
        if(choice==1){
            //alors on doit lui print les cartes qu'il peut acheter (celles qu'il a déjà reservé)
            vector<const JewelryCard*> reserved = Jeu::getJeu().getCurrentPlayer().getCartesReserved();
            for (int i = 0; i < reserved.size(); ++i) {
                cout<<"indice : "<<i<<" "<<*reserved[i]<<endl;
            }
            unsigned int indice;
            cout<<"veuillez renseigner l'indice de la carte choisie : ";
            cin>>indice;
            Jeu::getJeu().getCurrentPlayer().buyCardFromReserve(indice);
        }else{
            cout<<"\n\nTirage1 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_1()<<endl;
            cout<<"\nTirage2 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_2()<<endl;
            cout<<"\nTirage3 :"<<endl;
            cout<<*Jeu::getJeu().get_tirage_3()<<endl;
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
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_1(), indice);
                    break;
                }case 2:{
                    unsigned int indice = 0;
                    cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                    cout<<"choix : ";
                    cin>>indice;
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_2(), indice);
                    break;
                }
                case 3:{
                    unsigned int indice = 0;
                    cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                    cout<<"choix : ";
                    cin>>indice;
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_3(), indice);
                    break;
                }
            }
        }
    }
    else{
        cout<<"\n\nTirage1 :"<<endl;
        cout<<*Jeu::getJeu().get_tirage_1()<<endl;
        cout<<"\nTirage2 :"<<endl;
        cout<<*Jeu::getJeu().get_tirage_2()<<endl;
        cout<<"\nTirage3 :"<<endl;
        cout<<*Jeu::getJeu().get_tirage_3()<<endl;
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
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_1(), indice);
                break;
            }case 2:{
                unsigned int indice = 0;
                cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                cout<<"choix : ";
                cin>>indice;
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_2(), indice);
                break;
            }
            case 3:{
                unsigned int indice = 0;
                cout<<"Veuillez renseigner l'indice de la carte que vous voulez acheter ! "<<endl;
                cout<<"choix : ";
                cin>>indice;
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_1(), indice);
                break;
            }

        }
    }
}

void Joueur::buyCard(Tirage *t, const int indice){

    // la carte qu'il veut supp c'est la ième du tirage t

    const JewelryCard&carte =  t->getCarteSansSupr(indice);


    // ici calculer bonus permet de retirer du cout total des cartes le bonus des cartes déjà possédées.
    int cout_blanc = positiveOrNull(carte.getCostWhite() - calculateBonus(colorBonus::blanc));
    int cout_bleu = positiveOrNull(carte.getCostBlue() - calculateBonus(colorBonus::bleu));
    int cout_rouge = positiveOrNull(carte.getCostRed() - calculateBonus(colorBonus::red));
    int cout_vert = positiveOrNull(carte.getCostGreen() - calculateBonus(colorBonus::vert));
    int cout_noir = positiveOrNull(carte.getCostBlack() - calculateBonus(colorBonus::noir));
    int cout_perle = carte.getCostPerl();

    // Vérifier si le joueur veut utiliser des jetons en or (s'il en possède)
    // Et diminuer le coût respectivement
    int nb_gold = 0;
    if (nbJeton(Color::gold) > 0) {
        std::cout << "Voulez-vous utiliser un(des) jeton(s) or? [Y/N]" << std::endl;
        std::string choix;
        std::cin >> choix;
        int nb;
        if (choix == "Y") {
            while (nbJeton(Color::gold) > 0) {
                //choix de la couleur
                std::cout << "Couleur remplacée? Stop pour arrêter d'utiliser des jetons or:" << std::endl;
                std::cin >> choix;
                if (choix == "stop" || "Stop") {
                    break;
                }
                do {
                    //choix du nombre de jetons or utilisé pour la couleur en question
                    std::cout << "Nombre?" << std::endl;
                    std::cin >> nb;
                } while (nb > nbJeton(Color::gold));
                try{
                    if ((choix == "blanc" || "Blanc") && (nb>cout_blanc)) throw SplendorException("Le cout blanc est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "bleu" || "Bleu") && (nb>cout_bleu)) throw SplendorException("Le cout bleu est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "rouge" || "Rouge") && (nb>cout_rouge)) throw SplendorException("Le cout rouge est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "vert" || "Vert") && (nb>cout_vert)) throw SplendorException("Le cout vert est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "noir" || "Noir") && (nb>cout_noir)) throw SplendorException("Le cout noir est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "perle" || "Perle") && (nb>cout_blanc)) throw SplendorException("Le cout perle est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if (choix != "blanc" || "Blanc" || "bleu" || "Bleu" || "rouge" || "Rouge" || "vert" || "Vert" || "noir" || "Noir" || "perle" || "Perle") throw SplendorException("Couleur de jeton inconnue!");

                    // Si on a passé tous ces tests on peut utiliser les jetons or
                    nb_gold+=nb;
                    if (choix == "blanc" || "Blanc") cout_blanc = positiveOrNull(cout_blanc - nb);
                    if (choix == "bleu" || "Bleu") cout_bleu = positiveOrNull(cout_bleu - nb);
                    if (choix == "rouge" || "Rouge") cout_rouge = positiveOrNull(cout_rouge - nb);
                    if (choix == "vert" || "Vert") cout_vert = positiveOrNull(cout_vert - nb);
                    if (choix == "noir" || "Noir") cout_noir = positiveOrNull(cout_noir - nb);
                    if (choix == "perle" || "Perle") cout_perle = positiveOrNull(cout_perle - nb);
                }catch(SplendorException e){
                    cout<<e.getInfos()<<endl;
                }
            }
        }
    }
    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir &&
        nbJeton(Color::perle) >= cout_perle){ eligible_achat = 1;}

    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);
    withdrawJetons(Color::perle, cout_perle);
    withdrawJetons(Color::gold, nb_gold);

    // Mettre la carte dans la main du joueur et la supprimer du tirage
    cartes_joaillerie_achetees.push_back(&(t->getCarte(indice)));
    t->remplirTirage();



    // Rajouter le nb de couronnes
    nb_courones += carte.getNbCrown();
    nb_points += carte.getPrestige();
    nb_cartes_j++;
    // Dans le main tester si eligible pour carte royale et appeler get carte royale

}

void Joueur::buyCardFromReserve( const int indice){
    if(cartes_joaiellerie_reservees.size() == 0 || indice>3) {
        throw SplendorException("Pas de cartes réservées");
    }

    // on doit vérifier que l'achat peut se faire

    const JewelryCard* carte = cartes_joaiellerie_reservees[indice];

    int cout_blanc = positiveOrNull(carte->getCostWhite() - calculateBonus(colorBonus::blanc));
    int cout_bleu = positiveOrNull(carte->getCostBlue() - calculateBonus(colorBonus::bleu));
    int cout_rouge = positiveOrNull(carte->getCostRed() - calculateBonus(colorBonus::red));
    int cout_vert = positiveOrNull(carte->getCostGreen() - calculateBonus(colorBonus::vert));
    int cout_noir = positiveOrNull(carte->getCostBlack() - calculateBonus(colorBonus::noir));
    int cout_perle = carte->getCostPerl();

    int nb_gold = 0;
    if (nbJeton(Color::gold) > 0) {
        std::cout << "Voulez-vous utiliser un(des) jeton(s) or? [Y/N]" << std::endl;
        std::string choix;
        std::cin >> choix;
        int nb;
        if (choix == "Y") {
            while (nbJeton(Color::gold) > 0){
                //choix de la couleur
                std::cout << "Couleur remplacée? Stop pour arrêter d'utiliser des jetons or:" << std::endl;
                std::cin >> choix;
                if(choix == "stop"||"Stop"){
                    break;
                }
                do {
                    //choix du nombre de jetons or utilisé pour la couleur en question
                    std::cout << "Nombre?" << std::endl;
                    std::cin >> nb;
                } while (nb > nbJeton(Color::gold));
                try{
                    if ((choix == "blanc" || "Blanc") && (nb>cout_blanc)) throw SplendorException("Le cout blanc est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "bleu" || "Bleu") && (nb>cout_bleu)) throw SplendorException("Le cout bleu est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "rouge" || "Rouge") && (nb>cout_rouge)) throw SplendorException("Le cout rouge est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "vert" || "Vert") && (nb>cout_vert)) throw SplendorException("Le cout vert est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "noir" || "Noir") && (nb>cout_noir)) throw SplendorException("Le cout noir est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if ((choix == "perle" || "Perle") && (nb>cout_blanc)) throw SplendorException("Le cout perle est inférieur au nombre de jetons or que vous souhaitez utiliser en tant que joker!");
                    if (choix != "blanc" || "Blanc" || "bleu" || "Bleu" || "rouge" || "Rouge" || "vert" || "Vert" || "noir" || "Noir" || "perle" || "Perle") throw SplendorException("Couleur de jeton inconnue!");

                    // Si on a passé tous ces tests, on peut utiliser les jetons or
                    nb_gold+=nb;
                    if (choix == "blanc" || "Blanc") cout_blanc = positiveOrNull(cout_blanc - nb);
                    if (choix == "bleu" || "Bleu") cout_bleu = positiveOrNull(cout_bleu - nb);
                    if (choix == "rouge" || "Rouge") cout_rouge = positiveOrNull(cout_rouge - nb);
                    if (choix == "vert" || "Vert") cout_vert = positiveOrNull(cout_vert - nb);
                    if (choix == "noir" || "Noir") cout_noir = positiveOrNull(cout_noir - nb);
                    if (choix == "perle" || "Perle") cout_perle = positiveOrNull(cout_perle - nb);
                }catch(SplendorException e){
                    cout<<e.getInfos()<<endl;
                }
            }
        }
    }


    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir &&
        nbJeton(Color::perle) >= cout_perle){ eligible_achat = 1;}


    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);
    withdrawJetons(Color::perle, cout_perle);
    withdrawJetons(Color::gold, nb_gold);



    cartes_joaiellerie_reservees.erase(cartes_joaiellerie_reservees.begin()+indice);
    nb_cartes_j_reservees--;
    cartes_joaillerie_achetees.push_back(carte);
    nb_cartes_j++;
    nb_courones += carte->getNbCrown();
    nb_points += carte->getPrestige();

}

void Joueur::selectionRoyalCard(){
    cout<<"Votre nombre de couronne vous donne le droit de piocher une carte royale!"<<endl;
    Jeu::getJeu().printCarteRoyale();
    int tmp;
    bool choix_ok = 0;
    while(!choix_ok) {
        cout << "Veuillez entrer l'indice de la carte royale que vous souhaitez prendre:" << endl;
        cout << "choix: ";
        cin >> tmp;
        if (tmp >= 0 and tmp < Jeu::getJeu().getCartesRoyales().size()) {
            string validate;
            cout<<"Valider ? [Y/N] :"<<endl;
            cout<<"choix : ";
            cin>>validate;
            if(validate=="Y"){
                choix_ok = 1; // on peut sortir de la boucle
            }
        }
        else{
            cout<<"Indice de carte invalide!"<<endl;
        }

    }
    obtainRoyaleCard(tmp);
}

void Joueur::verifJetons(){
    if(nb_jetons>10){
        int nb = nb_jetons-10;
        cout<<"Vous avez trop de jetons, vous devez en remettre "<<nb<<" dans le sac."<<endl;
        cout<<"Voici vos jetons:"<<endl;
        for(int i = 0; i<nb_jetons; i++){
            cout<<"Indice "<<i<<" : "<<*jetons[i]<<endl;
        }
        vector<int> tab(0);
        int i = 0;
        int curNb = nb;
        while(curNb>0){
            int tmp;
            cout<<"Indice du jeton "<<i++<<" :"<<endl;
            cout<<"Choix : ";
            cin>>tmp;
            bool inTab = 0;
            for(int j = 0 ; j<tab.size(); j++){ // vérification qu'on a pas déjà essayé de l'enlever
                if(tab[j]==tmp){
                    inTab = 1;
                }
            }
            if(tmp>=0 and tmp < nb_jetons and inTab == false){
                tab.push_back(tmp);
                curNb--;
            }
        }
        // tri du tableau
        std::make_heap(tab.begin(), tab.end());
        std::sort_heap(tab.begin(), tab.end());
        for(int k = tab.size()-1; k>=0; k--){ // suppression de la fin vers le début pour ne pas décaler les indices
            Sac::get_sac().mettre_jeton_sac(jetons[tab[k]]);
            jetons.erase(jetons.begin()+tab[k]);
            nb_jetons--;
        }
    }
}
/******************** Joueur ********************/

/******************** IA ********************/

IA::IA(const string & nom) : Strategy_player(nom){}

IA::~IA(){
    // Déstruction cartes royales
    for (auto cartes_royale : cartes_royale){
        delete cartes_royale;
    }
    cartes_royale.clear();

    // Déstruction privilèges
    for (auto privilege : privileges){
        delete privilege;
    }
    privileges.clear();
}

// Méthodes polymorphiques adaptées pour une IA

void IA::choice() {
    cout<<"choix IA:"<<endl;
    bool fin_choix = 0;
    int nb_choice = 0;
    while (!fin_choix) {
        try {
            int i = 0;
            nb_choice = getOptionalChoices(); // bien vérifier la convention sur le retour dans la définition de la méthode
            i += nb_choice+2;
            int tmp = rand()%i +1 ;

            if (tmp < 1 or tmp > i+1) {
                throw SplendorException(
                        "Il n'y a que" + to_string(i) + " choix! Vous ne pouvez pas choisir autre chose!\n");
            }
            switch (nb_choice) { // l'affichage et donc le choix dépend de la valeur de retour des choix optionnels
                case (0): { // aucun choix optionnel possible
                    switch (tmp) {
                        case 1: {
                            cout<<"L'IA sélectionne des jetons!"<<endl;
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 2: {
                            cout<<"L'IA achète des cartes!"<<endl;
                            achat_carte();
                            fin_choix = 1;

                            break;
                        }
//                        case 3: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default: // on continue jusqu'à ce que l'utilisateur choisisse une entrée valide!
                            break;
                    }
                    break;
                }
                case (1): { // seulement possible d'utiliser un privilège
                    switch (tmp) {
                        case 1: {
                            cout<<"L'IA utilise un privilège!"<<endl;
                            utilisationPrivilege();
                            break;
                        }
                        case 2: {
                            cout<<"L'IA sélectionne des jetons!"<<endl;
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 3: {
                            cout<<"L'IA achète des cartes!"<<endl;
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 4: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }
                case (2): { // seulement possible de remplir le plateau
                    switch (tmp) {
                        case 1: { // remplissage plateau
                            cout<<"L'IA remplie le plateau!"<<endl;
                            remplissagePlateau();
                            break;
                        }
                        case 2: {
                            cout<<"L'IA sélectionne des jetons!"<<endl;
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 3: {
                            cout<<"L'IA achète des cartes!"<<endl;
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 4: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }
                case (3): { // deux choix optionnels possibles
                    switch (tmp) {
                        case 1: {
                            cout<<"L'IA utilise un privilège!"<<endl;
                            utilisationPrivilege();
                            break;
                        }
                        case 2: { // remplissage plateau
                            cout<<"L'IA remplie le plateau!"<<endl;
                            remplissagePlateau();
                            break;
                        }
                        case 3: {
                            cout<<"L'IA sélectionne des jetons!"<<endl;
                            selection_jetons();
                            fin_choix = 1;
                            break;
                        }
                        case 4: {
                            cout<<"L'IA achète des cartes!"<<endl;
                            achat_carte();
                            fin_choix = 1;
                            break;
                        }
//                        case 5: {
//                            // affichage des jetons du jouer !
//                            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
//                            // afficher pour chaque type
//                            break;
//                        }
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }

        } catch (SplendorException &e) {
            cout << e.getInfos() << "\n";
        }
    }
}

void IA::utilisationPrivilege() {
    if (nb_privileges<=0)
        throw SplendorException("Vous n'avez pas de privilège!");
    unsigned int indice = rand()%Jeton::getNbMaxJetons();
    Jeu::getJeu().get_tour().piocher_jeton(indice);
    retirerPrivilege();
}

void IA::selection_jetons(){
    bool nb_ok=0;
    bool choix_ok = 0;

    if(Plateau::get_plateau().onlyGold() and Jeu::getJeu().get_tour().getNbCartesReservees() >= 3)
        throw SplendorException("Pas possible de piocher: il ne reste que des jetons or et vous ne pouvez plus réserver de carte!");
    if(Plateau::get_plateau().getCurrentNb() == 0)
        throw SplendorException("Plateau vide!");
    while(!choix_ok){
        try{
            std::vector<int> tmp_tab(0);
            optional<Position> pos = nullopt;
            int nb_or = 0;
            int nb_perle = 0;
            string validation;
            while(tmp_tab.size()<3) {
                unsigned int indice;
                indice = rand()%Jeton::getNbMaxJetons();


                if (tmp_tab.size()>0){ // actif que après le 1e choix
                    if(rand()%2==0){
                        break;
                    }
                }
                if (Plateau::get_plateau().get_plateau_i(indice) ==nullptr) {//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                    nb_or = 0;
                    nb_perle = 0;
                    tmp_tab.clear();

                    throw SplendorException("Il n'y a pas de jeton à cet indice!\n");
                }
                if (indice >Jeton::getNbMaxJetons()) {//le nombre de cases sur le plateau correspond au nombre de jetons dans le jeu
                    nb_or = 0;
                    nb_perle = 0;
                    tmp_tab.clear();
                    throw SplendorException("Il n'y a que " + std::to_string(Jeton::getNbMaxJetons()) + " places sur le plateau\n");
                }
                if (Plateau::get_plateau().get_plateau_i(indice)->getColor() == Color::gold) {
                    nb_or++;
                }
                if (Plateau::get_plateau().get_plateau_i(indice)->getColor() == Color::perle) {
                    nb_perle++;
                }
                if ((nb_or == 1) && (Jeu::getJeu().get_tour().getNbCartesReservees() >= 3)) {
                    nb_or = 0;
                    nb_perle = 0;
                    tmp_tab.clear();
                    throw SplendorException("Vous n'avez pas le droit de réserver une carte supplémentaire!");
                }
                if (nb_or == 1 and tmp_tab.size() > 1) {
                    nb_or = 0;
                    nb_perle = 0;
                    tmp_tab.clear();
                    throw SplendorException("Attention, on ne peut prendre un jeton or seulement tout seul!");
                }
                tmp_tab.push_back(indice);
            }

            //tri du vecteur par selection
            int min = 0;
            for (int j = 0; j < tmp_tab.size() - 1; j++) {
                min = j;
                for (int k = j + 1; k < tmp_tab.size(); k++) {
                    if (tmp_tab[k] < tmp_tab[min]) {
                        min = k;
                    }
                }
                if (min != j) {
                    int tmp2 = tmp_tab[min];
                    tmp_tab[min] = tmp_tab[j];
                    tmp_tab[j] = tmp2;
                }
            }
            // vecteur trié
            // cout<<"vecteur trié\n";


            if (tmp_tab.size() == 2) { // vérification de l'alignement pour 2 jetons
                //cout<<"vérification pour 2 jetons\n";
                const Jeton *jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[0]);
                optional<Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1], jet1);
                if (pos1 == nullopt) {
                    throw SplendorException("Jetons non-alignés\n");
                }
            }
            if (tmp_tab.size() == 3) { // vérification de l'alignement pour 3 jetons
                //cout<<"vérification pour 3 jetons\n";
                const Jeton *jet1 = Plateau::get_plateau().get_plateau_i(tmp_tab[1]);
                optional<Position> pos1 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[0], jet1);

                const Jeton *jet2 = Plateau::get_plateau().get_plateau_i(tmp_tab[2]);
                optional<Position> pos2 = Plateau::get_plateau().jeton_i_est_a_cote(tmp_tab[1], jet2);

                if ((pos1 != pos2) || (pos1 == nullopt) || (pos2 == nullopt)) {
                    throw SplendorException("Jetons non-alignés\n");
                }
            }

            // on a vérifié l'alignement des jetons
            if(nb_perle == 2){ // obtention d'un privilège par l'adversaire si on pioche les 2 jetons perles en une fois
                Jeu::getJeu().getOpponent().obtainPrivilege();
            }

            if(tmp_tab.size()==3){// obtention d'un privilège par l'adversaire si les 3 jetons sont de la même couleur
                if((Plateau::get_plateau().get_plateau_i(tmp_tab[0])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor())
                   &&(Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[2])->getColor())){
                    Jeu::getJeu().getOpponent().obtainPrivilege();
                }
            }
            for(int i = 0; i<tmp_tab.size();i++){ // acquisition des jetons par le joueur
                Jeu::getJeu().getCurrentPlayer().piocher_jeton(tmp_tab[i]);
            }
            if(nb_or==1){
                reservation_carte();
            }
            choix_ok = 1;
        }catch(SplendorException& e){
            cout<<e.getInfos()<<"\n";
        }
    }
}

void IA::reservation_carte(){
    if(rand()%2 == 0){ // réservation sur un tirage
        int tirage = rand()%Pioche::getNbPioches() + 1; // on suppose que le nombre de pioche est égal au nombre de tirage (entre 1 et 3)
        switch (tirage) {
            case 1: {
                unsigned int indice = rand()%Jeu::getJeu().get_tirage_1()->getNbCartes();
                reserver_carte(Jeu::getJeu().get_tirage_1(), indice);
                break;
            }
            case 2: {
                unsigned int indice = rand()%Jeu::getJeu().get_tirage_2()->getNbCartes();
                reserver_carte(Jeu::getJeu().get_tirage_2(), indice);
                break;
            }
            case 3: {
                unsigned int indice = rand()%Jeu::getJeu().get_tirage_3()->getNbCartes();
                reserver_carte(Jeu::getJeu().get_tirage_3(), indice);
                break;
            }
        }
    }else{ // on reserve sur une pioche
        int pioche = rand()%Pioche::getNbPioches() + 1; // entre 1 et 3
        reserver_carte(Jeu::getJeu().getPioche(pioche));
    }
    for(auto c : Jeu::getJeu().getCurrentPlayer().getCartesReserved()){
        cout<<*c<<endl;
    }

}

void IA::achat_carte(){
    unsigned int choice = -1;
    if(Jeu::getJeu().getCurrentPlayer().getNbCartesReservees()>0){ // si le joueur a des cartes reservées
        choice = rand()%2;
        if(choice==1){//achat d'une carte qu'il a reservé
            cout<<"\nAchat d'une carte reservée!"<<endl;
            int nb_carte_reservee= Jeu::getJeu().getCurrentPlayer().getCartesReserved().size();
            unsigned int indice = rand()%nb_carte_reservee;
            Jeu::getJeu().getCurrentPlayer().buyCardFromReserve(indice);
        }else{
            cout<<"\nAchat d'une carte sur un tirage!"<<endl;
            int tirage = (rand()%Pioche::getNbPioches()) + 1; // entre 1 et 3
            switch (tirage) {
                case 1:{
                    cout<<"Achat d'une carte du tirage 1."<<endl;
                    unsigned int nbCartesT1 = Jeu::getJeu().get_tirage_1()->getNbCartes();
                    if(nbCartesT1 == 0) throw SplendorException("Plus de carte dans le Tirage 1");
                    unsigned int indice = rand()%nbCartesT1;
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_1(), indice);
                    break;
                }case 2:{
                    cout<<"Achat d'une carte du tirage 2."<<endl;
                    unsigned int nbCartesT2 = Jeu::getJeu().get_tirage_2()->getNbCartes();
                    if(nbCartesT2 == 0) throw SplendorException("Plus de carte dans le Tirage 2");
                    unsigned int indice = rand()%nbCartesT2;
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_2(), indice);
                    break;
                }
                case 3:{
                    cout<<"Achat d'une carte du tirage 3."<<endl;
                    unsigned int nbCartesT3 = Jeu::getJeu().get_tirage_3()->getNbCartes();
                    if(nbCartesT3== 0) throw SplendorException("Plus de carte dans le Tirage 3");
                    unsigned int indice = rand()%nbCartesT3;
                    Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_3(), indice);
                    break;
                }
            }
        }
    }else{ // si on ne peut que acheter
        cout<<"\nAchat d'une carte sur un tirage!"<<endl;
        int tirage = (rand()%Pioche::getNbPioches()) + 1;// entre 1 et 3
        switch (tirage) {
            case 1: {
                cout<<"Achat d'une carte du tirage 1."<<endl;
                unsigned int nbCartesT1 = Jeu::getJeu().get_tirage_1()->getNbCartes();
                if(nbCartesT1 == 0) throw SplendorException("Plus de carte dans le Tirage 1");
                unsigned int indice = rand()%nbCartesT1;
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_1(), indice);
                break;
            }
            case 2: {
                cout<<"Achat d'une carte du tirage 2."<<endl;
                unsigned int nbCartesT2 = Jeu::getJeu().get_tirage_2()->getNbCartes();
                if(nbCartesT2 == 0) throw SplendorException("Plus de carte dans le Tirage 2");
                unsigned int indice = rand()%nbCartesT2;
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_2(), indice);
                break;
            }
            case 3: {
                cout<<"Achat d'une carte du tirage 3."<<endl;
                unsigned int nbCartesT3 = Jeu::getJeu().get_tirage_3()->getNbCartes();
                if(nbCartesT3== 0) throw SplendorException("Plus de carte de le Tirage 3");
                unsigned int indice = rand()%nbCartesT3;
                Jeu::getJeu().getCurrentPlayer().buyCard(Jeu::getJeu().get_tirage_3(), indice);
                break;
            }
        }
    }
}

void IA::buyCard(Tirage *t, const int indice){
    const JewelryCard& carte =  t->getCarteSansSupr(indice);


    // ici calculer bonus permet de retirer du cout total des cartes le bonus des cartes déjà possédées.
    int cout_blanc = positiveOrNull(carte.getCostWhite() - calculateBonus(colorBonus::blanc));
    int cout_bleu = positiveOrNull(carte.getCostBlue() - calculateBonus(colorBonus::bleu));
    int cout_rouge = positiveOrNull(carte.getCostRed() - calculateBonus(colorBonus::red));
    int cout_vert = positiveOrNull(carte.getCostGreen() - calculateBonus(colorBonus::vert));
    int cout_noir = positiveOrNull(carte.getCostBlack() - calculateBonus(colorBonus::noir));
    int cout_perle = carte.getCostPerl();


    // Vérifier si le joueur veut utiliser des jetons en or (s'il en possède)
    // Et diminuer le coût respectivement
    int nb_gold = 0;
    if (nbJeton(Color::gold) > 0) {
        while (nbJeton(Color::gold) > 0 and rand()%2 == 1) { // rand pour arret aléatoire entre les choix (possibilité de ne pas utiliser tous les jetons)
            //choix de la couleur
            if (rand()%2 == 1) { // on arrête la
                break;
            }

            //choix du nombre de jetons or utilisé pour la couleur en question
            int nb = rand()%nbJeton(Color::gold);

            int choix = rand()%6;
            if (choix == 0 and cout_blanc>=nb) cout_blanc -= nb; nb_gold+=nb;
            if (choix == 1 and cout_bleu>=nb) cout_bleu -= nb; nb_gold+=nb;
            if (choix == 2 and cout_rouge>=nb) cout_rouge -= nb; nb_gold+=nb;
            if (choix == 3 and cout_vert>=nb) cout_vert -= nb; nb_gold+=nb;
            if (choix == 4 and cout_noir>=nb) cout_noir -= nb; nb_gold+=nb;
            if (choix == 5 and cout_perle>=nb) cout_perle -= nb; nb_gold+=nb;
            // si pas de bon choix par rapport au cout, l'ia recommence
        }
    }
    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir &&
        nbJeton(Color::perle) >= cout_perle){ eligible_achat = 1;}

    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);
    withdrawJetons(Color::perle, cout_perle);
    withdrawJetons(Color::gold, nb_gold);

    // Mettre la carte dans la main du joueur et la supprimer du tirage
    cartes_joaillerie_achetees.push_back(&(t->getCarte(indice)));
    t->remplirTirage();


    // Rajouter le nb de couronnes
    nb_courones += carte.getNbCrown();
    nb_cartes_j++;
    nb_points += carte.getPrestige();
    // Dans le main tester si eligible pour carte royale et appeler get carte royale

}

void IA::buyCardFromReserve(const int indice) {
    if(cartes_joaiellerie_reservees.size() == 0 || indice>3) {
        throw SplendorException("Pas de cartes réservées");
    }

    // on doit vérifier que l'achat peut se faire

    const JewelryCard* carte = cartes_joaiellerie_reservees[indice];

    int cout_blanc = positiveOrNull(carte->getCostWhite() - calculateBonus(colorBonus::blanc));
    int cout_bleu = positiveOrNull(carte->getCostBlue() - calculateBonus(colorBonus::bleu));
    int cout_rouge = positiveOrNull(carte->getCostRed() - calculateBonus(colorBonus::red));
    int cout_vert = positiveOrNull(carte->getCostGreen() - calculateBonus(colorBonus::vert));
    int cout_noir = positiveOrNull(carte->getCostBlack() - calculateBonus(colorBonus::noir));
    int cout_perle = carte->getCostPerl();

    int nb_gold = 0;
    if (nbJeton(Color::gold) > 0) {
        while (nbJeton(Color::gold) > 0 and rand()%2 == 1) { // rand pour arret aléatoire entre les choix (possibilité de ne pas utiliser tous les jetons)
            //choix de la couleur
            if (rand()%2 == 1) { // on arrête la
                break;
            }

            //choix du nombre de jetons or utilisé pour la couleur en question
            int nb = rand()%nbJeton(Color::gold);

            int choix = rand()%6;
            if (choix == 0 and cout_blanc>=nb) cout_blanc -= nb; nb_gold+=nb;
            if (choix == 1 and cout_bleu>=nb) cout_bleu -= nb; nb_gold+=nb;
            if (choix == 2 and cout_rouge>=nb) cout_rouge -= nb; nb_gold+=nb;
            if (choix == 3 and cout_vert>=nb) cout_vert -= nb; nb_gold+=nb;
            if (choix == 4 and cout_noir>=nb) cout_noir -= nb; nb_gold+=nb;
            if (choix == 5 and cout_perle>=nb) cout_perle -= nb; nb_gold+=nb;
            // si pas de bon choix par rapport au cout, l'ia recommence
        }
    }


    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir &&
        nbJeton(Color::perle) >= cout_perle){ eligible_achat = 1;}


    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);
    withdrawJetons(Color::perle, cout_perle);
    withdrawJetons(Color::gold, nb_gold);



    cartes_joaiellerie_reservees.erase(cartes_joaiellerie_reservees.begin()+indice);
    nb_cartes_j_reservees--;
    cartes_joaillerie_achetees.push_back(carte);
    nb_cartes_j++;
    nb_points += carte->getPrestige();
    this->nb_courones += carte->getNbCrown();

}

void IA::selectionRoyalCard(){
    int nb_carte_r_dans_jeu = Jeu::getJeu().getCartesRoyales().size();
    int tmp = rand()%nb_carte_r_dans_jeu;
    obtainRoyaleCard(tmp);
}

void IA::verifJetons(){
    if(nb_jetons>10){
        int nb = nb_jetons-10;
        cout<<"L'IA a trop de jetons, elle doit en remettre "<<nb<<" dans le sac."<<endl;
        cout<<"Voici ses jetons:"<<endl;
        for(int i = 0; i<nb_jetons; i++){
            cout<<"Indice "<<i<<" : "<<*jetons[i]<<endl;
        }
        vector<int> tab(0);
        int i = 0;
        int curNb = nb;
        while(curNb>0){
            int tmp = rand()%nb_jetons;
            cout<<tmp<<endl;
            bool inTab = 0;
            for(int j = 0 ; j<tab.size(); j++){ // vérification qu'on a pas déjà essayé de l'enlever
                if(tab[j]==tmp){
                    inTab = 1;
                    cout<<"Déjà dans tab"<<endl;
                }
            }
            if(tmp>=0 and tmp < nb_jetons and inTab == 0){
                tab.push_back(tmp);
                curNb--;
            }
        }
        // tri du tableau
        std::make_heap(tab.begin(), tab.end());
        std::sort_heap(tab.begin(), tab.end());
        for(int k = tab.size()-1; k>=0; k--){ // suppression de la fin vers le début pour ne pas décaler les indices
            Sac::get_sac().mettre_jeton_sac(jetons[tab[k]]);
            jetons.erase(jetons.begin()+tab[k]);
            nb_jetons--;
        }

    }
}

/******************** IA ********************/