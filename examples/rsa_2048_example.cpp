
#include <iostream>
#include "rsa_2048.h"

// initialize an rsa public key object given a base64 encoded string
void init_rsa_public_key_example()
{
    // 1. our rsa public key in base64 stored in a std::string
    const auto pkam_public_base64 = std::string{"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuO3DH9M/x6sLMDsBNLgNv7W6+qELN3n04JAfE3uI5wbo8pNcEK1gP6a7rOPiQ165tMGhfXdYoz/rbE0TxT6mSWpQSI8R2ePdpTfXCntt54mbFoOe/eTCGULB6Lr31ozrE0uKb+YGjfcLG4zKbqE5Plvk/G4P+sWiqMAtS2E+8wz1uuinPBGXCoR+OhLok2KRpxhTorxXFASQnPWTjKt3cJeIDnMMqFffdFdtLOZlOaUtFbleUtQaomHVJO4bx+mMsVoXT9YhxwZT6+N/QoLFVRmCWvKg2K3biVV+jAAlhwg5BVUEyMmKmjrm1JPPRpLd+7Hg6ozl68tpEeFPn7pvtQIDAQAB"};

    // 2. initialize rsa_2048::public_key struct
    rsa_2048::public_key pkam_public;

    // 3. populate the rsa_2048::public_key struct with the base64 encoded string
    rsa_2048::populate(pkam_public_base64, pkam_public);

    // 4. utilize n and e, where n and e are std::strings holding the modulus and exponent respectively in hex
    std::cout << "n: " << pkam_public.n << std::endl;
    std::cout << "e: " << pkam_public.e << std::endl;
}

// initialize an rsa private key object given a base64 encoded string
void init_rsa_private_key_example()
{
    // 1. our rsa private key in base64 stored in a std::string
    const auto pkam_private_base64 = std::string{"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC47cMf0z/HqwswOwE0uA2/tbr6oQs3efTgkB8Te4jnBujyk1wQrWA/prus4+JDXrm0waF9d1ijP+tsTRPFPqZJalBIjxHZ492lN9cKe23niZsWg5795MIZQsHouvfWjOsTS4pv5gaN9wsbjMpuoTk+W+T8bg/6xaKowC1LYT7zDPW66Kc8EZcKhH46EuiTYpGnGFOivFcUBJCc9ZOMq3dwl4gOcwyoV990V20s5mU5pS0VuV5S1BqiYdUk7hvH6YyxWhdP1iHHBlPr439CgsVVGYJa8qDYrduJVX6MACWHCDkFVQTIyYqaOubUk89Gkt37seDqjOXry2kR4U+fum+1AgMBAAECggEAY6Q4rr00cHFI5gPk8nL5dYKF7OU5FfswZo9BL04wxcqDWbDsuk+wvJsqJE3lbEdt6GcsjF3x9IRMZV5ieLT5BDW0bGQqSiztEEi2JX+8CDWsysTAtiy8KMA/mxai04e6Yfsh7IkUnwmtgnqp2FImdeMtzpW/Jm+25RYnUaZkNLCqZ9hv8nmYNIZ9a3Q4VEOHBlqxQOilR0i74Su3stWD0GiZIINrDM+kRvQlIVHt9RUaur190HPRRlfuZpA5Q1rNiPFh9Uwoqs9JvnwLDDekxSYykbTpJpWjZbe4V/6558rz2Xz7vbVdcHiP0SE4FW8a+XXn1r3wQKWEWYu2q0LiAQKBgQD4l0TXqs7ApK7ckKSJpl8gV2Otj69DMRQ6dB78AGAOYQG/cZcdpqvd2m07M80/Xo3bvhcJjsoZN+vlgOwEY7ytLzOOjciB2bYc92qpH4Gq4GMJW7uFARRBevZtsf055YGM/OozSPiin/KU70alkn90tO4Py6dhcry/e9TJbRqm6QKBgQC+cMFy7LYsthy42L66RJ6PvwxJFCOm2iM8OI71g518gUkoeWPLoGQU7KyDtad6eyQxyv01dk+W+aWxA7ayN9X8mIuaOYqQzBTK3Tssm9nj2IEs2OIBi0jMFV3Nzw6BkI4+RRONcu7Af0jl1aJ31eTk+wOavljhoHQfGG0laGBa7QKBgQD4SZXf1mE0dgeUkv9T4JDoa4BKTNWfRbjPfUWpKvLFycwGG3z0h5DnQA+TbvTUEyuay6yUxkJCl+EL1A1ngPpk+10CR8h5MSq8mb21d5t6QS2Jnk6X1HEXyamx/HFQT1Nqrv14Ba0YOKsAaFBmdQDKXx/bNOxT31Z35kWsfUV+aQKBgQCZoo997pd9dKGxQjKERO2CXAdGQXgNmHfKknpKeRapJgfmHiAzWz7CXrlCPF9TgVqOzQr/gWXuD5LrPmq6Vi9M66fcEMXH0MyJaHbfow/iL3zuuD2EL2DYO/iEG6HBRuRqOgHvICSaqVUfDf1XHfjd/d9HjH5Z778egu8yuYTadQKBgFRpfWQmWFtNkmeb0dmxb2I7wULayHrFcacA8N4jd2YstUSV4N8aW+w519c2+WCvP/YZajAslX6csJkfWXuOcQLDN7XkD1NIOOMc78p/PTGNnbYT8/3bM1sY6FHg50oQPS/6kNSv0DE8fc9BKWe9DnBH9zO9R5jKfQSbO7UI+2CU"};

    // 2. create an rsa_2048::private_key struct
    rsa_2048::private_key pkam_private;

    // 3. populate the struct with the base64 encoded string
    rsa_2048::populate(pkam_private_base64, pkam_private);

    // 4. print n e d p q, where each parameter is an std::string containing the hex representation of the parameter
    std::cout << "n: " << pkam_private.n << std::endl;
    std::cout << "e: " << pkam_private.e << std::endl;
    std::cout << "d: " << pkam_private.d << std::endl;
    std::cout << "p: " << pkam_private.p << std::endl;
    std::cout << "q: " << pkam_private.q << std::endl;    
}

// given an rsa private key encoded in base64, sign a string with the private key
void rsa_2048_sha_256_sign_example()
{
    // 1. create an rsa_2048::private_key struct
    const auto pkam_private_base64 = std::string{"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC47cMf0z/HqwswOwE0uA2/tbr6oQs3efTgkB8Te4jnBujyk1wQrWA/prus4+JDXrm0waF9d1ijP+tsTRPFPqZJalBIjxHZ492lN9cKe23niZsWg5795MIZQsHouvfWjOsTS4pv5gaN9wsbjMpuoTk+W+T8bg/6xaKowC1LYT7zDPW66Kc8EZcKhH46EuiTYpGnGFOivFcUBJCc9ZOMq3dwl4gOcwyoV990V20s5mU5pS0VuV5S1BqiYdUk7hvH6YyxWhdP1iHHBlPr439CgsVVGYJa8qDYrduJVX6MACWHCDkFVQTIyYqaOubUk89Gkt37seDqjOXry2kR4U+fum+1AgMBAAECggEAY6Q4rr00cHFI5gPk8nL5dYKF7OU5FfswZo9BL04wxcqDWbDsuk+wvJsqJE3lbEdt6GcsjF3x9IRMZV5ieLT5BDW0bGQqSiztEEi2JX+8CDWsysTAtiy8KMA/mxai04e6Yfsh7IkUnwmtgnqp2FImdeMtzpW/Jm+25RYnUaZkNLCqZ9hv8nmYNIZ9a3Q4VEOHBlqxQOilR0i74Su3stWD0GiZIINrDM+kRvQlIVHt9RUaur190HPRRlfuZpA5Q1rNiPFh9Uwoqs9JvnwLDDekxSYykbTpJpWjZbe4V/6558rz2Xz7vbVdcHiP0SE4FW8a+XXn1r3wQKWEWYu2q0LiAQKBgQD4l0TXqs7ApK7ckKSJpl8gV2Otj69DMRQ6dB78AGAOYQG/cZcdpqvd2m07M80/Xo3bvhcJjsoZN+vlgOwEY7ytLzOOjciB2bYc92qpH4Gq4GMJW7uFARRBevZtsf055YGM/OozSPiin/KU70alkn90tO4Py6dhcry/e9TJbRqm6QKBgQC+cMFy7LYsthy42L66RJ6PvwxJFCOm2iM8OI71g518gUkoeWPLoGQU7KyDtad6eyQxyv01dk+W+aWxA7ayN9X8mIuaOYqQzBTK3Tssm9nj2IEs2OIBi0jMFV3Nzw6BkI4+RRONcu7Af0jl1aJ31eTk+wOavljhoHQfGG0laGBa7QKBgQD4SZXf1mE0dgeUkv9T4JDoa4BKTNWfRbjPfUWpKvLFycwGG3z0h5DnQA+TbvTUEyuay6yUxkJCl+EL1A1ngPpk+10CR8h5MSq8mb21d5t6QS2Jnk6X1HEXyamx/HFQT1Nqrv14Ba0YOKsAaFBmdQDKXx/bNOxT31Z35kWsfUV+aQKBgQCZoo997pd9dKGxQjKERO2CXAdGQXgNmHfKknpKeRapJgfmHiAzWz7CXrlCPF9TgVqOzQr/gWXuD5LrPmq6Vi9M66fcEMXH0MyJaHbfow/iL3zuuD2EL2DYO/iEG6HBRuRqOgHvICSaqVUfDf1XHfjd/d9HjH5Z778egu8yuYTadQKBgFRpfWQmWFtNkmeb0dmxb2I7wULayHrFcacA8N4jd2YstUSV4N8aW+w519c2+WCvP/YZajAslX6csJkfWXuOcQLDN7XkD1NIOOMc78p/PTGNnbYT8/3bM1sY6FHg50oQPS/6kNSv0DE8fc9BKWe9DnBH9zO9R5jKfQSbO7UI+2CU"};
    rsa_2048::private_key pkam_private;
    rsa_2048::populate(pkam_private_base64, pkam_private);

    const auto challenge = std::string{"_fbe0809b-c7dd-4bc0-9a27-ab9e5812bc4c@22easy:ce4ab3f9-944d-495f-b385-8f499bef8fab"};

    // 2. sign a string
    const auto signature = rsa_2048::sign(challenge, pkam_private);

    // 3. print the signature
    std::cout << "signature: " << signature << std::endl;
};

// given an rsa public key encoded in base64, verify a signature
void rsa_2048_sha_256_verify_example()
{
    // WIP
}

// given an rsa private key encoded in base64, sign a message
void rsa_2048_encrypt_example()
{
    // WIP
}

void rsa_2048_decrypt_example()
{
    
    const auto rsa_private_str = std::string{"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC47cMf0z/HqwswOwE0uA2/tbr6oQs3efTgkB8Te4jnBujyk1wQrWA/prus4+JDXrm0waF9d1ijP+tsTRPFPqZJalBIjxHZ492lN9cKe23niZsWg5795MIZQsHouvfWjOsTS4pv5gaN9wsbjMpuoTk+W+T8bg/6xaKowC1LYT7zDPW66Kc8EZcKhH46EuiTYpGnGFOivFcUBJCc9ZOMq3dwl4gOcwyoV990V20s5mU5pS0VuV5S1BqiYdUk7hvH6YyxWhdP1iHHBlPr439CgsVVGYJa8qDYrduJVX6MACWHCDkFVQTIyYqaOubUk89Gkt37seDqjOXry2kR4U+fum+1AgMBAAECggEAY6Q4rr00cHFI5gPk8nL5dYKF7OU5FfswZo9BL04wxcqDWbDsuk+wvJsqJE3lbEdt6GcsjF3x9IRMZV5ieLT5BDW0bGQqSiztEEi2JX+8CDWsysTAtiy8KMA/mxai04e6Yfsh7IkUnwmtgnqp2FImdeMtzpW/Jm+25RYnUaZkNLCqZ9hv8nmYNIZ9a3Q4VEOHBlqxQOilR0i74Su3stWD0GiZIINrDM+kRvQlIVHt9RUaur190HPRRlfuZpA5Q1rNiPFh9Uwoqs9JvnwLDDekxSYykbTpJpWjZbe4V/6558rz2Xz7vbVdcHiP0SE4FW8a+XXn1r3wQKWEWYu2q0LiAQKBgQD4l0TXqs7ApK7ckKSJpl8gV2Otj69DMRQ6dB78AGAOYQG/cZcdpqvd2m07M80/Xo3bvhcJjsoZN+vlgOwEY7ytLzOOjciB2bYc92qpH4Gq4GMJW7uFARRBevZtsf055YGM/OozSPiin/KU70alkn90tO4Py6dhcry/e9TJbRqm6QKBgQC+cMFy7LYsthy42L66RJ6PvwxJFCOm2iM8OI71g518gUkoeWPLoGQU7KyDtad6eyQxyv01dk+W+aWxA7ayN9X8mIuaOYqQzBTK3Tssm9nj2IEs2OIBi0jMFV3Nzw6BkI4+RRONcu7Af0jl1aJ31eTk+wOavljhoHQfGG0laGBa7QKBgQD4SZXf1mE0dgeUkv9T4JDoa4BKTNWfRbjPfUWpKvLFycwGG3z0h5DnQA+TbvTUEyuay6yUxkJCl+EL1A1ngPpk+10CR8h5MSq8mb21d5t6QS2Jnk6X1HEXyamx/HFQT1Nqrv14Ba0YOKsAaFBmdQDKXx/bNOxT31Z35kWsfUV+aQKBgQCZoo997pd9dKGxQjKERO2CXAdGQXgNmHfKknpKeRapJgfmHiAzWz7CXrlCPF9TgVqOzQr/gWXuD5LrPmq6Vi9M66fcEMXH0MyJaHbfow/iL3zuuD2EL2DYO/iEG6HBRuRqOgHvICSaqVUfDf1XHfjd/d9HjH5Z778egu8yuYTadQKBgFRpfWQmWFtNkmeb0dmxb2I7wULayHrFcacA8N4jd2YstUSV4N8aW+w519c2+WCvP/YZajAslX6csJkfWXuOcQLDN7XkD1NIOOMc78p/PTGNnbYT8/3bM1sY6FHg50oQPS/6kNSv0DE8fc9BKWe9DnBH9zO9R5jKfQSbO7UI+2CU"};

    rsa_2048::private_key private_key;
    rsa_2048::populate(rsa_private_str, private_key);

    const auto cipher_text = std::string{"XZjE/lXrSZseVTFRvAGN70Mcky66QU3KYLpWjfTGErJ6rBh9GsHP1Ogp+No3aqL9nY972quKF2gTabGfqf3ykvpfKHgmQVUEg+wwaf8f8HObr25SUAM4GMHjSZsisLjndddTKFkYc7SetNnBxxOb3xN7S7aPop+Mz9yLSB9c73TyZQFK/J9HZVCV2fl+K3fFk/OGxeLKaZJIpeUgFvkRVKiEuWInD5Tuo1HVVuDI7DJALsMptLIBVJtzCYyRpNbMDrvxHCoKMF0eWUoTc026b0uyvqqSqbRn20GXwoS6IQmAakx/T2EGfF7mY86tq3vYUFx+jKtGC2I2fYro40yXOQ=="};

    const std::string output = rsa_2048::decrypt(cipher_text, private_key);
    std::cout << "setup() output: " << output.c_str() << std::endl;
}
