#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <mypixmapitem.h>
#include "imageprocessor.h"
#include "getc.h"
#include "test1.h"
#include "gauss.h"
#include "bilateral.h"
#include "middle.h"
#include "mor.h"
#include <linefilter.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileDialog *fd;
    QGraphicsScene *scene;
    MyPixmapItem *pitem;
    getC* dlgLog;
    test1* dlgLog2;
    gauss* dlgGauss;
    bilateral* dlgBila;
    middle* dlgMid;
    mor* dlgMor;
    lineFilter* dlgLiner;
    void showoff();
    void showoff(QImage img);
    QImage getCurrentImage() const;
    void normal(std::vector<double>&);
public slots:
    void on_btnOpen_clicked();
    void on_btnReset_clicked();
    void on_btnPre_clicked();
    void on_btnNext_clicked();
    void on_actionrgb2gray_triggered();
    void on_actionlog_triggered();
    void on_actioncontrast_triggered();
    void on_actiontest_triggered();
    void on_getC_confirmed(double);
    void on_test1_getval(double,double);
    void on_actionaverage_triggered();
    void on_actionrgbaverage_triggered();
    void on_actionLiner_triggered();
    void on_actiongauss_triggered();
    void on_actionbilateral_triggered();
    void on_actionmiddle_triggered();
    void on_actionmorphology_triggered();
    void on_lineFilter_confirmed(std::vector<double>,int,int,int);
    void on_gauss_gotit(int,double);
    void on_bilateral_gotit(int,double,double);
    void on_middle_getsize(int);
    void on_mor_confirmed(int,int);
};

#endif // MAINWINDOW_H
