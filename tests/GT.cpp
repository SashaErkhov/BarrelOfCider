#include"BankOfUsers.h"
#include "sha256.h"
#include "BC_Errors.h"

int main(){
    try {
        //BankOfUsers::addUser("test", "test");
        //BankOfUsers::addUser("test2", "test2");
        //BankOfUsers::addUser("tddffgwefef", "fgvoudhuwi");
        BankOfUsers::deleteAllUsers();
        BankOfUsers::addUser("test", "test");
        std::cout << BankOfUsers::checkUser("test", "test") << std::endl;
    }catch(BC_Error& error){
        std::cout<< error.what()<<std::endl;
        return 1;
    }
    return 0;
}