#include "qt_imageprocessor.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt_ImageProcessor w;
    w.show();
    return a.exec();
}
