/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionGenerate;
    QAction *actionEncode;
    QAction *actionDecode;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSplitter *splitter_3;
    QSplitter *splitter_2;
    QListWidget *listWidget;
    QSplitter *splitter;
    QTextEdit *textEditPrivateKey;
    QTextEdit *textEditPublicKey;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(585, 432);
        actionGenerate = new QAction(MainWindow);
        actionGenerate->setObjectName(QString::fromUtf8("actionGenerate"));
        actionEncode = new QAction(MainWindow);
        actionEncode->setObjectName(QString::fromUtf8("actionEncode"));
        actionDecode = new QAction(MainWindow);
        actionDecode->setObjectName(QString::fromUtf8("actionDecode"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_2 = new QSplitter(splitter_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        listWidget = new QListWidget(splitter_2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        splitter_2->addWidget(listWidget);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        textEditPrivateKey = new QTextEdit(splitter);
        textEditPrivateKey->setObjectName(QString::fromUtf8("textEditPrivateKey"));
        textEditPrivateKey->setReadOnly(true);
        splitter->addWidget(textEditPrivateKey);
        textEditPublicKey = new QTextEdit(splitter);
        textEditPublicKey->setObjectName(QString::fromUtf8("textEditPublicKey"));
        textEditPublicKey->setReadOnly(true);
        splitter->addWidget(textEditPublicKey);
        splitter_2->addWidget(splitter);
        splitter_3->addWidget(splitter_2);
        textEdit = new QTextEdit(splitter_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        splitter_3->addWidget(textEdit);

        gridLayout->addWidget(splitter_3, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 585, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionGenerate);
        toolBar->addAction(actionEncode);
        toolBar->addAction(actionDecode);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Qt RSA Demo", 0, QApplication::UnicodeUTF8));
        actionGenerate->setText(QApplication::translate("MainWindow", "Generate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionGenerate->setToolTip(QApplication::translate("MainWindow", "Generate RSA Key", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionEncode->setText(QApplication::translate("MainWindow", "Encode", 0, QApplication::UnicodeUTF8));
        actionDecode->setText(QApplication::translate("MainWindow", "Decode", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
