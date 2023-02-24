#include "aes_ctr.h"
#include <iostream>

void encrypt_sample()
{
	// 1. initialize base64 encoded aes-256 symmetric key
	const auto base64_encoded_key = std::string("1DPU9OP3CYvamnVBMwGgL7fm8yB1klAap0Uc5Z9R79g=");

	// 2. initialize plain text
	const auto plain_text = std::string("i like to eat pizza");

	// 3. run the `aes_ctr::encrypt` function
	const std::string result = aes_ctr::encrypt(plain_text, base64_encoded_key);

	// 4. print the result
	std::cout << result << std::endl;
}

void decrypt_sample()
{
	// 1. initialize base64 encoded aes-256 symmetric key
    const auto aes_key_base64 = std::string{"1DPU9OP3CYvamnVBMwGgL7fm8yB1klAap0Uc5Z9R79g="};

	// 2. initialize base64 encoded cipher text
    const auto cipher_text = std::string{"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"};

	// 3. run the `aes_ctr::decrypt` function
    const auto decrypted = aes_ctr::decrypt(cipher_text, aes_key_base64);

	// 4. print the decrypted text
    std::cout << decrypted << std::endl;
}
