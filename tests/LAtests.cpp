#include <gtest/gtest.h>
#include "../code/LexicalAnalysis.h"

class LexicalAnalysisTest : public ::testing::Test {
protected:
    LexicalAnalysis lexAnalyzer;
    std::string log;
};

TEST_F(LexicalAnalysisTest, CheckPassword_ValidPassword) {
    EXPECT_EQ(lexAnalyzer.checkPassword("Valid123_", log), LexResult::normal);
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckPassword_EmptyPassword) {
    EXPECT_EQ(lexAnalyzer.checkPassword("", log), LexResult::error);
    EXPECT_EQ(log, "Empty password");
}

TEST_F(LexicalAnalysisTest, CheckPassword_TooShort) {
    EXPECT_EQ(lexAnalyzer.checkPassword("abc", log), LexResult::error);
    EXPECT_EQ(log, "Password is too short");
}

TEST_F(LexicalAnalysisTest, CheckPassword_TooLong) {
    EXPECT_EQ(lexAnalyzer.checkPassword("aVeryLongPasswordThatExceedsFiftyCharacters12345678901234567", log), LexResult::error);
    EXPECT_EQ(log, "Password is too long");
}

TEST_F(LexicalAnalysisTest, CheckPassword_InvalidCharacters) {
    EXPECT_EQ(lexAnalyzer.checkPassword("Invalid@Password", log), LexResult::error);
    EXPECT_EQ(log, R"(Invalid password. Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')");
}

TEST_F(LexicalAnalysisTest, CheckUsername_ValidUsername) {
    EXPECT_EQ(lexAnalyzer.checkUsername("User_123", log), LexResult::normal);
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckUsername_EmptyUsername) {
    EXPECT_EQ(lexAnalyzer.checkUsername("", log), LexResult::error);
    EXPECT_EQ(log, "Empty username");
}

TEST_F(LexicalAnalysisTest, CheckUsername_TooLong) {
    EXPECT_EQ(lexAnalyzer.checkUsername("ThisUsernameIsWayTooLongAndShouldFail12345671234567", log), LexResult::error);
    EXPECT_EQ(log, "Username is too long");
}

TEST_F(LexicalAnalysisTest, CheckUsername_InvalidCharacters) {
    EXPECT_EQ(lexAnalyzer.checkUsername("Invalid@Username", log), LexResult::error);
    EXPECT_EQ(log, R"(Invalid username. Please, use: 'a'-'z' or 'A'-'Z' or '0'-'9' or '_' or '-')");
}


TEST_F(LexicalAnalysisTest, CheckBasicCommand_r1) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("r Nick qwerty1234", log,res), LexResult::normal);
    EXPECT_EQ(res,"rNick qwerty1234");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_r2) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("r Nick", log, res), LexResult::error);
    EXPECT_EQ(log, "Empty password");
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_a) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("a Note1 Hello_world0213409281049812094812094801294809218409128409128409128049812049821 ", log, res), LexResult::normal);
    EXPECT_EQ(res,"aNote1 Hello_world0213409281049812094812094801294809218409128409128409128049812049821");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_d1) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("d 1234567", log, res), LexResult::normal);
    EXPECT_EQ(res,"d1234567");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_d2) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("d 1234567 something", log, res), LexResult::error);
    EXPECT_EQ(log, "Invalid command");
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_u1) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("u 1234567 Name NewValue", log, res), LexResult::normal);
    EXPECT_EQ(res,"u1234567 Name NewValue");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_u2) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("u 1234567 Name", log, res), LexResult::error);
    EXPECT_EQ(log, "Empty value of record");
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_g1) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("g all", log, res), LexResult::normal);
    EXPECT_EQ(res,"l");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_g2) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("g name SomeName", log, res), LexResult::normal);
    EXPECT_EQ(res,"nSomeName");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_g3) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("g value SomeValue", log, res), LexResult::normal);
    EXPECT_EQ(res,"vSomeValue");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_Quit) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("q", log, res), LexResult::quit);
    EXPECT_EQ(res,"");
    EXPECT_TRUE(log.empty());
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_Unknown) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("q Name Surname", log, res), LexResult::error);
    EXPECT_EQ(log, "Unknown command");
}

TEST_F(LexicalAnalysisTest, CheckID_tooLong) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("d 12345678912345", log, res), LexResult::error);
    EXPECT_EQ(log, "ID is wrong");
}

TEST_F(LexicalAnalysisTest, CheckID_SymbolicCharacters) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("d abcdefg", log, res), LexResult::error);
    EXPECT_EQ(log, "Invalid ID of record");
}

TEST_F(LexicalAnalysisTest, CheckID_EmptyID) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("d", log, res), LexResult::error);
    EXPECT_EQ(log, "Empty ID of record");
}


TEST_F(LexicalAnalysisTest, CheckBasicCommand_EmptyCommand) {
    std::string res="";
    EXPECT_EQ(lexAnalyzer.checkBasic("", log, res), LexResult::error);
    EXPECT_EQ(log, "Empty command");
}

TEST_F(LexicalAnalysisTest, CheckBasicCommand_TooLong) {
    std::string res="";
    std::string longCommand(1201, 'a'); // Создаем строку длиной 1201 символ
    EXPECT_EQ(lexAnalyzer.checkBasic(longCommand, log, res), LexResult::error);
    EXPECT_EQ(log, "Command is too long");
}



