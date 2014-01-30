//#include <QtCore>
#include <QtSql>

int getrandomnumber();
QString escape_string(QString);

QStringList getHadith(int hadno){
    QStringList hadith
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("hadith.db");
    if(!db.open()){	// display database specific error messages.
	qDebug()<<"Error Opening Database File.";
	qFatal("Failed to connect to Db.");
	return;
    }
// SELECT * FROM hotd ORDER BY RANDOM() LIMIT 1
// will not require extra code for random numbers.
    QString qryText = QString("SELECT hid, matn, source, narrator FROM hotd WHERE hid = %1").arg(hadno);
    QSqlQuery q(qryText);
    QSqlRecord rec = q.record();
    while(q.next()){
      hadith << q.value(0).toInt()<< escape_string(q.value(1).toString()) \
      <<escape_string(q.value(2).toString())<<escape_string(q.value(3).toString());
    }
    // close the db.
    // check if hadith is NOT empty before returning a value.
    db.close(); // close the db and free any resources used.
    return hadith;
}

QString escape_string(QString text){
    // perform search and replace on %%25 to \'
    return text.replace(QString("%%25"),QString("\'"));
}