
#pragma once

#include <cstdint>
#include <WiFiClientSecure.h>

namespace at_secondary_connection
{
    bool connect(WiFiClientSecure &secondary_client, const std::string &host, const std::uint16_t &port);
    std::string execute_command(WiFiClientSecure &secondary_client, const std::string &data);
    bool pkam_authenticate(WiFiClientSecure &secondary_client, const std::string &pkam_private_key_base64, const std::string &at_sign);
}
