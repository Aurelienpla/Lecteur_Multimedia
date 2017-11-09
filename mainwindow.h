#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QTime>
#include <QTimer>
#include "slidertime.h"

class MainWindow : public QMainWindow
{

   Q_OBJECT

private:
   //PushButtons
   QPushButton * mPbPlay;
   QPushButton * mPbPause;
   QPushButton * mPbStop;
   QPushButton * mPbPrev;
   QPushButton * mPbNext;
   QPushButton * mPbPlus;
   QPushButton * mPbMinus;

   QVideoWidget * mVideoFrame;

   //QSlider * mSliderTime;
   SliderTime * mSliderTime;

   QLabel * mLbElapseTime;
   QLabel * mLbTotalTime;
   QLabel * mLbVolume;
   QLabel * mLbPourcentage;
   QLabel * mLbPlayList;

   QDial * mDialVolume;

   QListWidget * mListPlaylist;

   QFrame * mHorizontalLine;

   QSpacerItem * mSpacerPlusMinus;
   QSpacerItem * mSpacerVolume;

   QMediaPlayer * mPlayer;

   QTimer * mTimer;

   void initIHM();
   void connections();
   void playerSetup();

public:
   MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void onPbStopClicked();
   void onPrevPbClicked();
   void onNextPbClicked();
   void onPlaylistItemDoubleClicked(QListWidgetItem * item);
   void onMinusPbClicked();
   void onPlusPbClicked();
   void onDialChanged(int dialVal);
   void onPlayerPositionChanged(qint64 mediaPos);
   void onSliderPositionChanged(int sliderPos);
   void onPositionChangedByTimer();
   void onVideoLoaded(qint64 duree);
   void onFullScreenChanged(bool isFull);
};

#endif // MAINWINDOW_H
