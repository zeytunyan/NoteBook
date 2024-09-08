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

    void on_noteList_itemChanged(QListWidgetItem *changedNoteListItem);

    void on_noteList_itemClicked(QListWidgetItem *clickedNoteListItem);

    void on_saveNoteButton_clicked();

    void on_deleteNoteButton_clicked();

    void on_noteList_itemDoubleClicked(QListWidgetItem *doubleClickedNoteListItem);

    bool saveNoteList();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
