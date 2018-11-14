/********************************************************************************
** Form generated from reading UI file 'initdatafile.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITDATAFILE_H
#define UI_INITDATAFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_InitDataFile
{
public:
    QGroupBox *groupBoxOutput;
    QLabel *textLabel2;
    QPushButton *pushButtonInitDataFile;
    QLineEdit *lineEditInitDataFile;
    QFrame *BorderBottom;
    QFrame *BorderTop;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QGroupBox *groupBoxInput_2;
    QPushButton *pushButtonMeshDataFile;
    QLabel *textLabel1;
    QLineEdit *lineEditMeshDataFile;
    QLabel *textLabel1_4;
    QPushButton *pushButtonRivDataFile;
    QLineEdit *lineEditRivDataFile;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxInput_1;
    QLabel *textLabel1_2;
    QLineEdit *lineEditInterception;
    QRadioButton *radioButtonMeters;
    QRadioButton *radioButtonPercent;
    QLabel *textLabel1_5;
    QLabel *textLabel1_6;
    QLineEdit *lineEditSnow;
    QLineEdit *lineEditSurface;
    QFrame *line;
    QLabel *textLabel1_7;
    QLabel *textLabel1_8;
    QLineEdit *lineEditGroundwater;
    QLineEdit *lineEditSoilMoisture;
    QLabel *textLabel1_9;
    QLineEdit *lineEditRiverbed;
    QLineEdit *lineEditRiver;
    QLabel *textLabel1_10;

    void setupUi(QDialog *InitDataFile)
    {
        if (InitDataFile->objectName().isEmpty())
            InitDataFile->setObjectName(QStringLiteral("InitDataFile"));
        InitDataFile->resize(800, 539);
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
        InitDataFile->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        InitDataFile->setFont(font);
        groupBoxOutput = new QGroupBox(InitDataFile);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(5, 290, 781, 91));
        textLabel2 = new QLabel(groupBoxOutput);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setGeometry(QRect(309, 15, 131, 31));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        textLabel2->setFont(font1);
        textLabel2->setAlignment(Qt::AlignCenter);
        pushButtonInitDataFile = new QPushButton(groupBoxOutput);
        pushButtonInitDataFile->setObjectName(QStringLiteral("pushButtonInitDataFile"));
        pushButtonInitDataFile->setGeometry(QRect(678, 10, 98, 32));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        pushButtonInitDataFile->setFont(font2);
        pushButtonInitDataFile->setAutoDefault(false);
        lineEditInitDataFile = new QLineEdit(groupBoxOutput);
        lineEditInitDataFile->setObjectName(QStringLiteral("lineEditInitDataFile"));
        lineEditInitDataFile->setGeometry(QRect(5, 45, 771, 29));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        lineEditInitDataFile->setFont(font3);
        BorderBottom = new QFrame(InitDataFile);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 523, 800, 20));
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
        BorderTop = new QFrame(InitDataFile);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, -4, 800, 20));
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
        groupBoxButtons = new QGroupBox(InitDataFile);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(5, 379, 781, 41));
        groupBoxButtons->setFont(font2);
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(10, 4, 113, 32));
        pushButtonHelp->setFont(font2);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(544, 4, 113, 32));
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(664, 4, 113, 32));
        pushButtonRun->setFont(font2);
        pushButtonRun->setAutoDefault(false);
        groupBoxInput_2 = new QGroupBox(InitDataFile);
        groupBoxInput_2->setObjectName(QStringLiteral("groupBoxInput_2"));
        groupBoxInput_2->setGeometry(QRect(5, 141, 781, 151));
        pushButtonMeshDataFile = new QPushButton(groupBoxInput_2);
        pushButtonMeshDataFile->setObjectName(QStringLiteral("pushButtonMeshDataFile"));
        pushButtonMeshDataFile->setGeometry(QRect(678, 3, 98, 32));
        pushButtonMeshDataFile->setFont(font2);
        pushButtonMeshDataFile->setCheckable(false);
        pushButtonMeshDataFile->setAutoDefault(false);
        pushButtonMeshDataFile->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput_2);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(320, 9, 111, 31));
        textLabel1->setFont(font1);
        textLabel1->setAlignment(Qt::AlignCenter);
        lineEditMeshDataFile = new QLineEdit(groupBoxInput_2);
        lineEditMeshDataFile->setObjectName(QStringLiteral("lineEditMeshDataFile"));
        lineEditMeshDataFile->setGeometry(QRect(7, 37, 771, 29));
        lineEditMeshDataFile->setFont(font3);
        textLabel1_4 = new QLabel(groupBoxInput_2);
        textLabel1_4->setObjectName(QStringLiteral("textLabel1_4"));
        textLabel1_4->setGeometry(QRect(318, 76, 111, 31));
        textLabel1_4->setFont(font1);
        textLabel1_4->setAlignment(Qt::AlignCenter);
        pushButtonRivDataFile = new QPushButton(groupBoxInput_2);
        pushButtonRivDataFile->setObjectName(QStringLiteral("pushButtonRivDataFile"));
        pushButtonRivDataFile->setGeometry(QRect(678, 70, 98, 32));
        pushButtonRivDataFile->setFont(font2);
        pushButtonRivDataFile->setCheckable(false);
        pushButtonRivDataFile->setAutoDefault(false);
        pushButtonRivDataFile->setFlat(false);
        lineEditRivDataFile = new QLineEdit(groupBoxInput_2);
        lineEditRivDataFile->setObjectName(QStringLiteral("lineEditRivDataFile"));
        lineEditRivDataFile->setGeometry(QRect(7, 105, 771, 29));
        lineEditRivDataFile->setFont(font3);
        textBrowserLogs = new QTextBrowser(InitDataFile);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(5, 428, 781, 91));
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxInput_1 = new QGroupBox(InitDataFile);
        groupBoxInput_1->setObjectName(QStringLiteral("groupBoxInput_1"));
        groupBoxInput_1->setGeometry(QRect(5, 12, 781, 131));
        textLabel1_2 = new QLabel(groupBoxInput_1);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(20, 14, 91, 31));
        textLabel1_2->setFont(font2);
        lineEditInterception = new QLineEdit(groupBoxInput_1);
        lineEditInterception->setObjectName(QStringLiteral("lineEditInterception"));
        lineEditInterception->setGeometry(QRect(120, 16, 130, 29));
        lineEditInterception->setFont(font3);
        lineEditInterception->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        radioButtonMeters = new QRadioButton(groupBoxInput_1);
        radioButtonMeters->setObjectName(QStringLiteral("radioButtonMeters"));
        radioButtonMeters->setGeometry(QRect(420, 13, 111, 23));
        radioButtonMeters->setFont(font2);
        radioButtonMeters->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        radioButtonPercent = new QRadioButton(groupBoxInput_1);
        radioButtonPercent->setObjectName(QStringLiteral("radioButtonPercent"));
        radioButtonPercent->setGeometry(QRect(560, 13, 101, 23));
        radioButtonPercent->setFont(font2);
        radioButtonPercent->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        textLabel1_5 = new QLabel(groupBoxInput_1);
        textLabel1_5->setObjectName(QStringLiteral("textLabel1_5"));
        textLabel1_5->setGeometry(QRect(62, 51, 50, 31));
        textLabel1_5->setFont(font2);
        textLabel1_6 = new QLabel(groupBoxInput_1);
        textLabel1_6->setObjectName(QStringLiteral("textLabel1_6"));
        textLabel1_6->setGeometry(QRect(50, 88, 61, 31));
        textLabel1_6->setFont(font2);
        lineEditSnow = new QLineEdit(groupBoxInput_1);
        lineEditSnow->setObjectName(QStringLiteral("lineEditSnow"));
        lineEditSnow->setGeometry(QRect(120, 53, 130, 29));
        lineEditSnow->setFont(font3);
        lineEditSnow->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditSurface = new QLineEdit(groupBoxInput_1);
        lineEditSurface->setObjectName(QStringLiteral("lineEditSurface"));
        lineEditSurface->setGeometry(QRect(120, 90, 130, 29));
        lineEditSurface->setFont(font3);
        lineEditSurface->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        line = new QFrame(groupBoxInput_1);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(270, 10, 20, 111));
        line->setFrameShadow(QFrame::Plain);
        line->setLineWidth(2);
        line->setMidLineWidth(2);
        line->setFrameShape(QFrame::VLine);
        textLabel1_7 = new QLabel(groupBoxInput_1);
        textLabel1_7->setObjectName(QStringLiteral("textLabel1_7"));
        textLabel1_7->setGeometry(QRect(302, 46, 111, 31));
        textLabel1_7->setFont(font2);
        textLabel1_7->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        textLabel1_8 = new QLabel(groupBoxInput_1);
        textLabel1_8->setObjectName(QStringLiteral("textLabel1_8"));
        textLabel1_8->setGeometry(QRect(302, 87, 111, 31));
        textLabel1_8->setFont(font2);
        textLabel1_8->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        lineEditGroundwater = new QLineEdit(groupBoxInput_1);
        lineEditGroundwater->setObjectName(QStringLiteral("lineEditGroundwater"));
        lineEditGroundwater->setGeometry(QRect(414, 88, 130, 29));
        lineEditGroundwater->setFont(font3);
        lineEditGroundwater->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditSoilMoisture = new QLineEdit(groupBoxInput_1);
        lineEditSoilMoisture->setObjectName(QStringLiteral("lineEditSoilMoisture"));
        lineEditSoilMoisture->setGeometry(QRect(414, 47, 130, 29));
        lineEditSoilMoisture->setFont(font3);
        lineEditSoilMoisture->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_9 = new QLabel(groupBoxInput_1);
        textLabel1_9->setObjectName(QStringLiteral("textLabel1_9"));
        textLabel1_9->setGeometry(QRect(552, 43, 81, 31));
        textLabel1_9->setFont(font2);
        textLabel1_9->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        textLabel1_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditRiverbed = new QLineEdit(groupBoxInput_1);
        lineEditRiverbed->setObjectName(QStringLiteral("lineEditRiverbed"));
        lineEditRiverbed->setGeometry(QRect(642, 85, 130, 29));
        lineEditRiverbed->setFont(font3);
        lineEditRiverbed->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditRiver = new QLineEdit(groupBoxInput_1);
        lineEditRiver->setObjectName(QStringLiteral("lineEditRiver"));
        lineEditRiver->setGeometry(QRect(642, 44, 130, 29));
        lineEditRiver->setFont(font3);
        lineEditRiver->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel1_10 = new QLabel(groupBoxInput_1);
        textLabel1_10->setObjectName(QStringLiteral("textLabel1_10"));
        textLabel1_10->setGeometry(QRect(552, 84, 81, 31));
        textLabel1_10->setFont(font2);
        textLabel1_10->setStyleSheet(QStringLiteral("color: rgb(85, 0, 255);"));
        textLabel1_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(InitDataFile);

        QMetaObject::connectSlotsByName(InitDataFile);
    } // setupUi

    void retranslateUi(QDialog *InitDataFile)
    {
        InitDataFile->setWindowTitle(QApplication::translate("InitDataFile", "Init Data File", nullptr));
        groupBoxOutput->setTitle(QApplication::translate("InitDataFile", "Output", nullptr));
        textLabel2->setText(QApplication::translate("InitDataFile", "Init Data File", nullptr));
        pushButtonInitDataFile->setText(QApplication::translate("InitDataFile", "Browse", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("InitDataFile", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("InitDataFile", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("InitDataFile", "Run", nullptr));
        groupBoxInput_2->setTitle(QString());
        pushButtonMeshDataFile->setText(QApplication::translate("InitDataFile", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("InitDataFile", "Mesh Data File", nullptr));
        textLabel1_4->setText(QApplication::translate("InitDataFile", "Riv Data File", nullptr));
        pushButtonRivDataFile->setText(QApplication::translate("InitDataFile", "Browse", nullptr));
        groupBoxInput_1->setTitle(QApplication::translate("InitDataFile", "Input", nullptr));
        textLabel1_2->setText(QApplication::translate("InitDataFile", "Interception", nullptr));
        radioButtonMeters->setText(QApplication::translate("InitDataFile", " * meters", nullptr));
        radioButtonPercent->setText(QApplication::translate("InitDataFile", " * percent", nullptr));
        textLabel1_5->setText(QApplication::translate("InitDataFile", "Snow", nullptr));
        textLabel1_6->setText(QApplication::translate("InitDataFile", "Surface", nullptr));
        textLabel1_7->setText(QApplication::translate("InitDataFile", "*Soil Moisture", nullptr));
        textLabel1_8->setText(QApplication::translate("InitDataFile", "*Groundwater", nullptr));
        textLabel1_9->setText(QApplication::translate("InitDataFile", "*River", nullptr));
        textLabel1_10->setText(QApplication::translate("InitDataFile", "*Riverbed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InitDataFile: public Ui_InitDataFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITDATAFILE_H
