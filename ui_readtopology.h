/********************************************************************************
** Form generated from reading UI file 'readtopology.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READTOPOLOGY_H
#define UI_READTOPOLOGY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ReadTopology
{
public:
    QFrame *BorderBottom;
    QFrame *BorderTop;
    QGroupBox *groupBoxInput;
    QLineEdit *lineEditMerge;
    QPushButton *pushButtonMerge;
    QLabel *textLabel1;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QGroupBox *groupBoxOutput;
    QLineEdit *lineEditPSLG;
    QPushButton *pushButtonPSLG;
    QLabel *textLabel1_2;

    void setupUi(QDialog *ReadTopology)
    {
        if (ReadTopology->objectName().isEmpty())
            ReadTopology->setObjectName(QStringLiteral("ReadTopology"));
        ReadTopology->resize(611, 409);
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
        ReadTopology->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        ReadTopology->setFont(font);
        BorderBottom = new QFrame(ReadTopology);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 393, 611, 20));
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
        BorderTop = new QFrame(ReadTopology);
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
        groupBoxInput = new QGroupBox(ReadTopology);
        groupBoxInput->setObjectName(QStringLiteral("groupBoxInput"));
        groupBoxInput->setGeometry(QRect(16, 17, 581, 81));
        QFont font1;
        font1.setItalic(true);
        groupBoxInput->setFont(font1);
        lineEditMerge = new QLineEdit(groupBoxInput);
        lineEditMerge->setObjectName(QStringLiteral("lineEditMerge"));
        lineEditMerge->setGeometry(QRect(6, 44, 571, 29));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        lineEditMerge->setFont(font2);
        pushButtonMerge = new QPushButton(groupBoxInput);
        pushButtonMerge->setObjectName(QStringLiteral("pushButtonMerge"));
        pushButtonMerge->setGeometry(QRect(480, 10, 98, 32));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        pushButtonMerge->setFont(font3);
        pushButtonMerge->setCheckable(false);
        pushButtonMerge->setAutoDefault(false);
        pushButtonMerge->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(230, 10, 141, 31));
        QFont font4;
        font4.setPointSize(14);
        font4.setBold(true);
        font4.setItalic(false);
        font4.setWeight(75);
        textLabel1->setFont(font4);
        textBrowserLogs = new QTextBrowser(ReadTopology);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(13, 265, 581, 121));
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxButtons = new QGroupBox(ReadTopology);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(10, 210, 591, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(16, 6, 113, 32));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial"));
        font5.setPointSize(12);
        font5.setBold(true);
        font5.setWeight(75);
        pushButtonHelp->setFont(font5);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(330, 6, 113, 32));
        pushButtonClose->setFont(font5);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(455, 6, 113, 32));
        pushButtonRun->setFont(font5);
        pushButtonRun->setAutoDefault(false);
        groupBoxOutput = new QGroupBox(ReadTopology);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(15, 110, 581, 91));
        groupBoxOutput->setFont(font1);
        lineEditPSLG = new QLineEdit(groupBoxOutput);
        lineEditPSLG->setObjectName(QStringLiteral("lineEditPSLG"));
        lineEditPSLG->setGeometry(QRect(4, 50, 571, 29));
        lineEditPSLG->setFont(font2);
        pushButtonPSLG = new QPushButton(groupBoxOutput);
        pushButtonPSLG->setObjectName(QStringLiteral("pushButtonPSLG"));
        pushButtonPSLG->setGeometry(QRect(480, 10, 98, 32));
        pushButtonPSLG->setFont(font3);
        pushButtonPSLG->setAutoDefault(false);
        textLabel1_2 = new QLabel(groupBoxOutput);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(220, 10, 171, 31));
        textLabel1_2->setFont(font4);

        retranslateUi(ReadTopology);

        QMetaObject::connectSlotsByName(ReadTopology);
    } // setupUi

    void retranslateUi(QDialog *ReadTopology)
    {
        ReadTopology->setWindowTitle(QApplication::translate("ReadTopology", "Read Topology", nullptr));
        groupBoxInput->setTitle(QApplication::translate("ReadTopology", "Input", nullptr));
        pushButtonMerge->setText(QApplication::translate("ReadTopology", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("ReadTopology", "Merge Vector", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("ReadTopology", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("ReadTopology", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("ReadTopology", "Run", nullptr));
        groupBoxOutput->setTitle(QApplication::translate("ReadTopology", "Output", nullptr));
        pushButtonPSLG->setText(QApplication::translate("ReadTopology", "Browse", nullptr));
        textLabel1_2->setText(QApplication::translate("ReadTopology", "PSLG (.poly) File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ReadTopology: public Ui_ReadTopology {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READTOPOLOGY_H
