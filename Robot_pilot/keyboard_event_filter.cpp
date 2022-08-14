#include "keyboard_event_filter.h"
#include <QtBluetooth>
Keyboard_event_filter::Keyboard_event_filter(QObject *parent)
    : QObject{parent}
{
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
}

bool Keyboard_event_filter::eventFilter(QObject *watched, QEvent *event)
{

    if ( event->type() == QEvent::KeyPress ) {

        activeKeys += ((QKeyEvent*)event)->key();

        if ( activeKeys.contains(Qt::Key_W) && activeKeys.contains(Qt::Key_A) )
        {
           qDebug() << "pressed W and A";
           socket->write("Q");
            return true;
        }

        else if ( activeKeys.contains(Qt::Key_W) && activeKeys.contains(Qt::Key_D) )
        {
             qDebug() << "pressed W and D";
             socket->write("E");
            return true;
        }

        else if ( activeKeys.contains(Qt::Key_S) && activeKeys.contains(Qt::Key_A) )
        {
             qDebug() << "pressed S and A";
             socket->write("Z");
            return true;
        }

        else if ( activeKeys.contains(Qt::Key_S) && activeKeys.contains(Qt::Key_D) )
        {
             qDebug() << "pressed S and D";
             socket->write("C");
            return true;
        }

    }
    else if ( event->type() == QEvent::KeyRelease )
    {

        activeKeys -= ((QKeyEvent*)event)->key();
    }


    return false;
}
