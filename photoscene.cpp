#include "photoscene.h"

PhotoScene::PhotoScene()
{
    ReadURLs();
    connect(&t, SIGNAL(timeout()),
            this, SLOT(NextImage()));

    NextImage();
    t.setInterval(5000);
    t.start();
}

void PhotoScene::DrawScene(void)
{
    this->clear();
    QGraphicsPixmapItem backgroundImage;
    QGraphicsPixmapItem foregroundImage;
    backgroundImage.setPixmap(background);
    foregroundImage.setPixmap(foreground);
//    foregroundImage.setOffset(foregroundOffset);
    this->addItem(&backgroundImage);
    this->addItem(&foregroundImage);
    this->addPixmap(foreground);
    qDebug() << "offset:" << foregroundOffset;
    qDebug() << "foregroundImageSize:" << foreground.size();
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
//      this->setSceneRect(0,0,sceneWindow.width(), sceneWindow.height());
    }

    background = p.scaledToWidth(scRect.width());
    foreground = p.scaledToHeight(scRect.height());
    foregroundOffset = QPoint((scRect.width() - foreground.width())/2, (scRect.height() - foreground.height())/2);
    DrawScene();
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
