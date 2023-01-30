#include <iostream>
#include <iomanip>
#include <vector>
#include <mbedtls/aes.h>
#include <mbedtls/rsa.h>
#include "aes_ctr.h"
#include "base64.h"
#include <mbedtls/rsa_internal.h>
#include <mbedtls/pk.h>

#define ARRAY_SIZE 256

void inject(const std::vector<unsigned char> &input, unsigned char *output, size_t output_length);
std::string unhexlify(const unsigned char *input);
void print_bytes(const unsigned char *input, const size_t &length);
void print_bytes_as_base64_encoded(const unsigned char *input, const size_t &length);

std::string aes_ctr::decrypt(const std::string &cipher_text_base64, const std::string &key_base64)
{
    const std::vector<unsigned char> key_bytes = base64::base64_decode(key_base64);
    const size_t key_length = key_bytes.size();
    unsigned char key[key_length] = {0};
    inject(key_bytes, key, key_length);

    const std::vector<unsigned char> encrypted_text_bytes = base64::base64_decode(cipher_text_base64);
    // const size_t encrypted_text_len = encrypted_text_bytes.size();
    const size_t encrypted_text_len = 2048;
    unsigned char encrypted_text[encrypted_text_len] = {0};
    inject(encrypted_text_bytes, encrypted_text, encrypted_text_len);

    unsigned char decrypted_text[ARRAY_SIZE] = {0};

    mbedtls_aes_context aes;

    unsigned int nc_off = 0;
    unsigned char nonce_counter[16] = {0};
    unsigned char stream_block[16] = {0};

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_dec(&aes, key, 256);

    mbedtls_aes_crypt_ctr(&aes, encrypted_text_len, &nc_off, nonce_counter, stream_block, encrypted_text, decrypted_text); // decrypt

    const std::string decrypted = unhexlify(decrypted_text);

    mbedtls_aes_free(&aes);
    return decrypted;
}

std::string aes_ctr::encrypt(const std::string &plain_text_str, const std::string &key_base64)
{
    const std::vector<unsigned char> key_bytes = base64::base64_decode(key_base64);
    const size_t key_length = key_bytes.size();
    unsigned char key[key_length];
    inject(key_bytes, key, key_length);

    const std::uint32_t mod = (plain_text_str.size()) % 16;
    const std::uint32_t num_pad_bytes_to_add = 16 - mod;
    const unsigned char padding_val = num_pad_bytes_to_add;

    const size_t plain_text_len = plain_text_str.size() + num_pad_bytes_to_add;
    unsigned char plain_text[plain_text_len] = {0};
    for (std::uint32_t i = 0; i < plain_text_str.size(); i++)
    {
        plain_text[i] = plain_text_str[i];
    }

    for (std::uint32_t i = plain_text_str.size(); i < plain_text_len; i++)
    {
        plain_text[i] = padding_val;
    }

    unsigned char encrypted_text[ARRAY_SIZE] = {0};

    mbedtls_aes_context aes;

    unsigned int nc_off = 0;
    unsigned char nonce_counter[16] = {0};
    unsigned char stream_block[16] = {0};

    mbedtls_aes_init(&aes);
    mbedtls_aes_setkey_enc(&aes, key, 256);
    mbedtls_aes_crypt_ctr(&aes, plain_text_len, &nc_off, nonce_counter, stream_block, plain_text, encrypted_text); // decrypt

    std::int32_t i = 0;
    unsigned char c = encrypted_text[i];
    while (c != 0x00)
    {
        c = encrypted_text[++i];
    }

    auto to_return = base64::base64_encode(encrypted_text, i);
    return to_return;
}

/// ===============================
/// HELPER implementations
/// ===============================

void inject(const std::vector<unsigned char> &input, unsigned char *output, size_t output_length)
{
    for (std::uint32_t i = 0; i < output_length; i++)
    {
        output[i] = input[i];
    }
}

std::string unhexlify(const unsigned char *input)
{
    auto str = std::string();
    // index i until 0x08
    std::uint32_t i = 0;
    char c = input[i];
    while (base64::base64_chars.find(c) != std::string::npos)
    {
        str += c;
        i++;
        c = input[i];
    }
    return str;
}

void print_bytes(const unsigned char *input, const size_t &length)
{
    for (std::uint32_t i = 0; i < length; i++)
    {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)input[i] << " ";
    }
    std::cout << std::endl;
    
}

void print_bytes_as_base64_encoded(const unsigned char *input, const size_t &length)
{
    std::string base64_encoded = base64::base64_encode(input, length);
    std::cout << base64_encoded << std::endl;
}
