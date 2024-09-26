#include <gtest/gtest.h>
#include "../code/BankOfUsers.h"

TEST(BUtests, normal){
    using namespace BankOfUsers;
    deleteAllUsers();
    EXPECT_TRUE(checkUser("admin","admin"));
    EXPECT_FALSE(checkUser("admen","admin1"));
    addUser("test","test");
    EXPECT_TRUE(checkUser("test","test"));
    EXPECT_TRUE(checkUser("admin","admin"));
    EXPECT_FALSE(checkUser("adman","admin1"));
    addUser("test2","test2");
    addUser("fosfvoaohadfohasfoh","dieiudfuigdfuygsdfgu234234624");
    addUser("546346349634943978-_","terhoh--ieriu42624634_-");
    EXPECT_TRUE(checkUser("546346349634943978-_","terhoh--ieriu42624634_-"));
    EXPECT_TRUE(checkUser("fosfvoaohadfohasfoh","dieiudfuigdfuygsdfgu234234624"));
    EXPECT_TRUE(checkUser("test2","test2"));
    EXPECT_FALSE(checkUser("tefedffdt","tfddfffv4"));
    EXPECT_TRUE(checkUser("admin","admin"));
    deleteAllUsers();
    EXPECT_FALSE(checkUser("546346349634943978-_","terhoh--ieriu42624634_-"));
    EXPECT_FALSE(checkUser("fosfvoaohadfohasfoh","dieiudfuigdfuygsdfgu234234624"));
    EXPECT_FALSE(checkUser("test2","test2"));
    EXPECT_FALSE(checkUser("tefedffdt","tfddfffv4"));
    EXPECT_TRUE(checkUser("admin","admin"));
}