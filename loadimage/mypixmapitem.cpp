#include "mypixmapitem.h"
#include <QDebug>
MyPixmapItem::MyPixmapItem(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{

}
void MyPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("1");
}
void MyPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug("2");
    setPos(pos()+mapToParent(event->pos())-mapToParent(event->lastPos()));
}
void MyPixmapItem::wheelEvent(QGraphicsSceneWheelEvent *event)
{

    double s=scale();
    s=s*(1+double(event->delta())/1200);
    if(s<0.1) s=0.1;
    if(s>10) s=10;
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(s);
    //qDebug()<<s;
}
void MyPixmapItem::reset()
{
    setPos(0,0);
    setScale(1.0);
}
