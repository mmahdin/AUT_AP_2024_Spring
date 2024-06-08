#ifndef CRYPTO_H
#define CRYPTO_H

#include <assert.h>
#include <openssl/aes.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <string.h>

#include <iostream>

namespace crypto {

RSA* createPrivateRSA(std::string key);

RSA* createPublicRSA(std::string key);

bool RSASign(RSA* rsa, const unsigned char* Msg, size_t MsgLen,
			 unsigned char** EncMsg, size_t* MsgLenEnc);

bool RSAVerifySignature(RSA* rsa, unsigned char* MsgHash, size_t MsgHashLen,
						const char* Msg, size_t MsgLen, bool* Authentic);

void Base64Encode(const unsigned char* buffer, size_t length,
				  char** base64Text);

size_t calcDecodeLength(const char* b64input);

void Base64Decode(const char* b64message, unsigned char** buffer,
				  size_t* length);

std::string signMessage(std::string privateKey, std::string plainText);

bool verifySignature(std::string publicKey, std::string plainText,
					 std::string signatureBase64);

const char* keyFromRSA(RSA* rsa, bool isPrivate);

void generate_key(std::string& public_key, std::string& private_key);

std::string string_to_hex(const std::string& input);

std::string sha256_tmp(std::string s);

std::string sha256(std::string s);

}  // namespace crypto
#endif	// CRYPTO_H