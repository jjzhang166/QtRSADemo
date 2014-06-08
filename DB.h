#ifndef	__DB_H__
#define	__DB_H__

#include <string>
#include <QVector>

struct RSAData
{
	int index;
	QString description;
	QString privateKey;
	QString publicKey;
};

class DB
{
public:
	const static std::string _file;
public:
	DB();
	
	int getKeys(QVector<RSAData> &results,bool getDetail=false);
	bool getKeys(RSAData &result,int index);
	bool addKey(RSAData data);
	bool deleteKey(int index);
	
public:
	static bool init();
};
#endif