#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
static int index;
static QFileInfoList imgs;
using std::vector;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fd(new QFileDialog(this)),
  scene(nullptr),pitem(nullptr),
  dlgLog(new getC(this)),
  dlgLog2(new test1(this)),
  dlgGauss(new gauss(this)),
  dlgBila(new bilateral(this)),
  dlgMid(new middle(this)),
  dlgMor(new mor(this)),
  dlgLiner(new lineFilter(this))
{
    fd->setNameFilter("Image(*.png *.jpg *.bmp)");
    fd->setFileMode(QFileDialog::ExistingFile);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete dlgLog;
    delete dlgLog2;
    delete dlgGauss;
    delete dlgBila;
    delete dlgMid;
    delete ui;
    delete fd;
    delete pitem;
    delete scene;
}
void MainWindow::on_btnOpen_clicked()
{
    if(fd->exec())
    {
        QStringList files=fd->selectedFiles();
        //qDebug()<<files[0];

        QDir dir=fd->directory();
        QStringList filters;
        filters<<"*.png"<<"*.jpg"<<"*.bmp";
        imgs=dir.entryInfoList(filters);
        int i;
        for(i=0;i<imgs.size();i++)
        {
            if(imgs[i].absoluteFilePath()==files[0])
            {
                index=i;
                break;
            }
        }
    showoff();

    fd->close();
    }
}
void MainWindow::on_btnReset_clicked()
{
    QRectF rect=pitem->boundingRect();
    pitem->reset();
    scene->setSceneRect(rect);
    ui->graphicsView->fitInView(pitem,Qt::KeepAspectRatio);
    ui->graphicsView->centerOn(pitem);
    //showoff();
}
void MainWindow::on_btnPre_clicked()
{
    index--;
    if(index==-1) index=imgs.size()-1;
    showoff();
}
void MainWindow::on_btnNext_clicked()
{
    index++;
    if(index==imgs.size()) index=0;
    showoff();
}
void MainWindow::showoff(){
    QImage image(imgs[index].absoluteFilePath());
    showoff(image);
    on_btnReset_clicked();
}
void MainWindow::showoff(QImage img){
    if(pitem)
    {
        delete pitem;
        pitem=nullptr;

    }
    if(scene)
    {
        delete scene;
        scene=nullptr;
    }
    scene = new QGraphicsScene(this);
    pitem = new MyPixmapItem();
    pitem->setPixmap(QPixmap::fromImage(img));
    scene->addItem(pitem);
    ui->graphicsView->setScene(scene);

}

QImage MainWindow::getCurrentImage() const{
    //if(!pitem) return;
    QList<QGraphicsItem*> items=ui->graphicsView->scene()->items();
    QGraphicsPixmapItem* item=(QGraphicsPixmapItem*) items.at(0);
    QImage image=item->pixmap().toImage();
    return image;
}
void MainWindow::on_actionrgb2gray_triggered()
{
    //qDebug()<<"rgb";
    //get image
    if(!pitem) return;
    QImage image=getCurrentImage();
    //rgb2gray
    image = ImageProcessor::rgb2gray(image);
    //showimage
    showoff(image);
}
void MainWindow::on_actionlog_triggered(){
    //qDebug()<<"log";
    dlgLog->exec();
}
void MainWindow::on_getC_confirmed(double c){
    //qDebug()<<c;
    if(!pitem) return;
    QImage image=getCurrentImage();
    //transform
    image = ImageProcessor::logTransformation(image,c);
    //showimage
    showoff(image);
}
void MainWindow::on_actioncontrast_triggered()
{
    //qDebug()<<"ccccccccccc";
    //get image
    if(!pitem) return;
    QImage image=getCurrentImage();
    //rgb2gray
    image = ImageProcessor::contrast(image);
    //showimage
    showoff(image);
}
void MainWindow::on_actiontest_triggered()
{
    dlgLog2->exec();
}
void MainWindow::on_test1_getval(double m,double E){
    //qDebug()<<c;
    if(!pitem) return;
    QImage image=getCurrentImage();
    //transform
    image = ImageProcessor::strething(image,m,E);
    //showimage
    showoff(image);
}
void MainWindow::on_actionaverage_triggered(){
    if(!pitem) return;
        QImage image=getCurrentImage();
        //rgb2gray
        image = ImageProcessor::average(image);
        //showimage
        showoff(image);
}
void MainWindow::on_actionrgbaverage_triggered(){
    if(!pitem) return;
        QImage image=getCurrentImage();
        //rgb2gray
        image = ImageProcessor::rgbaverage(image);
        //showimage
        showoff(image);
}
void MainWindow::on_actionLiner_triggered()
{
    dlgLiner->exec();
}
void MainWindow::on_lineFilter_confirmed(vector<double> data,int nCol,int index,int col)
{
    QImage img=getCurrentImage();
    normal(data);
    img=ImageProcessor::linearFilter(img,data,nCol,index,col);
    showoff(img);
}
void MainWindow:: normal(vector<double>& data)
{
    double sum=0;
    for(int i=0;i<data.size();i++){
        sum+=data[i];
    }
    if(sum==0||sum==1) return;
    else{
        for(int i=0;i<data.size();i++){
            data[i]=data[i]/sum;
        }
    }
}
void MainWindow::on_actiongauss_triggered(){
    dlgGauss->exec();
}
void MainWindow::on_gauss_gotit(int size,double sigma){
    QImage img=getCurrentImage();
    img=ImageProcessor::gaussFilter(img,size,sigma);
    showoff(img);
}
void MainWindow::on_actionbilateral_triggered(){
    dlgBila->exec();
}
void MainWindow::on_bilateral_gotit(int size,double sigma1,double sigma2){
    QImage img=getCurrentImage();
    img=ImageProcessor::bilateralFilter(img,size,sigma1,sigma2);
    showoff(img);
}
void MainWindow::on_actionmiddle_triggered(){
    dlgMid->exec();
}
void MainWindow::on_middle_getsize(int size){
    QImage img=getCurrentImage();
    img=ImageProcessor::midFilter(img,size);
    showoff(img);
}
void MainWindow::on_actionmorphology_triggered(){
    dlgMor->exec();
}
void MainWindow::on_mor_confirmed(int size,int kind){
    QImage img=getCurrentImage();
    img=ImageProcessor::morFilter(img,size,kind);
    showoff(img);
}
