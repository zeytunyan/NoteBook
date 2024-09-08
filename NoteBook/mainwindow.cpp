#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString listFileName = "list";

    if (!QFile::exists(listFileName)) 
        return;
    
    QFile listFile(listFileName);
        
    if (!listFile.open(QIODevice::ReadOnly))
        return;
        
    QString list = listFile.readAll();
    
    listFile.close();
    
    ui->listWidget->addItems(list.split("\n"));   
    delete ui->listWidget->item(ui->listWidget->count() - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_toolButton_clicked()
{
    ui->textEdit->clear();
    ui->label_2->setText("Selected note:");
    
    auto *item = new QListWidgetItem();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    
    ui->listWidget->addItem(item);
    ui->listWidget->editItem(item);

    QFile fileO("list");
    
    if (fileO.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileO);
        
        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            QListWidgetItem const *itm = ui->listWidget->item(i);
            writeStream << itm->text() << "\n";
        }
        
        fileO.close();
    }
}

void MainWindow::on_listWidget_itemChanged(QListWidgetItem *item)
{
    QString oldName = ui->label_2->text().trimmed() + ".txt";
    
    if (oldName != "Selected note:.txt" && QFile::exists(oldName))
    {
        QFile::rename(oldName, item->text().trimmed() + ".txt");  
    }

    QFile fileO("list");
    
    if (fileO.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileO);
        
        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            QListWidgetItem const *itm = ui->listWidget->item(i);
            writeStream << itm->text() << "\n";
        }
        
        fileO.close();
    }
    
    ui->label_2->setText(item->text());
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->label_2->setText(item->text());
    ui->textEdit->clear();
    
    QString string = ui->label_2->text().trimmed() + ".txt";
    
    if (QFile::exists(string))
    {
        QFile file(string);
        
        if (!file.open(QIODevice::ReadOnly))
            return;
        
        ui->textEdit->setPlainText(QString::fromUtf8(file.readAll()));
        
        file.close();
    }
}

void MainWindow::on_toolButton_3_clicked()
{
    if (!QFile::exists("list"))
        return;
    
    QString nameInWgt = ui->label_2->text().trimmed() + ".txt";
    
    if (nameInWgt == "Selected note:.txt")
        return;

    QFile fileOut(nameInWgt);
    
    if (!fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    
    QTextStream out(&fileOut);
    out << ui->textEdit->toPlainText();
    
    fileOut.close();
}

void MainWindow::on_toolButton_2_clicked()
{
    if (!QFile::exists("list"))
        return;
    
    QString nameInLbl = ui->label_2->text().trimmed();
    
    if (nameInLbl == "Selected note:")
        return;
    
    if (QFile::exists(nameInLbl + ".txt"))
    {
        QFile(nameInLbl + ".txt").remove();
    }

    ui->textEdit->clear();
    ui->label_2->setText("Selected note:");

    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QListWidgetItem *itm = ui->listWidget->item(i);
        
        if (itm->text().trimmed() == nameInLbl)
            delete itm;
    }

    QFile fileO("list");
    
    if (fileO.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream writeStream(&fileO);
        
        for (int i = 0; i < ui->listWidget->count(); i++)
        {
            QListWidgetItem *itm = ui->listWidget->item(i);
            writeStream << itm->text() << "\n";
        }
        
        fileO.close();
    }
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    ui->label_2->setText(item->text());
    ui->textEdit->clear();
    
    QString string = ui->label_2->text().trimmed() + ".txt";
    
    if (QFile::exists(string))
    {
        QFile file(string);
        
        if (!file.open(QIODevice::ReadOnly))
            return;
        
        ui->textEdit->setPlainText(QString::fromUtf8(file.readAll()));
        
        file.close();
    }

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable);
    ui->listWidget->editItem(item);
}
