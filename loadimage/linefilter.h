#ifndef LINEFILTER_H
#define LINEFILTER_H

#include <QDialog>
#include <vector>
namespace Ui {
class lineFilter;
}

class lineFilter : public QDialog
{
    Q_OBJECT

public:
    explicit lineFilter(QWidget *parent = nullptr);
    ~lineFilter();

private:
    Ui::lineFilter *ui;
    bool parseRow(QString,std::vector<double>&,int&);
public slots:
    void accept();
signals:
    void confirmed(std::vector<double>,int nCol,int index,int col);
};

#endif // LINEFILTER_H
