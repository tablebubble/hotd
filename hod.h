#ifndef HOD_H
#define HOD_H

#include<QtGui>

class QLabel;
class QPushButton;
class QTextEdit;
class QHBoxLayout;
class QVBoxLayout;
class QGroupBox;
class QMessageBox;
class hodSetting;
class hodHelp;

class Hod : public QDialog
{
	Q_OBJECT

public :
   Hod(QWidget *parent=0);
    ~Hod();

private slots :
	int getrandomnumber();
	void readNextHadith();
    void option();
	void aboutHOD();
	void helpHOD();
	QStringList getHadith(int);
	QString escape_string(QString);
	void createSourceBox();
	void createNarratorsBox();
	
private :

	QTextEdit *textarea;
	QPushButton *okbutton;
	QPushButton *nextbutton;
    QPushButton *optionbutton;
	QPushButton *helpbutton;
	QPushButton *aboutbutton;
	QGroupBox *sourceBox;
	QLabel *sourceLabel;
	QGroupBox *narratorsBox;
	QLabel *narratedbyLabel;


};

#endif
//hod.h
