#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H

#include <QVideoWidget>
#include <QMouseEvent>

class MyVideoWidget : public QVideoWidget
{
public:
   MyVideoWidget(QWidget *parent = NULL);
   virtual ~MyVideoWidget();


protected:
   void mouseDoubleClickEvent(QMouseEvent *event) override;
   void keyPressEvent(QKeyEvent * event) override;
};

#endif // MYVIDEOWIDGET_H
