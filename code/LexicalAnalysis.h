//client

#ifndef BC_LEXICALANALYSIS_H
#define BC_LEXICALANALYSIS_H

#include <string>

enum LexResult {
    error,
    normal,
    quit
};

class LexicalAnalysis {
    const std::string quitStr_ = "q";

    LexResult checkName_(const std::string& name, std::string& log);
    LexResult checkValue_(const std::string& value, std::string& log);
    LexResult checkID_(const std::string& id, std::string& log);
public:
    LexResult checkBasic(const std::string& str, std::string& log, std::string& res) noexcept ;
    LexResult checkPassword(const std::string& password, std::string& log) noexcept;
    LexResult checkUsername(const std::string& username, std::string& log) noexcept;
};


#endif BC_LEXICALANALYSIS_H
