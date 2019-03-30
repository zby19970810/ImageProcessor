#include "linefilter.h"
#include "ui_linefilter.h"
#include <QDebug>
#include<QRegExp>
using std::vector;
lineFilter::lineFilter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lineFilter)
{
    ui->setupUi(this);
}

lineFilter::~lineFilter()
{
    delete ui;
}
void lineFilter::accept()
{
    QString str=ui->textEdit->toPlainText();
    int str1=ui->comboBox->currentIndex();
    int str2=ui->comboBox_2->currentIndex();
    str=str.replace("\n","").trimmed();
    vector<double> data;
    int nCol=-1;
    QStringList rows=str.split(";");
    for(int i=0;i<rows.size();++i)
    {
        if(rows[i].isEmpty()) continue;
        bool ok;
        int tmp;
        ok = parseRow(rows[i],data,tmp);
        if(nCol==-1) nCol=tmp;
        if(!ok||nCol!=tmp)
        {
            close();
            return;
        }
    }
    //qDebug()<<data;
    emit confirmed(data,nCol,str1,str2);
    close();
}
bool lineFilter::parseRow(QString row,vector<double>& data,int& nCol)
{
    nCol=0;
    QStringList cols=row.trimmed().split(QRegExp("\\s+|\\s*,\\s*"));
    for(int i=0;i<cols.size();i++){
        if(cols[i].isEmpty()) continue;
        bool ok;
        double d=cols[i].toDouble(&ok);
        if(ok)
        {
            data.push_back(d);
            nCol++;
        }
        else
        {
            return false;
        }
    }
    return true;
}
