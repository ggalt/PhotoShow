#ifndef PHOTOSCENE_H
#define PHOTOSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsBlurEffect>

#include <QString>
#include <QStringList>

#include <QImage>
#include <QImageReader>
#include <QPixmap>
#include <QRect>
#include <QPoint>

#include <QTimer>
#include <QPropertyAnimation>
#include <QEasingCurve>

#include <QDebug>

#include "myintobject.h"

typedef enum {
    BlurIn,
    BlurHold,
    BlurOut } BlurState;

class PhotoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PhotoScene();
    void Init(void);

public slots:
    void DrawScene(void);

private slots:
    void NextImage(void);
    void AnimateBlur(void);

private:
    void ReadURLs(void);
    QString SelectImage(void);

private:
    QStringList photoUrlList;
    int imageCount;
    QTimer displayTimer;
    QTimer animateTimer;

    QRect scRect;
    quint32 wideScreen;
    quint32 wideImage;
    QPixmap foreground;
    QPixmap background;
    QPoint foregroundOffset;
    QPropertyAnimation *foregroundBlur;
    QPropertyAnimation *backgroundBlur;

    myIntObject foreInt;
    myIntObject backInt;

//    QGraphicsBlurEffect *foreBlur;
//    QGraphicsBlurEffect *backBlur;


    BlurState blurState;
    int blurDuration;
    int blurOutVal;
    int blurBackgroundVal;
    int holdLength;
    int holdCounter;
    int blurJump;
};

#endif // PHOTOSCENE_H
