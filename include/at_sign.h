
#pragma once

#include <string>

class AtSign
{

private:
    std::string at_sign; // e.g. "@bob"

public:
    AtSign(const std::string &at_sign) : at_sign(at_sign)
    {
        // prepend '@' if it does not exist
        if (at_sign[0] != '@')
        {
            this->at_sign = "@" + at_sign;
        }
    }

    std::string get_value() const
    {
        return at_sign;
    }

    std::string without_prefix() const
    {
        return at_sign.substr(1);
    }
};
