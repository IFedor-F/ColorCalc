#include <QApplication>
#include <QStyleFactory.h>

#include "MainWindow.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    qApp->setStyle(QStyleFactory::create("Fusion"));
    QApplication::setWindowIcon(QIcon(":/resources/icon.png"));
    window.show();
    return QApplication::exec();
}
