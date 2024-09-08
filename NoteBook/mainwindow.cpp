#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ��������� ������ ������� � ��������� ��� � ���������
    QString noteListFileName = "list.txt";

    if (!QFile::exists(noteListFileName)) 
        return;
    
    QFile noteListFile(noteListFileName);
        
    if (!noteListFile.open(QIODevice::ReadOnly))
        return;
        
    QString noteListString = noteListFile.readAll();
    
    noteListFile.close();
    
    ui->noteList->addItems(noteListString.split("\n"));   
    delete ui->noteList->item(ui->noteList->count() - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_addNoteButton_clicked()
{
    // ��������� ����� �����-������� � ������ � ��������� ������ � �����
    ui->noteTextEdit->clear();
    ui->selectedNoteLabel->setText("Selected note:");
    
    auto *newNoteListItem = new QListWidgetItem();
    newNoteListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    
    ui->noteList->addItem(newNoteListItem);
    ui->noteList->editItem(newNoteListItem);


    QFile noteListFile("list.txt");
    
    if (!noteListFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream noteListFileWriteStream(&noteListFile);
        
    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem const *noteListItem = ui->noteList->item(i);
        noteListFileWriteStream << noteListItem->text() << "\n";
    }
        
    noteListFile.close();
}

void MainWindow::on_toolButton_2_clicked()
{
    if (!QFile::exists("list.txt"))
        return;

    QString nameInLbl = ui->selectedNoteLabel->text().trimmed();

    if (nameInLbl == "Selected note:")
        return;

    if (QFile::exists(nameInLbl + ".txt"))
    {
        QFile(nameInLbl + ".txt").remove();
    }

    ui->noteTextEdit->clear();
    ui->selectedNoteLabel->setText("Selected note:");

    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem* itm = ui->noteList->item(i);

        if (itm->text().trimmed() == nameInLbl)
            delete itm;
    }

    QFile fileO("list.txt");

    if (fileO.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileO);

        for (int i = 0; i < ui->noteList->count(); i++)
        {
            QListWidgetItem* itm = ui->noteList->item(i);
            writeStream << itm->text() << "\n";
        }

        fileO.close();
    }
}

void MainWindow::on_toolButton_3_clicked()
{
    if (!QFile::exists("list.txt"))
        return;

    QString nameInWgt = ui->selectedNoteLabel->text().trimmed() + ".txt";

    if (nameInWgt == "Selected note:.txt")
        return;

    QFile fileOut(nameInWgt);

    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&fileOut);
    out << ui->noteTextEdit->toPlainText();

    fileOut.close();
}


void MainWindow::on_noteList_itemChanged(QListWidgetItem *changedNoteListItem)
{
    // ������ �������� ����� ������� � ���������������� ������ � ������, ����� ��������� ������ � �����
    QString oldNoteName = ui->selectedNoteLabel->text().trimmed() + ".txt";
    
    if (oldNoteName != "Selected note:.txt" && QFile::exists(oldNoteName))
    {
        QFile::rename(oldNoteName, changedNoteListItem->text().trimmed() + ".txt");  
    }

    ui->selectedNoteLabel->setText(changedNoteListItem->text());

        
    QFile noteListFile("list.txt");
    
    if (!noteListFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    
    QTextStream noteListFileWriteStream(&noteListFile);
        
    for (int i = 0; i < ui->noteList->count(); i++)
    {
        QListWidgetItem const *noteListItem = ui->noteList->item(i);
        noteListFileWriteStream << noteListItem->text() << "\n";
    }
        
    noteListFile.close();
}


void MainWindow::on_noteList_itemClicked(QListWidgetItem *clickedNoteListItem)
{
    // ��������� ���������� ����� ������� � �������� ���� ����� � ��������� ����
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
    // ������ �� ��, ��� � ��� ������� �����, �� ��� ���� ��� � ����������� �����-������� � ������
    on_noteList_itemClicked(doubleClickedNoteListItem);

    doubleClickedNoteListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    ui->noteList->editItem(doubleClickedNoteListItem);
}
