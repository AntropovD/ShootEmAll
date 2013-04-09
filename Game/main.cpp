#include <QApplication>
#include "window.h"

int main(int argc, char **argv)
 {
     QApplication app(argc, argv);

     QDir::setCurrent(app.applicationDirPath());
             app.setLibraryPaths(QStringList() << (QDir::currentPath() + "/plugins") << app.libraryPaths());
     Window window;
     window.show(); 
     return app.exec();
}


