#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

#include "DB.h"

const std::string DB::_file="/Users/Leonard/Documents/Lab/QtRSADemo/rsa.db";

DB::DB()
{
}

int DB::getKeys(QVector<RSAData> &result,bool getDetail)
{
	int count=0;
	QSqlDatabase db=QSqlDatabase::database();
	
	if(!db.open())
		return count;
	result.clear();
	
	QSqlQuery query(db);
	if(!query.exec("select id,description,privatekey,publickey from rsakeys"))
	{
		db.close();
		return count;
	}
	
	while(query.next())
	{
		RSAData data;
		
		data.index=query.value(0).toInt();
		data.description=query.value(1).toString();
		if(getDetail)
		{
			data.privateKey=query.value(2).toString();
			data.publicKey=query.value(3).toString();
		}
		result.push_back(data);count++;
	}
	
	return count;
}

bool DB::getKeys(RSAData &result, int index)
{
	int count=0;
	QSqlDatabase db=QSqlDatabase::database();
	
	if(!db.open())
		return count;
	
	QSqlQuery query(db);
	query.prepare("select id,description,privatekey,publickey from rsakeys where id=:id");
	query.bindValue("id", index);
	if(!query.exec())
	{
		db.close();
		return false;
	}
	query.next();
	result.index=query.value(0).toInt();
	result.description=query.value(1).toString();
	result.privateKey=query.value(2).toString();
	result.publicKey=query.value(3).toString();
	db.close();
	
	return true;
}

bool DB::addKey(RSAData data)
{
	bool flag=false;
	QSqlDatabase db=QSqlDatabase::database();
	
	if(!db.open())
	{
		qDebug()<<"Cannot open the db";
		return false;
	}
	QSqlQuery query(db);
	query.prepare("insert into rsakeys(description,privatekey,publickey) values(:des,:pri,:pub)");
	query.bindValue("des", data.description);
	query.bindValue("pri", data.privateKey);
	query.bindValue("pub", data.publicKey);
	flag=query.exec();
	if(!flag)
	{
		qDebug()<<query.lastError().text();
	}
	db.close();
	
	return flag;
}

bool DB::deleteKey(int index)
{
	bool flag=false;
	QSqlDatabase db=QSqlDatabase::database();
	
	if(!db.open())
		return false;
	
	QSqlQuery query(db);
	query.prepare("delete from rsakeys where id=:index");
	query.bindValue("index", index);
	flag=query.exec();
	db.close();
	
	return flag;
}

bool DB::init()
{
	QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
	db.setDatabaseName(QString::fromStdString(_file));
	
	return true;
}