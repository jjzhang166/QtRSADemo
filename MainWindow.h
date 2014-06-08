#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QMainWindow>
#include <QListWidgetItem>
#include "ui_mainwindow.h"

class MainWindow:public QMainWindow,public Ui::MainWindow
{
	Q_OBJECT
public:
	MainWindow(QWidget *parent=0);
protected slots:
	void onGenerate();
	void onKeysCurrentItemChanged(QListWidgetItem *current,QListWidgetItem *previous);
	void onEncode();
	void onDecode();
protected:
	void loadKeys();
};

#endif