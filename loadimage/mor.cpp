#include "mor.h"
#include "ui_mor.h"

mor::mor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mor)
{
    ui->setupUi(this);
}

mor::~mor()
{
    delete ui;
}
void mor::accept()
{
    //qDebug()<<"accept";
    bool ok;
    int c=ui->lineEdit->text().toInt(&ok);
    int str1=ui->comboBox->currentIndex();
    if(ok)
    {
        emit confirmed(c,str1);
    }
    close();
}
