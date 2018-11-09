/********************************************************************************
** Form generated from reading UI file 'catchmentgrids.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CATCHMENTGRIDS_H
#define UI_CATCHMENTGRIDS_H

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

class Ui_CatchmentGrids
{
public:
    QGroupBox *groupBoxInput_2;
    QLabel *textLabel1_2;
    QPushButton *pushButtonCatchmentGrids;
    QLineEdit *lineEditCatchmentGrids;
    QCheckBox *checkBoxCatchmentGrids;
    QGroupBox *groupBoxInput;
    QPushButton *pushButtonLinkGrids;
    QLabel *textLabel1;
    QLineEdit *lineEditLinkGrids;
    QLineEdit *lineEditFlowDirGrids;
    QPushButton *pushButtonFlowDirGrids;
    QLabel *textLabel1_3;
    QFrame *BorderTop;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QFrame *BorderBottom;

    void setupUi(QDialog *CatchmentGrids)
    {
        if (CatchmentGrids->objectName().isEmpty())
            CatchmentGrids->setObjectName(QStringLiteral("CatchmentGrids"));
        CatchmentGrids->resize(800, 480);
        CatchmentGrids->setMinimumSize(QSize(800, 480));
        CatchmentGrids->setMaximumSize(QSize(800, 480));
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
        CatchmentGrids->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        CatchmentGrids->setFont(font);
        groupBoxInput_2 = new QGroupBox(CatchmentGrids);
        groupBoxInput_2->setObjectName(QStringLiteral("groupBoxInput_2"));
        groupBoxInput_2->setGeometry(QRect(15, 195, 771, 101));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        groupBoxInput_2->setFont(font1);
        textLabel1_2 = new QLabel(groupBoxInput_2);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(310, 10, 131, 31));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        textLabel1_2->setFont(font2);
        pushButtonCatchmentGrids = new QPushButton(groupBoxInput_2);
        pushButtonCatchmentGrids->setObjectName(QStringLiteral("pushButtonCatchmentGrids"));
        pushButtonCatchmentGrids->setGeometry(QRect(666, 10, 98, 32));
        pushButtonCatchmentGrids->setFont(font2);
        pushButtonCatchmentGrids->setAutoDefault(false);
        lineEditCatchmentGrids = new QLineEdit(groupBoxInput_2);
        lineEditCatchmentGrids->setObjectName(QStringLiteral("lineEditCatchmentGrids"));
        lineEditCatchmentGrids->setGeometry(QRect(7, 44, 761, 29));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        lineEditCatchmentGrids->setFont(font3);
        checkBoxCatchmentGrids = new QCheckBox(groupBoxInput_2);
        checkBoxCatchmentGrids->setObjectName(QStringLiteral("checkBoxCatchmentGrids"));
        checkBoxCatchmentGrids->setEnabled(false);
        checkBoxCatchmentGrids->setGeometry(QRect(670, 76, 101, 21));
        QFont font4;
        font4.setFamily(QStringLiteral("Sans Serif"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setUnderline(false);
        font4.setWeight(50);
        font4.setStrikeOut(false);
        checkBoxCatchmentGrids->setFont(font4);
        checkBoxCatchmentGrids->setCheckable(false);
        checkBoxCatchmentGrids->setChecked(false);
        groupBoxInput = new QGroupBox(CatchmentGrids);
        groupBoxInput->setObjectName(QStringLiteral("groupBoxInput"));
        groupBoxInput->setGeometry(QRect(15, 17, 771, 171));
        groupBoxInput->setFont(font1);
        pushButtonLinkGrids = new QPushButton(groupBoxInput);
        pushButtonLinkGrids->setObjectName(QStringLiteral("pushButtonLinkGrids"));
        pushButtonLinkGrids->setGeometry(QRect(666, 10, 98, 32));
        pushButtonLinkGrids->setFont(font2);
        pushButtonLinkGrids->setCheckable(false);
        pushButtonLinkGrids->setAutoDefault(false);
        pushButtonLinkGrids->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(330, 10, 87, 31));
        textLabel1->setFont(font2);
        lineEditLinkGrids = new QLineEdit(groupBoxInput);
        lineEditLinkGrids->setObjectName(QStringLiteral("lineEditLinkGrids"));
        lineEditLinkGrids->setGeometry(QRect(4, 46, 761, 29));
        lineEditLinkGrids->setFont(font3);
        lineEditFlowDirGrids = new QLineEdit(groupBoxInput);
        lineEditFlowDirGrids->setObjectName(QStringLiteral("lineEditFlowDirGrids"));
        lineEditFlowDirGrids->setGeometry(QRect(5, 126, 761, 29));
        lineEditFlowDirGrids->setFont(font3);
        pushButtonFlowDirGrids = new QPushButton(groupBoxInput);
        pushButtonFlowDirGrids->setObjectName(QStringLiteral("pushButtonFlowDirGrids"));
        pushButtonFlowDirGrids->setGeometry(QRect(666, 90, 98, 32));
        pushButtonFlowDirGrids->setFont(font2);
        pushButtonFlowDirGrids->setCheckable(false);
        pushButtonFlowDirGrids->setAutoDefault(false);
        pushButtonFlowDirGrids->setFlat(false);
        textLabel1_3 = new QLabel(groupBoxInput);
        textLabel1_3->setObjectName(QStringLiteral("textLabel1_3"));
        textLabel1_3->setGeometry(QRect(320, 90, 111, 31));
        textLabel1_3->setFont(font2);
        BorderTop = new QFrame(CatchmentGrids);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, -4, 791, 20));
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
        textBrowserLogs = new QTextBrowser(CatchmentGrids);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 347, 771, 111));
        QFont font5;
        font5.setPointSize(11);
        textBrowserLogs->setFont(font5);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxButtons = new QGroupBox(CatchmentGrids);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 294, 771, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(8, 8, 113, 32));
        QFont font6;
        font6.setPointSize(12);
        pushButtonHelp->setFont(font6);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(535, 8, 113, 32));
        pushButtonClose->setFont(font6);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(652, 8, 113, 32));
        pushButtonRun->setFont(font6);
        pushButtonRun->setAutoDefault(false);
        BorderBottom = new QFrame(CatchmentGrids);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 464, 791, 20));
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

        retranslateUi(CatchmentGrids);

        QMetaObject::connectSlotsByName(CatchmentGrids);
    } // setupUi

    void retranslateUi(QDialog *CatchmentGrids)
    {
        CatchmentGrids->setWindowTitle(QApplication::translate("CatchmentGrids", "Catchment Grids", nullptr));
        groupBoxInput_2->setTitle(QApplication::translate("CatchmentGrids", "Output", nullptr));
        textLabel1_2->setText(QApplication::translate("CatchmentGrids", "Catchment Grid", nullptr));
        pushButtonCatchmentGrids->setText(QApplication::translate("CatchmentGrids", "Browse", nullptr));
        checkBoxCatchmentGrids->setText(QApplication::translate("CatchmentGrids", "Load in GIS", nullptr));
        groupBoxInput->setTitle(QApplication::translate("CatchmentGrids", "Input", nullptr));
        pushButtonLinkGrids->setText(QApplication::translate("CatchmentGrids", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("CatchmentGrids", "Link Grid", nullptr));
        pushButtonFlowDirGrids->setText(QApplication::translate("CatchmentGrids", "Browse", nullptr));
        textLabel1_3->setText(QApplication::translate("CatchmentGrids", "Flow Dir. Grid", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("CatchmentGrids", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("CatchmentGrids", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("CatchmentGrids", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CatchmentGrids: public Ui_CatchmentGrids {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CATCHMENTGRIDS_H
