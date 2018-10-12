/********************************************************************************
** Form generated from reading UI file 'meshdatafile.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHDATAFILE_H
#define UI_MESHDATAFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_MeshDataFile
{
public:
    QFrame *BorderTop;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QGroupBox *groupBoxInput1;
    QPushButton *pushButtonElementFile;
    QLabel *textLabel1;
    QLineEdit *lineEditElementFile;
    QLineEdit *lineEditNodeFile;
    QLabel *textLabel1_3;
    QPushButton *pushButtonNodeFile;
    QLineEdit *lineEditNeighbourFile;
    QLabel *textLabel1_4;
    QPushButton *pushButtonNeighbourFile;
    QLineEdit *lineEditRiverFile;
    QLabel *textLabel1_5;
    QPushButton *pushButtonRiverFile;
    QGroupBox *groupBoxOutput;
    QLabel *textLabel1_2;
    QPushButton *pushButtonMeshDataFile;
    QLineEdit *lineEditMeshDataFile;
    QFrame *BorderBottom;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxInput2;
    QPushButton *pushButtonSurfaceElevationFile;
    QLabel *textLabel1_6;
    QLineEdit *lineEditSurfaceElevationFile;
    QLineEdit *lineEditSubsurfaceThickness;
    QLabel *textLabelSubsurface;
    QPushButton *pushButtonSubsurfaceThickness;
    QCheckBox *checkBoxSubsurfaceThickness;
    QDoubleSpinBox *doubleSpinBoxSubSurface;
    QLabel *textLabelSubsurface_2;

    void setupUi(QDialog *MeshDataFile)
    {
        if (MeshDataFile->objectName().isEmpty())
            MeshDataFile->setObjectName(QStringLiteral("MeshDataFile"));
        MeshDataFile->resize(611, 584);
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
        MeshDataFile->setPalette(palette);
        BorderTop = new QFrame(MeshDataFile);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, -4, 611, 20));
        BorderTop->setBaseSize(QSize(0, 0));
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
        BorderTop->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        BorderTop->setFont(font);
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        groupBoxButtons = new QGroupBox(MeshDataFile);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 372, 581, 41));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(10, 3, 113, 32));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonHelp->setFont(font1);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(340, 3, 113, 32));
        pushButtonClose->setFont(font1);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(460, 3, 113, 32));
        pushButtonRun->setFont(font1);
        pushButtonRun->setAutoDefault(false);
        groupBoxInput1 = new QGroupBox(MeshDataFile);
        groupBoxInput1->setObjectName(QStringLiteral("groupBoxInput1"));
        groupBoxInput1->setGeometry(QRect(15, 12, 581, 171));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(11);
        groupBoxInput1->setFont(font2);
        pushButtonElementFile = new QPushButton(groupBoxInput1);
        pushButtonElementFile->setObjectName(QStringLiteral("pushButtonElementFile"));
        pushButtonElementFile->setGeometry(QRect(475, 19, 98, 32));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButtonElementFile->setFont(font3);
        pushButtonElementFile->setCheckable(false);
        pushButtonElementFile->setAutoDefault(false);
        pushButtonElementFile->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput1);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(16, 19, 111, 31));
        textLabel1->setFont(font);
        textLabel1->setLayoutDirection(Qt::LeftToRight);
        textLabel1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditElementFile = new QLineEdit(groupBoxInput1);
        lineEditElementFile->setObjectName(QStringLiteral("lineEditElementFile"));
        lineEditElementFile->setGeometry(QRect(145, 20, 325, 29));
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        lineEditElementFile->setFont(font4);
        lineEditNodeFile = new QLineEdit(groupBoxInput1);
        lineEditNodeFile->setObjectName(QStringLiteral("lineEditNodeFile"));
        lineEditNodeFile->setGeometry(QRect(145, 57, 325, 29));
        lineEditNodeFile->setFont(font4);
        textLabel1_3 = new QLabel(groupBoxInput1);
        textLabel1_3->setObjectName(QStringLiteral("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(16, 56, 111, 31));
        textLabel1_3->setFont(font);
        textLabel1_3->setLayoutDirection(Qt::LeftToRight);
        textLabel1_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonNodeFile = new QPushButton(groupBoxInput1);
        pushButtonNodeFile->setObjectName(QStringLiteral("pushButtonNodeFile"));
        pushButtonNodeFile->setGeometry(QRect(475, 56, 98, 32));
        pushButtonNodeFile->setFont(font3);
        pushButtonNodeFile->setCheckable(false);
        pushButtonNodeFile->setAutoDefault(false);
        pushButtonNodeFile->setFlat(false);
        lineEditNeighbourFile = new QLineEdit(groupBoxInput1);
        lineEditNeighbourFile->setObjectName(QStringLiteral("lineEditNeighbourFile"));
        lineEditNeighbourFile->setGeometry(QRect(145, 94, 325, 29));
        lineEditNeighbourFile->setFont(font4);
        textLabel1_4 = new QLabel(groupBoxInput1);
        textLabel1_4->setObjectName(QStringLiteral("textLabel1_4"));
        textLabel1_4->setGeometry(QRect(16, 93, 111, 31));
        textLabel1_4->setFont(font);
        textLabel1_4->setLayoutDirection(Qt::LeftToRight);
        textLabel1_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonNeighbourFile = new QPushButton(groupBoxInput1);
        pushButtonNeighbourFile->setObjectName(QStringLiteral("pushButtonNeighbourFile"));
        pushButtonNeighbourFile->setGeometry(QRect(475, 93, 98, 32));
        pushButtonNeighbourFile->setFont(font3);
        pushButtonNeighbourFile->setCheckable(false);
        pushButtonNeighbourFile->setAutoDefault(false);
        pushButtonNeighbourFile->setFlat(false);
        lineEditRiverFile = new QLineEdit(groupBoxInput1);
        lineEditRiverFile->setObjectName(QStringLiteral("lineEditRiverFile"));
        lineEditRiverFile->setGeometry(QRect(145, 130, 325, 29));
        lineEditRiverFile->setFont(font4);
        textLabel1_5 = new QLabel(groupBoxInput1);
        textLabel1_5->setObjectName(QStringLiteral("textLabel1_5"));
        textLabel1_5->setGeometry(QRect(6, 129, 121, 31));
        textLabel1_5->setFont(font);
        textLabel1_5->setLayoutDirection(Qt::LeftToRight);
        textLabel1_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonRiverFile = new QPushButton(groupBoxInput1);
        pushButtonRiverFile->setObjectName(QStringLiteral("pushButtonRiverFile"));
        pushButtonRiverFile->setGeometry(QRect(475, 129, 98, 32));
        pushButtonRiverFile->setFont(font3);
        pushButtonRiverFile->setCheckable(false);
        pushButtonRiverFile->setAutoDefault(false);
        pushButtonRiverFile->setFlat(false);
        groupBoxOutput = new QGroupBox(MeshDataFile);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(15, 307, 581, 61));
        groupBoxOutput->setFont(font2);
        textLabel1_2 = new QLabel(groupBoxOutput);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(16, 20, 121, 31));
        QFont font5;
        font5.setBold(true);
        font5.setWeight(75);
        textLabel1_2->setFont(font5);
        textLabel1_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonMeshDataFile = new QPushButton(groupBoxOutput);
        pushButtonMeshDataFile->setObjectName(QStringLiteral("pushButtonMeshDataFile"));
        pushButtonMeshDataFile->setGeometry(QRect(475, 20, 98, 32));
        pushButtonMeshDataFile->setFont(font3);
        pushButtonMeshDataFile->setAutoDefault(false);
        lineEditMeshDataFile = new QLineEdit(groupBoxOutput);
        lineEditMeshDataFile->setObjectName(QStringLiteral("lineEditMeshDataFile"));
        lineEditMeshDataFile->setGeometry(QRect(145, 21, 325, 29));
        lineEditMeshDataFile->setFont(font4);
        BorderBottom = new QFrame(MeshDataFile);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 568, 611, 20));
        BorderBottom->setBaseSize(QSize(0, 0));
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
        BorderBottom->setPalette(palette2);
        BorderBottom->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderBottom->setFrameShadow(QFrame::Plain);
        BorderBottom->setLineWidth(12);
        BorderBottom->setMidLineWidth(0);
        BorderBottom->setFrameShape(QFrame::HLine);
        textBrowserLogs = new QTextBrowser(MeshDataFile);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 419, 581, 151));
        textBrowserLogs->setFont(font2);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxInput2 = new QGroupBox(MeshDataFile);
        groupBoxInput2->setObjectName(QStringLiteral("groupBoxInput2"));
        groupBoxInput2->setGeometry(QRect(15, 185, 581, 121));
        groupBoxInput2->setFont(font2);
        pushButtonSurfaceElevationFile = new QPushButton(groupBoxInput2);
        pushButtonSurfaceElevationFile->setObjectName(QStringLiteral("pushButtonSurfaceElevationFile"));
        pushButtonSurfaceElevationFile->setGeometry(QRect(475, 13, 98, 32));
        pushButtonSurfaceElevationFile->setFont(font3);
        pushButtonSurfaceElevationFile->setCheckable(false);
        pushButtonSurfaceElevationFile->setAutoDefault(false);
        pushButtonSurfaceElevationFile->setFlat(false);
        textLabel1_6 = new QLabel(groupBoxInput2);
        textLabel1_6->setObjectName(QStringLiteral("textLabel1_6"));
        textLabel1_6->setGeometry(QRect(16, 13, 111, 31));
        textLabel1_6->setFont(font);
        textLabel1_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEditSurfaceElevationFile = new QLineEdit(groupBoxInput2);
        lineEditSurfaceElevationFile->setObjectName(QStringLiteral("lineEditSurfaceElevationFile"));
        lineEditSurfaceElevationFile->setGeometry(QRect(145, 14, 325, 29));
        lineEditSurfaceElevationFile->setFont(font4);
        lineEditSubsurfaceThickness = new QLineEdit(groupBoxInput2);
        lineEditSubsurfaceThickness->setObjectName(QStringLiteral("lineEditSubsurfaceThickness"));
        lineEditSubsurfaceThickness->setGeometry(QRect(145, 51, 325, 29));
        lineEditSubsurfaceThickness->setFont(font4);
        textLabelSubsurface = new QLabel(groupBoxInput2);
        textLabelSubsurface->setObjectName(QStringLiteral("textLabelSubsurface"));
        textLabelSubsurface->setGeometry(QRect(20, 50, 111, 31));
        textLabelSubsurface->setFont(font);
        textLabelSubsurface->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButtonSubsurfaceThickness = new QPushButton(groupBoxInput2);
        pushButtonSubsurfaceThickness->setObjectName(QStringLiteral("pushButtonSubsurfaceThickness"));
        pushButtonSubsurfaceThickness->setGeometry(QRect(475, 50, 98, 32));
        pushButtonSubsurfaceThickness->setFont(font3);
        pushButtonSubsurfaceThickness->setCheckable(false);
        pushButtonSubsurfaceThickness->setAutoDefault(false);
        pushButtonSubsurfaceThickness->setFlat(false);
        checkBoxSubsurfaceThickness = new QCheckBox(groupBoxInput2);
        checkBoxSubsurfaceThickness->setObjectName(QStringLiteral("checkBoxSubsurfaceThickness"));
        checkBoxSubsurfaceThickness->setGeometry(QRect(290, 90, 16, 23));
        doubleSpinBoxSubSurface = new QDoubleSpinBox(groupBoxInput2);
        doubleSpinBoxSubSurface->setObjectName(QStringLiteral("doubleSpinBoxSubSurface"));
        doubleSpinBoxSubSurface->setGeometry(QRect(310, 90, 101, 22));
        doubleSpinBoxSubSurface->setDecimals(4);
        doubleSpinBoxSubSurface->setMaximum(10000);
        doubleSpinBoxSubSurface->setValue(5);
        textLabelSubsurface_2 = new QLabel(groupBoxInput2);
        textLabelSubsurface_2->setObjectName(QStringLiteral("textLabelSubsurface_2"));
        textLabelSubsurface_2->setGeometry(QRect(0, 85, 281, 31));
        textLabelSubsurface_2->setFont(font);
        textLabelSubsurface_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        retranslateUi(MeshDataFile);

        QMetaObject::connectSlotsByName(MeshDataFile);
    } // setupUi

    void retranslateUi(QDialog *MeshDataFile)
    {
        MeshDataFile->setWindowTitle(QApplication::translate("MeshDataFile", "Mesh Data File ", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("MeshDataFile", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("MeshDataFile", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("MeshDataFile", "Run", nullptr));
        groupBoxInput1->setTitle(QApplication::translate("MeshDataFile", "Input", nullptr));
        pushButtonElementFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("MeshDataFile", "Element File", nullptr));
        textLabel1_3->setText(QApplication::translate("MeshDataFile", "Node File", nullptr));
        pushButtonNodeFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        textLabel1_4->setText(QApplication::translate("MeshDataFile", "Neighbour File", nullptr));
        pushButtonNeighbourFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        textLabel1_5->setText(QApplication::translate("MeshDataFile", "River Shape File", nullptr));
        pushButtonRiverFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        groupBoxOutput->setTitle(QApplication::translate("MeshDataFile", "Output", nullptr));
        textLabel1_2->setText(QApplication::translate("MeshDataFile", "Mesh Data File", nullptr));
        pushButtonMeshDataFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        groupBoxInput2->setTitle(QApplication::translate("MeshDataFile", "Elevation", nullptr));
        pushButtonSurfaceElevationFile->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        textLabel1_6->setText(QApplication::translate("MeshDataFile", "Surface", nullptr));
        textLabelSubsurface->setText(QApplication::translate("MeshDataFile", "Subsurface File\n"
"Thickness (m)", nullptr));
        pushButtonSubsurfaceThickness->setText(QApplication::translate("MeshDataFile", "Browse", nullptr));
        checkBoxSubsurfaceThickness->setText(QString());
        textLabelSubsurface_2->setText(QApplication::translate("MeshDataFile", "OR Specify Subsurface Thickness (m)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MeshDataFile: public Ui_MeshDataFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHDATAFILE_H
