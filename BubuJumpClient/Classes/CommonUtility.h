#ifndef __CommonUtility_H__
#define __CommonUtility_H__

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
};

#endif // __CommonUtility_H__
