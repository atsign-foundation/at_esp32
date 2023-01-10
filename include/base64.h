

#pragma once

#include <vector>
#include <string>

namespace base64
{
    std::string base64_encode(unsigned char const* buf, unsigned int bufLen);
    std::vector<unsigned char> base64_decode(std::string const& encoded_string);
}
