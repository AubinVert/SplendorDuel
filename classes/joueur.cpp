#include "joueur.h"
#include "Exception.h"
#include "jeu.h"

// Au début le joueur n'a aucune carte ou jeton
Joueur::Joueur(const string &nom) : nb_points(0), nb_cartes_j(0), nb_cartes_r(0), nb_courones(0), nb_privileges(0),
                              nom(nom), nb_jetons(0)
                              {}

Joueur::~Joueur() = default;



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


void Joueur::buyCard(Tirage *t, const int indice){

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

int positiveOrNull(int x) {
    if (x < 0) return 0;
    return x;
}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Joueur::calculateBonus(enum colorBonus bonus) {
    int res = 0;
    // débug ton code engulé
    //cout<<cartes_joaillerie_achetees.size()<<endl;
    for (auto c = cartes_joaillerie_achetees.begin(); c != cartes_joaillerie_achetees.end(); ++c){
        if (bonus == (*c)->getBonus()) res++;
    }
    return res;
}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Joueur::nbJeton(const Color& couleur) const {
    int res = 0;
    for (auto j = jetons.begin(); j != jetons.end(); ++j){
        if ((*j)->getColor() == couleur) res++;
    }
    return res;
}

// Supprimer val jetons de la main du joueur et remettre dans le sac
void Joueur::withdrawJetons(const Color& c, int val) {
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

void Joueur::reserver_carte(Tirage *t, const int indice) { // pourquoi un pointeur de jetons ? il faut juste que le jeton soit stockée dedans

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

void Joueur::piocher_jeton( int i) {
    //cout<<"mabite"<<i<<endl;

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

void Joueur::obtainRoyaleCard(unsigned int i) {
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

bool Joueur::royaleCardEligibility() {
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

void Joueur::obtainPrivilege() {
    // on va chercher dans le tirage des privilège un privilège. (du plateau ou alors de ton adversaire ? )
    // d'abord je regarde s'il y a des privilèges dans le jeu :

    if(Jeu::getJeu().getNbPrivilege() <= 0){
        throw SplendorException("Plus de privilèges disponibles");
    }
    privileges.push_back(&Jeu::getJeu().getPrivilege());

    nb_privileges++;
}


void Joueur::retirerPrivilege(){
    if(nb_privileges==0){
        throw SplendorException("Vous ne pouvez pas retirer de privilège au joueur");
    }
    Jeu::getJeu().setPrivilege(*privileges[0]);
    privileges.erase(privileges.begin());
}


void testJoueurs(){

    Jeu::getJeu();

    Joueur j("pd");


    for (int i = 1; i < 20; ++i) {
        j.piocher_jeton(i);
    }

    j.obtainRoyaleCard(1);
    j.obtainPrivilege();
    Tirage* tmp = Jeu::getJeu().get_tirage_1();
    j.reserver_carte(tmp, 1);


    const JewelryCard cartej = Jeu::getJeu().get_tirage_1()->getCarte(1);



    cout<<j<<endl;
}