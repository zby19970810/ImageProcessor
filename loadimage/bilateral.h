#ifndef BILATERAL_H
#define BILATERAL_H

#include <QDialog>

namespace Ui {
class bilateral;
}

class bilateral : public QDialog
{
    Q_OBJECT

public:
    explicit bilateral(QWidget *parent = nullptr);
    ~bilateral();
public slots:
    void accept();
signals:
    void gotit(int,double,double);
private:
    Ui::bilateral *ui;
};

#endif // BILATERAL_H
