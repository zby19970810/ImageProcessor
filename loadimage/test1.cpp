#include "test1.h"
#include "ui_test1.h"

test1::test1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::test1)
{
    ui->setupUi(this);
}

test1::~test1()
{
    delete ui;
}
void test1::accept()
{
    //qDebug()<<"accept";
    bool ok1,ok2;
    double E=ui->lineEdit->text().toDouble(&ok1);
    double m=ui->lineEdit_2->text().toDouble(&ok2);
    bool ok=ok1&&ok2;
    if(ok)
    {
        emit getval(m,E);
    }
    close();
}
