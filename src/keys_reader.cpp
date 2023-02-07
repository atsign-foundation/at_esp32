
#include "keys_reader.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <iostream>
#include <SPIFFS.h>
#include <filesystem>
#include <vector>
#include "aes_ctr.h"

std::map<std::string, std::string> keys_reader::read_keys(const AtSign &at_sign)
{
    if (!SPIFFS.begin(true))
    {
        std::cout << "Error occurred while trying to begin SPIFFS.";
    }
    std::string path = "/keys/" + at_sign.get_value() + "_key.atKeys";
    std::cout << path << std::endl;
    File file = SPIFFS.open(path.c_str(), "r");
    
    // Serial.begin(115200);
    String line = file.readStringUntil('\n');
    // Serial.println(line);
    // Serial.end();

    DynamicJsonDocument doc(5192*16);
    deserializeJson(doc, line.c_str());

    const char* aesPkamPublicKey = doc["aesPkamPublicKey"]; // encrypted
    const char* aesPkamPrivateKey = doc["aesPkamPrivateKey"]; // encrypted
    const char* aesEncryptPublicKey = doc["aesEncryptPublicKey"]; // encrypted
    const char* aesEncryptPrivateKey = doc["aesEncryptPrivateKey"]; // encrypted
    const char* self_encryption_key = doc["selfEncryptionKey"];

    // std::cout << "[1]: " << aesPkamPublicKey << std::endl << std::endl;
    // std::cout << "[2]: " << aesPkamPrivateKey << std::endl << std::endl;
    // std::cout << "[3]: " << aesEncryptPublicKey << std::endl << std::endl;
    // std::cout << "[4]: " << aesEncryptPrivateKey << std::endl << std::endl;
    // std::cout << "[5]: " << self_encryption_key << std::endl << std::endl;

    const std::string pkam_public_key = aes_ctr::decrypt(aesPkamPublicKey, self_encryption_key);
    const std::string pkam_private_key = aes_ctr::decrypt(aesPkamPrivateKey, self_encryption_key);
    const std::string encrypt_public_key = aes_ctr::decrypt(aesEncryptPublicKey, self_encryption_key);
    const std::string encrypt_private_key = aes_ctr::decrypt(aesEncryptPrivateKey, self_encryption_key);

    std::map<std::string, std::string> keys;
    keys.insert(std::pair<std::string, std::string>{"self_encryption_key", self_encryption_key});
    keys.insert(std::pair<std::string, std::string>{"pkam_public_key", pkam_public_key});
    keys.insert(std::pair<std::string, std::string>{"pkam_private_key", pkam_private_key});
    keys.insert(std::pair<std::string, std::string>{"encrypt_public_key", encrypt_public_key});
    keys.insert(std::pair<std::string, std::string>{"encrypt_private_key", encrypt_private_key});

    file.close();
    SPIFFS.end();

    return keys;
}