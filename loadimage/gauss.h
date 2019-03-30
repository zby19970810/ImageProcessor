#ifndef GAUSS_H
#define GAUSS_H

#include <QDialog>

namespace Ui {
class gauss;
}

class gauss : public QDialog
{
    Q_OBJECT

public:
    explicit gauss(QWidget *parent = nullptr);
    ~gauss();
public slots:
    void accept();
signals:
    void gotit(int,double);
private:
    Ui::gauss *ui;
};

#endif // GAUSS_H
