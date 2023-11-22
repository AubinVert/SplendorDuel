#include "lots_privileges.h"

using namespace std;


Lot_Privilege::Handler_Lot_Privilege Lot_Privilege::handler_lot_privilege;

Lot_Privilege &Lot_Privilege::get_lot_privilege() {
    if(handler_lot_privilege.instance==nullptr){
        handler_lot_privilege.instance = new Lot_Privilege();
    }
    return *handler_lot_privilege.instance;
}

void Lot_Privilege::libere_lot_privilege() {
    delete handler_lot_privilege.instance;
    handler_lot_privilege.instance = nullptr;
}

void Lot_Privilege::init_lot_privileges(const std::vector<const Privilege*> p){
    for(int i = 0; i<Privilege::get_max_instance();i++) {
        lot_privileges.push_back(*p.begin()+i);
    }
}