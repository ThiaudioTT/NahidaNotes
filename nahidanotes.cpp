#include "nahidanotes.h"
#include "./ui_nahidanotes.h"

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
