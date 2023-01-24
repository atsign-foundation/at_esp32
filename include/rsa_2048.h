
#pragma once

#include <string>

namespace rsa_2048
{
    class private_key
    {
    public:
        private_key(const std::string &rsa_private_key_base64_encoded);
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
        std::string d; // string of hex bytes no spaces
        std::string p; // string of hex bytes no spaces
        std::string q; // string of hex bytes no spaces
    };

    class public_key
    {
    public:
        public_key(const std::string &rsa_public_key_base64_encoded);
        public_key(const std::string &n_hex, const std::string &e_hex);
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
    };

    std::string sign(const std::string &challenge, const private_key &private_key);
    std::string verify(const std::string &signature, const public_key &public_key_base64);
    std::string encrypt(const std::string &plain_text, const public_key &public_key_base64);
    std::string decrypt(const std::string &cipher_text_base64, const private_key &private_key_base64);
};
