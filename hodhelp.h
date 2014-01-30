#ifndef HODHELP_H
#define HODHELP_H

#include<QtGui>

class QTextEdit;
class QPushButton;

class hodHelp : public QDialog
{
	Q_OBJECT
	
	public :
		hodHelp(QWidget *parent=0);
        ~hodHelp();

	private :
		QPushButton *helpOk;
        QTextEdit *helpArea;
		
};
#endif 

