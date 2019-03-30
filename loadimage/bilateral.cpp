#include "bilateral.h"
#include "ui_bilateral.h"

bilateral::bilateral(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bilateral)
{
    ui->setupUi(this);
}

bilateral::~bilateral()
{
    delete ui;
}
void bilateral::accept()
{
    //qDebug()<<"accept";
    bool ok1,ok2,ok3;
    int size=ui->lineEdit_3->text().toInt(&ok1);
    double sigma1=ui->lineEdit_2->text().toDouble(&ok2);
    double sigma2=ui->lineEdit->text().toDouble(&ok3);
    if(ok1&&ok2&&ok3)
    {
        emit gotit(size,sigma1,sigma2);
    }
    close();
}
