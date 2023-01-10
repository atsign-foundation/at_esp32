#include "aes_ctr.h"
#include <iostream>

void encrypt_sample()
{
	// base64 encoded aes 256 key
	const auto base64_encoded_key = std::string("1DPU9OP3CYvamnVBMwGgL7fm8yB1klAap0Uc5Z9R79g=");

	// plain text
	const auto plain_text = std::string("i like to eat pizza");

	const std::string result = aes_ctr::encrypt(plain_text, base64_encoded_key);
	std::cout << result << std::endl;
}

void decrypt_sample()
{
	// base64 encoded aes 256 key
	const auto base64_encoded_key = std::string("1DPU9OP3CYvamnVBMwGgL7fm8yB1klAap0Uc5Z9R79g=");

	// base64 encoded rsa key (encrypted with the aes key)
	const auto base64_encoded_encrypted_str = std::string("BOybRjOLcaULBYrUsduxFw==");

	const std::string result = aes_ctr::decrypt(base64_encoded_encrypted_str, base64_encoded_key);
	std::cout << result << std::endl;
}