#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QTextStream>
#include <QFile>
#include <QListWidgetItem>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addNoteButton_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_toolButton_3_clicked();

    void on_toolButton_2_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
