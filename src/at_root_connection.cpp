
#include <iostream>
#include <string>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "at_root_connection.h"

bool at_root_connection::init_wifi(const std::string &ssid, const std::string &password)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin((char *)ssid.c_str(), (char *)password.c_str());
    std::cout << "Attempting to connect to " << ssid << "..." << std::endl;
    while (WiFi.status() != WL_CONNECTED)
    {
        std::cout << ".";
        delay(100);
    }
    std::cout << std::endl
              << "Connected!" << std::endl;
    std::cout << "IP address: " << WiFi.localIP() << std::endl;
    return WiFi.isConnected();
};

bool at_root_connection::connect(connection &conn, const std::string &host, const std::uint32_t &port)
{
    WiFiClientSecure client;
    client.setCACert(at_root_connection::root_ca);
    client.setTimeout(10000);
    if (!client.connect((char *) host.c_str(), port))
    {
        std::cout << "Connection failed!" << std::endl;
    }
    else
    {
        std::cout << "Connected to server!" << std::endl;
    }
    conn.client = client;
    return client.connected();
};

bool at_root_connection::send(connection &conn, const std::string &data){
    WiFiClientSecure client = conn.client;
    client.print((const char *) data.c_str());
    client.print("\n");
    unsigned char status[262] = {0};
    client.readBytesUntil('\r', status, 262);
    // status[0] = 32;
    std::cout << status << std::endl;
    return true;
};

void at_root_connection::disconnect(connection &conn){};
