#ifndef QT_IMAGEPROCESSOR_H
#define QT_IMAGEPROCESSOR_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QImage>
#include <QLabel>
#include <QString>

class qt_imageprocessor : public QMainWindow
{
    Q_OBJECT

public:
    explicit qt_imageprocessor(QWidget *parent = nullptr);
    ~qt_imageprocessor();

private slots:
    void showOpenFile();
    void zoomIn();
    void zoomOut();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void loadFile(QString filename);
    void updateImageView();

    QWidget  *central;
    QMenu    *fileMenu;
    QToolBar *fileTool;

    QLabel   *imgWin;
    QImage    img;
    QImage    originImg;
    QString   filename;

    QAction  *openFileAction;
    QAction  *exitAction;
    QAction  *zoomInAction;
    QAction  *zoomOutAction;

    double scaleFactor = 1.0;
};

#endif // QT_IMAGEPROCESSOR_H
