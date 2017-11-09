#include "myvideowidget.h"

MyVideoWidget::MyVideoWidget(QWidget * parent) : QVideoWidget(parent)
{

}

MyVideoWidget::~MyVideoWidget()
{

}

void MyVideoWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
   if(event->button() == Qt::LeftButton){
      setFullScreen(!isFullScreen());
      event->accept();
   }
}

void MyVideoWidget::keyPressEvent(QKeyEvent * event)
{
   if(event->key() == Qt::Key_Escape){
      setFullScreen(false);
      event->accept();
   }
}
