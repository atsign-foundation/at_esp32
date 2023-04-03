
#pragma once

#include <iostream>
#include <string>
#include <map>
#include "at_sign.h"
#include "at_root_connection.h"
#include "at_secondary_connection.h"
#include "at_key.h"
#include "keys_reader.h"

/// @brief AtClient - interact with atServer and its keys
class AtClient
{
protected:
    /// @brief atSign of the device
    AtSign at_sign;

    /// @brief keys of the device
    /// @details keys are stored in a map with the following keys:
    ///    - pkam_private_key
    ///    - pkam_public_key
    ///    - encrypt_private_key
    ///    - encrypt_public_key
    ///    - self_encryption_key
    std::map<std::string, std::string> keys; // [pkam_private_key, pkam_public_key, encrypt_private_key, encrypt_public_key, self_encryption_key]

    /// @brief root connection to atDirectory
    WiFiClientSecure root_client;

    /// @brief secondary connection to atServer belonging to at_sign
    WiFiClientSecure secondary_client;

    /// @brief get the base64 encoded decrypted aes key shared by us, shared with at_sign_shared_with
    std::string get_aes_key_shared_by_me(const AtSign *at_sign_shared_with);

    /// @brief get the base64 encoded decrypted aes key shared by at_sign_shared_by, shared with us
    std::string get_aes_key_shared_by_them(const AtSign *at_sign_shared_by);

    /// @brief create a `@them:shared_key@me` AtKey in our atServer that stores the base64 encoded (encrypted with @them's public encrypt rsa key)
    void create_shared_aes_key_for_them(const std::string &aes_key_decrypted_base64, const AtSign *at_sign_them);

public:
    /// @brief instantiates an AtClient object
    /// @param at_sign_ the atSign of the ESP32
    /// @param keys_ a map of the keys of the atSign
    AtClient(const AtSign &at_sign_, std::map<std::string, std::string> keys_) : at_sign(at_sign_), keys(keys_) {};

    /// @brief destructor
    ~AtClient() = default;

    /// @brief executes a command on the atServer. secondary_client connection should be established and wifi should be connected before calling this function
    std::string execute_command(const std::string &command);

    /// @brief connects to wifi, finds secondary adderss via the root_server, pkam authenticates the secondary_client connection
    bool pkam_authenticate(std::string ssid, std::string password);

    /// @brief puts an AtKey and its value in the atServer. Must be pkam_authenticated for this to work
    void put_ak(const AtKey &at_key, const std::string &value);

    /// @brief gets the value of an AtKey from the atServer. Must be pkam_authenticated for this to work for any keys that belong to the atSign.
    std::string get_ak(const AtKey &at_key);

    /// @brief deletes an AtKey from the atServer. Must be pkam_authenticated for this to work
    void delete_ak(const AtKey &at_key);
};
