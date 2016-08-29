#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QApplication>
#include <QDesktopWidget>

#include <QMouseEvent>
#include <QResizeEvent>

#include "photoscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void init(void);

private:
    void mouseDoubleClickEvent( QMouseEvent *);
    void resizeEvent( QResizeEvent *);

private:
    QGraphicsView *gView;
    PhotoScene *pScene;
};

#endif // MAINWINDOW_H
