#ifndef MOR_H
#define MOR_H

#include <QDialog>

namespace Ui {
class mor;
}

class mor : public QDialog
{
    Q_OBJECT

public:
    explicit mor(QWidget *parent = nullptr);
    ~mor();
public slots:
    void accept();
signals:
    void confirmed(int,int);
private:
    Ui::mor *ui;
};

#endif // MOR_H
