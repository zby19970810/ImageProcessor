#include "middle.h"
#include "ui_middle.h"

middle::middle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::middle)
{
    ui->setupUi(this);
}

middle::~middle()
{
    delete ui;
}
void middle::accept()
{
    //qDebug()<<"accept";
    bool ok;
    int c=ui->lineEdit->text().toInt(&ok);
    if(ok)
    {
        emit getsize(c);
    }
    close();
}
