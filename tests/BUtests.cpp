#include <gtest/gtest.h>
#include "../code/BankOfUsers.h"

using namespace BankOfUsers;

TEST(BUtests, normal){
    deleteAllUsers();
    EXPECT_TRUE(checkUser("admin","admin"));
    EXPECT_TRUE(checkName("admin"));
    EXPECT_FALSE(checkUser("admen","admin1"));
    addUser("test","test");
    EXPECT_TRUE(checkUser("test","test"));
    EXPECT_TRUE(checkUser("admin","admin"));
    EXPECT_FALSE(checkUser("adman","admin1"));
    EXPECT_TRUE(checkName("admin"));
    EXPECT_TRUE(checkName("test"));
    EXPECT_FALSE(checkName("admen"));
    addUser("test2","test2");
    addUser("fosfvoaohadfohasfoh","dieiudfuigdfuygsdfgu234234624");
    addUser("546346349634943978-_","terhoh--ieriu42624634_-");
    EXPECT_TRUE(checkUser("546346349634943978-_","terhoh--ieriu42624634_-"));
    EXPECT_TRUE(checkName("546346349634943978-_"));
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
    EXPECT_TRUE(checkName("admin"));
    deleteAllUsers();
}

TEST(BUtests, throws_addUser){
    EXPECT_ANY_THROW(addUser("===@)","#@@@@@@@@"));
    EXPECT_ANY_THROW(addUser("szvldfkdfkhsdh","#@@@@@@@@"));
    EXPECT_ANY_THROW(addUser("===@)","sdugkduydgu"));
    char s[101];
    for(std::size_t i = 0; i < 100; ++i) {
        s[i] = '0' + i % 10;
    }
    s[100] = '\0';
    EXPECT_ANY_THROW(addUser(s,"1234"));
    EXPECT_ANY_THROW(addUser("1234",s));
    EXPECT_ANY_THROW(addUser(s,s));
    EXPECT_ANY_THROW(addUser("",""));
    EXPECT_ANY_THROW(addUser("1",""));
    EXPECT_ANY_THROW(addUser("","1"));
    EXPECT_ANY_THROW(addUser("1","1"));
    EXPECT_ANY_THROW(addUser("1","123"));
    deleteAllUsers();
}

TEST(BUtests, throws_checkUser){
    EXPECT_ANY_THROW(checkUser("===@)","#@@@@@@@@"));
    EXPECT_ANY_THROW(checkUser("szvldfkdfkhsdh","#@@@@@@@@"));
    EXPECT_ANY_THROW(checkUser("===@)","sdugkduydgu"));
    char s[101];
    for(std::size_t i = 0; i < 100; ++i) {
        s[i] = '0' + i % 10;
    }
    s[100] = '\0';
    EXPECT_ANY_THROW(checkUser(s,"1234"));
    EXPECT_ANY_THROW(checkUser("1234",s));
    EXPECT_ANY_THROW(checkUser(s,s));
    EXPECT_ANY_THROW(checkUser("",""));
    EXPECT_ANY_THROW(checkUser("1",""));
    EXPECT_ANY_THROW(checkUser("","1"));
    EXPECT_ANY_THROW(checkUser("1","1"));
    EXPECT_ANY_THROW(checkUser("1","123"));
    deleteAllUsers();
}

TEST(BUtests, throws_checkName){
    EXPECT_ANY_THROW(checkName("===@)"));
    char s[101];
    for(std::size_t i = 0; i < 100; ++i) {
        s[i] = '0';
    }
    s[100] = '\0';
    EXPECT_ANY_THROW(checkName(s));
    EXPECT_ANY_THROW(checkName(""));
    deleteAllUsers();
}