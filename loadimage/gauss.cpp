#include "gauss.h"
#include "ui_gauss.h"

gauss::gauss(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gauss)
{
    ui->setupUi(this);
}

gauss::~gauss()
{
    delete ui;
}
void gauss::accept()
{
    //qDebug()<<"accept";
    bool ok1,ok2;
    int size=ui->lineEdit->text().toInt(&ok1);
    double sigma=ui->lineEdit_2->text().toDouble(&ok2);
    if(ok1&&ok2)
    {
        emit gotit(size,sigma);
    }
    close();
}
