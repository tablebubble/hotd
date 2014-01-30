#ifndef HODSET_H
#define HODSET_H

#include<QtGui>

class QPushButton;
class QLabel;

class hodSetting : public QDialog
{
	Q_OBJECT
	
	public :
		hodSetting(QWidget *parent=0);
        ~hodSetting();

	public slots :
		void saveSetting();
		QString startupOpts();
		void readSetting();
				
	private :
		QCheckBox *xstartUp;
		QPushButton *saveButton;
		QString xstartread;
        void addEntry();
        void removeEntry();
        void addEntryWin();
        void removeEntryWin();
};

#endif 



