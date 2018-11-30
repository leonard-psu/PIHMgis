#include <QDebug>
#include <QMessageBox>

#include "inspectproject.h"
#include "ui_inspectproject.h"
#include "globals.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InspectProject Constructor
// Parent is Main Window, filename is the open project text file used to store project details
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InspectProject::InspectProject(QWidget *parent, QString filename) : QDialog(parent), ui(new Ui::InspectProject)
{
    if(print_debug_messages)
        qDebug() << "INFO: Start InspectProject";

    try {
        ui->setupUi(this);

        filename_open_project = filename;
        bool found_file = false;

        if(print_debug_messages)
            qDebug() << "INFO: filename -> " << filename_open_project;

        QFile ProjectFile(filename_open_project);
        if ( ! ProjectFile.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            LogsString.append(tr("<span style=\"color:#FF0000\">Error: Unable to Open project file: </span>") + filename_open_project +tr("<br>"));
            ui->textBrowserLogs->setHtml(LogsString);
            ui->textBrowserLogs->repaint();
        }
        else
        {
            found_file = true;
        }

        ProjectFile.close();

        if(found_file)
        {
            Load_Project_Settings();
        }

    } catch (...) {
        qDebug() << "Error: InspectProject is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InspectProject Deconstructor
// Todo: Check for memory leaks
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
InspectProject::~InspectProject()
{
    delete ui;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Load_Project_Settings
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool InspectProject::Load_Project_Settings()
{
    if(print_debug_messages)
        qDebug() << "INFO: InspectProject::Load_Project_Settings()";

    try {

        QFile inputFile(filename_open_project);
        inputFile.open(QIODevice::ReadOnly);
        QTextStream in(&inputFile);
        in.setCodec("UTF-8");
        QString text = in.readAll();
        ui->textBrowserLogs->setText(text);


    } catch (...) {
        qDebug() << "Error: InspectProject::Load_Project_Settings is returning w/o checking";
        return false;
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear_Search Helper function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InspectProject::Clear_Search(bool reset_find)
{
    if(print_debug_messages)
        qDebug() << "INFO: InspectProject::Clear_Search()";

    try {

        QTextDocument *document = ui->textBrowserLogs->document();

        QTextCursor highlightCursor(document);
        QTextCursor cursor(document);

        cursor.beginEditBlock();

        QString searchString = last_search;
        QTextCharFormat plainFormat(highlightCursor.charFormat());
        QTextCharFormat colorFormat = plainFormat;
        colorFormat.setForeground(Qt::black);
        colorFormat.setBackground(Qt::white);

        while (!highlightCursor.isNull() && !highlightCursor.atEnd())
        {
            highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

            if (!highlightCursor.isNull())
            {
                highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                highlightCursor.mergeCharFormat(colorFormat);
            }
        }

        cursor.endEditBlock();
        ui->labelINFO->setText(" " );

        if(reset_find)
            ui->lineEdit->setText("");

    }
    catch (...)
    {
        qDebug() << "Error: InspectProject::Clear_Search is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear_Search Helper function
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InspectProject::on_pushButton_FIND_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: InspectProject::on_pushButton_FIND_clicked()";

    try {

        Clear_Search(false);

        QString searchString = ui->lineEdit->text();
        QTextDocument *document = ui->textBrowserLogs->document();
        bool found = false;
        document->undo();

        if (searchString.isEmpty())
        {
            QMessageBox::information(this, tr("Empty Search Field"), tr("The search field is empty. ""Please enter a word and click Find."));
        }
        else
        {
            QTextCursor highlightCursor(document);
            QTextCursor cursor(document);

            cursor.beginEditBlock();

            QTextCharFormat plainFormat(highlightCursor.charFormat());
            QTextCharFormat colorFormat = plainFormat;
            colorFormat.setForeground(Qt::white);
            colorFormat.setBackground(Qt::black);

            int count = 0;
            while (!highlightCursor.isNull() && !highlightCursor.atEnd())
            {
                highlightCursor = document->find(searchString, highlightCursor, QTextDocument::FindWholeWords);

                if (!highlightCursor.isNull())
                {
                    found = true;
                    count += 1;
                    highlightCursor.movePosition(QTextCursor::WordRight, QTextCursor::KeepAnchor);
                    highlightCursor.mergeCharFormat(colorFormat);
                }
            }

            cursor.endEditBlock();


            if (found == false) {
                QMessageBox::information(this, tr("Word Not Found"),tr("Sorry, the word cannot be found."));
                ui->labelINFO->setText(" " );
            }
            else
            {
                ui->labelINFO->setText("Found " + QString::number(count));
                last_search = searchString;
            }
        }

    }
    catch (...)
    {
        qDebug() << "Error: InspectProject::on_pushButton_FIND_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OK Button Evebt
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InspectProject::on_pushButton_OK_clicked()
{
    if(print_debug_messages)
        qDebug() << "INFO: InspectProject::on_pushButton_OK_clicked()";

    try {

        close();
    }
    catch (...)
    {
        qDebug() << "Error: InspectProject::on_pushButton_OK_clicked is returning w/o checking";
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Clear Last Search Button Event
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void InspectProject::on_pushButton_CLEAR_clicked()
{
    Clear_Search(true);
}
