
#include <cstdint>
#include <WiFiClientSecure.h>

namespace at_secondary_connection
{
    struct connection
    {
        WiFiClientSecure client;
    };
    bool connect(connection &conn, const std::string &host, const std::uint16_t &port);
    std::string execute_command(connection &conn, const std::string &data);
}
