/********************************************************************************
** Form generated from reading UI file 'checkproject.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHECKPROJECT_H
#define UI_CHECKPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_CheckProject
{
public:
    QTextBrowser *textBrowserLogs;
    QFrame *BorderTop;
    QFrame *BorderBottom;
    QPushButton *pushButtonClose;
    QLabel *label;
    QLineEdit *lineEditWorkspaceFolder;
    QPushButton *pushButtonRecheck;

    void setupUi(QDialog *CheckProject)
    {
        if (CheckProject->objectName().isEmpty())
            CheckProject->setObjectName(QStringLiteral("CheckProject"));
        CheckProject->resize(800, 400);
        CheckProject->setMaximumSize(QSize(800, 400));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        CheckProject->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        CheckProject->setFont(font);
        textBrowserLogs = new QTextBrowser(CheckProject);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(5, 100, 782, 241));
        QFont font1;
        font1.setPointSize(11);
        textBrowserLogs->setFont(font1);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        BorderTop = new QFrame(CheckProject);
        BorderTop->setObjectName(QStringLiteral("BorderTop"));
        BorderTop->setGeometry(QRect(0, -3, 800, 20));
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
        BorderBottom = new QFrame(CheckProject);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 384, 800, 20));
        BorderBottom->setBaseSize(QSize(0, 0));
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
        BorderBottom->setPalette(palette2);
        BorderBottom->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderBottom->setFrameShadow(QFrame::Plain);
        BorderBottom->setLineWidth(12);
        BorderBottom->setMidLineWidth(0);
        BorderBottom->setFrameShape(QFrame::HLine);
        pushButtonClose = new QPushButton(CheckProject);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(674, 350, 113, 32));
        pushButtonClose->setAutoDefault(false);
        label = new QLabel(CheckProject);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(210, 20, 381, 41));
        QFont font2;
        font2.setPointSize(18);
        label->setFont(font2);
        lineEditWorkspaceFolder = new QLineEdit(CheckProject);
        lineEditWorkspaceFolder->setObjectName(QStringLiteral("lineEditWorkspaceFolder"));
        lineEditWorkspaceFolder->setEnabled(false);
        lineEditWorkspaceFolder->setGeometry(QRect(5, 60, 782, 29));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        lineEditWorkspaceFolder->setFont(font3);
        pushButtonRecheck = new QPushButton(CheckProject);
        pushButtonRecheck->setObjectName(QStringLiteral("pushButtonRecheck"));
        pushButtonRecheck->setGeometry(QRect(554, 350, 113, 32));
        pushButtonRecheck->setAutoDefault(false);

        retranslateUi(CheckProject);

        QMetaObject::connectSlotsByName(CheckProject);
    } // setupUi

    void retranslateUi(QDialog *CheckProject)
    {
        CheckProject->setWindowTitle(QApplication::translate("CheckProject", "Check Project Workspace", nullptr));
        pushButtonClose->setText(QApplication::translate("CheckProject", "Close", nullptr));
        label->setText(QApplication::translate("CheckProject", "Issues found in your workspace", nullptr));
        pushButtonRecheck->setText(QApplication::translate("CheckProject", "Re-Check", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CheckProject: public Ui_CheckProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHECKPROJECT_H
