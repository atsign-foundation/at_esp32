#pragma once

#include <string>

/// @brief aes-256 CTR encryption/decryption
namespace aes_ctr
{
    /// @brief Encrypt plain text with aes-256 in ctr mode
    /// @param plain_text_str the plain text to encrypt
    /// @param key_base64 the aes-256 symmetric key encoded in base64
    /// @return cipher text base64 encoded std::string
    std::string encrypt(const std::string &plain_text_str, const std::string &key_base64);

    /// @brief Decrypt cipher text (that is encoded in base64) with aes-256 in ctr mode
    /// @param cipher_text_base64 the cipher text (encoded in base64) to decrypt
    /// @param key_base64 the aes-256 symmetric key encoded in base64
    /// @return plain text std::string
    std::string decrypt(const std::string &cipher_text_base64, const std::string &key_base64);
}
