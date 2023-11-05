#include "main.h"
#include "classes/plateau.h"
#include "classes/jetons.h"
#include "classes/sac.h"


int main() {
    try{
        Sac& sac = Sac::get_sac();
        sac.init_sac();
        Plateau& p = Plateau::get_plateau();
        p.remplir_plateau(sac);
        p.print_tab();









    }catch(const SplendorException& e){
        cout<<e.getInfos()<<endl;
    }
    return 0;
}


void test_unitaires(){
    // permet de tester la validité de notre code







}


