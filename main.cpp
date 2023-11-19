#include "main.h"
#include "classes/tirage.h"

int main(){

    try{
        testTirage();

    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}
