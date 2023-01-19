#include <mbedtls/rsa.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <mbedtls/pk.h>
#include <mbedtls/ctr_drbg.h>
#include <fstream>
#include <iomanip>
#include <mbedtls/entropy.h>
#include "mbedtls/pk.h"

#include "base64.h"

// for reading files on esp32
#include "SPIFFS.h"
#include "esp_tls.h"

using namespace std;

void printbytes(const unsigned char *input, const size_t &length)
{
  string output = "";
  for (std::uint32_t i = 0; i < length; i++)
  {
    std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)input[i] << " ";
    if (i == 0)
    {
      string str(1, input[i]);
      output = str;
    }
    string str(1, input[i]);
    str.push_back(input[i]);
    output = output + str;
  }
  std::cout << std::endl;
  cout << "printbytes output: " << output << endl;
}

void encryptKey(string to_encrypt, const unsigned char key_to_encrypt_with)
{
  // Start by initializing vars
  size_t to_encrypt_len = to_encrypt.length();
  // size_t *bufLen = new size_t;
  size_t *outputSize = 0;

  mbedtls_pk_context pk;
  mbedtls_pk_init(&pk);

  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_ctr_drbg_init(&ctr_drbg);
  // const unsigned char *key = (const unsigned char *)key_to_encrypt_with.c_str();
  unsigned char buf[MBEDTLS_MPI_MAX_SIZE];
  // void *myThing = (void *)key;

  // mbedtls_pk_setup_rsa_alt(&pk, myThing, NULL, NULL, NULL);
  /*
   * Calculate the RSA encryption of the data.
   * If encrypt function returns 0, then it was successful
   */

  // initializing a serial connection
  // Serial.begin(115200);
  // if (!SPIFFS.begin(true))
  // {
  //   Serial.println("An error has occurred while mounting SPIFFS");
  //   return;
  // }
  // create a new file to house public key
  // File file = SPIFFS.open("/test.pub", FILE_WRITE);

  // if (!file)
  // {
  //   Serial.println("There was an error opening the file for writing");
  //   return;
  // }

  // write the key to the file
  // file.print(key_to_encrypt_with);
  // file.close();

  Serial.begin(115200);
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  // create a new file to house public key
  SPIFFS.begin();
  File file = SPIFFS.open("/test.pub", "w");
  if (!file)
  {
    Serial.println("There was an error opening the file for writing");
    return;
  }

  file.print(key_to_encrypt_with);

  file.close();

  mbedtls_pk_free(&pk);
  int ret = 0;
  if ((ret = mbedtls_pk_parse_public_keyfile(&pk, "spiffs/test.pub")) != 0)
  {
    /**
     * This is where code breaks -> Jan 18
     * parse_public_keyfile needs path of file
     */
    cout << "Error in retrieving key" << endl;
    return;
  }

  mbedtls_pk_encrypt(&pk, &key_to_encrypt_with, to_encrypt_len, buf, outputSize, sizeof(buf),
                     mbedtls_ctr_drbg_random, &ctr_drbg);

  if ((ret = mbedtls_pk_encrypt(&pk, &key_to_encrypt_with, to_encrypt_len, buf, outputSize, sizeof(buf), mbedtls_ctr_drbg_random, &ctr_drbg)) != 0)
  {
    cout << "Error in encrypting" << endl;
  };
}

/**
 * This function is used to test reading/writing files on the esp32
 * Jan 18 -> testFiles functions as expected
 */
void testFiles(const unsigned char key_to_encrypt_with)
{
  // initializing a serial connection
  Serial.begin(115200);
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  // create a new file to house public key
  File file = SPIFFS.open("/test.pub", "w");
  if (!file)
  {
    Serial.println("There was an error opening the file for writing");
    return;
  }

  file.print(key_to_encrypt_with);
  file.close();

  file = SPIFFS.open("/test.txt", FILE_READ);
  cout << "File contents: " << endl;
  String s = file.readStringUntil('\n');
  Serial.println(s);
  file.close();
}

void setup()
{
  const unsigned char myKey = 'IIW+bRGEEJsgGJvE3bTcVALARDSNFr4mMNNS2JgoCCx5UaYUwfGq0lbH7yYREi+9pSWTReXXJOnsEqm9LfSfw0lfKlomR7OQQmdwIRQeiOBj+ZAee0Rb0PC6yAIgap6Zrb+sS0HIdO9FR3jXG2sDdw9+Y28XyfvPi0+l4N/kOKsW+toimEHh03J1d1CGFB3zef+WCqeS7YuShvOBYx8CK08CtF6muIqOBATzrwAk0DJilZqwlsF2jg8koere7XstRmyvwjHumtFEAeI0aD7mSp2iJhfTaPPXx5fjccDLyiU7bObkqtFCj+5cf2rS70S+UcZ4/Ir8kdAf9Tt/ZkEq0/oujv4TTq0ookCr32CtsvUxs61d9PjyNN7iAfVb/KUKqd3Kjhrfkirbh4cRhXZv24x1SxXt1lfpFPAepQ7k0afC/0FvqMBllFPctWkI+FAzgVDyi4OCp6VUxZrqNWaXjZE3FMCgCx9nzM7PsfmeoGkXnakhf/tjY4irPNTZ0EGec0s7Ijipk0tVQOFpyMARTA==';
  encryptKey("I like to eat pizza", myKey);
  // testFiles(myKey);
};
void loop(){};
