
#include "at_client.h"

void read_data()
{
    const AtSign esp = AtSign("@soccer0");
    std::map<std::string, std::string> keys = keys_reader::read_keys(esp);
    AtClient *at_client = new AtClient(esp, keys);
    at_client->pkam_authenticate();

    const auto java = AtSign("@22easy");
    const auto at_key = AtKey("test_esp", &java, &esp);
    std::string data;
    for (int i = 0; i < 500; i++)
    {
        data = at_client->get_ak(at_key);
        std::cout << "data: " << data << std::endl;
    }
}

void send_data()
{
    const AtSign esp = AtSign("@soccer0");
    std::map<std::string, std::string> keys = keys_reader::read_keys(esp);
    AtClient *at_client = new AtClient(esp, keys);
    at_client->pkam_authenticate();

    const auto java = AtSign("@tastelessbanana");
    const auto at_key = AtKey("test_esp32", &esp, &java);
    std::string data;
    std::string value = "0";
    for (int i = 0; i < 500; i++)
    {
        if(value == "0")
        {
            value = "1";
        }
        else
        {
            value = "0";
        }
        at_client->put_ak(at_key, value);
    }
}