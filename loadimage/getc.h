#ifndef GETC_H
#define GETC_H

#include <QDialog>

namespace Ui {
class getC;
}

class getC : public QDialog
{
    Q_OBJECT

public:
    explicit getC(QWidget *parent = nullptr);
    ~getC();
public slots:
    void accept();
signals:
    void confirmed(double);
private:
    Ui::getC *ui;
};

#endif // GETC_H
