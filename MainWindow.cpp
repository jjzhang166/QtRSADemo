#include <QInputDialog>
#include <QDebug>
#include <QByteArray>
#include "MainWindow.h"
#include "MyRSA.h"
#include "DB.h"

MainWindow::MainWindow(QWidget *parent)
:QMainWindow(parent)
{
	setupUi(this);
	
	loadKeys();
	
	connect(actionGenerate,SIGNAL(triggered()),this,SLOT(onGenerate()));
	connect(listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(onKeysCurrentItemChanged(QListWidgetItem*,QListWidgetItem*)));
	connect(actionEncode,SIGNAL(triggered()),this,SLOT(onEncode()));
	connect(actionDecode,SIGNAL(triggered()),this,SLOT(onDecode()));
	
	show();
}

void MainWindow::onGenerate()
{
	bool ok;
	QString desc=QInputDialog::getText(this, "Input the description about RSA Keys", "Description of new RSA keys",QLineEdit::Normal,"",&ok);
	
	if(!ok || desc.isEmpty())
		return;
	
	RSAData data;
	MyRSA rsa;
	
	if(rsa.generateKey())
	{
		std::string pri,pub;
		rsa.getPrivateKey2String(pri, pub);
		data.description=desc;
		data.privateKey=QString::fromStdString(pri);
		data.publicKey=QString::fromStdString(pub);
		
		//ready to save to db;
		DB db;
		db.addKey(data);
		loadKeys();
	}
}

void MainWindow::loadKeys()
{
	QVector<RSAData> keys;
	DB db;
	if(!db.getKeys(keys))
		return;
	
	listWidget->clear();
	
	for(QVector<RSAData>::const_iterator iter=keys.begin();iter!=keys.end();iter++)
	{
		QListWidgetItem *item=new QListWidgetItem(QString::number(iter->index)+"\t"+iter->description);
		item->setData(Qt::UserRole, iter->index);
		listWidget->addItem(item);
	}

}

void MainWindow::onKeysCurrentItemChanged(QListWidgetItem *current,QListWidgetItem *previous)
{
	Q_UNUSED(previous);
	if(current==0)
		return;
	
	//get the rsa data
	int index=current->data(Qt::UserRole).toInt();
	DB db;RSAData data;
	if(!db.getKeys(data, index))
	{
		qDebug()<<"did not get the data"<<index;
		return;
	}
	textEditPrivateKey->setText(data.privateKey);
	textEditPublicKey->setText(data.publicKey);
}

void MainWindow::onEncode()
{
	MyRSA rsa;
	std::string pkey=textEditPublicKey->toPlainText().toStdString();
	std::string src=textEdit->toPlainText().toStdString();
	std::string dst;
	
	if(!rsa.loadPublicKey(pkey))
		return;
	dst=rsa.encrypt(src);
	
	textEdit->clear();
	QByteArray tmp(dst.c_str(),dst.size());
	qDebug()<<tmp.size()<<"\t"<<tmp.toBase64().size();
	textEdit->setText(tmp.toBase64());
}

void MainWindow::onDecode()
{
	MyRSA rsa;
	std::string pkey=textEditPrivateKey->toPlainText().toStdString();
	std::string src;
	std::string dst;
	
	QString tmp=textEdit->toPlainText();
	QByteArray ba=QByteArray::fromBase64(tmp.toAscii());
	src=QString(ba).toStdString();
	
	if(!rsa.loadPrivateKey(pkey))
	{
		qDebug()<<"Load private key error";
		return;
	}
	dst=rsa.decrypt(src);
	
	textEdit->clear();textEdit->setText(QString::fromStdString(dst));
}