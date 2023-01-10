

#pragma once

#include <string>

namespace aes_ctr
{
    std::string encrypt(const std::string &plain_text_str, const std::string &key_base64);
    std::string decrypt(const std::string &cipher_text_base64, const std::string &key_base64);
}
