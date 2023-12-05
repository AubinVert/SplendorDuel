#include "joueur.h"
/******************** Fonction utilitaires ********************/
int positiveOrNull(int x) {
    if (x < 0) return 0;
    return x;
}
/******************** Fonction utilitaires ********************/


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

void Strategy_player::buyCardFromReserve( const int indice){
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
    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir){ eligible_achat = 1;}


    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);


    cartes_joaiellerie_reservees.erase(cartes_joaiellerie_reservees.begin()+indice);
    cartes_joaillerie_achetees.push_back(carte);

    this->nb_courones += carte->getNbCrown();

}

void Strategy_player::buyCard(Tirage *t, const int indice){

    // la carte qu'il veut supp c'est la ième du tirage t

    const JewelryCard carte =  t->getCarte(indice);


    // ici calculer bonus permet de retirer du cout total des cartes le bonus des cartes déjà possédées.
    int cout_blanc = positiveOrNull(carte.getCostWhite() - calculateBonus(colorBonus::blanc));
    int cout_bleu = positiveOrNull(carte.getCostBlue() - calculateBonus(colorBonus::bleu));
    int cout_rouge = positiveOrNull(carte.getCostRed() - calculateBonus(colorBonus::red));
    int cout_vert = positiveOrNull(carte.getCostGreen() - calculateBonus(colorBonus::vert));
    int cout_noir = positiveOrNull(carte.getCostBlack() - calculateBonus(colorBonus::noir));

    // Vérifier si le joueur veut utiliser des jetons en or (s'il en possède)
    // Et diminuer le coût respectivement

    if (nbJeton(Color::gold) != 0) {
        std::cout << "Voulez-vous utiliser des jetons or? (oui/non)" << std::endl;
        std::string choix;
        std::cin >> choix;
        int nb;
        if (choix == "oui") {
            while (nbJeton(Color::gold) != 0){
                std::cout << "Color remplacée?" << std::endl;
                std::cin >> choix;
                do {
                    std::cout << "Nombre?" << std::endl;
                    std::cin >> nb;
                } while (nb > nbJeton(Color::gold));
                withdrawJetons(Color::gold, nbJeton(Color::gold) - nb); // Màj nombre jetons or
                if (choix == "blanc" || "Blanc") cout_blanc = positiveOrNull(cout_blanc - nb);
                if (choix == "bleu"|| "Bleu") cout_bleu = positiveOrNull(cout_bleu - nb);
                if (choix == "red"|| "Rouge") cout_rouge = positiveOrNull(cout_rouge - nb);
                if (choix == "vert"|| "Vert") cout_vert = positiveOrNull(cout_vert - nb);
                if (choix == "noir"|| "Noir") cout_noir = positiveOrNull(cout_noir - nb);}
        }
    }

    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nbJeton(Color::blanc) >= cout_blanc &&
        nbJeton(Color::bleu) >= cout_bleu &&
        nbJeton(Color::rouge) >= cout_rouge &&
        nbJeton(Color::vert) >= cout_vert &&
        nbJeton(Color::noir) >= cout_noir){ eligible_achat = 1;}
    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    withdrawJetons(Color::blanc, cout_blanc);
    withdrawJetons(Color::bleu, cout_bleu);
    withdrawJetons(Color::rouge, cout_rouge);
    withdrawJetons(Color::vert, cout_vert);
    withdrawJetons(Color::noir, cout_noir);

    // Mettre la carte dans la main du joueur
    cartes_joaillerie_achetees.push_back(&carte);

    // Vérifier si c'est une carte réservée


    // Rajouter le nb de couronnes
    this->nb_courones += carte.getNbCrown();

    // Dans le main tester si eligible pour carte royale et appeler get carte royale

}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Strategy_player::calculateBonus(enum colorBonus bonus) {
    int res = 0;
    //cout<<cartes_joaillerie_achetees.size()<<endl;
    for (auto c = cartes_joaillerie_achetees.begin(); c != cartes_joaillerie_achetees.end(); ++c){
        if (bonus == (*c)->getBonus()) res++;
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
    int tmp = val;
    for(int k=0;k< jetons.size(); k++){
        if(jetons[k]->getColor() == c && tmp != 0){
            Sac::get_sac().mettre_jeton_sac(jetons[k]);
            jetons.erase(jetons.begin() +k);
            tmp--;
            nb_jetons--;
        }
    }
    if(tmp > 0){
        throw SplendorException("Pas assez de jetons de cette couleur pour en supprimer plus ! ");
    }
}

void Strategy_player::reserver_carte(Tirage *t, const int indice) { // pourquoi un pointeur de jetons ? il faut juste que le jeton soit stockée dedans

    // Vérifier que la personne a un jeton or
    unsigned int count =0;
    for (int i = 0; i < jetons.size(); ++i) {
        if(jetons[i]->getColor() == Color::gold) count++;
    }
    if(count == 0){
        throw SplendorException("Mauvaise couleur");
    }
    const JewelryCard tmp =  t->getCarte(indice);
    // la fonction getCarte retire déjà la carte du tirage en question
    cartes_joaiellerie_reservees.push_back(&tmp);
    nb_cartes_j++;
    t->remplirTirage();


    /*
    // Retirer du tirage
    switch(carte.getNiveau()){
        case 1:
            for (auto it = Jeu::getJeu().get_tirage_1()->getTirage().begin(); it != Jeu::getJeu().get_tirage_1()->getTirage().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_1()->getTirage().erase(it);
            }
            Jeu::getJeu().get_tirage_1()->remplirTirage();
            break;
        case 2:
            for (auto it = Jeu::getJeu().get_tirage_2()->getTirage().begin(); it != Jeu::getJeu().get_tirage_2()->getTirage().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_2()->getTirage().erase(it);
            }
            Jeu::getJeu().get_tirage_2()->remplirTirage();
            break;
        case 3:
            for (auto it = Jeu::getJeu().get_tirage_3()->getTirage().begin(); it != Jeu::getJeu().get_tirage_3()->getTirage().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_3()->getTirage().erase(it);
            }
            Jeu::getJeu().get_tirage_3()->remplirTirage();
            break;
    }
    */

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
    std::cout << "Jeton acquis." << std::endl;
    nb_jetons++;

    Plateau::get_plateau().setCurrentNb(Plateau::get_plateau().getCurrentNb()-1);

}

void Strategy_player::obtainRoyaleCard(unsigned int i) {
    // on prend une carte dans le jeu
    if(i>Jeu::getJeu().getCartesRoyales().size()){
        throw SplendorException("Card non disponible");
    }
    //if (royaleCardEligibility() == false) throw SplendorException("Pas eligible.");
    const RoyalCard tmp = Jeu::getJeu().pullCarteRoyale(i);
    cartes_royale.push_back(&tmp);
    // ENLEVER DU jeu
    nb_cartes_r++;
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

    if(Jeu::getJeu().getNbPrivilege() <= 0){
        throw SplendorException("Plus de privilèges disponibles");
    }
    privileges.push_back(&Jeu::getJeu().getPrivilege());

    nb_privileges++;
}

void Strategy_player::retirerPrivilege(){
    if(nb_privileges==0){
        throw SplendorException("Vous ne pouvez pas retirer de privilège au joueur");
    }
    Jeu::getJeu().setPrivilege(*privileges[0]);
    privileges.erase(privileges.begin());
}

// méthode utilitaire pour le main
int Strategy_player::getOptionalChoices(){
    /***Convention***
    Cette méthode renvoie:
     - 1 si le joueur ou l'ia ne peut qu'utiliser un privilège,
     - 2 si le joueur ou l'ia ne peut que remplir le plateau,
     - 3 si le joueur ou l'ia peut faire les deux.
    ****************/
    int nb_choices = 0;
    if (Jeu::getJeu().getCurrentPlayer().getNbPrivileges() > 0){
        nb_choices++;
    }
    if (Plateau::get_plateau().getCurrentNb() < Jeton::getNbMaxJetons() && Sac::get_sac().get_nb_sac() > 0){
        nb_choices++;
        nb_choices++;
    }
    return nb_choices;
}

/******************** Strategy_player ********************/



/******************** Joueur ********************/

//constructeur et destructeur
Joueur::Joueur(const string & nom) : Strategy_player(nom){}

Joueur::~Joueur(){
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

// Méthodes polymorphiques
void Joueur::optional_choice(){
    bool finished = 0;
    while(!finished) {
        int nb_choice = getOptionalChoices(); // bien vérifier la convention sur le retour dans la définition de la méthode
        int i = 1;
        int tmp;
        cout<<"Actions optionnelles disponibles:"<<endl;
        if(nb_choice%2 == 1){
            cout<<"Utiliser un privilège->"<<i++<<endl;
        }
        if(nb_choice>=2){
            cout<<"Remplir le plateau ->"<<i++<<endl;
        }
        cout<<"Vous ne voulez pas effectuer d'action optionnelle -> "<<i++<<endl;
        cout<<"Votre choix: ";
        cin>>tmp;
        string validation;
        cout<<"Validez vous votre choix? [Y/N] "<<endl;
        cin>>validation;
        if(validation=="N"){
            tmp = 100; // on rentre dans le default sans pour autant finir la boucle => on recommence le choix optionnel
        }
        switch(tmp){
            case(1):{
                switch(nb_choice){
                    case(0):{ // si pas d'action optionnelle possible, l'entrée 1 pour tmp vaut forcément exit de optionnal choice
                        finished = 1;
                        break;
                    }
                    case(1):{ // utilisation privilège
                        Jeu::getJeu().get_tour().retirerPrivilege();
                        unsigned int indice;
                        cout<<"Quel jeton voulez-vous piocher ? "<<endl;
                        cout<<"indice : ";
                        cin>>indice;
                        Jeu::getJeu().get_tour().piocher_jeton(indice);
                        break;
                    }
                    case(2):{ // remplissage plateau
                        Jeu::getJeu().remplirPlateau();
                        Jeu::getJeu().getOpponent().obtainPrivilege();
                        break;
                    }
                    case(3):{ // utilisation privilège
                        Jeu::getJeu().get_tour().retirerPrivilege();
                        unsigned int indice;
                        cout<<"Quel jeton voulez-vous piocher ? "<<endl;
                        cout<<"indice : ";
                        cin>>indice;
                        Jeu::getJeu().get_tour().piocher_jeton(indice);
                        break;
                    }
                    default:{break;}
                }
                break;
            }
            case(2):{
                switch(nb_choice){
                    case(0):{ // tmp = 2 interdit => compte pour exit
                        finished = 1;
                        break;
                    }
                    case(1):{ // exit
                        finished = 1;
                        break;
                    }
                    case(2):{ // exit
                        finished = 1;
                        break;
                    }
                    case(3):{ // remplissage plateau
                        Jeu::getJeu().remplirPlateau();
                        Jeu::getJeu().getOpponent().obtainPrivilege();
                        break;
                    }
                    default:{break;}
                }
                break;
            }
            case(3):{
                switch(nb_choice){
                    case(0):{ // interdit => exit
                        finished = 1;
                        break;
                    }
                    case(1):{ // interdit => exit
                        finished = 1;
                        break;
                    }
                    case(2):{ // interdit => exit
                        finished = 1;
                        break;
                    }
                    case(3):{ // exit
                        finished = 1;
                        break;
                    }
                    default:{break;}
                }
                break;
            }
            default:{break;}
        }
    }
}

void Joueur::choice(){
    int tmp = 0;
    bool fin_choix = 0;
    while (!fin_choix){
        try{
            cout<<"Actions obligatoire:"<<endl;
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
            selection_jetons();
            break;
        }

        case 2:

            // On demande s'il veut acheter une carte qu'il a réservé ou non
        {
            achat_carte();
            break;
        }

        case 3:
        {
            // affichage des jetons du jouer !
            //cout<<"Inventaire du joueur : "<<Jeu::getJeu().getCurrentPlayer().getName()<<endl;
            // afficher pour chaque type

            break;
        }
        default:break;


    }
}

void Joueur::selection_jetons() {
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
                reservation_carte();
            }
            if(nb_perle == 2){ // obtention d'un privilège par l'adversaire si on pioche les 2 jetons perles en une fois
                Jeu::getJeu().getOpponent().obtainPrivilege();
            }

            if(nb==3){// obtention d'un privilège par l'adversaire si les 3 jetons sont de la même couleur
                if((Plateau::get_plateau().get_plateau_i(tmp_tab[0])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor())
                   &&(Plateau::get_plateau().get_plateau_i(tmp_tab[1])->getColor()==Plateau::get_plateau().get_plateau_i(tmp_tab[2])->getColor())){
                    Jeu::getJeu().getOpponent().obtainPrivilege();
                }
            }
            for(int i = 0; i<nb;i++){ // acquisition des jetons par le joueur
                Jeu::getJeu().getCurrentPlayer().piocher_jeton(tmp_tab[i]);
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


