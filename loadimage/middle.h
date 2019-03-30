#ifndef MIDDLE_H
#define MIDDLE_H

#include <QDialog>

namespace Ui {
class middle;
}

class middle : public QDialog
{
    Q_OBJECT

public:
    explicit middle(QWidget *parent = nullptr);
    ~middle();
public slots:
    void accept();
signals:
    void getsize(int);
private:
    Ui::middle *ui;
};

#endif // MIDDLE_H
