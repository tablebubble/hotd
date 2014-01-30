#include <QtGui>
#include <QtSql>
#include "hod.h"
#include "hodset.h"
#include "hodhelp.h"

Hod::Hod(QWidget *parent)
 : QDialog(parent)
{
	//Window wide config.      
	setFixedSize(430, 330);
	setWindowIcon(QIcon(":/hod_logo.png"));
	setWindowTitle("Hadith of the Day");
	// define widgets.
	okbutton = new QPushButton("OK");
	optionbutton = new QPushButton("Option");
	nextbutton = new QPushButton("Next Hadith");
	helpbutton = new QPushButton("Help");
	aboutbutton = new QPushButton("About");
	textarea = new QTextEdit;
	textarea->setReadOnly(true);
	createNarratorsBox();
	createSourceBox();
	//set widgets here
	QVBoxLayout *buttonlayout = new QVBoxLayout;
	QHBoxLayout *textlayout = new QHBoxLayout;
	//groupBox added
	QHBoxLayout *groupboxes = new QHBoxLayout;
	QHBoxLayout *mainlayout = new QHBoxLayout;
	QVBoxLayout *finalLayout = new QVBoxLayout;
	buttonlayout->addWidget(okbutton);
	buttonlayout->addWidget(nextbutton);
	buttonlayout->addWidget(optionbutton);
	buttonlayout->addWidget(helpbutton);
	buttonlayout->addWidget(aboutbutton);
	buttonlayout->addStretch(8);
	groupboxes->addWidget(narratorsBox);
	groupboxes->addWidget(sourceBox);
	textlayout->addWidget(textarea);
	readNextHadith();
	//connect signal and slots
	connect(okbutton,SIGNAL(clicked()),this,SLOT(close()));
	connect(nextbutton,SIGNAL(clicked()),this,SLOT(readNextHadith()));
	connect(aboutbutton,SIGNAL(clicked()),this,SLOT(aboutHOD()));
	connect(optionbutton,SIGNAL(clicked()),this,SLOT(option()));
	connect(helpbutton,SIGNAL(clicked()),this,SLOT(helpHOD()));

	//set Layout here
	mainlayout->addLayout(textlayout);
	mainlayout->addLayout(buttonlayout);
	finalLayout->addLayout(mainlayout);
	finalLayout->addLayout(groupboxes);
	setLayout(finalLayout);
}

Hod::~Hod(){
}

int Hod::getrandomnumber(){
//	qsrand((unsigned int ) time(0));
    QDateTime now = QDateTime::currentDateTime();
    qsrand(now.toTime_t());
    int High = 20, Low = 1, randnumber =0;
    int Intervalsize = High - Low + 1;
    int RandomOffset = qrand() % Intervalsize;
    randnumber = Low + RandomOffset;
    return randnumber;
}

void Hod::readNextHadith(){
	// hid, matn, source, narrator - order.
	QStringList hadithtoday = getHadith(getrandomnumber()); 
	// Seperate strings into substring and display in their respective area.
        textarea->setText(hadithtoday.at(0));
        narratedbyLabel->setText(hadithtoday.at(1));
        sourceLabel->setText(hadithtoday.at(2));
}

void Hod::option(){
    hodSetting dialog(this);
    dialog.exec();
}

//Add official website and email to this
void Hod::aboutHOD(){
	QMessageBox::about(this, tr("About Hadith Of the Day"),
            tr("<img src=\":/bismillah.jpg\"></img>"
			"<p><h2>Hadith Of the Day</h2>"
			"<p>Written by: <i>Ajisebutu A. Abdulwaasi'</i>"
            "<p>CopyLeft &copy; 2010" ));
      //      "<p><a href=\"www.ddigroupng.com\"><TT>DataDefinitionsInterlinks</TT></a>"));
}

void Hod::helpHOD(){
	hodHelp dialog(this);
	dialog.exec();
}

void Hod::createSourceBox(){
	sourceBox = new QGroupBox("Source:");
	sourceLabel = new QLabel;
	QHBoxLayout *source = new QHBoxLayout;
	source->addWidget(sourceLabel);
	sourceBox->setLayout(source);
}

void Hod::createNarratorsBox(){
	narratorsBox = new QGroupBox("Narrated By:");
	narratedbyLabel = new QLabel;
	QHBoxLayout *narrator = new QHBoxLayout;
	narrator->addWidget(narratedbyLabel);
	narratorsBox->setLayout(narrator);	
}

QStringList Hod::getHadith(int hadithno){
    QStringList hadith;
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hadith.db");
    if(!db.open()){	// display database specific error messages.
	qDebug()<<"Error Opening Database File.";
	qFatal("Failed to connect to Db.");
//	return 0; // cant return 0 here, This is a GUI app. use QMessageBox instead.
    }

    QString qryText = QString("SELECT matn, source, narrator FROM hotd WHERE hid = %1").arg(hadithno);
    QSqlQuery q(qryText);
    QSqlRecord rec = q.record();
    while(q.next()){
      hadith <<escape_string(q.value(0).toString()) <<escape_string(q.value(1).toString());
      hadith <<escape_string(q.value(2).toString());
    }
    // close the db.
    // check if hadith is NOT empty before returning a value.
    db.close(); // close the db and free any resources used.
    return hadith;
}

QString Hod::escape_string(QString text){
    // perform search and replace on %%25 to \'
    return text.replace(QString("%%25"),QString("\'"));
}
