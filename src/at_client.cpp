
#include "at_client.h"
#include "constants.h"
#include "at_root_connection.h"
#include "at_secondary_connection.h"
#include "rsa_2048.h"

std::string AtClient::execute_command(const std::string &command)
{
    const auto raw = at_secondary_connection::execute_command(secondary_client, command);
    // remove "data:"
    auto data = raw.substr(5);
    return data;
};

bool AtClient::pkam_authenticate(const std::string &private_key)
{
    bool wifi_connected = at_root_connection::init_wifi(WIFI_SSID, WIFI_PASSWORD);
    bool root_connected = at_root_connection::connect(root_client, "root.atsign.org", 64);
    if (root_connected)
    {
        std::string res = at_root_connection::send(root_client, at_sign.without_prefix());
        std::string host = res.substr(0, res.find(":"));
        // trim
        host.erase(std::find_if(host.rbegin(), host.rend(), [](unsigned char ch)
                                { return !std::isspace(ch); })
                       .base(),
                   host.end());
        host.erase(host.begin(), std::find_if(host.begin(), host.end(), [](unsigned char ch)
                                              { return !std::isspace(ch); }));
        std::string port_str = res.substr(res.find(":") + 1);
        // convert port to int
        std::uint16_t port_int = std::stoi(port_str);
        bool secondary_connected = at_secondary_connection::connect(secondary_client, host, port_int);
        std::cout << "first: \"" << at_secondary_connection::execute_command(secondary_client, "scan") << "\"" << std::endl; // remove leading '@'
        // std::cout << "2: \"" << at_secondary_connection::execute_command(secondary_client, "scan") << "\"" << std::endl;
        // std::cout << "3: \"" << at_secondary_connection::execute_command(secondary_client, "scan") << "\"" << std::endl;
        // std::cout << "4: \"" << at_secondary_connection::execute_command(secondary_client, "scan") << "\"" << std::endl;

        std::cout << "Secondary connected: " << secondary_connected << std::endl;

        // std::string t = execute_command("scan");
        // std::cout << "scan unauthenticated: " << t << std::endl;

        std::string challenge = execute_command("from:" + at_sign.get_value());
        std::cout << "challenge: \"" << challenge << "\"" << std::endl;

        rsa_2048::private_key pkam_private_key;
        rsa_2048::populate(keys["pkam_private_key"], pkam_private_key);

        std::string digest = rsa_2048::sign(challenge, pkam_private_key);
        std::string command = "pkam:" + digest;
        std::cout << "pkam command: \"" << command << "\"" << std::endl;

        std::string response = execute_command(command);
        std::cout << "response: " << response << std::endl;
        
        bool authenticated = response.find_first_of("success") != std::string::npos;
        std::cout << "authenticated: " << authenticated << std::endl;

        // std::string scan_data = at_secondary_connection::execute_command(secondary_client, "scan");
        // std::cout << "scan authenticated : " << scan_data << std::endl;
        return authenticated;
    }
    return false;
};