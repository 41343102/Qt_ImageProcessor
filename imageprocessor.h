#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QImage>
#include <QLabel>



class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = 0);
    ~ImageProcessor();
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();
    void updateImageView();


private:
    QWidget  *central;
    QMenu    *fileMenu;
    QToolBar *fileTool;
    QImage    img;
    QString   filename;
    QLabel   *imgWin;
    QAction  *openFileAction;
    QAction  *exitAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    double scaleFactor = 1.0;     // 縮放倍率
    QImage  originImg;            // 保留原圖，避免越放越糊



};
#endif // IMAGEPROCESSOR_H
