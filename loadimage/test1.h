#ifndef TEST1_H
#define TEST1_H

#include <QDialog>

namespace Ui {
class test1;
}

class test1 : public QDialog
{
    Q_OBJECT

public:
    explicit test1(QWidget *parent = nullptr);
    ~test1();
public slots:
    void accept();
signals:
    void getval(double,double);
private:
    Ui::test1 *ui;
};

#endif // TEST1_H
