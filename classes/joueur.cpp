#include "joueur.h"
#include "Exception.h"

// Au début le joueur n'a aucune carte ou jeton
Joueur::Joueur(string &nom) : nb_points(0), nb_cartes_j(0), nb_cartes_r(0), nb_courones(0), nb_privileges(0),
                              nom(nom), nb_jetons(0)
{}

Joueur::~Joueur() {}

void Joueur::acheter_carte(const Carte_joaillerie& carte){

    int cout_blanc = positif_ou_nul(carte.getCoutBlanc() - calculer_bonus(Bonus_couleur::blanc));
    int cout_bleu = positif_ou_nul(carte.getCoutBleu() - calculer_bonus(Bonus_couleur::bleu));
    int cout_rouge = positif_ou_nul(carte.getCoutRouge() - calculer_bonus(Bonus_couleur::rouge));
    int cout_vert = positif_ou_nul(carte.getCoutVert() - calculer_bonus(Bonus_couleur::vert));
    int cout_noir = positif_ou_nul(carte.getCoutNoir() - calculer_bonus(Bonus_couleur::noir));
    int cout_perle = positif_ou_nul(carte.getCoutPerle() - calculer_bonus(Bonus_couleur::perle)); // ya pas

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
                if (choix == "noir"|| "Noir") cout_noir = positif_ou_nul(cout_noir - nb);
                if (choix == "perle"|| "Perle") cout_perle = positif_ou_nul(cout_perle - nb);
            }
        }
    }

    // Vérifier si assez de jetons
    int eligible_achat = 0;

    if (nb_jeton(Couleur::blanc) >= cout_blanc &&
        nb_jeton(Couleur::bleu) >= cout_bleu &&
        nb_jeton(Couleur::rouge) >= cout_rouge &&
        nb_jeton(Couleur::vert) >= cout_vert &&
        nb_jeton(Couleur::noir) >= cout_noir &&
        nb_jeton(Couleur::perle) >= cout_perle)
        eligible_achat = 1;

    if (eligible_achat == 0) throw SplendorException("Pas assez de jetons");

    // Retirer les jetons utilisés et les mettre dans le sac
    retirer_jeton(Couleur::blanc, cout_blanc);
    retirer_jeton(Couleur::bleu, cout_bleu);
    retirer_jeton(Couleur::rouge, cout_rouge);
    retirer_jeton(Couleur::vert, cout_vert);
    retirer_jeton(Couleur::noir, cout_noir);
    retirer_jeton(Couleur::perle, cout_perle);

    // Mettre la carte dans la main du joueur et la retirer de la pioche
    cartes_joaillerie_achetees.push_back(&carte);


    // Vérifier si c'est une carte réservée
    int est_reservee = 0;
    for (auto it = cartes_joaiellerie_reservees.begin(); it != cartes_joaiellerie_reservees.end(); ++it){
        if ((*it) == &carte) est_reservee = 1;
    }

    if (est_reservee == 1){ // La retirer des cartes reservées
        for (auto it = cartes_joaiellerie_reservees.begin(); it != cartes_joaiellerie_reservees.end(); ++it) {
            if ((*it) == &carte) cartes_joaiellerie_reservees.erase(it);
        }
    }

    else { // La retirer du tirage et re piocher
        switch(carte.getNiveau()){
            case 1:
                for (auto it = Jeu::getJeu().get_tirage_1()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_1()->get_cartes().end(); ++it){
                    if ((*it) == &carte) it = Jeu::getJeu().get_tirage_1()->get_cartes().erase(it);
                }
                // Re piocher
                break;
            case 2:
                for (auto it = Jeu::getJeu().get_tirage_2()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_2()->get_cartes().end(); ++it){
                    if ((*it) == &carte) it = Jeu::getJeu().get_tirage_2()->get_cartes().erase(it);
                }
                // Re piocher
                break;
            case 3:
                for (auto it = Jeu::getJeu().get_tirage_3()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_3()->get_cartes().end(); ++it){
                    if ((*it) == &carte) it = Jeu::getJeu().get_tirage_3()->get_cartes().erase(it);
                }
                // Re piocher
                break;
        }
    }

    // Rajouter le nb de couronnes
    set_nb_couronnes(get_nb_couronnes() + carte.get_nb_couronnes());

    // Dans le main tester si eligible pour carte royale et appeler get carte royale

}

int positif_ou_nul(int x) {
    if (x < 0) return 0;
    else return x;
}


// Calculer le nb de jetons du joueur d'une couleur donnée
int Joueur::calculer_bonus(Bonus_couleur bonus) {
    int res = 0;
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
    while (val > 0){
        for (auto j = jetons.begin(); j != jetons.end(); ++j){
            if ((*j)->get_couleur() == c){
                Sac::get_sac().mettre_jeton_sac(*j);
                j = jetons.erase(j);
            }
        }
        val--;
    }
}

void Joueur::reserver_carte(const Carte_joaillerie& carte, const Jeton* jet) {
    // Vérifier que cela est suite à une acquisiton de jeton or
    if (jet->get_couleur() != Couleur::gold) throw SplendorException("Mauvaise couleur");
    cartes_joaiellerie_reservees.push_back(&carte);

    // Retirer du tirage
    switch(carte.getNiveau()){
        case 1:
            for (auto it = Jeu::getJeu().get_tirage_1()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_1()->get_cartes().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_1()->get_cartes().erase(it);
            }
            // remplir tirage niveau 1
            // Re piocher
            break;
        case 2:
            for (auto it = Jeu::getJeu().get_tirage_2()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_2()->get_cartes().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_2()->get_cartes().erase(it);
            }
            // remplir tirage niveau 2
            // Re piocher
            break;
        case 3:
            for (auto it = Jeu::getJeu().get_tirage_3()->get_cartes().begin(); it != Jeu::getJeu().get_tirage_3()->get_cartes().end(); ++it){
                if ((*it) == &carte) it = Jeu::getJeu().get_tirage_3()->get_cartes().erase(it);
            }
            // remplir tirage niveau 3
            // Re piocher
            break;
    }

    // Remplir le tirage
}

void Joueur::piocher_jetons() {
    // random jeton
}

void Joueur::obtenir_carte_royale(const Carte_royale& carte) {
    if (eligible_carte_royale() == false) throw SplendorException("Pas eligible.");
    cartes_royale.push_back(&carte);
    increment_carte_royale();
}

bool Joueur::eligible_carte_royale() {
    if (get_nb_couronnes() >= 3 and get_nb_couronnes() < 6 and get_nb_r() == 0){
        return true;
    }

    else if (get_nb_couronnes() >= 6 and get_nb_r() == 1){
        return true;
    }

    else {
        return false;
    }
}

