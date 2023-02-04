
#pragma once

#include <string>

class AtSign {

private:
    std::string at_sign;

public:
    AtSign(const std::string &at_sign) : at_sign(at_sign) {}

    std::string get_value() const {
        return at_sign;
    }

    std::string without_prefix() const {
        return at_sign.substr(1);
    }
};
