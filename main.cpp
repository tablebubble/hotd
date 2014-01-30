#include<QApplication>
#if defined(Q_OS_LINUX)
	#include <unistd.h>
#else 
	#include <windows.h>
#endif
#include "hod.h"

int main(int argc, char *argv[]){
	QApplication app(argc,argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/bootsplash.png"));
    splash->show();
	Hod mains;
        // sleep for 5 secs
    for(int i = 0; i < 3; i++){
        app.processEvents();
	#if defined(Q_OS_WIN32)
        Sleep(100); //thanks to windows.h
	#else 
		sleep(1);
	#endif
    }
	mains.show();
    splash->finish(&mains);
	return app.exec();
}
