#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include<QImage>
#include<vector>
class ImageProcessor
{
public:
    ImageProcessor();
    static QImage rgb2gray(const QImage& img);
    static QImage logTransformation(const QImage& img,double c);
    static QImage contrast(const QImage& img);
    static QImage strething(const QImage& img,double E,double m);
    static QImage average(const QImage& img);
    static QImage rgbaverage(const QImage& img);
    static QRgb rgb2hsi(const QRgb& rgb);
    static QRgb hsi2rgb(double, double, double);
    static int getInt(const QRgb& rgb);
    static double getH(const QRgb& rgb);
    static double getS(const QRgb& rgb);
    static double Hue_2_RGB( double, double, double );
    static QImage linearFilter(const QImage&,std::vector<double>,int,int,int);
    static QImage linearFilter(const QImage&,std::vector<double>,int,int);
    static QImage gaussFilter(const QImage& img,int size,double sigma);
    static QImage bilateralFilter(const QImage& img,int size,double sigmas,double sigmac);
    static QImage midFilter(const QImage& img,int size);
    static QImage morFilter(const QImage& img,int size,int kind);
};

#endif // IMAGEPROCESSOR_H
