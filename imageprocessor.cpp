#include "imageprocessor.h"
#include <QHBoxLayout>
#include <QMenuBar>
#include <QFileDialog>
#include <QDebug>
#include <QLabel>
#include <QToolBar>
#include <QAction>
#include <QPixmap>
#include <QImage>
#include <QColor>
#include <cstdio>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("影像處理"));
    central = new QWidget();
    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    imgWin = new QLabel();
    QPixmap *initPixmap = new QPixmap(300, 200);
    initPixmap->fill(QColor(255, 255, 255));
    imgWin->resize(300, 200);
    imgWin->setScaledContents(true);
    imgWin->setPixmap(*initPixmap);
    mainLayout->addWidget(imgWin);
    setCentralWidget(central);
    createActions();
    createMenus();
    createToolBars();
}


ImageProcessor::~ImageProcessor()
{
}

void ImageProcessor::createActions()
{
    openFileAction = new QAction(QStringLiteral("開啟檔案&O"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));
    openFileAction->setStatusTip(QStringLiteral("開啟影像檔案"));
    connect(openFileAction, SIGNAL(triggered()), this, SLOT(showOpenFile()));

    exitAction = new QAction(QStringLiteral("結束&Q"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(QStringLiteral("退出程式"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    zoomInAction = new QAction(QStringLiteral("放大"), this);
    zoomInAction->setShortcut(tr("Ctrl+U"));
    zoomInAction->setStatusTip(QStringLiteral("放大影像"));
    connect(zoomInAction, SIGNAL(triggered()), this, SLOT(zoomIn()));


    zoomOutAction = new QAction(QStringLiteral("縮小"), this);
    zoomOutAction->setShortcut(tr("Ctrl+Y"));
    zoomOutAction->setStatusTip(QStringLiteral("縮小影像"));
    connect(zoomOutAction, SIGNAL(triggered()), this, SLOT(zoomOut()));

}


void ImageProcessor::createMenus()
{
    fileMenu = menuBar()->addMenu(QStringLiteral("檔案&F"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(exitAction);

    QMenu *toolsMenu = menuBar()->addMenu(QStringLiteral("工具&T"));
    toolsMenu->addAction(zoomInAction);
    toolsMenu->addAction(zoomOutAction);


}

void ImageProcessor::createToolBars()
{
    fileTool = addToolBar("file");
    fileTool->addAction(openFileAction);
    fileTool->addAction(zoomInAction);
    fileTool->addAction(zoomOutAction);

}

void ImageProcessor::loadFile(QString filename)
{
    qDebug() << QString("file name:%1").arg(filename);
    QByteArray ba = filename.toLatin1();
    printf("FN:%s\n", (char *)ba.data());

    originImg.load(filename);
    img = originImg;        // 你原本用的 img 也同步一下
    scaleFactor = 1.0;      // 每次開新圖先回到 1 倍

    updateImageView();
}


void ImageProcessor::showOpenFile()
{
    filename = QFileDialog::getOpenFileName(this,
                                            QStringLiteral("開啟影像"),
                                            tr("."),
                                            "bmp (*.bmp);;png (*.png)"
                                            ";;jpeg (*.jpg)");

    if (!filename.isEmpty())
    {
        if (img.isNull())
        {
            loadFile(filename);
        }
        else
        {
            ImageProcessor *newIPWin = new ImageProcessor();
            newIPWin->show();
            newIPWin->loadFile(filename);
        }
    }

}
void ImageProcessor::zoomIn()
{
    if (originImg.isNull()) return;

    scaleFactor *= 1.25;
    if (scaleFactor > 5.0) scaleFactor = 5.0;
    updateImageView();
}

void ImageProcessor::zoomOut()
{
    if (originImg.isNull()) return;

    scaleFactor /= 1.25;
    if (scaleFactor < 0.2) scaleFactor = 0.2;
    updateImageView();
}
void ImageProcessor::updateImageView()
{
    if (originImg.isNull()) return;

    int w = int(originImg.width()  * scaleFactor);
    int h = int(originImg.height() * scaleFactor);

    QImage scaled = originImg.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    imgWin->setPixmap(QPixmap::fromImage(scaled));
}
