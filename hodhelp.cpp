 #include <QtGui>
 #include <QApplication>
 #include "hodhelp.h"
 
 hodHelp::hodHelp(QWidget *parent)
 	: QDialog(parent)
{
    setWindowTitle("Hadith Of The Day Help");
    setFixedSize(335, 260);
    helpOk = new QPushButton("OK");
    helpOk->setMaximumSize(50, 30);
    helpArea = new QTextEdit;
    helpArea->setReadOnly(true);

    QVBoxLayout *textView = new QVBoxLayout;
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QVBoxLayout *helpLayout = new QVBoxLayout;

    textView->addWidget(helpArea);
    buttonLayout->addWidget(helpOk);
    helpLayout->addLayout(textView);
    helpLayout->addLayout(buttonLayout);
    setLayout(helpLayout);

    connect(helpOk,SIGNAL(clicked()), this, SLOT(close()));

    helpArea->setText("AsSaalam Alaykum!"
                "<p>Here's Some Help...</p>"
                "<p>OK Button: This will exit the program</p>"
                "<p>Next Button: This will display the next hadith </p>"
                "<p>About Button: Information on the program and author.</p>"
                "<p>In the options menu, you have the choice to make the program start everytime you enter windows.</p>");
 }
 hodHelp::~hodHelp(){
 }
