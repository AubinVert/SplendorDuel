#include "main.h"

int main(){

    try{
        testTirage();

    }catch(SplendorException& e){
        cout<< e.getInfos()<<endl;
    }


    return 0;
}
