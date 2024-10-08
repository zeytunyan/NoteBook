/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QToolButton *addNoteButton;
    QToolButton *deleteNoteButton;
    QListWidget *noteList;
    QTextEdit *noteTextEdit;
    QToolButton *saveNoteButton;
    QLabel *noteListLabel;
    QLabel *selectedNoteLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(490, 420);
        MainWindow->setMinimumSize(QSize(490, 420));
        MainWindow->setMaximumSize(QSize(490, 420));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../Resources/notebook.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        addNoteButton = new QToolButton(centralWidget);
        addNoteButton->setObjectName(QString::fromUtf8("addNoteButton"));
        addNoteButton->setGeometry(QRect(10, 370, 91, 41));
        QPalette palette;
        QBrush brush(QColor(0, 130, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        addNoteButton->setPalette(palette);
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        addNoteButton->setFont(font);
        deleteNoteButton = new QToolButton(centralWidget);
        deleteNoteButton->setObjectName(QString::fromUtf8("deleteNoteButton"));
        deleteNoteButton->setGeometry(QRect(110, 370, 91, 41));
        QPalette palette1;
        QBrush brush2(QColor(255, 0, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        deleteNoteButton->setPalette(palette1);
        deleteNoteButton->setFont(font);
        noteList = new QListWidget(centralWidget);
        noteList->setObjectName(QString::fromUtf8("noteList"));
        noteList->setGeometry(QRect(10, 50, 191, 311));
        noteTextEdit = new QTextEdit(centralWidget);
        noteTextEdit->setObjectName(QString::fromUtf8("noteTextEdit"));
        noteTextEdit->setGeometry(QRect(210, 50, 271, 311));
        saveNoteButton = new QToolButton(centralWidget);
        saveNoteButton->setObjectName(QString::fromUtf8("saveNoteButton"));
        saveNoteButton->setGeometry(QRect(210, 370, 271, 41));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        saveNoteButton->setFont(font1);
        noteListLabel = new QLabel(centralWidget);
        noteListLabel->setObjectName(QString::fromUtf8("noteListLabel"));
        noteListLabel->setGeometry(QRect(20, 10, 141, 31));
        noteListLabel->setFont(font1);
        selectedNoteLabel = new QLabel(centralWidget);
        selectedNoteLabel->setObjectName(QString::fromUtf8("selectedNoteLabel"));
        selectedNoteLabel->setGeometry(QRect(220, 10, 261, 31));
        selectedNoteLabel->setFont(font1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "NoteBook", nullptr));
        addNoteButton->setText(QApplication::translate("MainWindow", "+", nullptr));
        deleteNoteButton->setText(QApplication::translate("MainWindow", "\303\227", nullptr));
        saveNoteButton->setText(QApplication::translate("MainWindow", "Save", nullptr));
        noteListLabel->setText(QApplication::translate("MainWindow", "Notes:", nullptr));
        selectedNoteLabel->setText(QApplication::translate("MainWindow", "Selected note:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
