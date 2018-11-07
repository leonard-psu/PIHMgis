/********************************************************************************
** Form generated from reading UI file 'importproject.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTPROJECT_H
#define UI_IMPORTPROJECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ImportProject
{
public:
    QGroupBox *groupBoxButtons;
    QPushButton *pushButtonHelp;
    QPushButton *pushButtonClose;
    QPushButton *pushButtonImport;
    QGroupBox *groupBox;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QPushButton *pushButtonProject;
    QLineEdit *lineEditOld;
    QLabel *label_3;
    QLineEdit *lineEditNew;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *new_lineEdit_ProjectFile;
    QLabel *label_6;
    QLineEdit *lineEdit_Data_Base_Folder;
    QPushButton *pushButtonProject_DataFolder;
    QLabel *label_7;
    QComboBox *comboBox_old_project_dirs;
    QLabel *label_8;
    QCheckBox *checkBox_Search;
    QFrame *BorderTop;
    QFrame *BorderBottom;
    QTextBrowser *textBrowserLogs;

    void setupUi(QDialog *ImportProject)
    {
        if (ImportProject->objectName().isEmpty())
            ImportProject->setObjectName(QStringLiteral("ImportProject"));
        ImportProject->resize(611, 550);
        ImportProject->setMaximumSize(QSize(611, 550));
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
        ImportProject->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        ImportProject->setFont(font);
        groupBoxButtons = new QGroupBox(ImportProject);
        groupBoxButtons->setObjectName(QStringLiteral("groupBoxButtons"));
        groupBoxButtons->setGeometry(QRect(16, 369, 581, 51));
        pushButtonHelp = new QPushButton(groupBoxButtons);
        pushButtonHelp->setObjectName(QStringLiteral("pushButtonHelp"));
        pushButtonHelp->setEnabled(false);
        pushButtonHelp->setGeometry(QRect(11, 6, 113, 32));
        pushButtonHelp->setFont(font);
        pushButtonHelp->setAutoDefault(false);
        pushButtonClose = new QPushButton(groupBoxButtons);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));
        pushButtonClose->setGeometry(QRect(321, 6, 113, 32));
        pushButtonClose->setFont(font);
        pushButtonClose->setAutoDefault(false);
        pushButtonImport = new QPushButton(groupBoxButtons);
        pushButtonImport->setObjectName(QStringLiteral("pushButtonImport"));
        pushButtonImport->setGeometry(QRect(441, 6, 131, 32));
        pushButtonImport->setFont(font);
        pushButtonImport->setAutoDefault(false);
        groupBox = new QGroupBox(ImportProject);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(15, 20, 581, 351));
        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 41, 561, 31));
        QFont font1;
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        lineEdit->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(170, 10, 221, 20));
        label_2->setFont(font);
        pushButtonProject = new QPushButton(groupBox);
        pushButtonProject->setObjectName(QStringLiteral("pushButtonProject"));
        pushButtonProject->setGeometry(QRect(459, 6, 113, 32));
        pushButtonProject->setFont(font);
        pushButtonProject->setAutoDefault(false);
        lineEditOld = new QLineEdit(groupBox);
        lineEditOld->setObjectName(QStringLiteral("lineEditOld"));
        lineEditOld->setEnabled(false);
        lineEditOld->setGeometry(QRect(160, 80, 411, 22));
        lineEditOld->setFont(font1);
        lineEditOld->setReadOnly(true);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(38, 80, 121, 20));
        label_3->setFont(font);
        lineEditNew = new QLineEdit(groupBox);
        lineEditNew->setObjectName(QStringLiteral("lineEditNew"));
        lineEditNew->setEnabled(false);
        lineEditNew->setGeometry(QRect(159, 110, 411, 22));
        lineEditNew->setFont(font1);
        lineEditNew->setReadOnly(true);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 112, 151, 20));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(16, 142, 141, 20));
        label_5->setFont(font);
        new_lineEdit_ProjectFile = new QLineEdit(groupBox);
        new_lineEdit_ProjectFile->setObjectName(QStringLiteral("new_lineEdit_ProjectFile"));
        new_lineEdit_ProjectFile->setEnabled(false);
        new_lineEdit_ProjectFile->setGeometry(QRect(160, 140, 411, 22));
        new_lineEdit_ProjectFile->setFont(font1);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 328, 531, 16));
        lineEdit_Data_Base_Folder = new QLineEdit(groupBox);
        lineEdit_Data_Base_Folder->setObjectName(QStringLiteral("lineEdit_Data_Base_Folder"));
        lineEdit_Data_Base_Folder->setGeometry(QRect(11, 206, 561, 31));
        lineEdit_Data_Base_Folder->setFont(font1);
        pushButtonProject_DataFolder = new QPushButton(groupBox);
        pushButtonProject_DataFolder->setObjectName(QStringLiteral("pushButtonProject_DataFolder"));
        pushButtonProject_DataFolder->setGeometry(QRect(460, 170, 113, 32));
        pushButtonProject_DataFolder->setFont(font);
        pushButtonProject_DataFolder->setAutoDefault(false);
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 180, 411, 20));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        comboBox_old_project_dirs = new QComboBox(groupBox);
        comboBox_old_project_dirs->setObjectName(QStringLiteral("comboBox_old_project_dirs"));
        comboBox_old_project_dirs->setGeometry(QRect(10, 262, 561, 31));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        comboBox_old_project_dirs->setFont(font2);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(110, 240, 321, 20));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        checkBox_Search = new QCheckBox(groupBox);
        checkBox_Search->setObjectName(QStringLiteral("checkBox_Search"));
        checkBox_Search->setGeometry(QRect(210, 300, 371, 20));
        BorderTop = new QFrame(ImportProject);
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
        QFont font3;
        font3.setFamily(QStringLiteral("Arial"));
        font3.setPointSize(10);
        BorderTop->setFont(font3);
        BorderTop->setStyleSheet(QStringLiteral("color: rgb(0, 51, 153);"));
        BorderTop->setFrameShadow(QFrame::Plain);
        BorderTop->setLineWidth(12);
        BorderTop->setMidLineWidth(0);
        BorderTop->setFrameShape(QFrame::HLine);
        BorderBottom = new QFrame(ImportProject);
        BorderBottom->setObjectName(QStringLiteral("BorderBottom"));
        BorderBottom->setGeometry(QRect(0, 530, 611, 20));
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
        textBrowserLogs = new QTextBrowser(ImportProject);
        textBrowserLogs->setObjectName(QStringLiteral("textBrowserLogs"));
        textBrowserLogs->setGeometry(QRect(16, 422, 581, 101));
        textBrowserLogs->setFont(font1);
        textBrowserLogs->setLineWrapMode(QTextEdit::NoWrap);

        retranslateUi(ImportProject);

        pushButtonClose->setDefault(false);
        pushButtonProject->setDefault(false);
        pushButtonProject_DataFolder->setDefault(false);


        QMetaObject::connectSlotsByName(ImportProject);
    } // setupUi

    void retranslateUi(QDialog *ImportProject)
    {
        ImportProject->setWindowTitle(QApplication::translate("ImportProject", "Import Project", nullptr));
        groupBoxButtons->setTitle(QString());
        pushButtonHelp->setText(QApplication::translate("ImportProject", "Help", nullptr));
        pushButtonClose->setText(QApplication::translate("ImportProject", "Close", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonImport->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pushButtonImport->setText(QApplication::translate("ImportProject", " Import Project ", nullptr));
        groupBox->setTitle(QString());
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_2->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("ImportProject", "Import PIHMgis Project File", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButtonProject->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonProject->setText(QApplication::translate("ImportProject", "Browse...", nullptr));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer.", nullptr));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("ImportProject", "Old Workspace", nullptr));
#ifndef QT_NO_TOOLTIP
        label_4->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer.", nullptr));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("ImportProject", "Current Workspace", nullptr));
#ifndef QT_NO_TOOLTIP
        label_5->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("ImportProject", "New Project Name", nullptr));
#ifndef QT_NO_TOOLTIP
        new_lineEdit_ProjectFile->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
        new_lineEdit_ProjectFile->setText(QString());
        label_6->setText(QApplication::translate("ImportProject", "Note: Import does not copy the datasets into your new workspace", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_Data_Base_Folder->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButtonProject_DataFolder->setToolTip(QApplication::translate("ImportProject", "Existing Project is a project that was not created on some other computer or Home directory structure has been altered (by moving or renaming).", nullptr));
#endif // QT_NO_TOOLTIP
        pushButtonProject_DataFolder->setText(QApplication::translate("ImportProject", "Browse...", nullptr));
#ifndef QT_NO_TOOLTIP
        label_7->setToolTip(QApplication::translate("ImportProject", "<html><head/><body><p>Specify the New Base/Root Folder Location. By Default this is the same location as your import PIHMgis file. This may not work for you. So you can change the folder location.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_7->setText(QApplication::translate("ImportProject", "<html><head/><body><p>Specify the New Base/Root Folder Location</p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        label_8->setToolTip(QApplication::translate("ImportProject", "<html><head/><body><p>Specify the New Base/Root Folder Location. By Default this is the same location as your import PIHMgis file. This may not work for you. So you can change the folder location.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("ImportProject", "<html><head/><body><p>to replace these old project directories</p></body></html>", nullptr));
        checkBox_Search->setText(QApplication::translate("ImportProject", "Try to find input files within new base folder?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImportProject: public Ui_ImportProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTPROJECT_H
