#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Считываем список заметок и добавляем его в интерфейс
    QString noteListFileName = "list.ntbk";

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
    resetNoteView();
    
    auto *newNoteListItem = new QListWidgetItem();
    newNoteListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    
    ui->noteList->addItem(newNoteListItem);
    ui->noteList->editItem(newNoteListItem);
}
        

void MainWindow::on_deleteNoteButton_clicked()
{
    // Удаляем соответствующий заметке элемент списка и файл, затем сохраняем список в файле
    if (!checkNoteSelection())
        return;

    QString deleteNoteName = ui->selectedNoteLabel->text().trimmed();

    resetNoteView();

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
    if (!checkNoteSelection())
        return;

    QFile noteFile(ui->selectedNoteLabel->text().trimmed() + ".txt");

    if (!noteFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream noteFileWriteStream(&noteFile);
    noteFileWriteStream.setCodec("UTF-8");
    
    noteFileWriteStream << ui->noteTextEdit->toPlainText();

    noteFile.close();
}


void MainWindow::on_noteList_itemChanged(QListWidgetItem *changedNoteListItem)
{
    // Меняем название файла заметки и сохраняем список заметок
    QString newNoteName = changedNoteListItem->text();
    
    QString oldNoteFileName = ui->selectedNoteLabel->text().trimmed() + ".txt";
    
    if (QFile::exists(oldNoteFileName))
    {
        QFile::rename(oldNoteFileName, newNoteName.trimmed() + ".txt");
    }

    ui->selectedNoteLabel->setText(newNoteName);

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
        
    QString noteText = noteFile.readAll();
    ui->noteTextEdit->setPlainText(noteText);
        
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
    QFile noteListFile("list.ntbk");

    if (!noteListFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream noteListFileWriteStream(&noteListFile);
    noteListFileWriteStream.setCodec("UTF-8");

    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem const* noteListItem = ui->noteList->item(i);
        noteListFileWriteStream << noteListItem->text().trimmed() << "\n";
    }

    noteListFile.close();
    return true;
}


void MainWindow::resetNoteView() 
{
    ui->noteTextEdit->clear();
    ui->selectedNoteLabel->setText("Selected note:");
}

bool MainWindow::checkNoteSelection()
{
    return QFile::exists("list.ntbk") && ui->selectedNoteLabel->text().trimmed() != "Selected note:";
}
