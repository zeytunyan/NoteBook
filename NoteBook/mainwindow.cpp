﻿#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Считываем список заметок и добавляем его в интерфейс
    QString noteListFileName = "list.txt";

    if (!QFile::exists(noteListFileName)) 
        return;
    
    QFile noteListFile(noteListFileName);
        
    if (!noteListFile.open(QIODevice::ReadOnly))
        return;
        
    QString noteListString = noteListFile.readAll();
    
    noteListFile.close();
    
    QStringList noteListNames = noteListString.split("\r\n");
    ui->noteList->addItems(noteListNames);
    delete ui->noteList->item(ui->noteList->count() - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addNoteButton_clicked()
{
    // Добавляем новый пункт-заметку в список и сразу активируем её редактирование
    ui->noteTextEdit->clear();
    ui->selectedNoteLabel->setText("Selected note:");
    
    auto *newNoteListItem = new QListWidgetItem();
    newNoteListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    
    ui->noteList->addItem(newNoteListItem);
    ui->noteList->editItem(newNoteListItem);
    }
        

void MainWindow::on_deleteNoteButton_clicked()
{
    // Удаляем соответствующие заметке элемент списка и файл, затем сохраняем списко в файле
    if (!QFile::exists("list.txt"))
        return;

    QString selectedNoteLabelText = "Selected note:";
    QString deleteNoteName = ui->selectedNoteLabel->text().trimmed();
    
    if (deleteNoteName == selectedNoteLabelText)
        return;


    ui->noteTextEdit->clear();
    ui->selectedNoteLabel->setText(selectedNoteLabelText);

    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem* noteListItem = ui->noteList->item(i);

        if (noteListItem->text().trimmed() == deleteNoteName)
            delete noteListItem;
    }

    QString deleteNoteFileName = deleteNoteName + ".txt";

    if (QFile::exists(deleteNoteFileName))
    {
        QFile(deleteNoteFileName).remove();
    }

    saveNoteList();
}


void MainWindow::on_saveNoteButton_clicked()
{
    // Сохраняем текст заметки в соответствующий файл
    if (!QFile::exists("list.txt"))
        return;

    QString saveNoteFileName = ui->selectedNoteLabel->text().trimmed() + ".txt";

    if (saveNoteFileName == "Selected note:.txt")
        return;

    QFile noteFile(saveNoteFileName);

    if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream noteFileWriteStream(&noteFile);
    
    noteFileWriteStream << ui->noteTextEdit->toPlainText();

    noteFile.close();
}


void MainWindow::on_noteList_itemChanged(QListWidgetItem *changedNoteListItem)
{
    // Меняем название файла заметки и соответствующего пункта в списке, затем сохраняем список в файле
    QString oldNoteFileName = ui->selectedNoteLabel->text().trimmed() + ".txt";
    
    if (oldNoteFileName != "Selected note:.txt" && QFile::exists(oldNoteFileName))
    {
        QFile::rename(oldNoteFileName, changedNoteListItem->text().trimmed() + ".txt");  
    }

    ui->selectedNoteLabel->setText(changedNoteListItem->text());

    saveNoteList();
}


void MainWindow::on_noteList_itemClicked(QListWidgetItem *clickedNoteListItem)
{
    // Считываем содержимое файла заметки и помещаем этот текст в текстовое поле
    ui->selectedNoteLabel->setText(clickedNoteListItem->text());
    ui->noteTextEdit->clear();
    
    QString selectedNoteFileName = ui->selectedNoteLabel->text().trimmed() + ".txt";
    
    if (!QFile::exists(selectedNoteFileName))
        return;
    
    QFile noteFile(selectedNoteFileName);
        
    if (!noteFile.open(QIODevice::ReadOnly))
        return;
        
    ui->noteTextEdit->setPlainText(QString::fromUtf8(noteFile.readAll()));
        
    noteFile.close();
}


void MainWindow::on_noteList_itemDoubleClicked(QListWidgetItem *doubleClickedNoteListItem)
{
    // Делаем то же, что и при обычном клике, но при этом ещё и редактируем пункт-заметку в списке
    on_noteList_itemClicked(doubleClickedNoteListItem);

    doubleClickedNoteListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    ui->noteList->editItem(doubleClickedNoteListItem);
}


bool MainWindow::saveNoteList() 
{
    QFile noteListFile("list.txt");

    if (!noteListFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream noteListFileWriteStream(&noteListFile);

    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem const* noteListItem = ui->noteList->item(i);
        noteListFileWriteStream << noteListItem->text().trimmed() << "\n";
    }

    noteListFile.close();
}
