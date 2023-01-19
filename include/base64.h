

#pragma once

#include <vector>
#include <string>

namespace base64
{
    static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/=";
    std::string base64_encode(unsigned char const* buf, unsigned int bufLen);
    std::vector<unsigned char> base64_decode(std::string const& encoded_string);
}
