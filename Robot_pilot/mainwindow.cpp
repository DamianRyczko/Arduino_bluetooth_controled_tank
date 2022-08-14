#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtBluetooth>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->hide();

    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),this,SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
            agent->start();

    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Find_clicked()
{
    ui->listWidget->show();
    ui->listWidget->clear();
    agent->stop();
    agent->start();
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

    if (((QKeyEvent*)event)->isAutoRepeat())
       {
           return false;
       }

       if (!((QKeyEvent*)event)->isAutoRepeat())
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
               else if (activeKeys.contains(Qt::Key_W))
               {
                    qDebug() << "pressed w";
                    socket->write("F");
                   return true;
               }
               else if (activeKeys.contains(Qt::Key_A))
               {
                    qDebug() << "pressed a";
                    socket->write("L");
                   return true;
               }
               else if (activeKeys.contains(Qt::Key_S))
               {
                    qDebug() << "pressed s";
                    socket->write("B");
                   return true;
               }
               else if (activeKeys.contains(Qt::Key_D))
               {
                    qDebug() << "pressed d";
                    socket->write("R");
                   return true;
               }
           }
           else if ( event->type() == QEvent::KeyRelease )
           {

               activeKeys -= ((QKeyEvent*)event)->key();
               qDebug() << "key released";
               if(activeKeys.empty()){
                   socket->write("S");
               }
           }
           return false;
       }

}
void MainWindow::on_Autopilot_clicked()
{
    socket->write("A");
}

void MainWindow::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}


void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    string = item->text();
    ui->listWidget->addItem(string);
    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));

      socket->connectToService(QBluetoothAddress(string), QBluetoothUuid(serviceUuid),  QIODevice::ReadWrite);
}

void MainWindow::on_Forward_pressed()
{
    socket->write("F");
}

void MainWindow::on_RorateLeft_pressed()
{
    socket->write("L");
}

void MainWindow::on_Stop_pressed()
{
    socket->write("S");
}

void MainWindow::on_RorateRight_pressed()
{
    socket->write("R");
}

void MainWindow::on_Backward_pressed()
{
    socket->write("B");
}

void MainWindow::on_Forward_released()
{
    socket->write("S");
}


void MainWindow::on_RorateLeft_released()
{
    socket->write("S");
}

void MainWindow::on_RorateRight_released()
{
    socket->write("S");
}

void MainWindow::on_Backward_released()
{
    socket->write("S");
}

void MainWindow::on_ForwardLeft_pressed()
{
    socket->write("Q");
}

void MainWindow::on_ForwardRight_pressed()
{
    socket->write("E");
}

void MainWindow::on_BottomLeft_pressed()
{
    socket->write("Z");
}

void MainWindow::on_BottomRight_pressed()
{
    socket->write("C");
}

void MainWindow::on_ForwardLeft_released()
{
    socket->write("S");
}

void MainWindow::on_ForwardRight_released()
{
    socket->write("S");
}

void MainWindow::on_BottomLeft_released()
{
    socket->write("S");
}

void MainWindow::on_BottomRight_released()
{
    socket->write("S");
}



void MainWindow::on_dial_sliderMoved(int position)
{
    switch(position)
    {
        case 0:
            socket->write("0");
        break;
        case 1:
            socket->write("1");
        break;
        case 2:
            socket->write("2");
        break;
        case 3:
            socket->write("3");
        break;
        case 4:
            socket->write("4");
        break;
        case 5:
            socket->write("5");
        break;
        case 6:
            socket->write("6");
        break;
        case 7:
            socket->write("7");
        break;
        case 8:;
            socket->write("8");
        break;
        case 9:
            socket->write("9");
        break;
    }
}

