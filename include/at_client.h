
#pragma once

#include <iostream>
#include <string>
#include <map>
#include "at_sign.h"
#include "at_root_connection.h"
#include "at_secondary_connection.h"
#include "at_key.h"
#include "keys_reader.h"

class AtClient
{
protected:
    AtSign at_sign;
    std::map<std::string, std::string> keys; // [pkam_private_key, pkam_public_key, encrypt_private_key, encrypt_public_key, self_encryption_key]
    WiFiClientSecure root_client;
    WiFiClientSecure secondary_client;
    std::string get_aes_key_shared_by_me(const AtSign *at_sign_shared_with);
    std::string get_aes_key_shared_by_them(const AtSign *at_sign_shared_by);
    void create_shared_aes_key_for_them(const std::string &aes_key_decrypted_base64, const AtSign *at_sign_them);

public:
    AtClient(const AtSign &at_sign_, std::map<std::string, std::string> keys_) : at_sign(at_sign_), keys(keys_) {};
    ~AtClient() = default;

    std::string execute_command(const std::string &command);
    bool pkam_authenticate(std::string ssid, std::string password);
    void put_ak(const AtKey &at_key, const std::string &value);
    std::string get_ak(const AtKey &at_key);
    void delete_ak(const AtKey &at_key);
};
