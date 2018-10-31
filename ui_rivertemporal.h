/********************************************************************************
** Form generated from reading UI file 'rivertemporal.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RIVERTEMPORAL_H
#define UI_RIVERTEMPORAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_RiverTemporal
{
public:
    QFrame *BorderTop;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QFrame *BorderBottom;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBoxOutput;
    QLabel *textLabel2;
    QPushButton *pushButtonOutputDataFolder;
    QLineEdit *lineEditOutputDataFolder;
    QLineEdit *lineEditDataKey;
    QLabel *textLabel2_2;
    QLabel *textLabel2_3;
    QLabel *textLabel2_4;
    QComboBox *comboBoxPlotVariable;
    QLineEdit *lineEditModelSegments;
    QComboBox *comboBoxModelSegments;

    void setupUi(QDialog *RiverTemporal)
    {
        if (RiverTemporal->objectName().isEmpty())
            RiverTemporal->setObjectName(QStringLiteral("RiverTemporal"));
        RiverTemporal->resize(611, 426);
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
        RiverTemporal->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        RiverTemporal->setFont(font);
        BorderTop = new QFrame(RiverTemporal);
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
        groupBoxButtons = new QGroupBox(RiverTemporal);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 239, 581, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(10, 6, 113, 32));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        pushButtonHelp->setFont(font1);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(340, 6, 113, 32));
        pushButtonClose->setFont(font1);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(460, 6, 113, 32));
        pushButtonRun->setFont(font1);
        pushButtonRun->setAutoDefault(false);
        BorderBottom = new QFrame(RiverTemporal);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 410, 611, 20));
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
        textBrowserLogs = new QTextBrowser(RiverTemporal);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 295, 581, 111));
        QFont font2;
        font2.setPointSize(11);
        textBrowserLogs->setFont(font2);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        groupBoxOutput = new QGroupBox(RiverTemporal);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(15, 30, 581, 211));
        textLabel2 = new QLabel(groupBoxOutput);
        textLabel2->setObjectName(QStringLiteral("textLabel2"));
        textLabel2->setGeometry(QRect(210, 10, 151, 31));
        textLabel2->setFont(font1);
        pushButtonOutputDataFolder = new QPushButton(groupBoxOutput);
        pushButtonOutputDataFolder->setObjectName(QStringLiteral("pushButtonOutputDataFolder"));
        pushButtonOutputDataFolder->setGeometry(QRect(476, 3, 98, 32));
        pushButtonOutputDataFolder->setFont(font1);
        pushButtonOutputDataFolder->setAutoDefault(false);
        lineEditOutputDataFolder = new QLineEdit(groupBoxOutput);
        lineEditOutputDataFolder->setObjectName(QStringLiteral("lineEditOutputDataFolder"));
        lineEditOutputDataFolder->setGeometry(QRect(0, 40, 571, 29));
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setWeight(75);
        lineEditOutputDataFolder->setFont(font3);
        lineEditDataKey = new QLineEdit(groupBoxOutput);
        lineEditDataKey->setObjectName(QStringLiteral("lineEditDataKey"));
        lineEditDataKey->setGeometry(QRect(148, 75, 421, 29));
        lineEditDataKey->setFont(font3);
        textLabel2_2 = new QLabel(groupBoxOutput);
        textLabel2_2->setObjectName(QStringLiteral("textLabel2_2"));
        textLabel2_2->setGeometry(QRect(10, 75, 131, 31));
        textLabel2_2->setFont(font1);
        textLabel2_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_3 = new QLabel(groupBoxOutput);
        textLabel2_3->setObjectName(QStringLiteral("textLabel2_3"));
        textLabel2_3->setGeometry(QRect(7, 173, 131, 31));
        textLabel2_3->setFont(font1);
        textLabel2_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textLabel2_4 = new QLabel(groupBoxOutput);
        textLabel2_4->setObjectName(QStringLiteral("textLabel2_4"));
        textLabel2_4->setGeometry(QRect(10, 106, 131, 31));
        textLabel2_4->setFont(font1);
        textLabel2_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
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
        comboBoxPlotVariable->setGeometry(QRect(148, 173, 421, 28));
        comboBoxPlotVariable->setFont(font1);
        lineEditModelSegments = new QLineEdit(groupBoxOutput);
        lineEditModelSegments->setObjectName(QStringLiteral("lineEditModelSegments"));
        lineEditModelSegments->setGeometry(QRect(147, 140, 421, 29));
        lineEditModelSegments->setFont(font3);
        lineEditModelSegments->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        comboBoxModelSegments = new QComboBox(groupBoxOutput);
        comboBoxModelSegments->addItem(QString());
        comboBoxModelSegments->addItem(QString());
        comboBoxModelSegments->addItem(QString());
        comboBoxModelSegments->addItem(QString());
        comboBoxModelSegments->addItem(QString());
        comboBoxModelSegments->setObjectName(QStringLiteral("comboBoxModelSegments"));
        comboBoxModelSegments->setGeometry(QRect(148, 107, 421, 28));
        comboBoxModelSegments->setFont(font1);

        retranslateUi(RiverTemporal);

        QMetaObject::connectSlotsByName(RiverTemporal);
    } // setupUi

    void retranslateUi(QDialog *RiverTemporal)
    {
        RiverTemporal->setWindowTitle(QApplication::translate("RiverTemporal", "River Time Series", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("RiverTemporal", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("RiverTemporal", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("RiverTemporal", "Run", nullptr));
        groupBoxOutput->setTitle(QString());
        textLabel2->setText(QApplication::translate("RiverTemporal", "Output Data Folder", nullptr));
        pushButtonOutputDataFolder->setText(QApplication::translate("RiverTemporal", "Browse", nullptr));
        textLabel2_2->setText(QApplication::translate("RiverTemporal", "Data Key (ID)", nullptr));
        textLabel2_3->setText(QApplication::translate("RiverTemporal", "Plot Variable", nullptr));
        textLabel2_4->setText(QApplication::translate("RiverTemporal", "Model Segments", nullptr));
        comboBoxPlotVariable->setItemText(0, QApplication::translate("RiverTemporal", "River Outflow", nullptr));
        comboBoxPlotVariable->setItemText(1, QApplication::translate("RiverTemporal", "River Inflow", nullptr));
        comboBoxPlotVariable->setItemText(2, QApplication::translate("RiverTemporal", "River Storage", nullptr));
        comboBoxPlotVariable->setItemText(3, QApplication::translate("RiverTemporal", "River Surfaceflow", nullptr));
        comboBoxPlotVariable->setItemText(4, QApplication::translate("RiverTemporal", "River Baseflow", nullptr));
        comboBoxPlotVariable->setItemText(5, QApplication::translate("RiverTemporal", "River Surfaceflow Left", nullptr));
        comboBoxPlotVariable->setItemText(6, QApplication::translate("RiverTemporal", "River Surfaceflow Right", nullptr));
        comboBoxPlotVariable->setItemText(7, QApplication::translate("RiverTemporal", "River Baseflow Left", nullptr));
        comboBoxPlotVariable->setItemText(8, QApplication::translate("RiverTemporal", "River Baseflow Right", nullptr));
        comboBoxPlotVariable->setItemText(9, QApplication::translate("RiverTemporal", "River Seepage to Bed", nullptr));
        comboBoxPlotVariable->setItemText(10, QApplication::translate("RiverTemporal", "Riverbed Outflow", nullptr));
        comboBoxPlotVariable->setItemText(11, QApplication::translate("RiverTemporal", "Riverbed Inflow", nullptr));
        comboBoxPlotVariable->setItemText(12, QApplication::translate("RiverTemporal", "Riverbed Storage", nullptr));
        comboBoxPlotVariable->setItemText(13, QApplication::translate("RiverTemporal", "Riverbed Baseflow ", nullptr));
        comboBoxPlotVariable->setItemText(14, QApplication::translate("RiverTemporal", "Riverbed Baseflow Left", nullptr));
        comboBoxPlotVariable->setItemText(15, QApplication::translate("RiverTemporal", "Riverbed Baseflow Right", nullptr));

        lineEditModelSegments->setText(QApplication::translate("RiverTemporal", "  1 2 3", nullptr));
        lineEditModelSegments->setPlaceholderText(QString());
        comboBoxModelSegments->setItemText(0, QApplication::translate("RiverTemporal", "Individual Model Segments", nullptr));
        comboBoxModelSegments->setItemText(1, QApplication::translate("RiverTemporal", "Average of Model Segments", nullptr));
        comboBoxModelSegments->setItemText(2, QApplication::translate("RiverTemporal", "Average All Model Segments", nullptr));
        comboBoxModelSegments->setItemText(3, QApplication::translate("RiverTemporal", "Total of Model Segments", nullptr));
        comboBoxModelSegments->setItemText(4, QApplication::translate("RiverTemporal", "Total All Model Segments", nullptr));

    } // retranslateUi

};

namespace Ui {
    class RiverTemporal: public Ui_RiverTemporal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RIVERTEMPORAL_H
