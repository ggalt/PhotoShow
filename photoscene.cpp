#include "photoscene.h"

PhotoScene::PhotoScene()
{
}

void PhotoScene::Init( void )
{
    blurState = BlurIn;
    blurDuration = 2000;
    blurOutVal = 300;
    blurBackgroundVal = 75;

    holdLength = 150;
    holdCounter = 0;
    foregroundBlur = new QPropertyAnimation(&foreInt, "blurVal");
    backgroundBlur = new QPropertyAnimation(&backInt, "blurVal");
    foregroundBlur->setStartValue( blurOutVal );
    foregroundBlur->setEndValue(0);
    foregroundBlur->setDuration(blurDuration);
    foregroundBlur->setEasingCurve(QEasingCurve::OutCubic);
    foregroundBlur->setLoopCount(1);
    backgroundBlur->setStartValue( blurOutVal );
    backgroundBlur->setEndValue(blurBackgroundVal);
    backgroundBlur->setDuration(blurDuration);
    backgroundBlur->setEasingCurve(QEasingCurve::OutCubic);
    backgroundBlur->setLoopCount(1);

    blurJump = 50;

    ReadURLs();
    connect(&displayTimer, SIGNAL(timeout()),
            this, SLOT(AnimateBlur()));
    connect(&animateTimer, SIGNAL(timeout()),
            this, SLOT(AnimateBlur()));

    NextImage();
    displayTimer.setInterval(5000);
    animateTimer.setInterval(20);
//    displayTimer.start();
    foregroundBlur->start();
    backgroundBlur->start();
    animateTimer.start();
}

void PhotoScene::DrawScene(void)
{
    this->clear();
    QGraphicsPixmapItem *backgroundImage = addPixmap(background);
    QGraphicsPixmapItem *foregroundImage = addPixmap(foreground);

    QGraphicsBlurEffect *foreBlur;
    QGraphicsBlurEffect *backBlur;
    foreBlur = new QGraphicsBlurEffect();
    backBlur = new QGraphicsBlurEffect();

    if( foreBlur != NULL && backBlur != NULL ){
        foreBlur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);
        backBlur->setBlurHints(QGraphicsBlurEffect::PerformanceHint);

        backBlur->setBlurRadius(backgroundBlur->currentValue().toInt());
        foreBlur->setBlurRadius(foregroundBlur->currentValue().toInt());
        backgroundImage->setGraphicsEffect(backBlur);
        foregroundImage->setGraphicsEffect(foreBlur);
        foregroundImage->setOffset(foregroundOffset);
    }
    this->update();
}

void PhotoScene::NextImage(void)
{
    QImageReader reader;

    #if QT_VERSION < QT_VERSION_CHECK(5, 4, 0)
    reader.autoDetectImageFormat();
    #else
    reader.setAutoTransform(true);
    #endif

    reader.setFileName(SelectImage());

    QPixmap p(QPixmap::fromImage(reader.read()));
    if(this->views().count() > 0) {
      scRect = this->views()[0]->geometry();
      wideScreen = ( scRect.width() * 1000 ) / scRect.height();
    }
    wideImage = ( p.width() * 1000 ) / p.height();

    if( wideScreen > wideImage ) {
        background = p.scaledToWidth(scRect.width());
        foreground = p.scaledToHeight(scRect.height());
    } else {
        background = p.scaledToHeight(scRect.height());
        foreground = p.scaledToWidth(scRect.width());
    }
    foregroundOffset = QPoint((scRect.width() - foreground.width())/2, (scRect.height() - foreground.height())/2);
    blurState = BlurIn;

//    foreBlur = new QGraphicsBlurEffect();
//    backBlur = new QGraphicsBlurEffect();

//    DrawScene();
}

QString PhotoScene::SelectImage(void)
{
    return photoUrlList.at(qrand() % photoUrlList.count());
}

void PhotoScene::ReadURLs(void)
{
    photoUrlList.clear();
#ifdef Q_OS_LINUX
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0004.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0686-1.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0712-1.JPG");
    photoUrlList.append("/home/ggalt/Pictures/DesktopImages/DSC_0796-1.JPG");

//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0430.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2006-Summer/IMG_0431.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0611.JPG");
//    photoUrlList.append("/home/ggalt/Pictures/2015/Hawaii and California/DSC_0633.JPG");
#else
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0682");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0759");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_1656");
    photoUrlList.append("C:/Users/ggalt66/Pictures/Desktop Images/DSC_0738");
#endif

}

void PhotoScene::AnimateBlur( void )
{
//    qDebug() << "animate" << foregroundBlur->currentValue().toInt();
    switch(blurState) {
        case BlurIn:
            if( foregroundBlur->currentValue().toInt() <= 0 ) {
                animateTimer.stop();
                blurState = BlurHold;
                displayTimer.start();
            }
            break;

        case BlurHold:
//            qDebug() << "holding";
            blurState = BlurOut;
            displayTimer.stop();
            foregroundBlur->setStartValue(0);
            foregroundBlur->setEndValue(blurOutVal);
            foregroundBlur->setDuration(blurDuration);
            foregroundBlur->setEasingCurve(QEasingCurve::InCubic);
            foregroundBlur->setLoopCount(1);
            backgroundBlur->setStartValue(blurBackgroundVal);
            backgroundBlur->setEndValue(blurOutVal);
            backgroundBlur->setDuration(blurDuration);
            backgroundBlur->setEasingCurve(QEasingCurve::InCubic);
            backgroundBlur->setLoopCount(1);
            foregroundBlur->start();
            backgroundBlur->start();
            animateTimer.start();
        break;

        case BlurOut:
            if( foregroundBlur->currentValue().toInt() >= blurOutVal ) {
                NextImage();
                blurState = BlurIn;
                foregroundBlur->setStartValue( blurOutVal );
                foregroundBlur->setEndValue(0);
                foregroundBlur->setDuration(blurDuration);
                foregroundBlur->setEasingCurve(QEasingCurve::OutCubic);
                foregroundBlur->setLoopCount(1);
                backgroundBlur->setStartValue( blurOutVal );
                backgroundBlur->setEndValue(blurBackgroundVal);
                backgroundBlur->setDuration(blurDuration);
                backgroundBlur->setEasingCurve(QEasingCurve::OutCubic);
                backgroundBlur->setLoopCount(1);
                foregroundBlur->start();
                backgroundBlur->start();
            }

        break;
    }

    DrawScene();
}
