/********************************************************************************
** Form generated from reading UI file 'flowgrids.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FLOWGRIDS_H
#define UI_FLOWGRIDS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_FlowGrids
{
public:
    QTextBrowser *textBrowserLogs;
    QFrame *BorderTop;
    QGroupBox *groupBoxInput;
    QLineEdit *lineEditFillPits;
    QPushButton *pushButtonFillPits;
    QLabel *textLabel1;
    QFrame *BorderBottom;
    QGroupBox *groupBoxInput_2;
    QLabel *textLabel1_2;
    QCheckBox *checkBoxFlowDirGrid;
    QPushButton *pushButtonFlowAccGrid;
    QLineEdit *lineEditFlowAccGrids;
    QLabel *textLabel1_2_2;
    QLineEdit *lineEditFlowDirGrids;
    QCheckBox *checkBoxFlowAccGrid;
    QPushButton *pushButtonsFlowDirGrid;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;

    void setupUi(QDialog *FlowGrids)
    {
        if (FlowGrids->objectName().isEmpty())
            FlowGrids->setObjectName(QStringLiteral("FlowGrids"));
        FlowGrids->resize(611, 480);
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
        FlowGrids->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        FlowGrids->setFont(font);
        textBrowserLogs = new QTextBrowser(FlowGrids);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 357, 581, 101));
        QFont font1;
        font1.setPointSize(11);
        textBrowserLogs->setFont(font1);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        BorderTop = new QFrame(FlowGrids);
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
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        groupBoxInput = new QGroupBox(FlowGrids);
        groupBoxInput->setObjectName(QStringLiteral("groupBoxInput"));
        groupBoxInput->setGeometry(QRect(15, 17, 581, 81));
        lineEditFillPits = new QLineEdit(groupBoxInput);
        lineEditFillPits->setObjectName(QStringLiteral("lineEditFillPits"));
        lineEditFillPits->setGeometry(QRect(10, 44, 561, 29));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(true);
        font2.setWeight(75);
        lineEditFillPits->setFont(font2);
        pushButtonFillPits = new QPushButton(groupBoxInput);
        pushButtonFillPits->setObjectName(QStringLiteral("pushButtonFillPits"));
        pushButtonFillPits->setGeometry(QRect(480, 10, 98, 32));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButtonFillPits->setFont(font3);
        pushButtonFillPits->setCheckable(false);
        pushButtonFillPits->setAutoDefault(false);
        pushButtonFillPits->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(170, 10, 271, 31));
        textLabel1->setFont(font3);
        BorderBottom = new QFrame(FlowGrids);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 464, 611, 20));
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
        groupBoxInput_2 = new QGroupBox(FlowGrids);
        groupBoxInput_2->setObjectName(QStringLiteral("groupBoxInput_2"));
        groupBoxInput_2->setGeometry(QRect(15, 95, 581, 201));
        textLabel1_2 = new QLabel(groupBoxInput_2);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(230, 10, 121, 31));
        textLabel1_2->setFont(font3);
        checkBoxFlowDirGrid = new QCheckBox(groupBoxInput_2);
        checkBoxFlowDirGrid->setObjectName(QStringLiteral("checkBoxFlowDirGrid"));
        checkBoxFlowDirGrid->setEnabled(false);
        checkBoxFlowDirGrid->setGeometry(QRect(480, 80, 101, 21));
        QFont font4;
        font4.setFamily(QStringLiteral("Sans Serif"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(50);
        font4.setStrikeOut(false);
        checkBoxFlowDirGrid->setFont(font4);
        checkBoxFlowDirGrid->setChecked(false);
        pushButtonFlowAccGrid = new QPushButton(groupBoxInput_2);
        pushButtonFlowAccGrid->setObjectName(QStringLiteral("pushButtonFlowAccGrid"));
        pushButtonFlowAccGrid->setGeometry(QRect(480, 110, 98, 32));
        pushButtonFlowAccGrid->setFont(font3);
        pushButtonFlowAccGrid->setAutoDefault(false);
        lineEditFlowAccGrids = new QLineEdit(groupBoxInput_2);
        lineEditFlowAccGrids->setObjectName(QStringLiteral("lineEditFlowAccGrids"));
        lineEditFlowAccGrids->setGeometry(QRect(10, 150, 561, 29));
        lineEditFlowAccGrids->setFont(font2);
        textLabel1_2_2 = new QLabel(groupBoxInput_2);
        textLabel1_2_2->setObjectName(QStringLiteral("textLabel1_2_2"));
        textLabel1_2_2->setGeometry(QRect(230, 110, 121, 31));
        textLabel1_2_2->setFont(font3);
        lineEditFlowDirGrids = new QLineEdit(groupBoxInput_2);
        lineEditFlowDirGrids->setObjectName(QStringLiteral("lineEditFlowDirGrids"));
        lineEditFlowDirGrids->setGeometry(QRect(10, 48, 561, 29));
        lineEditFlowDirGrids->setFont(font2);
        checkBoxFlowAccGrid = new QCheckBox(groupBoxInput_2);
        checkBoxFlowAccGrid->setObjectName(QStringLiteral("checkBoxFlowAccGrid"));
        checkBoxFlowAccGrid->setEnabled(false);
        checkBoxFlowAccGrid->setGeometry(QRect(490, 180, 91, 21));
        checkBoxFlowAccGrid->setFont(font4);
        checkBoxFlowAccGrid->setChecked(false);
        pushButtonsFlowDirGrid = new QPushButton(groupBoxInput_2);
        pushButtonsFlowDirGrid->setObjectName(QStringLiteral("pushButtonsFlowDirGrid"));
        pushButtonsFlowDirGrid->setGeometry(QRect(480, 10, 98, 32));
        pushButtonsFlowDirGrid->setFont(font3);
        pushButtonsFlowDirGrid->setAutoDefault(false);
        groupBoxButtons = new QGroupBox(FlowGrids);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 303, 581, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(16, 7, 113, 32));
        pushButtonHelp->setFont(font3);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(330, 7, 113, 32));
        pushButtonClose->setFont(font3);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(455, 7, 113, 32));
        pushButtonRun->setFont(font3);
        pushButtonRun->setAutoDefault(false);

        retranslateUi(FlowGrids);

        QMetaObject::connectSlotsByName(FlowGrids);
    } // setupUi

    void retranslateUi(QDialog *FlowGrids)
    {
        FlowGrids->setWindowTitle(QApplication::translate("FlowGrids", "Flow Grids", nullptr));
        groupBoxInput->setTitle(QApplication::translate("FlowGrids", "Input", nullptr));
        pushButtonFillPits->setText(QApplication::translate("FlowGrids", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("FlowGrids", "Pit-Filled DEM Grid (From Step #1)", nullptr));
        groupBoxInput_2->setTitle(QApplication::translate("FlowGrids", "Output", nullptr));
        textLabel1_2->setText(QApplication::translate("FlowGrids", "Flow Dir. Grid", nullptr));
        checkBoxFlowDirGrid->setText(QApplication::translate("FlowGrids", "Load in GIS", nullptr));
        pushButtonFlowAccGrid->setText(QApplication::translate("FlowGrids", "Browse", nullptr));
        textLabel1_2_2->setText(QApplication::translate("FlowGrids", "Flow Acc. Grid", nullptr));
        checkBoxFlowAccGrid->setText(QApplication::translate("FlowGrids", "Load in GIS", nullptr));
        pushButtonsFlowDirGrid->setText(QApplication::translate("FlowGrids", "Browse", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("FlowGrids", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("FlowGrids", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("FlowGrids", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FlowGrids: public Ui_FlowGrids {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FLOWGRIDS_H
