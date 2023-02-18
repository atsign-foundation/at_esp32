
#pragma once

#include <string>
#include <map>
#include "at_sign.h"

namespace keys_reader
{
    std::map<std::string, std::string> read_keys(const AtSign &at_sign);
}