
#pragma once

#include <WiFiClientSecure.h>
#include "constants.h"

namespace at_root_connection
{
    struct connection
    {
        WiFiClientSecure *client;
    };
    bool init_wifi(const std::string &ssid, const std::string &password);
    bool connect(WiFiClientSecure &client, const std::string &host, const std::uint16_t &port);
    std::string send(WiFiClientSecure &client, const std::string &data);
    void disconnect(connection &conn);
}
