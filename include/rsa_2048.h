
#pragma once

#include <string>

class rsa_private_key
{
    public:
        rsa_private_key(std::string rsa_private_key_base64_encoded);
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
        std::string d; // string of hex bytes no spaces
        std::string p; // string of hex bytes no spaces
        std::string q; // string of hex bytes no spaces
};

class rsa_public_key
{
    public:
        rsa_public_key(std::string rsa_public_key_base64_encoded);
        rsa_public_key(std::string n_hex, std::string e_hex);
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
};

namespace rsa_2048
{
    std::string sign(std::string challenge, rsa_private_key private_key);
    std::string verify(std::string signature, rsa_public_key public_key_base64);
    std::string encrypt(std::string plain_text, rsa_public_key public_key_base64);
    std::string decrypt(std::string cipher_text_base64, rsa_private_key private_key_base64);
};
