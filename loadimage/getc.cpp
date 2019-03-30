#include "getc.h"
#include "ui_getc.h"
#include "QDebug"

getC::getC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::getC)
{
    ui->setupUi(this);
}

getC::~getC()
{
    delete ui;
}
void getC::accept()
{
    //qDebug()<<"accept";
    bool ok;
    double c=ui->lineEdit->text().toDouble(&ok);
    if(ok)
    {
        emit confirmed(c);
    }
    close();
}
