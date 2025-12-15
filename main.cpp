#include <QApplication>
#include "qt_imageprocessor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qt_imageprocessor w;
    w.show();
    return a.exec();
}

