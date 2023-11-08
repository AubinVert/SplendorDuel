#ifndef LO21_SPLENDOR_DUEL_PRIVILEGE_H
#define LO21_SPLENDOR_DUEL_PRIVILEGE_H
#include <iostream>
#include <stdexcept>
#include "Exception.h"


class Privilege{
private:
    const int id;
    static int instanceCount;  // Compteur d'instances actuelles
    static const int maxInstances = 3;
    Privilege(const Privilege&) = delete;
    Privilege& operator=(const Privilege&) = delete;
    Privilege(): id(instanceCount) {}

public:
    const int get_id()const{return id;}
    static int getCount(){
        return instanceCount;
    }

    // Méthode statique pour obtenir une instance de la classe
    static Privilege* GetInstance() {
        if (instanceCount < maxInstances) {
            ++instanceCount;
            return new Privilege();
        }
        throw SplendorException("Nombres d'instances de privileges depasse");
    }



};

#endif //LO21_SPLENDOR_DUEL_PRIVILEGE_H
