
#include "at_client.h"

// App - @22easy
// ESP32 - @soccer0
// reading data from @22easy's atServer as @soccer0 (ESP32)
void read_data()
{
    // 1. initialize atSigns
    const auto esp = AtSign("@soccer0");
    const auto java = AtSign("@22easy");

    // 2. read @soccer0's keys (@soccer0 is the ESP32)
    std::map<std::string, std::string> keys = keys_reader::read_keys(esp);

    // 3. initialize AtClient object
    AtClient *at_client = new AtClient(esp, keys);

    // 4. pkam authenticate into @soccer0's atServer
    at_client->pkam_authenticate("ssid", "password");

    // 5. create AtKey object. This AtKey is sharedBy(aka createdBy) the java app (@22easy) and the ESP32 (@soccer0) is whom it's sharedWith
    const auto at_key = AtKey("test_esp", &java, &esp);

    // 6. use `get_ak` to get the value of the AtKey
    std::string data;
    for (int i = 0; i < 500; i++)
    {
        data = at_client->get_ak(at_key);
        std::cout << "data: " << data << std::endl;
    }
}

// App - @tastelessbanana
// ESP32 - @soccer0
// ESP32 is sending encrypted data to App
void send_data()
{
    // 1. intiialize AtSign objects
    const AtSign esp = AtSign("@soccer0");
    const auto java = AtSign("@tastelessbanana");

    // 2. read @soccer0's keys (@soccer0 is the ESP32)
    std::map<std::string, std::string> keys = keys_reader::read_keys(esp);

    // 3. initialize AtClient object
    AtClient *at_client = new AtClient(esp, keys);

    // 4. pkam authenticate into @soccer0's atServer
    at_client->pkam_authenticate("ssid", "password");

    // 5. create AtKey object. This AtKey is sharedBy(aka createdBy) the ESP32 (@soccer0) and the java app (@tastelessbanana) is whom it's sharedWith
    const auto at_key = AtKey("test_esp32", &esp, &java);

    // 6. use `put_ak` to put the value of the AtKey
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
