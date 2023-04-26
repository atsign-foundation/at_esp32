#pragma once

#include <string>
#include "at_sign.h"

struct Metadata
{
    std::uint32_t *ttl = nullptr;
    std::uint32_t *ttb = nullptr;
    std::uint32_t *ttr = nullptr;
    bool *ccd = nullptr;
    // OffsetDateTime createdBy;
    // OffsetDateTime updatedBy;
    // OffsetDateTime availableAt;
    // OffsetDateTime expiresAt;
    // OffsetDateTime refreshAt;
    // OffsetDateTime createdAt;
    // OffsetDateTime updatedAt;
    std::string *status = nullptr;
    std::uint32_t *version = nullptr;
    std::string *data_signature = nullptr;
    std::string *shared_key_status = nullptr;
    bool *is_public = nullptr;
    bool *is_encrypted = nullptr;
    bool *is_hidden = nullptr;
    bool *namespace_aware = nullptr;
    bool *is_binary = nullptr;
    bool *is_cached = nullptr;
    std::string *shared_key_enc = nullptr;
    std::string *pub_key_cs = nullptr;
    std::string *encoding = nullptr;

    std::string to_string()
    {
        std::string s;
        if (ttl != nullptr)
        {
            s += ":ttl:" + *ttl;
        }
        if (ttb != nullptr)
        {
            s += ":ttb:" + *ttb;
        }
        if (ttr != nullptr)
        {
            s += ":ttr:" + *ttr;
        }
        if (ccd != nullptr)
        {
            s += ":ccd:" + *ccd;
        }
        if (data_signature != nullptr && data_signature->empty())
        {
            s += ":dataSignature:" + *data_signature;
        }
        if (shared_key_status != nullptr && shared_key_status->empty())
        {
            s += ":sharedKeyStatus:" + *shared_key_status;
        }
        if (shared_key_enc != nullptr && shared_key_enc->empty())
        {
            s += ":sharedKeyEnc:" + *shared_key_enc;
        }
        if (pub_key_cs != nullptr && pub_key_cs->empty())
        {
            s += ":pubKeyCS:" + *pub_key_cs;
        }
        if (is_binary != nullptr)
        {
            s += ":isBinary:" + *is_binary;
        }
        if (is_encrypted != nullptr)
        {
            s += ":isEncrypted:" + *is_encrypted;
        }
        if (encoding != nullptr && encoding->empty())
        {
            s += ":encoding:" + *encoding;
        }
        return s;
    };
};

class AtKey
{

public:
    const std::string key;
    std::string namespace_str;
    const AtSign *shared_by; // the atSign that this key is sharedBy (creator)
    const AtSign *shared_with; // the atSign that this key is sharedWith (could be nullptr)
    Metadata *metadata;
    AtKey(const std::string &key_, const AtSign *shared_by_, const AtSign *shared_with_ = nullptr) : key(key_), shared_by(shared_by_), shared_with(shared_with_) {
        metadata = new Metadata();
    };
    ~AtKey() = default;
    // AtKey(const std::string &key_, const AtSign *shared_by_) : key(key_), shared_by(shared_by_) {};

    std::string to_string()
    {
        std::string s;
        if (metadata->is_public)
        {
            s += "public:";
        }
        if (shared_with != nullptr)
        {
            s += shared_with->get_value() + ":";
        }
        s += key;
        if (!namespace_str.empty())
        {
            s += "." + namespace_str;
        }
        if (shared_by != nullptr)
        {
            s += shared_by->get_value();
        }
        return s;
    };
};

class SelfKey : AtKey
{
public:
    SelfKey(const std::string &key_, const AtSign *shared_by_) : AtKey(key_, shared_by_) {};
};

class PublicKey : AtKey
{
public:
    PublicKey(const std::string &key_, const AtSign *shared_by_) : AtKey(key_, shared_by_) {};
};

class SharedKey : AtKey
{
public:
    SharedKey(const std::string &key_, const AtSign *shared_by_, const AtSign *shared_with_) : AtKey(key_, shared_by_, shared_with_) {};
};
