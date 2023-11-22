#ifndef LO21_SPLENDOR_DUEL_LOTS_PRIVILEGES_H
#define LO21_SPLENDOR_DUEL_LOTS_PRIVILEGES_H
#include "privilege.h"
#include <iostream>
#include <vector>


class Lot_Privilege{
    std::vector<const Privilege*> lot_privileges;
    struct Handler_Lot_Privilege{
        Lot_Privilege * instance = nullptr;
        ~Handler_Lot_Privilege(){
            delete instance;
            instance = nullptr;
        }
    };
    static Handler_Lot_Privilege handler_lot_privilege;
public:
    Lot_Privilege():lot_privileges(){}
    ~Lot_Privilege()=default; // car agrégation
    Lot_Privilege& operator=(const Lot_Privilege&)=delete;
    Lot_Privilege(const Lot_Privilege&)=delete;

    static Lot_Privilege& get_lot_privilege();
    static void libere_lot_privilege();

    void init_lot_privileges(const std::vector<const Privilege*> p);


};


#endif //LO21_SPLENDOR_DUEL_LOTS_PRIVILEGES_H
