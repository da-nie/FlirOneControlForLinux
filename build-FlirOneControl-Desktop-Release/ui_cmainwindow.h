/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralWidget;
    QLabel *CLabel_ThermalImage;
    QLabel *CLabel_VideoImage;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QStringLiteral("CMainWindow"));
        CMainWindow->resize(989, 550);
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CLabel_ThermalImage = new QLabel(centralWidget);
        CLabel_ThermalImage->setObjectName(QStringLiteral("CLabel_ThermalImage"));
        CLabel_ThermalImage->setGeometry(QRect(10, 10, 371, 341));
        CLabel_VideoImage = new QLabel(centralWidget);
        CLabel_VideoImage->setObjectName(QStringLiteral("CLabel_VideoImage"));
        CLabel_VideoImage->setGeometry(QRect(600, 10, 371, 341));
        CMainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(CMainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CMainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMainWindow->setStatusBar(statusBar);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "CMainWindow", Q_NULLPTR));
        CLabel_ThermalImage->setText(QString());
        CLabel_VideoImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
