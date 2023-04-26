
#include "at_client.h"
#include "constants.h"
#include "at_root_connection.h"
#include "at_secondary_connection.h"
#include "rsa_2048.h"
#include "aes_ctr.h"

std::string AtClient::execute_command(const std::string &command)
{
    const auto raw = at_secondary_connection::execute_command(secondary_client, command);
    // remove "data:"
    auto data = raw.substr(5);
    return data;
};

bool AtClient::pkam_authenticate(std::string ssid, std::string password)
{
    const std::string private_key = keys["pkam_private_key"];
    bool wifi_connected = at_root_connection::init_wifi(ssid, password);
    bool root_connected = at_root_connection::connect(root_client, ROOT_DOMAIN, ROOT_PORT);
    if (root_connected)
    {
        std::string res = at_root_connection::send(root_client, at_sign.without_prefix());
        std::cout << "res: \"" << res << "\"" << std::endl;
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


std::string AtClient::get_aes_key_shared_by_them(const AtSign *at_sign_shared_by)
{
    // shared key (lookup:key@them)
    const auto aes_key_base64_encrypted = execute_command("lookup:shared_key" + at_sign_shared_by->get_value());
    std::cout << "aes_key_base64_encrypted: " << aes_key_base64_encrypted << std::endl;

    rsa_2048::private_key rsa_private_key;
    rsa_2048::populate(keys["encrypt_private_key"], rsa_private_key);

    // decrypt aes_key_base64_encrypted with rsa_public_key
    const auto aes_key_base64 = rsa_2048::decrypt(aes_key_base64_encrypted, rsa_private_key);

    return aes_key_base64;
}

std::string AtClient::get_aes_key_shared_by_me(const AtSign *at_sign_shared_with)
{
    const auto aes_key_base64_encrypted = execute_command("llookup:" + at_sign_shared_with->get_value() + ":shared_key" + at_sign.get_value());

    rsa_2048::private_key rsa_private_key;
    rsa_2048::populate(keys["encrypt_private_key"], rsa_private_key);

    // decrypt aes_key_base64_encrypted with rsa_public_key
    const auto aes_key_base64 = rsa_2048::decrypt(aes_key_base64_encrypted, rsa_private_key);

    return aes_key_base64;
}

void AtClient::create_shared_aes_key_for_them(const std::string &aes_key_decrypted_base64, const AtSign *at_sign_them)
{
    std::cout << "begin creating shared aes key for them: \"" << at_sign_them->get_value() << "\"" << std::endl;
    // get their public key
    const auto their_public_key = execute_command("plookup:publickey" + at_sign_them->get_value());

    std::cout << "their public key: " << their_public_key << std::endl;

    // populate rsa_public_key
    rsa_2048::public_key rsa_public_key;
    rsa_2048::populate(their_public_key, rsa_public_key);

    // encrypt aes_key_base64 with their_public_key
    const auto aes_key_encrypted_base64 = rsa_2048::encrypt(aes_key_decrypted_base64, rsa_public_key);

    // store encrypted aes key
    const auto command = "update:" + at_sign_them->get_value() + ":shared_key" + at_sign.get_value() + " " + aes_key_encrypted_base64;
    std::cout << "command: " << command << std::endl;
    execute_command(command);
}

std::string AtClient::get_ak(const AtKey &at_key)
{
    std::string data;

    if (at_key.shared_by != nullptr && at_key.shared_with != nullptr && strcmp(at_key.shared_with->get_value().c_str(), at_sign.get_value().c_str()) == 0) // if the at key is shared with us, then it's a shared key shared with us shared by some other atSign
    {
        const auto aes_key_base64 = get_aes_key_shared_by_them(at_key.shared_by);

        create_shared_aes_key_for_them(aes_key_base64, at_key.shared_by);

        std::string command;
        if(!at_key.namespace_str.empty())
        {   
            command = "lookup:" + at_key.key + "." + at_key.namespace_str + at_key.shared_by->get_value();
        } else {
            command = "lookup:" + at_key.key + at_key.shared_by->get_value();
        }

        const auto encrypted_data = execute_command(command);
        std::cout << "encrypted_data: \"" << encrypted_data << "\"" << std::endl;

        // decrypt encrypted_data with aes_key_base64
        data = aes_ctr::decrypt(encrypted_data, aes_key_base64);
    }
    else if (at_key.metadata->is_public != nullptr && at_key.shared_by != nullptr && strcmp(at_key.shared_by->get_value().c_str(), at_sign.get_value().c_str()) != 0)
    {
        // public key (plookup:key@them)

        const auto command = "plookup:" + at_key.key + at_key.shared_by->get_value();

        data = execute_command(command);
    }
    else
    {
        // self key (llookup:key@me)
        const auto command = "llookup:" + at_key.key + at_sign.get_value();
        std::cout << "command: \"" << command << "\"" << std::endl;

        const auto encrypted_value = execute_command(command);

        data = aes_ctr::decrypt(encrypted_value, keys["self_encryption_key"]);
    }

    return data;
};

void AtClient::put_ak(const AtKey &at_key, const std::string &value)
{
    std::string command;

    if (at_key.shared_with != nullptr)
    {
        // shared key (update:@alice:phone@bob 444121212[encrypted])

        // 1. find shared key shared with me shared by them 'shared_key'
        // const auto shared_key = AtKey(std::string{"shared_key"}, at_key.shared_with, at_key.shared_by);
        // const auto aes_key_base64_encrypted = execute_command("lookup:shared_key" + at_key.shared_with->get_value());
        const auto aes_key_base64 = get_aes_key_shared_by_them(at_key.shared_with);
        std::cout << "aes_key_base64: \"" << aes_key_base64 << "\"" << std::endl;

        create_shared_aes_key_for_them(aes_key_base64, at_key.shared_with);

        // 2. encrypt value with aes_key_base64
        const auto encrypted_value = aes_ctr::encrypt(value, aes_key_base64);
        std::cout << "encrypted_value: \"" << encrypted_value << "\"" << std::endl;

        // 3. update:@alice:phone@bob 444121212[encrypted]
        command = "update:" + at_key.shared_with->get_value() + ":" + at_key.key;
        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;

        }
        command = command + at_key.shared_by->get_value() + " " + encrypted_value;
    }
    else if (at_key.metadata->is_public != nullptr && *at_key.metadata->is_public)
    {
        // public key (update:public:phone@bob 444121212)
        command = "update:public:" + at_key.key;
        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;
        }
        command = command + at_key.shared_by->get_value() + " " + value;
    }
    else
    {
        // self key (update:phone@bob 444121212)
        command = "update:" + at_key.key;
        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;
        }
        // encrypt value with our aes self key
        const auto encrypted_value = aes_ctr::encrypt(value, keys["self_encryption_key"]);

        command = command + at_key.shared_by->get_value() + " " + encrypted_value;
    }

    std::cout << "command: \"" << command << "\"" << std::endl;
    const auto response = execute_command(command);
    std::cout << "response: \"" << response << "\"" << std::endl;
};

void AtClient::delete_ak(const AtKey &at_key)
{
    std::string command;
    if (at_key.metadata->is_public != nullptr && *at_key.metadata->is_public)
    {
        // public key (delete:public:phone@bob)
        command = "delete:public:" + at_key.key;
        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;
        }
        command = command + at_key.shared_by->get_value();
    }
    else if (at_key.shared_with != nullptr)
    {
        // shared key (delete:@alice:phone@bob)
        command = "delete:" + at_key.shared_with->get_value() + ":" + at_key.key ;

        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;
        }
        
        command = command + at_key.shared_by->get_value();
    }
    else
    {
        // self key (delete:phone@bob)
        command = "delete:" + at_key.key;
        if(!at_key.namespace_str.empty())
        {
            command = command + "." + at_key.namespace_str;
        }
        command = command + at_key.shared_by->get_value();
    }
    std::string response = execute_command(command);
    std::cout << "response: \"" << response << "\"" << std::endl;
};
