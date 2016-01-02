#include "QMailArchiver.h"

#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

QMailArchiver::QMailArchiver()
{
    QLabel* label = new QLabel( this );
    label->setText( "Hello World!" );
    setCentralWidget( label );
    QAction* action = new QAction(this);
    action->setText( "Quit" );
    connect(action, SIGNAL(triggered()), SLOT(close()) );
    menuBar()->addMenu( "File" )->addAction( action );
}

QMailArchiver::~QMailArchiver()
{}

#include "QMailArchiver.moc"
