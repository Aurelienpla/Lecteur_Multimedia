#ifndef SLIDERTIME_H
#define SLIDERTIME_H

#include <QSlider>
#include <QMouseEvent>

class SliderTime : public QSlider
{
public:
   SliderTime(QWidget *parent = NULL);
   virtual ~SliderTime();

protected:
   void mousePressEvent(QMouseEvent * mEvent) override;
};

#endif // SLIDERTIME_H
