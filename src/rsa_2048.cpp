

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "rsa_2048.h"
#include "base64.h"
#include "tiny-asn1.h"

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

rsa_2048::public_key::public_key(const std::string &rsa_public_key_base64_encoded)
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

    n = get_hex_string(cms_ptr1->child->data, cms_ptr1->child->length);
    e = get_hex_string(cms_ptr1->child->next->data, cms_ptr1->child->next->length);
}

rsa_2048::public_key::public_key(const std::string &n_hex, const std::string &e_hex)
{
    n = n_hex;
    e = e_hex;
}

rsa_2048::private_key::private_key(const std::string &rsa_private_key_base64_encoded)
{
    std::vector<uint8_t> a;
    a = base64::base64_decode(rsa_private_key_base64_encoded);

    // der decode operation
    std::uint8_t *input = a.data();
    const size_t input_length = a.size();

    const std::uint32_t asn1_object_count = der_object_count(input, input_length);
    asn1_tree *asn1_objects = (asn1_tree *)(malloc(sizeof(asn1_tree) * asn1_object_count));
    asn1_tree cms;
    asn1_tree *cms_ptr = &cms;
    der_decode(input, input_length, cms_ptr, asn1_objects, asn1_object_count);

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

    n = get_hex_string(n_ptr->data, n_ptr->length);
    e = get_hex_string(e_ptr->data, e_ptr->length);
    d = get_hex_string(d_ptr->data, d_ptr->length);
    p = get_hex_string(p_ptr->data, p_ptr->length);
    q = get_hex_string(q_ptr->data, q_ptr->length);
}