
#include <iostream>
#include "rsa_2048.h"

void init_rsa_public_key_example()
{
    const auto pkam_public_base64 = std::string{"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuO3DH9M/x6sLMDsBNLgNv7W6+qELN3n04JAfE3uI5wbo8pNcEK1gP6a7rOPiQ165tMGhfXdYoz/rbE0TxT6mSWpQSI8R2ePdpTfXCntt54mbFoOe/eTCGULB6Lr31ozrE0uKb+YGjfcLG4zKbqE5Plvk/G4P+sWiqMAtS2E+8wz1uuinPBGXCoR+OhLok2KRpxhTorxXFASQnPWTjKt3cJeIDnMMqFffdFdtLOZlOaUtFbleUtQaomHVJO4bx+mMsVoXT9YhxwZT6+N/QoLFVRmCWvKg2K3biVV+jAAlhwg5BVUEyMmKmjrm1JPPRpLd+7Hg6ozl68tpEeFPn7pvtQIDAQAB"};
    rsa_2048::public_key pkam_public;
    rsa_2048::populate(pkam_public_base64, pkam_public);

    // print n e
    std::cout << "n: " << pkam_public.n << std::endl;
    std::cout << "e: " << pkam_public.e << std::endl;
}

void init_rsa_private_key_example()
{
    const auto pkam_private_base64 = std::string{"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC47cMf0z/HqwswOwE0uA2/tbr6oQs3efTgkB8Te4jnBujyk1wQrWA/prus4+JDXrm0waF9d1ijP+tsTRPFPqZJalBIjxHZ492lN9cKe23niZsWg5795MIZQsHouvfWjOsTS4pv5gaN9wsbjMpuoTk+W+T8bg/6xaKowC1LYT7zDPW66Kc8EZcKhH46EuiTYpGnGFOivFcUBJCc9ZOMq3dwl4gOcwyoV990V20s5mU5pS0VuV5S1BqiYdUk7hvH6YyxWhdP1iHHBlPr439CgsVVGYJa8qDYrduJVX6MACWHCDkFVQTIyYqaOubUk89Gkt37seDqjOXry2kR4U+fum+1AgMBAAECggEAY6Q4rr00cHFI5gPk8nL5dYKF7OU5FfswZo9BL04wxcqDWbDsuk+wvJsqJE3lbEdt6GcsjF3x9IRMZV5ieLT5BDW0bGQqSiztEEi2JX+8CDWsysTAtiy8KMA/mxai04e6Yfsh7IkUnwmtgnqp2FImdeMtzpW/Jm+25RYnUaZkNLCqZ9hv8nmYNIZ9a3Q4VEOHBlqxQOilR0i74Su3stWD0GiZIINrDM+kRvQlIVHt9RUaur190HPRRlfuZpA5Q1rNiPFh9Uwoqs9JvnwLDDekxSYykbTpJpWjZbe4V/6558rz2Xz7vbVdcHiP0SE4FW8a+XXn1r3wQKWEWYu2q0LiAQKBgQD4l0TXqs7ApK7ckKSJpl8gV2Otj69DMRQ6dB78AGAOYQG/cZcdpqvd2m07M80/Xo3bvhcJjsoZN+vlgOwEY7ytLzOOjciB2bYc92qpH4Gq4GMJW7uFARRBevZtsf055YGM/OozSPiin/KU70alkn90tO4Py6dhcry/e9TJbRqm6QKBgQC+cMFy7LYsthy42L66RJ6PvwxJFCOm2iM8OI71g518gUkoeWPLoGQU7KyDtad6eyQxyv01dk+W+aWxA7ayN9X8mIuaOYqQzBTK3Tssm9nj2IEs2OIBi0jMFV3Nzw6BkI4+RRONcu7Af0jl1aJ31eTk+wOavljhoHQfGG0laGBa7QKBgQD4SZXf1mE0dgeUkv9T4JDoa4BKTNWfRbjPfUWpKvLFycwGG3z0h5DnQA+TbvTUEyuay6yUxkJCl+EL1A1ngPpk+10CR8h5MSq8mb21d5t6QS2Jnk6X1HEXyamx/HFQT1Nqrv14Ba0YOKsAaFBmdQDKXx/bNOxT31Z35kWsfUV+aQKBgQCZoo997pd9dKGxQjKERO2CXAdGQXgNmHfKknpKeRapJgfmHiAzWz7CXrlCPF9TgVqOzQr/gWXuD5LrPmq6Vi9M66fcEMXH0MyJaHbfow/iL3zuuD2EL2DYO/iEG6HBRuRqOgHvICSaqVUfDf1XHfjd/d9HjH5Z778egu8yuYTadQKBgFRpfWQmWFtNkmeb0dmxb2I7wULayHrFcacA8N4jd2YstUSV4N8aW+w519c2+WCvP/YZajAslX6csJkfWXuOcQLDN7XkD1NIOOMc78p/PTGNnbYT8/3bM1sY6FHg50oQPS/6kNSv0DE8fc9BKWe9DnBH9zO9R5jKfQSbO7UI+2CU"};
    rsa_2048::private_key pkam_private;
    rsa_2048::populate(pkam_private_base64, pkam_private);

    // print n e d p q
    std::cout << "n: " << pkam_private.n << std::endl;
    std::cout << "e: " << pkam_private.e << std::endl;
    std::cout << "d: " << pkam_private.d << std::endl;
    std::cout << "p: " << pkam_private.p << std::endl;
    std::cout << "q: " << pkam_private.q << std::endl;    
}


void rsa_2048_sha_256_sign_example()
{
    const auto pkam_private_base64 = std::string{"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC47cMf0z/HqwswOwE0uA2/tbr6oQs3efTgkB8Te4jnBujyk1wQrWA/prus4+JDXrm0waF9d1ijP+tsTRPFPqZJalBIjxHZ492lN9cKe23niZsWg5795MIZQsHouvfWjOsTS4pv5gaN9wsbjMpuoTk+W+T8bg/6xaKowC1LYT7zDPW66Kc8EZcKhH46EuiTYpGnGFOivFcUBJCc9ZOMq3dwl4gOcwyoV990V20s5mU5pS0VuV5S1BqiYdUk7hvH6YyxWhdP1iHHBlPr439CgsVVGYJa8qDYrduJVX6MACWHCDkFVQTIyYqaOubUk89Gkt37seDqjOXry2kR4U+fum+1AgMBAAECggEAY6Q4rr00cHFI5gPk8nL5dYKF7OU5FfswZo9BL04wxcqDWbDsuk+wvJsqJE3lbEdt6GcsjF3x9IRMZV5ieLT5BDW0bGQqSiztEEi2JX+8CDWsysTAtiy8KMA/mxai04e6Yfsh7IkUnwmtgnqp2FImdeMtzpW/Jm+25RYnUaZkNLCqZ9hv8nmYNIZ9a3Q4VEOHBlqxQOilR0i74Su3stWD0GiZIINrDM+kRvQlIVHt9RUaur190HPRRlfuZpA5Q1rNiPFh9Uwoqs9JvnwLDDekxSYykbTpJpWjZbe4V/6558rz2Xz7vbVdcHiP0SE4FW8a+XXn1r3wQKWEWYu2q0LiAQKBgQD4l0TXqs7ApK7ckKSJpl8gV2Otj69DMRQ6dB78AGAOYQG/cZcdpqvd2m07M80/Xo3bvhcJjsoZN+vlgOwEY7ytLzOOjciB2bYc92qpH4Gq4GMJW7uFARRBevZtsf055YGM/OozSPiin/KU70alkn90tO4Py6dhcry/e9TJbRqm6QKBgQC+cMFy7LYsthy42L66RJ6PvwxJFCOm2iM8OI71g518gUkoeWPLoGQU7KyDtad6eyQxyv01dk+W+aWxA7ayN9X8mIuaOYqQzBTK3Tssm9nj2IEs2OIBi0jMFV3Nzw6BkI4+RRONcu7Af0jl1aJ31eTk+wOavljhoHQfGG0laGBa7QKBgQD4SZXf1mE0dgeUkv9T4JDoa4BKTNWfRbjPfUWpKvLFycwGG3z0h5DnQA+TbvTUEyuay6yUxkJCl+EL1A1ngPpk+10CR8h5MSq8mb21d5t6QS2Jnk6X1HEXyamx/HFQT1Nqrv14Ba0YOKsAaFBmdQDKXx/bNOxT31Z35kWsfUV+aQKBgQCZoo997pd9dKGxQjKERO2CXAdGQXgNmHfKknpKeRapJgfmHiAzWz7CXrlCPF9TgVqOzQr/gWXuD5LrPmq6Vi9M66fcEMXH0MyJaHbfow/iL3zuuD2EL2DYO/iEG6HBRuRqOgHvICSaqVUfDf1XHfjd/d9HjH5Z778egu8yuYTadQKBgFRpfWQmWFtNkmeb0dmxb2I7wULayHrFcacA8N4jd2YstUSV4N8aW+w519c2+WCvP/YZajAslX6csJkfWXuOcQLDN7XkD1NIOOMc78p/PTGNnbYT8/3bM1sY6FHg50oQPS/6kNSv0DE8fc9BKWe9DnBH9zO9R5jKfQSbO7UI+2CU"};
    rsa_2048::private_key pkam_private;
    rsa_2048::populate(pkam_private_base64, pkam_private);

    const auto challenge = std::string{"_fbe0809b-c7dd-4bc0-9a27-ab9e5812bc4c@22easy:ce4ab3f9-944d-495f-b385-8f499bef8fab"};

    const auto signature = rsa_2048::sign(challenge, pkam_private);

    std::cout << "signature: " << signature << std::endl;
};

void rsa_2048_sha_256_verify_example()
{
    // WIP
}

void rsa_2048_encrypt_example()
{
    // WIP
}

void rsa_2048_decrypt_example()
{
    // WIP
}

void loop() {};