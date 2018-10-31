/********************************************************************************
** Form generated from reading UI file 'riverspatial.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIVERSPATIAL_H
#define UI_RIVERSPATIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_RiverSpatial
{
public:
    QFrame *BorderBottom;
    QFrame *BorderTop;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxOutput;
    QLabel *textLabel2;
    QPushButton *pushButtonOutputDataFolder;
    QLineEdit *lineEditOutputDataFolder;
    QLineEdit *lineEditDataKey;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QLabel *textLabel2_5;
    QLineEdit *lineEditRiverShapeFile;
    QPushButton *pushButtonRiverShapeFile;
    QLabel *textLabel2_6;
    QLabel *textLabel2_7;
    QSpinBox *spinBoxStartTime;
    QSpinBox *spinBoxStopTime;
    QComboBox *comboBoxStartStop;
    QLabel *textLabel2_8;
    QSpinBox *spinBoxNumBreaks;
    QComboBox *comboBoxPlotVariable;

    void setupUi(QDialog *RiverSpatial)
    {
        if (RiverSpatial->objectName().isEmpty())
            RiverSpatial->setObjectName(QStringLiteral("RiverSpatial"));
        RiverSpatial->resize(611, 467);
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush1);
        QBrush brush2(QColor(127, 127, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush2);
        QBrush brush3(QColor(170, 170, 170, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush1);
        QBrush brush4(QColor(255, 255, 220, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        RiverSpatial->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        RiverSpatial->setFont(font);
        BorderBottom = new QFrame(RiverSpatial);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 451, 611, 20));
        BorderBottom->setBaseSize(QSize(0, 0));
        QPalette palette1;
        QBrush brush5(QColor(0, 51, 153, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        QBrush brush6(QColor(128, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush6);
        QBrush brush7(QColor(192, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush7);
        QBrush brush8(QColor(160, 0, 0, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        QBrush brush9(QColor(64, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush9);
        QBrush brush10(QColor(85, 0, 0, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush9);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        BorderBottom->setPalette(palette1);
        BorderBottom->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderBottom->setFrameShadow(QFrame::Plain);
        BorderBottom->setLineWidth(12);
        BorderBottom->setMidLineWidth(0);
        BorderBottom->setFrameShape(QFrame::HLine);
        BorderTop = new QFrame(RiverSpatial);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, -4, 611, 20));
        BorderTop->setBaseSize(QSize(0, 0));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush8);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush9);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush10);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush5);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush5);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush9);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush10);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush9);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush9);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush10);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        BorderTop->setPalette(palette2);
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        groupBoxButtons = new QGroupBox(RiverSpatial);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 265, 581, 41));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(10, 5, 113, 32));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonHelp->setFont(font1);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(340, 5, 113, 32));
        pushButtonClose->setFont(font1);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(460, 5, 113, 32));
        pushButtonRun->setFont(font1);
        pushButtonRun->setAutoDefault(false);
        textBrowserLogs = new QTextBrowser(RiverSpatial);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 306, 581, 141));
        QFont font2;
        font2.setPointSize(11);
        textBrowserLogs->setFont(font2);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxOutput = new QGroupBox(RiverSpatial);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(15, 26, 581, 241));
        textLabel2 = new QLabel(groupBoxOutput);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setGeometry(QRect(194, 7, 151, 31));
        textLabel2->setFont(font1);
        textLabel2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonOutputDataFolder = new QPushButton(groupBoxOutput);
        pushButtonOutputDataFolder->setObjectName(QStringLiteral("pushButtonOutputDataFolder"));
        pushButtonOutputDataFolder->setGeometry(QRect(480, 0, 98, 32));
        pushButtonOutputDataFolder->setFont(font1);
        pushButtonOutputDataFolder->setAutoDefault(false);
        lineEditOutputDataFolder = new QLineEdit(groupBoxOutput);
        lineEditOutputDataFolder->setObjectName(QStringLiteral("lineEditOutputDataFolder"));
        lineEditOutputDataFolder->setGeometry(QRect(5, 33, 571, 29));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        lineEditOutputDataFolder->setFont(font3);
        lineEditDataKey = new QLineEdit(groupBoxOutput);
        lineEditDataKey->setObjectName(QStringLiteral("lineEditDataKey"));
        lineEditDataKey->setGeometry(QRect(124, 67, 451, 29));
        lineEditDataKey->setFont(font3);
        textLabel2_2 = new QLabel(groupBoxOutput);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(-14, 66, 131, 31));
        textLabel2_2->setFont(font1);
        textLabel2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3 = new QLabel(groupBoxOutput);
        textLabel2_3->setObjectName(QStringLiteral("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(-16, 101, 131, 31));
        textLabel2_3->setFont(font1);
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_5 = new QLabel(groupBoxOutput);
        textLabel2_5->setObjectName(QStringLiteral("textLabel2_5"));
        textLabel2_5->setGeometry(QRect(200, 175, 131, 31));
        textLabel2_5->setFont(font1);
        textLabel2_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditRiverShapeFile = new QLineEdit(groupBoxOutput);
        lineEditRiverShapeFile->setObjectName(QStringLiteral("lineEditRiverShapeFile"));
        lineEditRiverShapeFile->setGeometry(QRect(10, 200, 561, 29));
        lineEditRiverShapeFile->setFont(font3);
        pushButtonRiverShapeFile = new QPushButton(groupBoxOutput);
        pushButtonRiverShapeFile->setObjectName(QStringLiteral("pushButtonRiverShapeFile"));
        pushButtonRiverShapeFile->setGeometry(QRect(474, 167, 98, 32));
        pushButtonRiverShapeFile->setFont(font1);
        pushButtonRiverShapeFile->setAutoDefault(false);
        textLabel2_6 = new QLabel(groupBoxOutput);
        textLabel2_6->setObjectName(QStringLiteral("textLabel2_6"));
        textLabel2_6->setGeometry(QRect(-16, 134, 131, 31));
        textLabel2_6->setFont(font1);
        textLabel2_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_7 = new QLabel(groupBoxOutput);
        textLabel2_7->setObjectName(QStringLiteral("textLabel2_7"));
        textLabel2_7->setGeometry(QRect(210, 134, 31, 31));
        textLabel2_7->setFont(font1);
        spinBoxStartTime = new QSpinBox(groupBoxOutput);
        spinBoxStartTime->setObjectName(QStringLiteral("spinBoxStartTime"));
        spinBoxStartTime->setGeometry(QRect(128, 134, 71, 29));
        spinBoxStartTime->setFont(font1);
        spinBoxStartTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxStartTime->setMaximum(999999999);
        spinBoxStopTime = new QSpinBox(groupBoxOutput);
        spinBoxStopTime->setObjectName(QStringLiteral("spinBoxStopTime"));
        spinBoxStopTime->setGeometry(QRect(235, 134, 71, 29));
        spinBoxStopTime->setFont(font1);
        spinBoxStopTime->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxStopTime->setMaximum(999999999);
        spinBoxStopTime->setValue(2);
        comboBoxStartStop = new QComboBox(groupBoxOutput);
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->addItem(QString());
        comboBoxStartStop->setObjectName(QStringLiteral("comboBoxStartStop"));
        comboBoxStartStop->setGeometry(QRect(320, 134, 131, 28));
        comboBoxStartStop->setFont(font1);
        textLabel2_8 = new QLabel(groupBoxOutput);
        textLabel2_8->setObjectName(QStringLiteral("textLabel2_8"));
        textLabel2_8->setGeometry(QRect(454, 134, 41, 31));
        textLabel2_8->setFont(font1);
        spinBoxNumBreaks = new QSpinBox(groupBoxOutput);
        spinBoxNumBreaks->setObjectName(QStringLiteral("spinBoxNumBreaks"));
        spinBoxNumBreaks->setGeometry(QRect(500, 134, 71, 29));
        spinBoxNumBreaks->setFont(font1);
        spinBoxNumBreaks->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBoxNumBreaks->setMaximum(999999999);
        spinBoxNumBreaks->setValue(1);
        comboBoxPlotVariable = new QComboBox(groupBoxOutput);
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->addItem(QString());
        comboBoxPlotVariable->setObjectName(QStringLiteral("comboBoxPlotVariable"));
        comboBoxPlotVariable->setGeometry(QRect(124, 102, 451, 28));
        comboBoxPlotVariable->setFont(font1);

        retranslateUi(RiverSpatial);

        comboBoxStartStop->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RiverSpatial);
    } // setupUi

    void retranslateUi(QDialog *RiverSpatial)
    {
        RiverSpatial->setWindowTitle(QApplication::translate("RiverSpatial", "River Spatial Analysis", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("RiverSpatial", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("RiverSpatial", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("RiverSpatial", "Run", nullptr));
        groupBoxOutput->setTitle(QString());
        textLabel2->setText(QApplication::translate("RiverSpatial", "Output Data Folder", nullptr));
        pushButtonOutputDataFolder->setText(QApplication::translate("RiverSpatial", "Browse", nullptr));
        textLabel2_2->setText(QApplication::translate("RiverSpatial", "Data Key (ID)", nullptr));
        textLabel2_3->setText(QApplication::translate("RiverSpatial", "Plot Variable", nullptr));
        textLabel2_5->setText(QApplication::translate("RiverSpatial", "River Shape File", nullptr));
        pushButtonRiverShapeFile->setText(QApplication::translate("RiverSpatial", "Browse", nullptr));
        textLabel2_6->setText(QApplication::translate("RiverSpatial", "Time Interval", nullptr));
        textLabel2_7->setText(QApplication::translate("RiverSpatial", "to", nullptr));
        comboBoxStartStop->setItemText(0, QApplication::translate("RiverSpatial", "Minutes", nullptr));
        comboBoxStartStop->setItemText(1, QApplication::translate("RiverSpatial", "Hours", nullptr));
        comboBoxStartStop->setItemText(2, QApplication::translate("RiverSpatial", "Days", nullptr));
        comboBoxStartStop->setItemText(3, QApplication::translate("RiverSpatial", "Weeks", nullptr));
        comboBoxStartStop->setItemText(4, QApplication::translate("RiverSpatial", "Months", nullptr));
        comboBoxStartStop->setItemText(5, QApplication::translate("RiverSpatial", "Years", nullptr));

        comboBoxStartStop->setCurrentText(QApplication::translate("RiverSpatial", "Minutes", nullptr));
        textLabel2_8->setText(QApplication::translate("RiverSpatial", "into", nullptr));
        comboBoxPlotVariable->setItemText(0, QApplication::translate("RiverSpatial", "River Outflow", nullptr));
        comboBoxPlotVariable->setItemText(1, QApplication::translate("RiverSpatial", "River Inflow", nullptr));
        comboBoxPlotVariable->setItemText(2, QApplication::translate("RiverSpatial", "River Storage", nullptr));
        comboBoxPlotVariable->setItemText(3, QApplication::translate("RiverSpatial", "River Surfaceflow", nullptr));
        comboBoxPlotVariable->setItemText(4, QApplication::translate("RiverSpatial", "River Baseflow", nullptr));
        comboBoxPlotVariable->setItemText(5, QApplication::translate("RiverSpatial", "River Surfaceflow Left", nullptr));
        comboBoxPlotVariable->setItemText(6, QApplication::translate("RiverSpatial", "River Surfaceflow Right", nullptr));
        comboBoxPlotVariable->setItemText(7, QApplication::translate("RiverSpatial", "River Baseflow Left", nullptr));
        comboBoxPlotVariable->setItemText(8, QApplication::translate("RiverSpatial", "River Baseflow Right", nullptr));
        comboBoxPlotVariable->setItemText(9, QApplication::translate("RiverSpatial", "River Seepage to Bed", nullptr));
        comboBoxPlotVariable->setItemText(10, QApplication::translate("RiverSpatial", "Riverbed Outflow", nullptr));
        comboBoxPlotVariable->setItemText(11, QApplication::translate("RiverSpatial", "Riverbed Inflow", nullptr));
        comboBoxPlotVariable->setItemText(12, QApplication::translate("RiverSpatial", "Riverbed Storage", nullptr));
        comboBoxPlotVariable->setItemText(13, QApplication::translate("RiverSpatial", "Riverbed Baseflow ", nullptr));
        comboBoxPlotVariable->setItemText(14, QApplication::translate("RiverSpatial", "Riverbed Baseflow Left", nullptr));
        comboBoxPlotVariable->setItemText(15, QApplication::translate("RiverSpatial", "Riverbed Baseflow Right", nullptr));

    } // retranslateUi

};

namespace Ui {
    class RiverSpatial: public Ui_RiverSpatial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIVERSPATIAL_H
