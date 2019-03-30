#include "imageprocessor.h"
#include <cmath>
#include <QDebug>
#include <algorithm>
using std::vector;
ImageProcessor::ImageProcessor()
{

}

QImage ImageProcessor::rgb2gray(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int gray=qGray(rgb);
            //int gray=(red*0.299+green*0.587+blue*0.199);
            ret.setPixel(i,j,qRgb(gray,gray,gray));
        }
    }
    return ret;
}
QImage ImageProcessor::logTransformation(const QImage& img,double c){
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int gray=qGray(rgb);
            int newPixel=c*log(1+gray/255.0)*255;
            if(newPixel>255) newPixel=255;
            //int gray=(red*0.299+green*0.587+blue*0.199);
            ret.setPixel(i,j,qRgb(newPixel,newPixel,newPixel));
        }
    }
    return ret;
}
QImage ImageProcessor::contrast(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int red=255-qRed(rgb);
            int green=255-qGreen(rgb);
            int blue=255-qBlue(rgb);
            //int gray=(red*0.299+green*0.587+blue*0.199);
            ret.setPixel(i,j,qRgb(red,green,blue));
        }
    }
    return ret;
}
QImage ImageProcessor::strething(const QImage& img,double m,double E)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int red=qRed(rgb);
            int green=qGreen(rgb);
            int blue=qBlue(rgb);
            double gray=(red+green+blue)/3.0;
            int stgray=1/(1+pow((m/gray*1.0),E))*255;
            ret.setPixel(i,j,qRgb(stgray,stgray,stgray));
        }
    }
    return ret;
}
QImage ImageProcessor::average(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    double compose[255]={0};
    int result[255]={0};
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int red=qRed(rgb);
            int green=qGreen(rgb);
            int blue=qBlue(rgb);
            int gray=round((red+green+blue)/3.0+.5);
            ret.setPixel(i,j,qRgb(gray,gray,gray));
            compose[gray]++;
        }
    }
    for(int k=1;k<256;k++){
        compose[k]+=compose[k-1];
        result[k]=round(255.0*compose[k]/(w*h));
        //qDebug()<<compose[k];
    }
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            int red=qRed(rgb);
            ret.setPixel(i,j,qRgb(result[red],result[red],result[red]));
        }
    }
    return ret;
}
QImage ImageProcessor::rgbaverage(const QImage& img)
{
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    double compose[255]={0};
    int result[255]={0};
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            compose[getInt(rgb)]++;
        }
    }
    for(int k=1;k<256;k++){
        compose[k]+=compose[k-1];
        result[k]=round(255.0*compose[k]/(w*h)+.5);
    }
    for(int i=0;i<w;++i){
        for(int j=0;j<h;++j){
            QRgb rgb=img.pixel(i,j);
            double h=getH(rgb);
            double s=getS(rgb);
            int inten=getInt(rgb);
            QRgb res=hsi2rgb(h,s,result[inten]/255.0);
            ret.setPixel(i,j,res);
        }
    }
    return ret;
}
QRgb ImageProcessor::rgb2hsi(const QRgb& rgb){
    int R=qRed(rgb);
    int G=qGreen(rgb);
    int B=qBlue(rgb);
    double var_R = ( R / 255.0 ); //RGB from 0 to 255
    double var_G = ( G / 255.0 );
    double var_B = ( B / 255.0 );
    double var_Min;//Min. value of RGB
    double var_Max; //Max. value of RGB
    if(var_B<=var_G&&var_B<=var_R) var_Min=var_B;
    if(var_G<=var_B&&var_G<=var_R) var_Min=var_G;
    if(var_R<=var_G&&var_R<=var_B) var_Min=var_R;
    if(var_B>=var_G&&var_B>=var_R) var_Max=var_B;
    if(var_G>=var_B&&var_G>=var_R) var_Max=var_G;
    if(var_R>=var_G&&var_R>=var_B) var_Max=var_R;
    double del_Max = var_Max - var_Min; //Delta RGB value
    double L = ( var_Max + var_Min ) / 2;
    double H; //HSL results from 0 to 1
    double S;
    if ( del_Max == 0.0 ) //This is a gray, no chroma...
    {
        H = 0; //HSL results from 0 to 1
        S = 0;
    }
    else //Chromatic data...
    {
    if ( L < 0.5 ) S = del_Max / ( var_Max + var_Min );
    else S = del_Max / ( 2 - var_Max - var_Min );
    double del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
    double del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
    double del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
    if ( var_R == var_Max ) H = del_B - del_G;
    else if ( var_G == var_Max ) H = ( 1 / 3 ) + del_R - del_B;
    else if ( var_B == var_Max ) H = ( 2 / 3 ) + del_G - del_R;
    if ( H < 0 ) H += 1;
    if ( H > 1 ) H -= 1;
    }
    return qRgb(255*H,255*S,255*L);
}
QRgb ImageProcessor::hsi2rgb(double H,double S,double L){
    int R,G,B;
    double var_1,var_2;
    if ( S == 0 ) //HSL from 0 to 1
    {
    R = L * 255; //RGB results from 0 to 255
    G = L * 255;
    B = L * 255;
    }
    else
    {
    if ( L < 0.5 ) var_2 = L * ( 1 + S );
    else var_2 = ( L + S ) - ( S * L );
    var_1 = 2 * L - var_2;
    R = 255 * Hue_2_RGB( var_1, var_2, H + ( 1.0 / 3.0 ) );
    G = 255 * Hue_2_RGB( var_1, var_2, H );
    B = 255 * Hue_2_RGB( var_1, var_2, H - ( 1.0 / 3.0 ) );
    }
    return qRgb(R,G,B);
}
int ImageProcessor::getInt(const QRgb& rgb){
    int R=qRed(rgb);
    int G=qGreen(rgb);
    int B=qBlue(rgb);
    int Min,Max;
    if(B<=G&&B<=R) Min=B;
    if(G<=B&&G<=R) Min=G;
    if(R<=G&&R<=B) Min=R;
    if(B>=G&&B>=R) Max=B;
    if(G>=B&&G>=R) Max=G;
    if(R>=G&&R>=B) Max=R;
    int L = (Max + Min ) / 2;
    return L;
}
double ImageProcessor::getH(const QRgb& rgb){
    int R=qRed(rgb);
    int G=qGreen(rgb);
    int B=qBlue(rgb);
    double var_R = ( R / 255.0 ); //RGB from 0 to 255
    double var_G = ( G / 255.0 );
    double var_B = ( B / 255.0 );
    double var_Min;//Min. value of RGB
    double var_Max; //Max. value of RGB
    if(var_B<=var_G&&var_B<=var_R) var_Min=var_B;
    if(var_G<=var_B&&var_G<=var_R) var_Min=var_G;
    if(var_R<=var_G&&var_R<=var_B) var_Min=var_R;
    if(var_B>=var_G&&var_B>=var_R) var_Max=var_B;
    if(var_G>=var_B&&var_G>=var_R) var_Max=var_G;
    if(var_R>=var_G&&var_R>=var_B) var_Max=var_R;
    double del_Max = var_Max - var_Min; //Delta RGB value
    double H; //HSL results from 0 to 1
    if ( del_Max == 0.0 ) //This is a gray, no chroma...
    {
        H = 0; //HSL results from 0 to 1

    }
    else //Chromatic data...
    {
        double del_R = ( ( ( var_Max - var_R ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        double del_G = ( ( ( var_Max - var_G ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        double del_B = ( ( ( var_Max - var_B ) / 6 ) + ( del_Max / 2 ) ) / del_Max;
        if ( var_R == var_Max ) H = del_B - del_G;
        else if ( var_G == var_Max ) H = ( 1 / 3.0 ) + del_R - del_B;
        else if ( var_B == var_Max ) H = ( 2 / 3.0 ) + del_G - del_R;
        if ( H < 0 ) H += 1;
        if ( H > 1 ) H -= 1;
    }
    return H;
}
double ImageProcessor::getS(const QRgb& rgb){
    int R=qRed(rgb);
    int G=qGreen(rgb);
    int B=qBlue(rgb);
    double var_R = ( R / 255.0 ); //RGB from 0 to 255
    double var_G = ( G / 255.0 );
    double var_B = ( B / 255.0 );
    double var_Min;//Min. value of RGB
    double var_Max; //Max. value of RGB
    if(var_B<=var_G&&var_B<=var_R) var_Min=var_B;
    if(var_G<=var_B&&var_G<=var_R) var_Min=var_G;
    if(var_R<=var_G&&var_R<=var_B) var_Min=var_R;
    if(var_B>=var_G&&var_B>=var_R) var_Max=var_B;
    if(var_G>=var_B&&var_G>=var_R) var_Max=var_G;
    if(var_R>=var_G&&var_R>=var_B) var_Max=var_R;
    double del_Max = var_Max - var_Min; //Delta RGB value
    double L = ( var_Max + var_Min ) / 2;
    double S;
    if ( del_Max == 0.0 ) //This is a gray, no chroma...
    {
        S = 0;
    }
    else //Chromatic data...
    {
        if ( L < 0.5 ) S = del_Max / ( var_Max + var_Min );
        else S = del_Max / ( 2 - var_Max - var_Min );
    }
    return S;
}
double ImageProcessor::Hue_2_RGB (double v1,double v2,double vH ) //Function Hue_2_RGB
{
if ( vH < 0 ) vH += 1;
if ( vH > 1 ) vH -= 1;
if ( ( 6 * vH ) < 1 ) return ( v1 + ( v2 - v1 ) * 6 * vH );
if ( ( 2 * vH ) < 1 ) return ( v2 );
if ( ( 3 * vH ) < 2 ) return ( v1 + ( v2 - v1 ) * ( ( 2.0 / 3.0 ) - vH ) * 6 );
return ( v1 );
}
QImage ImageProcessor::linearFilter(const QImage& img,vector<double> data,int nCol,int index){
    QImage ret(img);
    int w=ret.width();
    int h=ret.height();
    int nRow=data.size()/nCol;
    if(nRow%2==0||nCol%2==0){
        qDebug()<<"should be odd";
        return img;
    }
    QSize q(w+nCol-1,h+nRow-1);
    QImage ima(q,img.format());
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            ima.setPixel(i+nCol/2,j+nRow/2,img.pixel(i,j));
        }
    }
    //padding
    if(index==1){
        for(int i=nCol/2-1;i>=0;i--){
            for(int j=0;j<h;j++){
                ima.setPixel(i,j+nRow/2,img.pixel(0,j));
            }
        }
        for(int i=nCol/2+w;i<w+nCol-1;i++){
            for(int j=0;j<h;j++){
                ima.setPixel(i,j+nRow/2,img.pixel(w-1,j));
            }
        }
        for(int i=0;i<w+nCol-1;i++){
            for(int j=nRow/2-1;j>=0;j--){
                ima.setPixel(i,j,ima.pixel(i,nRow/2));
            }
        }
        for(int i=0;i<w+nCol-1;i++){
            for(int j=h+nRow/2-1;j<h+nRow-1;j++){
                ima.setPixel(i,j,ima.pixel(i,h+nRow/2-1));
            }
        }
    }
    if(index==2){
        int a=0;
        for(int i=nCol/2-1;i>=0;i--){
            for(int j=0;j<h;j++){
                ima.setPixel(i,j+nRow/2,img.pixel(a,j));
            }
            a++;
        }
        a=w-1;
        for(int i=nCol/2+w;i<w+nCol-1;i++){

            for(int j=0;j<h;j++){
                ima.setPixel(i,j+nRow/2,img.pixel(a,j));
            }
            a--;
        }

        for(int i=0;i<w+nCol-1;i++){
            a=nRow/2;
            for(int j=nRow/2-1;j>=0;j--){
                ima.setPixel(i,j,ima.pixel(i,a));
                a++;
            }

        }

        for(int i=0;i<w+nCol-1;i++){
            a=h+nRow/2-1;
            for(int j=h+nRow/2-1;j<h+nRow-1;j++){
                ima.setPixel(i,j,ima.pixel(i,a));
                a--;
            }

        }
    }
    //filter
    for(int i=nCol/2;i<w+nCol/2;i++){
        for(int j=nRow/2;j<h+nRow/2;j++){
            QRect rect(i-nCol/2,j-nRow/2,nCol,nRow);
            QImage patch=ima.copy(rect);
            double sum=0;
            for(int k=0;k<data.size();k++){
                sum+=data[k]*qGray(patch.pixel(k/nCol,k%nCol));
            }
            if(sum<0) sum=0;
            if(sum>255) sum=255;
            ret.setPixel(i-nCol/2,j-nRow/2,qRgb(sum,sum,sum));
        }
    }
    //crop
    return ret;
}
QImage ImageProcessor::linearFilter(const QImage& img,vector<double> data,int nCol,int index,int col){
    if(col==0){
        QImage ret(img);
        QImage ret1(img);
        QImage ret2(img);
        int w=ret.width();
        int h=ret.height();
        for(int i=0;i<w;++i){
            for(int j=0;j<h;++j){
                QRgb rgb=img.pixel(i,j);
                int red=qRed(rgb);
                int green=qGreen(rgb);
                int blue=qBlue(rgb);
                ret.setPixel(i,j,qRgb(red,red,red));
                ret1.setPixel(i,j,qRgb(green,green,green));
                ret2.setPixel(i,j,qRgb(blue,blue,blue));
            }
        }
        ret=linearFilter(ret,data,nCol,index);
        ret1=linearFilter(ret1,data,nCol,index);
        ret2=linearFilter(ret2,data,nCol,index);
        QImage retx(img);
        for(int i=0;i<w;++i){
            for(int j=0;j<h;++j){
                QRgb rgb=ret.pixel(i,j);
                QRgb rgb1=ret1.pixel(i,j);
                QRgb rgb2=ret2.pixel(i,j);
                int red=qRed(rgb);
                int green=qRed(rgb1);
                int blue=qRed(rgb2);
                retx.setPixel(i,j,qRgb(red,green,blue));
            }
        }
        return retx;
    }
    if(col==1){
        return linearFilter(img,data,nCol,index);
    }
}
QImage ImageProcessor::gaussFilter(const QImage& img,int size,double sigma)
{
    QImage ret(img);
    vector<double> data;
    int c=size/2;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            int deltax=abs(i-c);
            int deltay=abs(j-c);
            double res=exp(-(   deltax*deltax/(2.0*sigma*sigma)+deltay*deltay/(2.0*sigma*sigma) ));
            data.push_back(res);
        }

    }
    double sum = 0;
    for(int i=0;i<data.size();++i)
        sum+=data[i];
    for(int i=0;i<data.size();++i)
            data[i]=data[i]/sum;
    ret=linearFilter(img,data,size,0,0);
    return ret;
}
QImage ImageProcessor::bilateralFilter(const QImage& img,int size,double sigmas,double sigmac)
{
    if(size%2==0)
    {
        qDebug()<<"nCol and nRow should be odd";
        return img;
    }
    QImage ret(img);
    int w = img.width();
    int h = img.height();
    //算Gauss
    vector<double> data;
    int c=size/2;
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            int deltax=abs(i-c);
            int deltay=abs(j-c);
            double res=exp(-(   deltax*deltax/(2.0*sigmas*sigmas)+deltay*deltay/(2.0*sigmas*sigmas) ));
            data.push_back(res);
        }
    }

    //存平方
    vector<double> num2;
    for(int i=0;i<255;i++)
    {
        double res=(i*i)/(2.0*sigmac*sigmac);
        num2.push_back(res);
    }

    for(int i=0;i<w;++i)
    {
        for(int j=0;j<h;++j)
        {
            QRect rect(i-size/2,j-size/2,size,size);
            QImage patch = img.copy(rect);
            vector<double> data1=data;

            double sum0=0;
            int deltagray;
            int deltagrayc=qGray(img.pixel(i,j));
            for(int k=0;k<data.size();++k)
            {
                deltagray=qGray(patch.pixel(k/size,k%size));
                double res=exp(-(num2[abs(deltagray-deltagrayc)]));
                data1[k] = data1[k]*res;
                sum0+=data1[k];
            }
            for(int k=0;k<data.size();++k)
            {
                data1[k] = data1[k]/sum0;
            }

            //filter
            double sum=0;
            for(int k=0;k<data.size();++k)
            {
                sum += data1[k]*qGray(patch.pixel(k/size,k%size));
            }
            if(sum<=0)  sum=0;
            if(sum>=255)    sum=255;
            ret.setPixel(i,j,qRgb(sum,sum,sum));
        }
    }
    //crop
    //.......
    return ret;
}
QImage ImageProcessor::midFilter(const QImage& img,int size){
    if(size%2==0)
    {
        qDebug()<<"nCol and nRow should be odd";
        return img;
    }
    QImage ret(img);
    int w = img.width();
    int h = img.height();
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRect rect(i-size/2,j-size/2,size,size);
            QImage patch = img.copy(rect);
            vector<int> data;
            for(int k1=0;k1<size;k1++){
                for(int k2=0;k2<size;k2++){
                    data.push_back(qGray(patch.pixel(k1,k2)));
                }
            }
            std::sort(data.begin(),data.end());
            ret.setPixel(i,j,qRgb(data[size*size/2],data[size*size/2],data[size*size/2]));
        }
    }
    return ret;
}
QImage ImageProcessor::morFilter(const QImage& img,int size,int kind){
    if(size%2==0)
    {
        qDebug()<<"nCol and nRow should be odd";
        return img;
    }
    QImage ret(img);
    int w = img.width();
    int h = img.height();
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            QRect rect(i-size/2,j-size/2,size,size);
            QImage patch = img.copy(rect);
            vector<int> data;
            for(int k1=0;k1<size;k1++){
                for(int k2=0;k2<size;k2++){
                    data.push_back(qGray(patch.pixel(k1,k2)));
                }
            }
            std::sort(data.begin(),data.end());
            if(kind==1) ret.setPixel(i,j,qRgb(data[size*size-1],data[size*size-1],data[size*size-1]));
            if(kind==0) ret.setPixel(i,j,qRgb(data[0],data[0],data[0]));
        }
    }
    return ret;
}
