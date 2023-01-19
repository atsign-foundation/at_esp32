
#include <iostream>
#include <vector>
#include <mbedtls/base64.h>
#include "base64.h"
#include <mbedtls/asn1.h>
#include "tiny-asn1.h"

void convert(const std::string &s, std::vector<uint8_t> &v)
{
	v = base64::base64_decode(s);
}


void print_hex(const uint8_t* data, unsigned int len)
{
  unsigned int count = 0;
  unsigned int blockCount = 0;
  while(count < len) {
    printf("%02x ", data[count]);
    ++count;
    ++blockCount;
    if(blockCount == 4)
      printf("  ");
    if(blockCount == 8) {
      printf("\n");
      blockCount = 0;
    }
  }
  printf("\n");
}


void print_asn1(const asn1_tree* list, int depth)
{
  std::cout << "d=" << depth << ", Tag: " << std::hex << list->type << ", len=" << list->length << std::endl;
  if(list->child == NULL) {
    printf("Value:\n");
    print_hex(list->data, list->length);
  } else {
    print_asn1(list->child, depth+1);
  }

  if(list->next != NULL)
    print_asn1(list->next, depth);
}


void setup()
{
	// base64 encoded RSA-2048 public key
	const auto public_key_base64 = std::string{""};

	// base64 encoded RSA-2048 private key
	const auto private_key_base64 = std::string{"MIIEvAIBADANBgkqhkiG9w0BAQEFAASCBKYwggSiAgEAAoIBAQCEzYZ5jImqMsvbCC2fDHRVFN2+MOAhMJcDs0SucuFub2Q8MARDi05jnz4fdxoQ2okLqm3ke/A5GlCe/vR76euOiRDHwTL73Hoquc00CAXytDK0uirXxfnGn+jp7qksY2BcpLSWyqqDmRSTtWBbg+i6h6aTfahPXHPsihBN9Uvdnd4fWZprP2Ctnov29DdgP6TJ92oI2kvDM9LreBYPfjBvFTw6BTzAugkkD4bG8/B0OLeGgPia7J0g7ecljAg8ZzBDp1fuIyOCSIbW3OYvaKnA8+rHvFAqcPg/sLKr9KVgrli916bpiizVO8jEA6/J4nafUhCfN7XTpnXCFp2BMuylAgMBAAECggEAXuSw+zd1wvzq94afeq+ejJENZXJtJKogrk8xe2mxNYU43Vz+HvlyuPK3pCopoPNWy9QrFAGPhG4OP540OjrKy52bNPETKi6/yLndLBmzjlo+hS8ln+rh8JChEE8t6P7Vgz1ZoQoNz1zZ/DW1NY9LA8YcO/WlB5graVC6F8p4PFEigG7vuhpoA5henkVfTVnXmiYkaA0GQ/brOBPXyzXHhYdNjAY5pSpeqgpUxhltY2n75CGWnoMWu1HhDTvGVhsroqZqAnkGugWSpA8byFOPLgI6l6sjQZXpdSHuNxPxyah25Bh6OpDeWJhfmFyPIosWbYXCUAUATHOf7gSADMGMgQKBgQDGwbihOz5ZdxXrD3kLIMJMaqhY8nXdWPjrOd2Zqa5CLheCVvBGVHNKtYZkHRFi3OFgGvqkTNjdiBAidJ23i7dQ/SqKvqM/SDpYFFJk+nhbAAg4BGIEapt8KWh2KLv9rpPWtF2YFVLPd3b3z1iCbmNzIIrL1Aesj96rYmD+t0N2hQKBgQCrDQq0M/pCf9WlzenXz5dLvojfwUM1XVPjCUGThYQU6wtuQ7DMT5N7GKHL9DbtzOsSZZigsjIi74xiMQnZC/NkjIgzkQUR8zHFz/D3yFXdfGjo47H3OvFrV6EDfrBEY816q5nDVAK/i69ljCk0JuZbNH7x+XTAN12w1d1Dr1THoQKBgE1JTw4DB3+qeu9omNzm5Cbq4oOT5Jkp28E8QxtZi9VYLvQT8mKmvB408AlF9FjJIypH02bIKxwZqIx9ZEbXIXVwvHYvIzOcVnOhk1iIvPxFyuxdZ+/ntIZXY7Nuq4s9s2ctw6c7w3PBNJWwHu65FhrScKZJ0KIdX6ytGKJziNwxAoGAezxlNtmv95NEaTXGwY610YOP962071CzLIKxtUhflfaWALZSPZEjj296uofTv1aBEnsSEMzx5Eu0V9Y+4xqCHDJHuudDwN/3Py6GzO6QNof4ybmqsZXM8+ppfiwbcNp642OY36q6ZCiOkNn/oaxZEOLshweT/xykqtAanzZGHaECgYAoqejWFqzGa1Oor5qNxfb6qtgGon3X60wgEJccpddFzeoyRLZOEcUkOBdkyvAR+UkWFcjyqU67nS1vYSdY8ZyMxP6eIsdcuvh3WzJJPcqRxJIGBFN55FOgt3t0qLiEwjrrL2mF+cGoPyFWfeM8urkqslc2lAbXAfohvbq/kiILew=="};

	std::vector<uint8_t> b;

	convert(private_key_base64, b);

	std::cout << "size: " << b.size() << std::endl;
	for(std::uint32_t i = 0; i < b.size(); i++) {
		std::cout << b[i] << " ";

	}
	std::cout << std::endl;

	std::uint8_t *input = b.data();
	const size_t input_length = b.size();

	std::uint32_t asn1_object_count = der_object_count(input, input_length);
	asn1_tree* asn1_objects = (asn1_tree*) (malloc(sizeof(asn1_tree) * asn1_object_count));
	asn1_tree cms;
	der_decode(input, input_length, &cms, asn1_objects, asn1_object_count);
	// print_asn1(&cms, 0);

	// for(std::uint32_t i = 0; i < 5; i++) {
		print_asn1(&cms, 1);
	// }

	/**
	 * @brief int32_t asn1_object_count = der_object_count(cms_data, file_size);
	if(asn1_object_count < 0) {
		fprintf(stderr, "ERROR: Could not calculate the number of Elements within the data.\n");
		free(cms_data);
    	return 1;
  	}

	asn1_tree* asn1_objects = (asn1_tree*)(malloc(sizeof(asn1_tree) * asn1_object_count));
  	if(asn1_objects == NULL){
		fprintf(stderr, "ERROR: Could not allocate the memory for the ASN.1 objects.\n");
		free(cms_data);
    	return 1;
  	}

  	asn1_tree cms;

  	if(der_decode(cms_data, file_size, &cms, asn1_objects, asn1_object_count) < 0) {
		fprintf(stderr, "ERROR: Could not parse the data.\n");
		free(cms_data);
    	return 1;
  	}

	 * 
	 */

	// const unsigned int obj_count = der_object_count(input, input_length);
	// asn1_tree *out_objects = new asn1_tree[obj_count];
	// asn1_tree *out = (asn1_tree *) malloc(sizeof(asn1_tree));

	// der_decode(input, input_length, out, out_objects, obj_count);

	
}

void loop()
{
}
