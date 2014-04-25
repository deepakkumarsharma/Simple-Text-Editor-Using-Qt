#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextEdit>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                QString(),
                tr("file Name(*.txt)")
                );
    if (!filename.isEmpty()) {
        QFile file(filename);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void MainWindow::on_actionSave_triggered()
{

     QString filename=QFileDialog::getSaveFileName(
                 this,
                 tr("Save File"),
                 QString(),
                 tr("file Name(*.txt)")
                 );
     if(!filename.isEmpty()) {
         QFile file(filename);
         if (!file.open(QIODevice::WriteOnly)) {
             QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
             return;
         } else {
             QTextStream stream(&file);
             stream << ui->textEdit->toPlainText();
             stream.flush();
             file.close();
         }

     }

}

