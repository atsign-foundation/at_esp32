#include <mbedtls/rsa.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <mbedtls/pk.h>
#include <mbedtls/ctr_drbg.h>
#include <fstream>
#include "mbedtls/pk.h"

// for reading files on esp32
#include "SPIFFS.h"

using namespace std;

unsigned char *encryptKey(string to_encrypt, const unsigned char key_to_encrypt_with)
{
  // Start by initializing vars
  size_t to_encrypt_len = to_encrypt.length();
  size_t *outputSize = 0;

  mbedtls_pk_context pk;
  mbedtls_pk_init(&pk);

  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_ctr_drbg_init(&ctr_drbg);
  unsigned char buf[MBEDTLS_MPI_MAX_SIZE];

  Serial.begin(115200);
  if (!SPIFFS.begin(true))
  {
    Serial.println("An error has occurred while mounting SPIFFS");
    return;
  }
  // create a new file to house public key
  SPIFFS.begin();
  File file = SPIFFS.open("/test.pub", "w");
  cout << "file name: " << file.name() << endl;
  if (!file)
  {
    Serial.println("There was an error opening the file for writing");
    return;
  }

  file.print(key_to_encrypt_with);

  mbedtls_pk_free(&pk);
  int ret = 0;
  if ((ret = mbedtls_pk_parse_public_keyfile(&pk, file.name())) != 0)
  {
    /**
     * This is where code breaks -> Jan 18
     * parse_public_keyfile needs path of file
     */
    cout << "Error in retrieving key" << endl;
    return;
  }
  file.close();

  mbedtls_pk_encrypt(&pk, &key_to_encrypt_with, to_encrypt_len, buf, outputSize, sizeof(buf),
                     mbedtls_ctr_drbg_random, &ctr_drbg);

  if ((ret = mbedtls_pk_encrypt(&pk, &key_to_encrypt_with, to_encrypt_len, buf, outputSize, sizeof(buf), mbedtls_ctr_drbg_random, &ctr_drbg)) != 0)
  {
    cout << "Error in encrypting" << endl;
    return;
  };

  return buf;
}

unsigned char *decryptKey(const unsigned char key_to_decrypt_with, unsigned char *to_decrypt)
{
  // Start by initializing vars
  size_t to_decrypt_len = sizeof(to_decrypt);
  size_t *outputSize = 0;
  int ret = 0;
  mbedtls_ctr_drbg_context ctr_drbg;
  mbedtls_ctr_drbg_init(&ctr_drbg);

  mbedtls_pk_context pk;

  mbedtls_pk_init(&pk);

  /*
   * Read the RSA privatekey
   */
  if ((ret = mbedtls_pk_parse_keyfile(&pk, "/test.pub", "")) != 0)
  {
    printf("failed to parse keyfile.", -ret);
    return;
  }

  unsigned char result[MBEDTLS_MPI_MAX_SIZE];
  size_t olen = 0;

  /*
   * Calculate the RSA encryption of the data.
   */
  printf("\n  . Generating the encrypted value");
  fflush(stdout);

  if ((ret = mbedtls_pk_decrypt(&pk, to_decrypt, to_decrypt_len, result, &olen, sizeof(result),
                                mbedtls_ctr_drbg_random, &ctr_drbg)) != 0)
  {
    printf("Failed to decrypt.", -ret);
    return;
  }
  return result;
}

/**
 *This function is used to test reading / writing files on the esp32
 *Jan 18->testFiles functions as expected*/
// void testFiles(const unsigned char key_to_encrypt_with)
// {
//   // initializing a serial connection
//   Serial.begin(115200);
//   if (!SPIFFS.begin(true))
//   {
//     Serial.println("An error has occurred while mounting SPIFFS");
//     return;
//   }
//   // create a new file to house public key
//   File file = SPIFFS.open("/test.pub", "w");
//   if (!file)
//   {
//     Serial.println("There was an error opening the file for writing");
//     return;
//   }

//   file.print(key_to_encrypt_with);
//   file.close();

//   file = SPIFFS.open("/test.txt", FILE_READ);
//   cout << "File contents: " << endl;
//   String s = file.readStringUntil('\n');
//   Serial.println(s);
//   file.close();
// }

void setup()
{
  const unsigned char myPublicKey = 'IIW+bRGEEJsgGJvE3bTcVALARDSNFr4mMNNS2JgoCCx5UaYUwfGq0lbH7yYREi+9pSWTReXXJOnsEqm9LfSfw0lfKlomR7OQQmdwIRQeiOBj+ZAee0Rb0PC6yAIgap6Zrb+sS0HIdO9FR3jXG2sDdw9+Y28XyfvPi0+l4N/kOKsW+toimEHh03J1d1CGFB3zef+WCqeS7YuShvOBYx8CK08CtF6muIqOBATzrwAk0DJilZqwlsF2jg8koere7XstRmyvwjHumtFEAeI0aD7mSp2iJhfTaPPXx5fjccDLyiU7bObkqtFCj+5cf2rS70S+UcZ4/Ir8kdAf9Tt/ZkEq0/oujv4TTq0ookCr32CtsvUxs61d9PjyNN7iAfVb/KUKqd3Kjhrfkirbh4cRhXZv24x1SxXt1lfpFPAepQ7k0afC/0FvqMBllFPctWkI+FAzgVDyi4OCp6VUxZrqNWaXjZE3FMCgCx9nzM7PsfmeoGkXnakhf/tjY4irPNTZ0EGec0s7Ijipk0tVQOFpyMARTA==';
  const unsigned char myPrivKey = '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';
  unsigned char *myencryptedStuff = encryptKey("I like to eat pizza", myPublicKey);
  unsigned char *mydecryptedstuff = decryptKey(myPrivKey, myencryptedStuff);
  //  testFiles(myKey);
};
void loop(){};
