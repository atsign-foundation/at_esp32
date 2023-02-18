

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <mbedtls/rsa.h>
#include <mbedtls/entropy.h>
#include <mbedtls/ctr_drbg.h>
#include <algorithm>
#include "base64.h"
#include "tiny-asn1.h"
#include "rsa_2048.h"

// ==================== helper functions ====================
std::string get_hex_string(const uint8_t *data, unsigned int len);
void print_hex(const uint8_t *data, unsigned int len);
int ascii2val(char c);
std::vector<uint8_t> unhexlify(const std::string &InBuffer);
void print_asn1(const asn1_tree *list, int depth);
// ==================== helper functions ====================

// ==================== rsa_2048.h implementations ====================
void rsa_2048::populate(const std::string &rsa_public_key_base64_encoded, rsa_2048::public_key &public_key)
{
    std::vector<uint8_t> a;
    a = base64::base64_decode(rsa_public_key_base64_encoded);

    // der decode operation
    const std::uint8_t *input = a.data();
    const std::uint32_t input_length = a.size();

    const std::uint32_t asn1_object_count = der_object_count(input, input_length);
    asn1_tree *asn1_objects = (asn1_tree *)(malloc(sizeof(asn1_tree) * asn1_object_count));
    asn1_tree cms;
    asn1_tree *cms_ptr = &cms;
    der_decode(input, input_length, cms_ptr, asn1_objects, asn1_object_count);

    // print_asn1(cms_ptr, 0);

    cms_ptr = cms_ptr->child->next;
    // print_asn1(cms_ptr, 0);

    // remove first 00

    // der decode operation again
    const std::uint8_t *input1 = cms_ptr->data + 1;
    const std::uint32_t input_length1 = cms_ptr->length -1;
    const std::uint32_t asn1_object_count1 = der_object_count(input1, input_length1);
    asn1_tree *asn1_objects1 = (asn1_tree *) (malloc(sizeof(asn1_tree) * asn1_object_count1));
    asn1_tree cms1;
    asn1_tree *cms_ptr1 = &cms1;
    der_decode(input1, input_length1, cms_ptr1, asn1_objects1, asn1_object_count1);

    // print_asn1(cms_ptr1, 0);

    public_key.n = get_hex_string(cms_ptr1->child->data, cms_ptr1->child->length);
    public_key.e = get_hex_string(cms_ptr1->child->next->data, cms_ptr1->child->next->length);
}

void rsa_2048::populate(const std::string &rsa_private_key_base64_encoded, rsa_2048::private_key &private_key)
{
    std::vector<uint8_t> a = base64::base64_decode(rsa_private_key_base64_encoded);

    // der decode operation
    std::uint8_t *input = a.data();
    const size_t input_length = a.size();

    const std::uint32_t asn1_object_count = der_object_count(input, input_length);
    asn1_tree *asn1_objects = (asn1_tree *)(malloc(sizeof(asn1_tree) * asn1_object_count));
    asn1_tree cms;
    asn1_tree *cms_ptr = &cms;
    der_decode(input, input_length, cms_ptr, asn1_objects, asn1_object_count);

    // print_asn1(cms_ptr, 0);

    // std::string hex_str = get_hex_string(cms_ptr->child->next->next->data, cms_ptr->child->next->next->length);

    cms_ptr = cms_ptr->child->next->next;

    // der decode operation again
    const std::uint8_t *input1 = cms_ptr->data;
    const size_t input_length1 = cms_ptr->length;
    const std::uint32_t asn1_object_count1 = der_object_count(input1, input_length1);
    asn1_tree *asn1_objects1 = (asn1_tree *)(malloc(sizeof(asn1_tree) * asn1_object_count1));
    asn1_tree cms1;
    asn1_tree *cms_ptr1 = &cms1;
    der_decode(input1, input_length1, cms_ptr1, asn1_objects1, asn1_object_count1);

    // print_asn1(cms_ptr1, 0);

    asn1_tree *n_ptr = cms_ptr1->child->next;
    asn1_tree *e_ptr = n_ptr->next;
    asn1_tree *d_ptr = e_ptr->next;
    asn1_tree *p_ptr = d_ptr->next;
    asn1_tree *q_ptr = p_ptr->next;

    private_key.n = get_hex_string(n_ptr->data, n_ptr->length);
    private_key.e = get_hex_string(e_ptr->data, e_ptr->length);
    private_key.d = get_hex_string(d_ptr->data, d_ptr->length);
    private_key.p = get_hex_string(p_ptr->data, p_ptr->length);
    private_key.q = get_hex_string(q_ptr->data, q_ptr->length);
}

std::string rsa_2048::sign(const std::string &challenge, const private_key &private_key)
{
    std::string n_hex_str = private_key.n;
    std::string e_hex_str = private_key.e;
    std::string d_hex_str = private_key.d;
    std::string p_hex_str = private_key.p;
    std::string q_hex_str = private_key.q;

    // std::cout << "n: " << n_hex_str << std::endl;
    // std::cout << "e: " << e_hex_str << std::endl;
    // std::cout << "d: " << d_hex_str << std::endl;
    // std::cout << "p: " << p_hex_str << std::endl;
    // std::cout << "q: " << q_hex_str << std::endl;

    mbedtls_rsa_context rsa;

    mbedtls_mpi n, e, p, d, q;
    mbedtls_mpi_init(&n);
    mbedtls_mpi_init(&e);
    mbedtls_mpi_init(&d);
    mbedtls_mpi_init(&p);
    mbedtls_mpi_init(&q);

    mbedtls_mpi_read_string(&n, 16, (n_hex_str.c_str()));
    mbedtls_mpi_read_string(&e, 16, (e_hex_str.c_str()));
    mbedtls_mpi_read_string(&d, 16, (d_hex_str.c_str()));
    mbedtls_mpi_read_string(&p, 16, (p_hex_str.c_str()));
    mbedtls_mpi_read_string(&q, 16, (q_hex_str.c_str()));

    mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

    std::cout << "import: " << mbedtls_rsa_import(&rsa, &n, &p, &q, &d, &e) << std::endl;

    std::cout << "complete: " << mbedtls_rsa_complete(&rsa) << std::endl;

    std::cout << "private key check: " << mbedtls_rsa_check_privkey(&rsa) << std::endl;

    const auto challenge_bytes = std::vector<unsigned char>(challenge.begin(), challenge.end());
    // const int value = challenge.size() % 16;
    // const int num_bytes_to_add = 16 - value;
    // const unsigned char byte_to_add = num_bytes_to_add;
    // std::cout << "value: " << value << std::endl;
    // std::cout << "num_bytes_to_add: " << num_bytes_to_add << std::endl;
    // std::cout << "byte_to_add: " << std::hex << std::setfill('0') << std::setw(2) << (int) byte_to_add << std::endl;

    // hash
    mbedtls_md_context_t ctx;
    mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;

    mbedtls_md_init(&ctx);
    mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0);
    mbedtls_md_starts(&ctx);
    mbedtls_md_update(&ctx, (unsigned char *) challenge.c_str(), challenge.size());
    unsigned char hash[32];
    mbedtls_md_finish(&ctx, hash);
    mbedtls_md_free(&ctx);

    // std::cout << "hash bytes (" << "32" << "): " << std::endl;
    // for(int i = 0; i < 32; i++) {
    //     std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) hash[i] << " ";
    // }
    // std::cout << std::endl;

    // base64 encode and print
    // std::string hash_base64 = base64::base64_encode(hash, 32);
    // std::cout << "hash base64: " << hash_base64 << std::endl;

    unsigned char signature[256];

    int ret = mbedtls_rsa_pkcs1_sign(&rsa, NULL, NULL, MBEDTLS_RSA_PRIVATE, MBEDTLS_MD_SHA256, 0, hash, signature);
    std::cout << "sign success: " << ret << std::endl;

    // for (std::uint32_t i = 0; i < 256; i++)
    // {
    //     std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)signature[i] << " ";
    // }
    // std::cout << std::endl;

    const std::string signature_base64 = base64::base64_encode(signature, 256);

    // std::cout << "base64 encoded string: " <<  signature_base64 << std::endl;
    return signature_base64;
}

std::string rsa_2048::encrypt(const std::string &plain_text, const public_key &public_key_base64)
{ // not working

    // intiializes rsa functions with n and e
    mbedtls_rsa_context rsa;
    mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

    mbedtls_mpi n, e;
    mbedtls_mpi_init(&n);
    mbedtls_mpi_init(&e);

    mbedtls_mpi_read_string(&n, 16, (public_key_base64.n.c_str()));
    mbedtls_mpi_read_string(&e, 16, (public_key_base64.e.c_str()));

    // import n and e, outputs 0 if successful
    std::cout << "import: " << mbedtls_rsa_import(&rsa, &n, NULL, NULL, NULL, &e) << std::endl;

    // context can be used
    std::cout << "complete: " << mbedtls_rsa_complete(&rsa) << std::endl;

    // public key is valid
    std::cout << "public key check: " << mbedtls_rsa_check_pubkey(&rsa) << std::endl;

    unsigned char output[256] = {0};

    // transform base64 plain text to bytes
    std::cout << "plain_text: " << plain_text << std::endl;
    const unsigned char *buffer = (unsigned char *)plain_text.c_str();
    const auto bytes = base64::base64_decode(base64::base64_encode(buffer, plain_text.size()));
    // display bytes
    for (std::uint32_t i = 0; i < bytes.size(); i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)bytes[i] << " ";
    }
    std::cout << std::endl << std::resetiosflags(std::ios::hex);

    mbedtls_entropy_context entropy;
    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ctr_drbg_init(&ctr_drbg);

    std::cout << "seed: " << mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func,
                                &entropy, (const unsigned char *) "rsa_encrypt",
                                std::string{"rsa_encrypt"}.size()) << std::endl;

    int ret = mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_ctr_drbg_random, &ctr_drbg, MBEDTLS_RSA_PUBLIC, bytes.size(), bytes.data(), output);
    // int ret = mbedtls_rsa_pkcs1_encrypt(&rsa, mbedtls_ctr_drbg_random, nullptr, MBEDTLS_RSA_PUBLIC, bytes.size(), bytes.data(), output);
    std::cout << "encrypt: " <<  ret << std::endl;

    const auto encrypted_base64 = base64::base64_encode(output, 256);
    return encrypted_base64;

}

std::string rsa_2048::decrypt(const std::string &cipher_text_base64, const private_key &private_key)
{
    mbedtls_rsa_context rsa;
    mbedtls_mpi n, e, d, p, q;
    mbedtls_mpi_init(&n);
    mbedtls_mpi_init(&e);
    mbedtls_mpi_init(&d);
    mbedtls_mpi_init(&p);
    mbedtls_mpi_init(&q);

    mbedtls_mpi_read_string(&n, 16, (private_key.n.c_str()));
    mbedtls_mpi_read_string(&e, 16, (private_key.e.c_str()));
    mbedtls_mpi_read_string(&d, 16, (private_key.d.c_str()));
    mbedtls_mpi_read_string(&p, 16, (private_key.p.c_str()));
    mbedtls_mpi_read_string(&q, 16, (private_key.q.c_str()));

    // std::cout << "n: " << private_key.n << std::endl;
    // std::cout << "e: " << private_key.e << std::endl;
    // std::cout << "d: " << private_key.d << std::endl;
    // std::cout << "p: " << private_key.p << std::endl;
    // std::cout << "q: " << private_key.q << std::endl;

    mbedtls_rsa_init(&rsa, MBEDTLS_RSA_PKCS_V15, 0);

    std::cout << "import: " << mbedtls_rsa_import(&rsa, &n, &p, &q, &d, &e) << std::endl;

    std::cout << "complete: " << mbedtls_rsa_complete(&rsa) << std::endl;


    std::cout << "private key check: " << mbedtls_rsa_check_privkey(&rsa) << std::endl;

    unsigned char output[256] = {0};
    const std::vector<unsigned char> bytes = base64::base64_decode(cipher_text_base64);
    // display bytes
    // for (std::uint32_t i = 0; i < bytes.size(); i++)
    // {
    //     std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)bytes[i] << " ";
    // }
    // std::cout << std::endl << std::resetiosflags(std::ios::hex);

    std::size_t *i = new std::size_t{bytes.size()};
    // std::size_t *i = new std::size_t{cipher_text_base64.size()};

    int ret = mbedtls_rsa_pkcs1_decrypt(&rsa, NULL, NULL, MBEDTLS_RSA_PRIVATE, i, bytes.data(), output, 256);

    std::cout << "decrypted: " << ret << std::endl;

    // display output
    for (std::uint32_t i = 0; i < 256; i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)output[i] << " ";
    }
    std::cout << std::endl << std::resetiosflags(std::ios::hex);

    const auto unhexlified = unhexlify(get_hex_string(output, 256));
    // decrypted_base64 is string from beginning to null terminator or end
    // find index of unhexlified that is 00
    const auto null_terminator_index = std::find(unhexlified.begin(), unhexlified.end(), '\0');
    const auto decrypted_base64 = std::string{unhexlified.begin(), null_terminator_index};

    return decrypted_base64;
    // mbedtls_rsa_pkcs1_decrypt(&rsa, mbedtls_ctr_drbg_random, &ctr_drbg, &i, buf, result, 1024);
}
// ==================== rsa_2048.h implementations ====================

// ==================== helper implementations ====================
std::string get_hex_string(const uint8_t *data, unsigned int len)
{
    const char *hex_chars = "0123456789abcdef";
    std::string x;
    unsigned int count = 0;
    while (count < len)
    {
        x += hex_chars[data[count] >> 4];
        x += hex_chars[data[count] & 0x0F];
        ++count;
    }
    return x;
}

void print_hex(const uint8_t *data, unsigned int len)
{
    unsigned int count = 0;
    unsigned int blockCount = 0;
    while (count < len)
    {
        // printf("%02x ", data[count]);
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (int) data[count] << " ";
        ++count;
        ++blockCount;
        if (blockCount == 4)
        {

            std::cout << " ";
        }
        if (blockCount == 8)
        {
            std::cout << '\n';
            blockCount = 0;
        }
    }
    std::cout << '\n';
}

int ascii2val(char c)
{
    int iRetVal;

    if ((c >= '0') && (c <= '9'))
    {
        iRetVal = (c - '0');
    }
    else if ((c >= 'a') && (c <= 'f'))
    {
        iRetVal = (c - 'a' + 10);
    }
    else if ((c >= 'A') && (c <= 'F'))
    {
        iRetVal = (c - 'A' + 10);
    }
    else
    {
        iRetVal = 0;
    }

    return iRetVal;
}

std::vector<uint8_t> unhexlify(const std::string &InBuffer)
{
    std::vector<uint8_t> OutBuffer(InBuffer.size() / 2 + 1);

    for (size_t i = 0, j = 0; i < InBuffer.size(); i += 2, ++j)
    {
        uint8_t *dest = &OutBuffer[j];
        *dest++ = (((ascii2val(InBuffer[i]) << 4) | (ascii2val(InBuffer[i + 1]))));
    }

    return OutBuffer;
}

void print_asn1(const asn1_tree *list, int depth)
{
    std::cout << "d=" << depth << ", Type: " << list->type << ", len=" << list->length << std::endl;
    if (list->child == NULL)
    {
        std::cout << "Value:" << std::endl;
        print_hex(list->data, list->length);
    }
    else
    {
        print_asn1(list->child, depth + 1);
    }

    if (list->next != NULL)
        print_asn1(list->next, depth);
}
// ==================== helper implementations ====================
