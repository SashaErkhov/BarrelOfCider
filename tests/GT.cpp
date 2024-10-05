#include "BankOfUsers.h"
#include "sha256.h"
#include "BC_Errors.h"
#include <string>

int main(){
    try {
        std::cout << UINT_MAX << ' ' << std::endl;

    }catch(BC_Error& error){
        std::cout<< error.what()<<std::endl;
        return 1;
    }
    return 0;
}