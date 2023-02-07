
#pragma once

#include <iostream>
#include <string>
#include <map>
#include "at_sign.h"
#include "at_root_connection.h"
#include "at_secondary_connection.h"
#include "at_key.h"

class AtClient
{
protected:
    AtSign at_sign;
    std::map<std::string, std::string> keys; // [pkam_private_key, pkam_public_key, encrypt_private_key, encrypt_public_key, self_encryption_key]
    WiFiClientSecure root_client;
    WiFiClientSecure secondary_client;

public:
    AtClient(AtSign at_sign, std::map<std::string, std::string> keys) : at_sign(at_sign), keys(keys) {};
    ~AtClient() = default;

    std::string execute_command(const std::string &command);
    bool pkam_authenticate(const std::string &private_key);
    void put_ak(const AtKey &at_key, const std::string &value);
    std::string get_ak(const AtKey &at_key);
    void delete_ak(const AtKey &at_key);
};
