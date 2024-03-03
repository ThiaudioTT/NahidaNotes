#include "nahidanotes.h"
#include "./ui_nahidanotes.h"

#include <QFileDialog>
#include <QMessageBox>

NahidaNotes::NahidaNotes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::NahidaNotes)
{
    ui->setupUi(this);
}

NahidaNotes::~NahidaNotes()
{
    delete ui;
}


void NahidaNotes::on_actionNew_triggered()
{
    currentFile.clear(); // clears filename
    ui->textEdit->setText(QString());
}


void NahidaNotes::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty()) return;

    if(!fileName.contains(".txt") && !fileName.contains(".md")){
        QMessageBox::warning(this, "Warning", "Please, use only .txt or .md files!");
        return;
    }

    QFile file(fileName);
    currentFile = fileName;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

// Save the opened file
// TODO: improve doc and code
void NahidaNotes::on_actionSave_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();

}

