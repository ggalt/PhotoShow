#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{

}

void MainWindow::init(void)
{
//    this->showFullScreen();
    QRect r = this->geometry();
    gView = new QGraphicsView(this);
    gView->setGeometry(r);
    gView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    pScene = new PhotoScene();
    pScene->Init();
    gView->setScene(pScene);
}

void MainWindow::mouseDoubleClickEvent( QMouseEvent *me )
{
//    myChooserDialog = new chooserDialog(this, isFullScreen);
//    connect(myChooserDialog,SIGNAL(OpenOptions()),
//            this,SLOT(loadSettingsDialog()));

//    connect(myChooserDialog,SIGNAL(ExitProgram()),
//            this,SLOT(close()));
//    connect(myChooserDialog,SIGNAL(SwitchScreen(bool)),
//            this,SLOT(ToggleFullScreen(bool)));
//    myChooserDialog->show();

    if( this->isFullScreen() ) {
        this->showNormal();
    } else {
        this->showFullScreen();
    }
    return QWidget::mouseDoubleClickEvent(me);
}

void MainWindow::resizeEvent(QResizeEvent *event )
{
    QMainWindow::resizeEvent(event);
    QRect r(0,0,this->width(),this->height());
    gView->setGeometry(r);
}
