#include "joueur.h"
#include "Exception.h"
#include "jeu.h"

// Au début le joueur n'a aucune carte ou jeton
Joueur::Joueur(const string &nom) : nb_points(0), nb_cartes_j(0), nb_cartes_r(0), nb_courones(0), nb_privileges(0),
                              nom(nom), nb_jetons(0)
                              {}

Joueur::~Joueur() = default;


void Joueur::acheter_carte(const Carte_joaillerie& carte){




    // ici calculer bonus permet de retirer du cout total des cartes le bonus des cartes déjà possédées.



    int cout_blanc = positif_ou_nul(carte.getCoutBlanc() - calculer_bonus(Bonus_couleur::blanc));
    int cout_bleu = positif_ou_nul(carte.getCoutBleu() - calculer_bonus(Bonus_couleur::bleu));
    int cout_rouge = positif_ou_nul(carte.getCoutRouge() - calculer_bonus(Bonus_couleur::rouge));
    int cout_vert = positif_ou_nul(carte.getCoutVert() - calculer_bonus(Bonus_couleur::vert));
    int cout_noir = positif_ou_nul(carte.getCoutNoir() - calculer_bonus(Bonus_couleur::noir));

    // Vérifier si le joueur veut utiliser des jetons en or (s'il en possède)
    // Et diminuer le coût respectivement



    if (nb_jeton(Couleur::gold) != 0) {
        std::cout << "Voulez-vous utiliser des jetons or? (oui/non)" << std::endl;
        std::string choix;
        std::cin >> choix;
        int nb;
        if (choix == "oui") {
            while (nb_jeton(Couleur::gold) != 0){
                std::cout << "Couleur remplacée?" << std::endl;
                std::cin >> choix;
                do {
                    std::cout << "Nombre?" << std::endl;
                    std::cin >> nb;
                } while (nb > nb_jeton(Couleur::gold));
                retirer_jeton(Couleur::gold, nb_jeton(Couleur::gold) - nb); // Màj nombre jetons or
                if (choix == "blanc" || "Blanc") cout_blanc = positif_ou_nul(cout_blanc - nb);
                if (choix == "bleu"|| "Bleu") cout_bleu = positif_ou_nul(cout_bleu - nb);
                if (choix == "rouge"|| "Rouge") cout_rouge = positif_ou_nul(cout_rouge - nb);
                if (choix == "vert"|| "Vert") cout_vert = positif_ou_nul(cout_vert - nb);
                if (choix == "noir"|| "Noir") cout_noir = positif_ou_nul(cout_noir - nb);}
        }
    }



    // Vérifier si assez de jetons
    int eligible_achat = 0;

    // vérifier si on a le nombre de jetons pour acheter
    if (nb_jeton(Couleur::blanc) >= cout_blanc &&
        nb_jeton(Couleur::bleu) >= cout_bleu &&
        nb_jeton(Couleur::rouge) >= cout_rouge &&
        nb_jeton(Couleur::vert) >= cout_vert &&
        nb_jeton(Couleur::noir) >= cout_noir){eligible_achat = 1;}


    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons pour acheter la carte !");

    // Retirer les jetons utilisés et les mettre dans le sac
    retirer_jeton(Couleur::blanc, cout_blanc);
    retirer_jeton(Couleur::bleu, cout_bleu);
    retirer_jeton(Couleur::rouge, cout_rouge);
    retirer_jeton(Couleur::vert, cout_vert);
    retirer_jeton(Couleur::noir, cout_noir);

    // Mettre la carte dans la main du joueur
    cartes_joaillerie_achetees.push_back(&carte);


    // Vérifier si c'est une carte réservée




    int est_reservee = 0;

    for(int k=0;k< cartes_joaiellerie_reservees.size(); k++){
        if(cartes_joaiellerie_reservees[k] == &carte){
            est_reservee =1;
        }
    }

    if (est_reservee == 1){ // La retirer des cartes reservées
        for (auto it = cartes_joaiellerie_reservees.begin(); it != cartes_joaiellerie_reservees.end(); ++it) {
            if ((*it) == &carte) cartes_joaiellerie_reservees.erase(it);
        }
    }

    else { // La retirer du tirage et re piocher


        switch(carte.getNiveau()){

            case 1:

                cout<<Jeu::getJeu().get_tirage_1()->getTirage().size()<<endl;





                //Jeu::getJeu().get_tirage_1()->remplirTirage();

                break;
                /*
            case 2:
                for (auto it = Jeu::getJeu().get_tirage_2()->getTirage().begin(); it != Jeu::getJeu().get_tirage_2()->getTirage().end(); ++it){
                    //if ((*it) == &carte) Jeu::getJeu().get_tirage_2()->getCarte(*it - Jeu::getJeu().get_tirage_2()->getTirage().begin());
                }
                Jeu::getJeu().get_tirage_2()->remplirTirage();
                break;
            case 3:
                for (auto it = Jeu::getJeu().get_tirage_3()->getTirage().begin(); it != Jeu::getJeu().get_tirage_3()->getTirage().end(); ++it){
                   // if ((*it) == &carte) Jeu::getJeu().get_tirage_3()->getCarte(*it - Jeu::getJeu().get_tirage_3()->getTirage().begin());
                }
                Jeu::getJeu().get_tirage_3()->remplirTirage();
                break;*/

        }

    }

    // Rajouter le nb de couronnes
    this->nb_courones += carte.get_nb_couronnes();

    // Dans le main tester si eligible pour carte royale et appeler get carte royale

}


int positif_ou_nul(int x) {
    if (x < 0) return 0;
    return x;
}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Joueur::calculer_bonus(enum Bonus_couleur bonus) {
    int res = 0;
    // débug ton code engulé
    cout<<cartes_joaillerie_achetees.size()<<endl;
    for (auto c = cartes_joaillerie_achetees.begin(); c != cartes_joaillerie_achetees.end(); ++c){
        if (bonus == (*c)->get_bonus()) res++;
    }
    return res;
}

// Calculer le nb de jetons du joueur d'une couleur donnée
int Joueur::nb_jeton(const Couleur& couleur) const {
    int res = 0;
    for (auto j = jetons.begin(); j != jetons.end(); ++j){
        if ((*j)->get_couleur() == couleur) res++;
    }
    return res;
}

// Supprimer val jetons de la main du joueur et remettre dans le sac
void Joueur::retirer_jeton(const Couleur& c, int val) {
    int tmp = val;
        for(int k=0;k< jetons.size(); k++){
            if(jetons[k]->get_couleur() == c && tmp !=0){
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

void Joueur::reserver_carte(const Carte_joaillerie& carte, const Jeton* jet) { // pourquoi un pointeur de jetons ? il faut juste que le jeton soit stockée dedans

    // Vérifier que cela est suite à une acquisiton de jeton or

    if (jet->get_couleur() != Couleur::gold) throw SplendorException("Mauvaise couleur");
    cartes_joaiellerie_reservees.push_back(&carte);

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

}

void Joueur::piocher_jeton( int i) {

    if(i>25 || i<0){
        throw SplendorException("Indice du plateau non valide ! ");
    }
    const Jeton* tmp = Plateau::get_plateau().get_plateau_i(i);
    jetons.push_back(tmp);
    Plateau::get_plateau().set_plateau_i(i,nullptr);
    std::cout << "Jeton acquis." << std::endl;
    nb_jetons++;
}

void Joueur::obtenir_carte_royale(unsigned int i) {
    // on prend une carte dans le jeu
    if(i>Jeu::getJeu().getCartesRoyales().size()){
        throw SplendorException("Carte non disponible");
    }
    //if (eligible_carte_royale() == false) throw SplendorException("Pas eligible.");
    const Carte_royale tmp = Jeu::getJeu().pullCarteRoyale(i);
    cartes_royale.push_back(&tmp);
    // ENLEVER DU jeu
    nb_cartes_r++;
}

bool Joueur::eligible_carte_royale() {
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

void Joueur::obtenir_privilege() {
    // on va chercher dans le tirage des privilège un privilège. (du plateau ou alors de ton adversaire ? )
    // d'abord je regarde s'il y a des privilèges dans le jeu :

    if(Jeu::getJeu().getNbPrivilege() <= 0){
        throw SplendorException("Plus de privilèges disponibles");
    }
    privileges.push_back(&Jeu::getJeu().getPrivilege());

    nb_privileges++;
}


void testJoueurs(){

    Jeu::getJeu();

    Joueur j("pd");
    j.setPoints(3);
    j.setNbCouronnes(2);


    for (int i = 1; i < 20; ++i) {
        j.piocher_jeton(i);
    }

    j.obtenir_carte_royale(1);


    j.obtenir_privilege();


    //j.acheter_carte(*cartej);



    cout<<j<<endl;
}