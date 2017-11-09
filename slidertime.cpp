#include "slidertime.h"

SliderTime::SliderTime(QWidget * parent): QSlider(Qt::Horizontal,parent)
{
}

SliderTime::~SliderTime()
{

}

void SliderTime::mousePressEvent(QMouseEvent * mouseEvent)
{
//   int mousePosX = mouseEvent->x();
   if(mouseEvent->button() == Qt::LeftButton){
      setValue(minimum() + ((maximum()-minimum()) * mouseEvent->x()) / width() );
      mouseEvent->accept();
   }
   QSlider::mousePressEvent(mouseEvent);
}
