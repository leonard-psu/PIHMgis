/********************************************************************************
** Form generated from reading UI file 'polygontopolylines.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLYGONTOPOLYLINES_H
#define UI_POLYGONTOPOLYLINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_PolygonToPolylines
{
public:
    QTextBrowser *textBrowserLogs;
    QFrame *BorderTop;
    QFrame *BorderBottom;
    QGroupBox *groupBoxInput;
    QPushButton *pushButtonAdd;
    QTableWidget *tableWidget;
    QPushButton *pushButtonRemove;
    QCheckBox *checkBoxDissolvePolygons;
    QPushButton *pushButtonClear;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;

    void setupUi(QDialog *PolygonToPolylines)
    {
        if (PolygonToPolylines->objectName().isEmpty())
            PolygonToPolylines->setObjectName(QStringLiteral("PolygonToPolylines"));
        PolygonToPolylines->resize(800, 419);
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
        PolygonToPolylines->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        PolygonToPolylines->setFont(font);
        textBrowserLogs = new QTextBrowser(PolygonToPolylines);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(15, 286, 771, 111));
        QFont font1;
        font1.setPointSize(11);
        textBrowserLogs->setFont(font1);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);
        BorderTop = new QFrame(PolygonToPolylines);
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
        BorderBottom = new QFrame(PolygonToPolylines);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 403, 791, 20));
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
        groupBoxInput = new QGroupBox(PolygonToPolylines);
        groupBoxInput->setObjectName(QStringLiteral("groupBoxInput"));
        groupBoxInput->setGeometry(QRect(15, 29, 771, 201));
        pushButtonAdd = new QPushButton(groupBoxInput);
        pushButtonAdd->setObjectName(QStringLiteral("pushButtonAdd"));
        pushButtonAdd->setGeometry(QRect(665, 28, 98, 32));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        pushButtonAdd->setFont(font2);
        pushButtonAdd->setCheckable(false);
        pushButtonAdd->setAutoDefault(false);
        pushButtonAdd->setFlat(false);
        tableWidget = new QTableWidget(groupBoxInput);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem->setFont(font3);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qtablewidgetitem1->setFont(font4);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(15, 19, 641, 171));
        QFont font5;
        font5.setFamily(QStringLiteral("Arial"));
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setWeight(75);
        tableWidget->setFont(font5);
        tableWidget->setAcceptDrops(true);
        tableWidget->setLayoutDirection(Qt::LeftToRight);
        tableWidget->setFrameShape(QFrame::StyledPanel);
        tableWidget->setFrameShadow(QFrame::Sunken);
        tableWidget->setLineWidth(1);
        tableWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged|QAbstractItemView::SelectedClicked);
        tableWidget->setDragEnabled(true);
        tableWidget->setDragDropMode(QAbstractItemView::DragDrop);
        tableWidget->setWordWrap(false);
        tableWidget->setCornerButtonEnabled(true);
        tableWidget->setColumnCount(2);
        tableWidget->horizontalHeader()->setDefaultSectionSize(218);
        tableWidget->horizontalHeader()->setMinimumSectionSize(100);
        pushButtonRemove = new QPushButton(groupBoxInput);
        pushButtonRemove->setObjectName(QStringLiteral("pushButtonRemove"));
        pushButtonRemove->setGeometry(QRect(665, 67, 98, 32));
        pushButtonRemove->setFont(font2);
        pushButtonRemove->setAutoDefault(false);
        checkBoxDissolvePolygons = new QCheckBox(groupBoxInput);
        checkBoxDissolvePolygons->setObjectName(QStringLiteral("checkBoxDissolvePolygons"));
        checkBoxDissolvePolygons->setEnabled(false);
        checkBoxDissolvePolygons->setGeometry(QRect(667, 150, 101, 21));
        QFont font6;
        font6.setFamily(QStringLiteral("Arial"));
        font6.setPointSize(10);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setUnderline(false);
        font6.setWeight(75);
        font6.setStrikeOut(false);
        checkBoxDissolvePolygons->setFont(font6);
        checkBoxDissolvePolygons->setCheckable(false);
        checkBoxDissolvePolygons->setChecked(false);
        pushButtonClear = new QPushButton(groupBoxInput);
        pushButtonClear->setObjectName(QStringLiteral("pushButtonClear"));
        pushButtonClear->setGeometry(QRect(665, 107, 98, 32));
        pushButtonClear->setFont(font2);
        pushButtonClear->setAutoDefault(false);
        groupBoxButtons = new QGroupBox(PolygonToPolylines);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(15, 233, 771, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(10, 5, 113, 32));
        QFont font7;
        font7.setPointSize(12);
        pushButtonHelp->setFont(font7);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(530, 5, 113, 32));
        pushButtonClose->setFont(font2);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(650, 5, 113, 32));
        pushButtonRun->setFont(font2);
        pushButtonRun->setAutoDefault(false);

        retranslateUi(PolygonToPolylines);

        QMetaObject::connectSlotsByName(PolygonToPolylines);
    } // setupUi

    void retranslateUi(QDialog *PolygonToPolylines)
    {
        PolygonToPolylines->setWindowTitle(QApplication::translate("PolygonToPolylines", "Polygon To Polylines", nullptr));
        groupBoxInput->setTitle(QApplication::translate("PolygonToPolylines", "Input and Output", nullptr));
        pushButtonAdd->setText(QApplication::translate("PolygonToPolylines", "Add", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("PolygonToPolylines", "Polygon Layers", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("PolygonToPolylines", "Polyline Layers", nullptr));
        pushButtonRemove->setText(QApplication::translate("PolygonToPolylines", "Remove", nullptr));
        checkBoxDissolvePolygons->setText(QApplication::translate("PolygonToPolylines", "Load in GIS", nullptr));
        pushButtonClear->setText(QApplication::translate("PolygonToPolylines", "Clear", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("PolygonToPolylines", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("PolygonToPolylines", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("PolygonToPolylines", "Run", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PolygonToPolylines: public Ui_PolygonToPolylines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLYGONTOPOLYLINES_H
