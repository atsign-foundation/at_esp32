
#pragma once

#include <string>

namespace rsa_2048
{
    // represents an rsa 2048 private key
    struct private_key
    {
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
        std::string d; // string of hex bytes no spaces
        std::string p; // string of hex bytes no spaces
        std::string q; // string of hex bytes no spaces
    };

    // represents an rsa 2048 public key
    struct public_key
    {
        std::string n; // string of hex bytes no spaces
        std::string e; // string of hex bytes no spaces
    };

    /// @brief populate a rsa_2048::private_key with its n, e, d, p, q values by giving it a base64 encoded private key
    /// @param private_key_base64_encoded base64 encoded private key string
    /// @param private_key empty rsa_2048::private_key struct to populate
    void populate(const std::string &private_key_base64_encoded, private_key &private_key);

    /// @brief populate a rsa_2048::public_key with its n, e values by giving it a base64 encoded public key
    /// @param public_key_base64_encoded base64 encoded public key string
    /// @param public_key empty rsa_2048::public_key struct to populate
    void populate(const std::string &public_key_base64_encoded, public_key &public_key);

    /// @brief rsa 2048 sha 256 sign a challenge. sha256 hashing -> digest is already done
    /// @param challenge challenge to sign
    /// @param private_key private key to sign with
    /// @return base64 encoded signature
    std::string sign(const std::string &challenge, const private_key &private_key);

    // WIP
    std::string verify(const std::string &signature, const public_key &public_key_base64);

    /// @brief encrypt a string of text given an rsa 2048 public key struct
    /// @param plain_text the plain text to encrypt
    /// @param public_key_base64 the public key struct populated with the n and e values
    /// @return the base64 encoded cipher text
    std::string encrypt(const std::string &plain_text, const public_key &public_key_base64);

    /// @brief decrypt a string of text given an rsa 2048 private key struct
    /// @param cipher_text_base64 the base64 encoded cipher text to decrypt
    /// @param private_key_base64 the private key struct populated with the n, e, d, p, q values
    /// @return the plain text
    std::string decrypt(const std::string &cipher_text_base64, const private_key &private_key_base64);
};
