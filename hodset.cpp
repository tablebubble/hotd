#include<QtGui>
#include<QApplication>
#include "hodset.h"

hodSetting::hodSetting(QWidget *parent)
 : QDialog(parent)
{
	setWindowTitle("Hadith of the Day Options");
        setFixedSize(280, 84);
	xstartUp = new QCheckBox("Load When windows starts");
	readSetting();
	saveButton = new QPushButton("  Ok\nInsha'Allah");

	connect(saveButton,SIGNAL(clicked()),this,SLOT(saveSetting()));
	
	QHBoxLayout *settingLayout = new QHBoxLayout;
	QHBoxLayout *mainLayout = new QHBoxLayout;
	settingLayout->addWidget(xstartUp);	
	settingLayout->addWidget(saveButton);
	mainLayout->addLayout(settingLayout);
	setLayout(mainLayout);
}

hodSetting::~hodSetting(){
}

void hodSetting::saveSetting(){
        QSettings settings("DDI","HOD");
        settings.beginGroup("MainWindow");
        settings.setValue("onStartup",startupOpts());
        #if defined(Q_OS_WIN32)
            settings.setPath(QSettings::IniFormat,QSettings::UserScope,"HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run");
        #endif
        if(startupOpts() == "true"){
                #if defined(Q_OS_LINUX)
                    addEntry();	// rename to linux
                #else
                        addEntryWin();	// and rename to windows
            #endif
        } else {	// do same here.
            #if defined(Q_OS_LINUX)
                removeEntry();
            #else
                removeEntryWin();
            #endif
        }
        settings.endGroup();
        close();
}

// File should be in ~/.kde4/Autostart/
//QDir::homePath() // will return the user home dir full path then append the other dir.
//
void hodSetting::addEntry(){
	// for linux specifics, use #if defined(Q_OS_LINUX) ... else for windows specifics
	// that's the way to go for cross platform apps.
	// NB:: All the code is the block are strictly for linux platform,
	// use the above to seperate the windows from linux.
	QString desktopFile = QString("%1/.kde4/Autostart/hotd.desktop").arg(QDir::homePath());
  	QFile settingsFile(desktopFile);
  	if(!settingsFile.open(QIODevice::WriteOnly)){
  /*	QMessageBox msg;
  		msg.setText("Unable to create startup option file,\nCheck permission");
  		msg.exec(); 
  */
  		return ;
  	}
  	QTextStream out(&settingsFile);
  	out<<"#!/usr/bin/env xdg-open"<<endl;
  	out<<"[Desktop Entry]"<<endl;
	out<<"Comment[en_US]= "<<endl;
  	out<<"Comment= "<<endl;
	out<<QString("Exec= %1").arg(QCoreApplication::applicationFilePath())<<endl;
	out<<"GenericName[en_US]= "<<endl;
	out<<"GenericName="<<endl;
	out<<"Icon=system-run"<<endl;
	out<<"MimeType="<<endl;
	out<<QString("Name[en_US]=%1").arg(QCoreApplication::applicationName())<<endl;
	out<<QString("Name=%1").arg(QCoreApplication::applicationName())<<endl; 
	out<<QString("Path=%1").arg(QCoreApplication::applicationDirPath())<<endl; 
	out<<"StartupNotify=true"<<endl; // i think this should be false.
	out<<"Terminal=false"<<endl;
	out<<"TerminalOptions="<<endl;
	out<<"Type=Application"<<endl;
	out<<"X-DBUS-ServiceName="<<endl;
	out<<"X-DBUS-StartupType="<<endl;
	out<<"X-KDE-SubstituteUID=false"<<endl;
	out<<"X-KDE-Username="<<endl;
	//set the executable permission for the file.
	settingsFile.setPermissions(QFile::ReadOwner | QFile::ExeOwner);
	settingsFile.close();
}

// File should be in ~/.kde4/Autostart/
void hodSetting::removeEntry(){
	//remove the file created above.
	// NB:: This block contained linux specifics only, correct this...
	QString desktopFile = QString("%1/.kde4/Autostart/hotd.desktop").arg(QDir::homePath());	
	QFile settingsFile(desktopFile);
	if(settingsFile.exists()){
		if(settingsFile.remove()){
		}else{
			qDebug()<<"Error Removing file.";
		}	
	}else{
		qDebug()<<"startup File doesnt exist.";
	}
}

// windows zone.

void hodSetting::addEntryWin(){
    QSettings currentVer("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    currentVer.setValue("HOD", QCoreApplication::applicationFilePath().replace('/','\\'));
}

void hodSetting::removeEntryWin(){
    QSettings currentVer("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
    currentVer.remove("HOD");
}

QString hodSetting::startupOpts(){
	if(xstartUp->isChecked()){
            return "true";
	}
	else {
            return "false";
	}
}

void hodSetting::readSetting(){
	QSettings settings("DDI","HOD");
	settings.beginGroup("MainWindow");
	xstartread = settings.value("onStartup").toString();
	settings.endGroup();
	if(xstartread == "true"){
		xstartUp->setChecked(true);
	}
	else{
		xstartUp->setChecked(false);
	}
}


