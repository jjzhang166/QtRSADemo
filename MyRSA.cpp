#include <openssl/bio.h>
#include <openssl/pem.h>
#include <QDebug>
#include "MyRSA.h"

MyRSA::MyRSA()
:_key(0)
{

}

MyRSA::~MyRSA()
{
	//free the rsa key
	if(_key==NULL)
	{
		RSA_free(_key);
	}
}

bool MyRSA::generateKey(int bits)
{
	return _key=RSA_generate_key(bits, RSA_F4, 0, 0);
}

bool MyRSA::loadPrivateKey(std::string content)
{
	BIO *bio;
	bool flag=true;
	
	if((bio=BIO_new(BIO_s_mem()))==NULL)
		return false;

	//write key string to bio
	BIO_write(bio, content.c_str(),content.length());
	if((_key=PEM_read_bio_RSAPrivateKey(bio, &_key, 0, 0))==0)
		flag=false;
	
	BIO_free(bio);
	return flag;
}

bool MyRSA::loadPublicKey(std::string content)
{
	BIO *bio;
	bool flag=true;
	
	if((bio=BIO_new(BIO_s_mem()))==NULL)
		return false;
	
	//write key string to bio
	BIO_write(bio, content.c_str(),content.length());
	if((_key=PEM_read_bio_RSAPublicKey(bio, &_key, 0, 0))==0)
		flag=false;
	
	BIO_free(bio);
	return flag;
}

bool MyRSA::getPrivateKey2String(std::string &privateKey, std::string &publicKey)
{
	BIO *bio;
	int length;
	char *content;
	
	if((bio=BIO_new(BIO_s_mem()))==NULL)
		return false;
	
	//read private key
	PEM_write_bio_RSAPrivateKey(bio, _key, 0, 0, RSA_size(_key), 0, 0);
	length=BIO_ctrl_pending(bio);
	content=(char*)OPENSSL_malloc(length);
	length=BIO_read(bio, content, length);
	privateKey=content;
	OPENSSL_free(content);
	
	//read public key
	BIO_reset(bio);
	PEM_write_bio_RSAPublicKey(bio, _key);
	length=BIO_ctrl_pending(bio);
	content=(char*)OPENSSL_malloc(length);
	length=BIO_read(bio, content, length);
	publicKey=content;
	OPENSSL_free(content);
	
	BIO_free(bio);
	
	return true;
}

std::string MyRSA::encrypt(std::string src)
{
	std::string dst;
	unsigned int blockSize=RSA_size(_key)-11;
	
	for(int i=0;;i+=blockSize)
	{
		if(i>src.size())
			break;
		
		char *tmp=new char[RSA_size(_key)];
		int rtn=0;
		int flen=(src.size()-i)>blockSize?blockSize:src.size()-i;
		
		rtn=RSA_public_encrypt(flen, (unsigned char*)src.c_str()+i, (unsigned char*)tmp, _key, RSA_PKCS1_PADDING);
		if(rtn!=-1)dst.append(tmp, rtn);
		if(tmp)delete tmp;
	}
	
	return dst;
}

std::string MyRSA::decrypt(std::string src)
{
	std::string dst;
	unsigned int blockSize=RSA_size(_key);
	
	for(int i=0;;i+=blockSize)
	{
		if(i>src.size())
			break;
		
		char *tmp=new char[RSA_size(_key)];
		int rtn=0;
		int flen=(src.size()-i)>blockSize?blockSize:src.size()-i;//这里其实可以直接写作blockSize,因为密文的长度应该是m_key的整数倍
		
		rtn=RSA_private_decrypt(flen, (unsigned char*)src.c_str()+i, (unsigned char*)tmp,_key,RSA_PKCS1_PADDING);
		if(rtn!=-1)dst.append(tmp,rtn);
		else
			qDebug()<<"RSA_private_decrypt error";
		if(tmp)delete tmp;
	}
	
	return dst;
}