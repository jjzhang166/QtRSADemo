#ifndef __MY_RSA_H__
#define __MY_RSA_H__

#include <string>
#include <openssl/rsa.h>

class MyRSA
{
public:
	MyRSA();
	~MyRSA();
	
	bool generateKey(int bits=1024);
	bool loadPublicKey(std::string content);
	bool loadPrivateKey(std::string content);
	
	bool getPrivateKey2String(std::string &privateKey,std::string &publicKey);
	
	std::string encrypt(std::string src);
	std::string decrypt(std::string src);
protected:
	RSA *_key;
};

#endif