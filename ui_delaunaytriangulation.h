/********************************************************************************
** Form generated from reading UI file 'delaunaytriangulation.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELAUNAYTRIANGULATION_H
#define UI_DELAUNAYTRIANGULATION_H

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

class Ui_DelaunayTriangulation
{
public:
    QFrame *BorderBottom;
    QGroupBox *groupBoxOutput;
    QLineEdit *lineEditAngle;
    QCheckBox *checkBoxAngle;
    QLineEdit *lineEditArea;
    QCheckBox *checkBoxArea;
    QCheckBox *checkBoxOthers;
    QLineEdit *lineEditOthers;
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonRun;
    QFrame *BorderTop;
    QGroupBox *groupBoxInput;
    QLineEdit *lineEditPSLG;
    QPushButton *pushButtonPSLG;
    QLabel *textLabel1;
    QTextBrowser *textBrowserLogs;
    QGroupBox *groupBox;
    QPushButton *pushButtonFIND;
    QLineEdit *lineEditFIND;
    QLabel *textLabel1_2;

    void setupUi(QDialog *DelaunayTriangulation)
    {
        if (DelaunayTriangulation->objectName().isEmpty())
            DelaunayTriangulation->setObjectName(QStringLiteral("DelaunayTriangulation"));
        DelaunayTriangulation->resize(611, 500);
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
        DelaunayTriangulation->setPalette(palette);
        BorderBottom = new QFrame(DelaunayTriangulation);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 484, 611, 20));
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
        groupBoxOutput = new QGroupBox(DelaunayTriangulation);
        groupBoxOutput->setObjectName(QStringLiteral("groupBoxOutput"));
        groupBoxOutput->setGeometry(QRect(15, 100, 581, 100));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(10);
        font.setItalic(true);
        groupBoxOutput->setFont(font);
        lineEditAngle = new QLineEdit(groupBoxOutput);
        lineEditAngle->setObjectName(QStringLiteral("lineEditAngle"));
        lineEditAngle->setGeometry(QRect(21, 58, 141, 29));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        lineEditAngle->setFont(font1);
        lineEditAngle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBoxAngle = new QCheckBox(groupBoxOutput);
        checkBoxAngle->setObjectName(QStringLiteral("checkBoxAngle"));
        checkBoxAngle->setGeometry(QRect(21, 31, 141, 20));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        font2.setWeight(75);
        checkBoxAngle->setFont(font2);
        lineEditArea = new QLineEdit(groupBoxOutput);
        lineEditArea->setObjectName(QStringLiteral("lineEditArea"));
        lineEditArea->setGeometry(QRect(180, 58, 231, 29));
        lineEditArea->setFont(font1);
        lineEditArea->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBoxArea = new QCheckBox(groupBoxOutput);
        checkBoxArea->setObjectName(QStringLiteral("checkBoxArea"));
        checkBoxArea->setGeometry(QRect(219, 31, 151, 20));
        checkBoxArea->setFont(font2);
        checkBoxOthers = new QCheckBox(groupBoxOutput);
        checkBoxOthers->setObjectName(QStringLiteral("checkBoxOthers"));
        checkBoxOthers->setGeometry(QRect(429, 31, 131, 20));
        checkBoxOthers->setFont(font2);
        lineEditOthers = new QLineEdit(groupBoxOutput);
        lineEditOthers->setObjectName(QStringLiteral("lineEditOthers"));
        lineEditOthers->setGeometry(QRect(429, 58, 131, 29));
        lineEditOthers->setFont(font1);
        lineEditOthers->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        groupBoxButtons = new QGroupBox(DelaunayTriangulation);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(10, 200, 581, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(16, 10, 113, 32));
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        pushButtonHelp->setFont(font3);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(330, 10, 113, 32));
        pushButtonClose->setFont(font3);
        pushButtonClose->setAutoDefault(false);
        pushButtonRun = new QPushButton(groupBoxButtons);
        pushButtonRun->setObjectName(QStringLiteral("pushButtonRun"));
        pushButtonRun->setGeometry(QRect(455, 10, 113, 32));
        pushButtonRun->setFont(font3);
        pushButtonRun->setAutoDefault(false);
        BorderTop = new QFrame(DelaunayTriangulation);
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
        QFont font4;
        font4.setFamily(QStringLiteral("Arial"));
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        BorderTop->setFont(font4);
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        groupBoxInput = new QGroupBox(DelaunayTriangulation);
        groupBoxInput->setObjectName(QStringLiteral("groupBoxInput"));
        groupBoxInput->setGeometry(QRect(16, 17, 581, 81));
        groupBoxInput->setFont(font);
        lineEditPSLG = new QLineEdit(groupBoxInput);
        lineEditPSLG->setObjectName(QStringLiteral("lineEditPSLG"));
        lineEditPSLG->setGeometry(QRect(12, 44, 561, 29));
        QFont font5;
        font5.setPointSize(10);
        font5.setBold(false);
        font5.setItalic(false);
        font5.setWeight(50);
        lineEditPSLG->setFont(font5);
        pushButtonPSLG = new QPushButton(groupBoxInput);
        pushButtonPSLG->setObjectName(QStringLiteral("pushButtonPSLG"));
        pushButtonPSLG->setGeometry(QRect(475, 10, 98, 32));
        pushButtonPSLG->setFont(font2);
        pushButtonPSLG->setCheckable(false);
        pushButtonPSLG->setAutoDefault(false);
        pushButtonPSLG->setFlat(false);
        textLabel1 = new QLabel(groupBoxInput);
        textLabel1->setObjectName(QStringLiteral("textLabel1"));
        textLabel1->setGeometry(QRect(220, 10, 141, 31));
        textLabel1->setFont(font2);
        textBrowserLogs = new QTextBrowser(DelaunayTriangulation);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(13, 255, 581, 141));
        QFont font6;
        font6.setItalic(false);
        textBrowserLogs->setFont(font6);
        textBrowserLogs->setAutoFormatting(QTextEdit::AutoAll);
        textBrowserLogs->setLineWrapMode(QTextEdit::WidgetWidth);
        groupBox = new QGroupBox(DelaunayTriangulation);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 400, 591, 81));
        QFont font7;
        font7.setFamily(QStringLiteral("Arial"));
        font7.setPointSize(12);
        font7.setItalic(true);
        groupBox->setFont(font7);
        pushButtonFIND = new QPushButton(groupBox);
        pushButtonFIND->setObjectName(QStringLiteral("pushButtonFIND"));
        pushButtonFIND->setGeometry(QRect(482, 13, 98, 32));
        pushButtonFIND->setFont(font2);
        pushButtonFIND->setCheckable(false);
        pushButtonFIND->setAutoDefault(false);
        pushButtonFIND->setFlat(false);
        lineEditFIND = new QLineEdit(groupBox);
        lineEditFIND->setObjectName(QStringLiteral("lineEditFIND"));
        lineEditFIND->setGeometry(QRect(20, 50, 561, 29));
        lineEditFIND->setFont(font5);
        textLabel1_2 = new QLabel(groupBox);
        textLabel1_2->setObjectName(QStringLiteral("textLabel1_2"));
        textLabel1_2->setGeometry(QRect(120, 20, 301, 31));
        textLabel1_2->setFont(font2);

        retranslateUi(DelaunayTriangulation);

        QMetaObject::connectSlotsByName(DelaunayTriangulation);
    } // setupUi

    void retranslateUi(QDialog *DelaunayTriangulation)
    {
        DelaunayTriangulation->setWindowTitle(QApplication::translate("DelaunayTriangulation", "Delaunay Triangulations", nullptr));
        groupBoxOutput->setTitle(QApplication::translate("DelaunayTriangulation", "Input Options", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBoxAngle->setToolTip(QApplication::translate("DelaunayTriangulation", "Minimum Angle Quality Constrain", nullptr));
#endif // QT_NO_TOOLTIP
        checkBoxAngle->setText(QApplication::translate("DelaunayTriangulation", "Angle (degrees)", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBoxArea->setToolTip(QApplication::translate("DelaunayTriangulation", "Maximum Area Quality Constrain", nullptr));
#endif // QT_NO_TOOLTIP
        checkBoxArea->setText(QApplication::translate("DelaunayTriangulation", "Area (sq. meters)", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBoxOthers->setToolTip(QApplication::translate("DelaunayTriangulation", "e  output a list of edges of the triangulation\n"
"v  output the Voronoi diagram associated with the triangulation\n"
"D Delaunay not constrained Delaunay\n"
"O ignore the holes in the poly file\n"
"Y prohibit the insertion of Steiner points on mesh boundary\n"
"YY prohibits the insertion of Steiner point on any segment\n"
"i  use the incremental algorith rather than divide and conquer", nullptr));
#endif // QT_NO_TOOLTIP
        checkBoxOthers->setText(QApplication::translate("DelaunayTriangulation", "Other Options", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("DelaunayTriangulation", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("DelaunayTriangulation", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonRun->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonRun->setText(QApplication::translate("DelaunayTriangulation", "Run", nullptr));
        groupBoxInput->setTitle(QApplication::translate("DelaunayTriangulation", "Input", nullptr));
        pushButtonPSLG->setText(QApplication::translate("DelaunayTriangulation", "Browse", nullptr));
        textLabel1->setText(QApplication::translate("DelaunayTriangulation", "PSLG (.poly) File", nullptr));
        groupBox->setTitle(QApplication::translate("DelaunayTriangulation", "Triangle Software Location", nullptr));
        pushButtonFIND->setText(QApplication::translate("DelaunayTriangulation", "Find", nullptr));
        textLabel1_2->setText(QApplication::translate("DelaunayTriangulation", "Specify your Triangle Tool and Location", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DelaunayTriangulation: public Ui_DelaunayTriangulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELAUNAYTRIANGULATION_H
