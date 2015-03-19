#ifndef __CommonUtility_H__
#define __CommonUtility_H__

#include <regex.h>

class CommonUtility
{
public:
    template <class T>
    static std::string convertToString(T value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }
    
    inline static std::string& trim(std::string& text)
    {
        if(!text.empty())
        {
            text.erase(0, text.find_first_not_of((" \n\r\t")));
            text.erase(text.find_last_not_of((" \n\r\t")) + 1);
        }
        return text;
    }
    
    static bool isStringStartWith(const std::string& source, const std::string& target)
    {
        return source.compare(0, target.size(), target) == 0;
    }
    
    static bool checkMobilePhoneNumber(std::string phoneNumber)
    {
        regex_t match_regex;
//        regcomp(&match_regex, "\\d{11}", REG_EXTENDED | REG_NEWLINE);
        regcomp(&match_regex, "^((13[0-9])|(15[0-3,5-9])|(18[0,5-9]))[0-9]{8}$", REG_EXTENDED | REG_NEWLINE);
//        regcomp(&match_regex, "^((13[0-9])|(15[^4,\\D])|(18[0,5-9]))\\d{8}$", REG_EXTENDED | REG_NEWLINE);
        if (regexec(&match_regex, phoneNumber.c_str(), 0, nullptr, 0) == 0)
        {
            return true;
        }
        else
        {
            return false;
        }

//        std::regex pattern("^((13[0-9])|(15[^4,\\D])|(18[0,5-9]))\\d{8}$");
//        if (std::regex_match(phoneNumber, pattern))
    }
};

#endif // __CommonUtility_H__
