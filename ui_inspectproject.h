/********************************************************************************
** Form generated from reading UI file 'inspectproject.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSPECTPROJECT_H
#define UI_INSPECTPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_InspectProject
{
public:
    QTextBrowser *textBrowserLogs;
    QFrame *BorderTop;
    QFrame *BorderTop_2;
    QLabel *label_2;
    QPushButton *pushButton_FIND;
    QPushButton *pushButton_OK;
    QLineEdit *lineEdit;
    QLabel *labelINFO;
    QPushButton *pushButton_CLEAR;

    void setupUi(QDialog *InspectProject)
    {
        if (InspectProject->objectName().isEmpty())
            InspectProject->setObjectName(QStringLiteral("InspectProject"));
        InspectProject->resize(800, 600);
        InspectProject->setMinimumSize(QSize(800, 600));
        InspectProject->setMaximumSize(QSize(800, 600));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        InspectProject->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        InspectProject->setFont(font);
        textBrowserLogs = new QTextBrowser(InspectProject);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(5, 60, 782, 461));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        textBrowserLogs->setFont(font1);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        BorderTop = new QFrame(InspectProject);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, 0, 800, 20));
        BorderTop->setBaseSize(QSize(0, 0));
        QPalette palette1;
        QBrush brush1(QColor(0, 51, 153, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        QBrush brush2(QColor(128, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        QBrush brush3(QColor(192, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush3);
        QBrush brush4(QColor(160, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush4);
        QBrush brush5(QColor(64, 0, 0, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush5);
        QBrush brush6(QColor(85, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        QBrush brush7(QColor(0, 0, 0, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush5);
        QBrush brush8(QColor(255, 255, 220, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        BorderTop->setPalette(palette1);
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        BorderTop_2 = new QFrame(InspectProject);
        BorderTop_2->setObjectName(QStringLiteral("BorderTop_2"));
        BorderTop_2->setGeometry(QRect(0, 585, 800, 20));
        BorderTop_2->setBaseSize(QSize(0, 0));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush3);
        palette2.setBrush(QPalette::Active, QPalette::Midlight, brush4);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush5);
        palette2.setBrush(QPalette::Active, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Active, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette2.setBrush(QPalette::Active, QPalette::Shadow, brush7);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush5);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Midlight, brush4);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Shadow, brush7);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush5);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::Midlight, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush5);
        palette2.setBrush(QPalette::Disabled, QPalette::Mid, brush6);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Shadow, brush7);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush8);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush7);
        BorderTop_2->setPalette(palette2);
        BorderTop_2->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop_2->setFrameShadow(QFrame::Plain);
        BorderTop_2->setLineWidth(12);
        BorderTop_2->setMidLineWidth(0);
        BorderTop_2->setFrameShape(QFrame::HLine);
        label_2 = new QLabel(InspectProject);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(270, 20, 261, 31));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignCenter);
        pushButton_FIND = new QPushButton(InspectProject);
        pushButton_FIND->setObjectName(QStringLiteral("pushButton_FIND"));
        pushButton_FIND->setGeometry(QRect(630, 530, 75, 30));
        pushButton_OK = new QPushButton(InspectProject);
        pushButton_OK->setObjectName(QStringLiteral("pushButton_OK"));
        pushButton_OK->setGeometry(QRect(710, 565, 75, 21));
        lineEdit = new QLineEdit(InspectProject);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 530, 611, 30));
        labelINFO = new QLabel(InspectProject);
        labelINFO->setObjectName(QStringLiteral("labelINFO"));
        labelINFO->setGeometry(QRect(14, 565, 611, 20));
        pushButton_CLEAR = new QPushButton(InspectProject);
        pushButton_CLEAR->setObjectName(QStringLiteral("pushButton_CLEAR"));
        pushButton_CLEAR->setGeometry(QRect(710, 530, 75, 30));

        retranslateUi(InspectProject);

        QMetaObject::connectSlotsByName(InspectProject);
    } // setupUi

    void retranslateUi(QDialog *InspectProject)
    {
        InspectProject->setWindowTitle(QApplication::translate("InspectProject", "Inspect PIHMgis Project", nullptr));
        label_2->setText(QApplication::translate("InspectProject", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Lucida Grande'; font-size:14pt; font-weight:600;\">Inspect PIHMgis Project</span></p></body></html>", nullptr));
        pushButton_FIND->setText(QApplication::translate("InspectProject", "Find", nullptr));
        pushButton_OK->setText(QApplication::translate("InspectProject", "OK", nullptr));
        labelINFO->setText(QString());
        pushButton_CLEAR->setText(QApplication::translate("InspectProject", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InspectProject: public Ui_InspectProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSPECTPROJECT_H
