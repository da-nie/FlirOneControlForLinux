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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_3;
    QLabel *label_Emission;
    QPushButton *pushButton_SaveRAW;
    QPushButton *pushButton_SaveVideo;
    QLabel *label_Palette;
    QPushButton *pushButton_ShowVideo;
    QPushButton *pushButton_SaveImageNoScale;
    QDoubleSpinBox *doubleSpinBox_Emission;
    QComboBox *comboBox_Palette;
    QPushButton *pushButton_ApplyPalette;
    QLabel *label_Temper;
    QPushButton *pushButton_SaveAllFrame;
    QPushButton *pushButton_SaveImageCross;
    QDoubleSpinBox *doubleSpinBox_Temperature;
    QLabel *CLabel_ThermalImage;
    QLabel *label_LevelMinT;
    QPushButton *pushButton_SaveFrame;
    QDoubleSpinBox *doubleSpinBox_MaxT;
    QLabel *label_LevelMaxT;
    QLabel *CLabel_VideoImage;
    QDoubleSpinBox *doubleSpinBox_MinT;
    QLabel *label_Alarm;
    QCheckBox *checkBox_AlarmSaveFrame;
    QComboBox *comboBox_Language;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QStringLiteral("CMainWindow"));
        CMainWindow->resize(1048, 746);
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_Emission = new QLabel(centralWidget);
        label_Emission->setObjectName(QStringLiteral("label_Emission"));
        label_Emission->setFrameShape(QFrame::Panel);
        label_Emission->setFrameShadow(QFrame::Plain);

        gridLayout_3->addWidget(label_Emission, 5, 0, 1, 2);

        pushButton_SaveRAW = new QPushButton(centralWidget);
        pushButton_SaveRAW->setObjectName(QStringLiteral("pushButton_SaveRAW"));

        gridLayout_3->addWidget(pushButton_SaveRAW, 9, 3, 1, 1);

        pushButton_SaveVideo = new QPushButton(centralWidget);
        pushButton_SaveVideo->setObjectName(QStringLiteral("pushButton_SaveVideo"));

        gridLayout_3->addWidget(pushButton_SaveVideo, 5, 3, 1, 1);

        label_Palette = new QLabel(centralWidget);
        label_Palette->setObjectName(QStringLiteral("label_Palette"));

        gridLayout_3->addWidget(label_Palette, 9, 0, 1, 1);

        pushButton_ShowVideo = new QPushButton(centralWidget);
        pushButton_ShowVideo->setObjectName(QStringLiteral("pushButton_ShowVideo"));

        gridLayout_3->addWidget(pushButton_ShowVideo, 10, 3, 1, 1);

        pushButton_SaveImageNoScale = new QPushButton(centralWidget);
        pushButton_SaveImageNoScale->setObjectName(QStringLiteral("pushButton_SaveImageNoScale"));

        gridLayout_3->addWidget(pushButton_SaveImageNoScale, 7, 3, 1, 1);

        doubleSpinBox_Emission = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Emission->setObjectName(QStringLiteral("doubleSpinBox_Emission"));
        doubleSpinBox_Emission->setMinimum(0.01);
        doubleSpinBox_Emission->setMaximum(1);
        doubleSpinBox_Emission->setSingleStep(0.1);
        doubleSpinBox_Emission->setValue(0.95);

        gridLayout_3->addWidget(doubleSpinBox_Emission, 5, 2, 1, 1);

        comboBox_Palette = new QComboBox(centralWidget);
        comboBox_Palette->setObjectName(QStringLiteral("comboBox_Palette"));

        gridLayout_3->addWidget(comboBox_Palette, 9, 1, 1, 2);

        pushButton_ApplyPalette = new QPushButton(centralWidget);
        pushButton_ApplyPalette->setObjectName(QStringLiteral("pushButton_ApplyPalette"));

        gridLayout_3->addWidget(pushButton_ApplyPalette, 10, 0, 1, 3);

        label_Temper = new QLabel(centralWidget);
        label_Temper->setObjectName(QStringLiteral("label_Temper"));
        label_Temper->setFrameShape(QFrame::Panel);

        gridLayout_3->addWidget(label_Temper, 7, 0, 1, 2);

        pushButton_SaveAllFrame = new QPushButton(centralWidget);
        pushButton_SaveAllFrame->setObjectName(QStringLiteral("pushButton_SaveAllFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_SaveAllFrame->sizePolicy().hasHeightForWidth());
        pushButton_SaveAllFrame->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_SaveAllFrame, 5, 5, 2, 4);

        pushButton_SaveImageCross = new QPushButton(centralWidget);
        pushButton_SaveImageCross->setObjectName(QStringLiteral("pushButton_SaveImageCross"));

        gridLayout_3->addWidget(pushButton_SaveImageCross, 6, 3, 1, 1);

        doubleSpinBox_Temperature = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_Temperature->setObjectName(QStringLiteral("doubleSpinBox_Temperature"));
        doubleSpinBox_Temperature->setMinimum(-99.99);
        doubleSpinBox_Temperature->setSingleStep(0.1);
        doubleSpinBox_Temperature->setValue(20);

        gridLayout_3->addWidget(doubleSpinBox_Temperature, 7, 2, 1, 1);

        CLabel_ThermalImage = new QLabel(centralWidget);
        CLabel_ThermalImage->setObjectName(QStringLiteral("CLabel_ThermalImage"));

        gridLayout_3->addWidget(CLabel_ThermalImage, 0, 0, 5, 4);

        label_LevelMinT = new QLabel(centralWidget);
        label_LevelMinT->setObjectName(QStringLiteral("label_LevelMinT"));

        gridLayout_3->addWidget(label_LevelMinT, 11, 5, 1, 3);

        pushButton_SaveFrame = new QPushButton(centralWidget);
        pushButton_SaveFrame->setObjectName(QStringLiteral("pushButton_SaveFrame"));
        sizePolicy.setHeightForWidth(pushButton_SaveFrame->sizePolicy().hasHeightForWidth());
        pushButton_SaveFrame->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(pushButton_SaveFrame, 9, 5, 2, 4);

        doubleSpinBox_MaxT = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_MaxT->setObjectName(QStringLiteral("doubleSpinBox_MaxT"));
        doubleSpinBox_MaxT->setMinimum(-300);
        doubleSpinBox_MaxT->setMaximum(300);
        doubleSpinBox_MaxT->setValue(100);

        gridLayout_3->addWidget(doubleSpinBox_MaxT, 11, 3, 1, 1);

        label_LevelMaxT = new QLabel(centralWidget);
        label_LevelMaxT->setObjectName(QStringLiteral("label_LevelMaxT"));

        gridLayout_3->addWidget(label_LevelMaxT, 11, 0, 1, 3);

        CLabel_VideoImage = new QLabel(centralWidget);
        CLabel_VideoImage->setObjectName(QStringLiteral("CLabel_VideoImage"));

        gridLayout_3->addWidget(CLabel_VideoImage, 0, 5, 5, 4);

        doubleSpinBox_MinT = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_MinT->setObjectName(QStringLiteral("doubleSpinBox_MinT"));
        doubleSpinBox_MinT->setMinimum(-300);
        doubleSpinBox_MinT->setMaximum(300);
        doubleSpinBox_MinT->setValue(-100);

        gridLayout_3->addWidget(doubleSpinBox_MinT, 11, 8, 1, 1);

        label_Alarm = new QLabel(centralWidget);
        label_Alarm->setObjectName(QStringLiteral("label_Alarm"));

        gridLayout_3->addWidget(label_Alarm, 12, 0, 1, 3);

        checkBox_AlarmSaveFrame = new QCheckBox(centralWidget);
        checkBox_AlarmSaveFrame->setObjectName(QStringLiteral("checkBox_AlarmSaveFrame"));

        gridLayout_3->addWidget(checkBox_AlarmSaveFrame, 12, 3, 1, 1);

        comboBox_Language = new QComboBox(centralWidget);
        comboBox_Language->setObjectName(QStringLiteral("comboBox_Language"));

        gridLayout_3->addWidget(comboBox_Language, 12, 5, 1, 4);


        gridLayout_2->addLayout(gridLayout_3, 0, 0, 1, 1);

        CMainWindow->setCentralWidget(centralWidget);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "CMainWindow", Q_NULLPTR));
        label_Emission->setText(QApplication::translate("CMainWindow", "\320\232\320\276\321\215\321\204\321\204\320\270\321\206\320\270\320\265\320\275\321\202 \320\270\320\267\320\273\321\203\321\207\320\265\320\275\320\270\321\217 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\320\260", Q_NULLPTR));
        pushButton_SaveRAW->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \321\204\320\260\320\271\320\273 RAW", Q_NULLPTR));
        pushButton_SaveVideo->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \320\272\320\260\320\264\321\200\321\213 \321\201 \320\262\320\270\320\264\320\265\320\276\320\272\320\260\320\274\320\265\321\200\321\213", Q_NULLPTR));
        label_Palette->setText(QApplication::translate("CMainWindow", "\320\237\320\260\320\273\320\270\321\202\321\200\320\260", Q_NULLPTR));
        pushButton_ShowVideo->setText(QApplication::translate("CMainWindow", "\320\237\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\262\320\270\320\264\320\265\320\276", Q_NULLPTR));
        pushButton_SaveImageNoScale->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \320\270\320\267\320\276\320\261\321\200\320\260\320\266\320\265\320\275\320\270\321\217 \320\261\320\265\320\267 \321\210\320\272\320\260\320\273\321\213", Q_NULLPTR));
        pushButton_ApplyPalette->setText(QApplication::translate("CMainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \320\277\320\260\320\273\320\270\321\202\321\200\321\203", Q_NULLPTR));
        label_Temper->setText(QApplication::translate("CMainWindow", "\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260 \320\261\320\276\320\273\320\276\320\274\320\265\321\202\321\200\320\276\320\262, C", Q_NULLPTR));
        pushButton_SaveAllFrame->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \320\262\321\201\320\265 \320\272\320\260\320\264\321\200\321\213", Q_NULLPTR));
        pushButton_SaveImageCross->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\321\217\321\202\321\214 \321\201 \320\272\320\260\320\264\321\200\321\213 \321\201 \320\277\320\265\321\200\320\265\320\272\321\200\320\265\321\201\321\202\321\214\320\265\320\274", Q_NULLPTR));
        CLabel_ThermalImage->setText(QString());
        label_LevelMinT->setText(QApplication::translate("CMainWindow", "\320\235\320\270\320\266\320\275\321\217\321\217 \320\263\321\200\320\260\320\275\320\270\321\206\320\260 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\321\213 \320\264\320\273\321\217 \321\201\320\270\320\263\320\275\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270", Q_NULLPTR));
        pushButton_SaveFrame->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\276\320\264\320\270\320\275 \320\272\320\260\320\264\321\200", Q_NULLPTR));
        label_LevelMaxT->setText(QApplication::translate("CMainWindow", "\320\222\320\265\321\200\321\205\320\275\321\217\321\217 \320\263\321\200\320\260\320\275\320\270\321\206\320\260 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\321\213 \320\264\320\273\321\217 \321\201\320\270\320\263\320\275\320\260\320\273\320\270\320\267\320\260\321\206\320\270\320\270", Q_NULLPTR));
        CLabel_VideoImage->setText(QString());
        label_Alarm->setText(QApplication::translate("CMainWindow", "\320\237\321\200\320\270 \320\262\321\213\321\205\320\276\320\264\320\265 \320\267\320\260 \320\263\321\200\320\260\320\275\320\270\321\206\321\213 \321\202\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\321\213 \320\262\321\213\320\277\320\276\320\273\320\275\320\270\321\202\321\214:", Q_NULLPTR));
        checkBox_AlarmSaveFrame->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\320\264\321\200", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
