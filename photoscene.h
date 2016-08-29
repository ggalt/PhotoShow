#ifndef PHOTOSCENE_H
#define PHOTOSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

#include <QString>
#include <QStringList>

#include <QImage>
#include <QImageReader>
#include <QPixmap>
#include <QRect>
#include <QPoint>

#include <QTimer>

#include <QDebug>

class PhotoScene : public QGraphicsScene
{
    Q_OBJECT
public:
    PhotoScene();

public slots:
    void DrawScene(void);

private slots:
    void NextImage(void);

private:
    void ReadURLs(void);
    QString SelectImage(void);

private:
    QStringList photoUrlList;
    int imageCount;
    QTimer t;

    QRect scRect;
    QPixmap foreground;
    QPixmap background;
    QPoint foregroundOffset;
};

#endif // PHOTOSCENE_H
