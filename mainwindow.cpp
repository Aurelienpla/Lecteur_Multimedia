#include "mainwindow.h"
#include "myvideowidget.h"

void MainWindow::initIHM()
{
   setCentralWidget(new QWidget());

   mPbPlay = new QPushButton("Lecture");
   mPbPause = new QPushButton("Pause");
   mPbStop = new QPushButton("Stop");
   mPbPrev = new QPushButton("Précédent");
   mPbNext = new QPushButton("Suivant");
   mPbPlus = new QPushButton("+");
   mPbMinus = new QPushButton("-");

   mVideoFrame = new MyVideoWidget();
   mVideoFrame->setMinimumSize(200,200);

   //mSliderTime = new QSlider(Qt::Horizontal);
   mSliderTime = new SliderTime();

   mLbElapseTime = new QLabel("0:00");
   mLbTotalTime = new QLabel();
   mLbVolume = new QLabel("Volume : ");
   mLbPourcentage = new QLabel("50 %");
   mLbPlayList = new QLabel("Liste Lecture :");

   mDialVolume = new QDial();
   mDialVolume->setFixedSize(100,100);
   mDialVolume->setMinimum(0);
   mDialVolume->setMaximum(100);
   mDialVolume->setValue(50);

   mListPlaylist = new QListWidget();
   //mListPlaylist->setFixedWidth(100);

   mHorizontalLine = new QFrame();
   mHorizontalLine->setGeometry(QRect(160, 150, 3, 61));
   mHorizontalLine->setFrameShape(QFrame::VLine);
   mHorizontalLine->setFrameShadow(QFrame::Sunken);

   mSpacerPlusMinus = new QSpacerItem(10,10);
   mSpacerVolume = new QSpacerItem(10,10);

   QHBoxLayout * principalLayout = new QHBoxLayout(centralWidget());

   QHBoxLayout * layoutBouton = new QHBoxLayout();
   layoutBouton->addWidget(mPbPlay);
   layoutBouton->addWidget(mPbPause);
   layoutBouton->addWidget(mPbStop);
   layoutBouton->addWidget(mPbPrev);
   layoutBouton->addWidget(mPbNext);

   QHBoxLayout * layoutTime = new QHBoxLayout();
   layoutTime->addWidget(mLbElapseTime);
   layoutTime->addWidget(mSliderTime);
   layoutTime->addWidget(mLbTotalTime);

   QVBoxLayout * layoutLeftVideo = new QVBoxLayout();
   layoutLeftVideo->addWidget(mVideoFrame);
   layoutLeftVideo->addLayout(layoutTime);
   layoutLeftVideo->addLayout(layoutBouton);

   QHBoxLayout * layoutPlusMinusBt = new QHBoxLayout();
   //layoutPlusMinusBt->addWidget(mSpacerPlusMinus);
   layoutPlusMinusBt->addWidget(mPbPlus);
   layoutPlusMinusBt->addWidget(mPbMinus);

   QHBoxLayout * layoutVolume = new QHBoxLayout();
   layoutVolume->addWidget(mLbVolume);
   layoutVolume->addWidget(mDialVolume);
   layoutVolume->addWidget(mLbPourcentage);

   QVBoxLayout * layoutRightPlaylist = new QVBoxLayout();
   layoutRightPlaylist->addWidget(mLbPlayList);
   layoutRightPlaylist->addWidget(mListPlaylist);
   layoutRightPlaylist->addLayout(layoutPlusMinusBt);
   layoutRightPlaylist->addLayout(layoutVolume);

   principalLayout->addLayout(layoutLeftVideo);
   principalLayout->addWidget(mHorizontalLine);
   principalLayout->addLayout(layoutRightPlaylist);
}

void MainWindow::connections()
{
   //connection des boutons du lecteur
   connect(mPbPlay,SIGNAL(clicked(bool)),mPlayer, SLOT(play()));
   connect(mPbPause,SIGNAL(clicked(bool)),mPlayer, SLOT(pause()));
   //connect(mPbStop,SIGNAL(clicked(bool)),mPlayer, SLOT(stop()));
   connect(mPbStop,SIGNAL(clicked(bool)),this, SLOT(onPbStopClicked()));
   connect(mPbNext,SIGNAL(clicked(bool)),this, SLOT(onNextPbClicked()));
   connect(mPbPrev,SIGNAL(clicked(bool)),this, SLOT(onPrevPbClicked()));
   connect(mPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onPlayerPositionChanged(qint64)));
   connect(mSliderTime,SIGNAL(sliderMoved(int)),this,SLOT(onSliderPositionChanged(int)));

   //connection du changement de valeur du dial au volume du player
   connect(mDialVolume,SIGNAL(valueChanged(int)),this,SLOT(onDialChanged(int)));

   //connection du bouton plus
   connect(mPbPlus,SIGNAL(clicked(bool)),this,SLOT(onPlusPbClicked()));
   connect(mPbMinus,SIGNAL(clicked(bool)),this,SLOT(onMinusPbClicked()));

   connect(mListPlaylist,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onPlaylistItemDoubleClicked(QListWidgetItem*)));

   connect(mVideoFrame,SIGNAL(fullScreenChanged(bool)),this,SLOT(onFullScreenChanged(bool)));
}

void MainWindow::playerSetup()
{
   mPlayer = new QMediaPlayer();
   connect(mPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(onVideoLoaded(qint64)));
   mPlayer->setMedia(QUrl::fromLocalFile("/home/aurelien/Documents/Qt/TP3/game-of-thrones.mkv"));
   mPlayer->setVideoOutput(mVideoFrame);
   mPlayer->setVolume(mDialVolume->value());
   mVideoFrame->show();
}


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
{
   initIHM();
   playerSetup();
   connections();
}

MainWindow::~MainWindow()
{

}

void MainWindow::onPbStopClicked()
{
   mPlayer->setPosition(0);
   mPlayer->stop();
}

void MainWindow::onPrevPbClicked()
{
   int currentRow = mListPlaylist->currentRow();
   if(currentRow > 0){
      int prevRow = currentRow - 1;
      mListPlaylist->setCurrentRow(prevRow);
      mListPlaylist->setCurrentItem(mListPlaylist->item(prevRow));
      QListWidgetItem * item = mListPlaylist->currentItem();
      QVariant fileName = item->data(3);
      mPlayer->setMedia(QUrl::fromLocalFile(fileName.toString()));
      mPlayer->play();
   }
}

void MainWindow::onNextPbClicked()
{
   int currentRow = mListPlaylist->currentRow();
   if(currentRow < mListPlaylist->count() - 1){
      int nextRow = currentRow + 1;
      mListPlaylist->setCurrentRow(nextRow);
      mListPlaylist->setCurrentItem(mListPlaylist->item(nextRow));
      QListWidgetItem * item = mListPlaylist->currentItem();
      QVariant fileName = item->data(3);
      mPlayer->setMedia(QUrl::fromLocalFile(fileName.toString()));
      mPlayer->play();
   }
}

void MainWindow::onPlaylistItemDoubleClicked(QListWidgetItem * item)
{
   QVariant fileName = item->data(3);
   mPlayer->setMedia(QUrl::fromLocalFile(fileName.toString()));
   mPlayer->play();
}

void MainWindow::onMinusPbClicked()
{
   QListWidgetItem * item = mListPlaylist->takeItem(mListPlaylist->currentRow());
   delete item;
}

void MainWindow::onPlusPbClicked()
{
   QString fileName = QFileDialog::getOpenFileName();
   QFileInfo fileInfo(fileName);
   QString shortName = fileInfo.baseName();
   QListWidgetItem * item = new QListWidgetItem();
   item->setText(shortName);
   item->setData(3,fileName);
   mListPlaylist->addItem(item);
}

void MainWindow::onDialChanged(int dialVal)
{
   QString dialPourcent;
   dialPourcent+=QString::number(dialVal);
   dialPourcent+=" %";
   mLbPourcentage->setText(dialPourcent);
   mPlayer->setVolume(dialVal);
}

void MainWindow::onPlayerPositionChanged(qint64 mediaPos)
{
   disconnect(mSliderTime,SIGNAL(valueChanged(int)),this,SLOT(onSliderPositionChanged(int)));

   QTime time(0,0,0);
   time = time.addMSecs(mediaPos);
   QString sPosition = time.toString("hh:mm:ss");
   mLbElapseTime->setText(sPosition);
   mSliderTime->setValue(mediaPos);

   connect(mSliderTime,SIGNAL(valueChanged(int)),this,SLOT(onSliderPositionChanged(int)));
}

void MainWindow::onSliderPositionChanged(int sliderPos)
{
   mPlayer->setPosition(sliderPos);
}

void MainWindow::onPositionChangedByTimer()
{
   qint64 mediaPosition = mPlayer->position();
   QTime time(0,0,0);
   time = time.addMSecs(mediaPosition);
   QString sPosition = time.toString("hh:mm:ss");
   mLbElapseTime->setText(sPosition);
   mSliderTime->setValue(mPlayer->position());
}

void MainWindow::onVideoLoaded(qint64 duree)
{
   mSliderTime->setMaximum(duree);
   QTime time(0,0,0);
   time = time.addMSecs(duree);
   QString sTime = time.toString("hh:mm:ss");
   mLbTotalTime->setText(sTime);
}

void MainWindow::onFullScreenChanged(bool isFull)
{
  if (isFull == false){
   mPlayer->setMedia(QUrl::fromLocalFile("/home/aurelien/Documents/Qt/TP3/game-of-thrones.mkv"));
   mPlayer->setVideoOutput(mVideoFrame);
  }
}
