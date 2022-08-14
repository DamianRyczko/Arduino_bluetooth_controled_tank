#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QListWidget>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Find_clicked();

    void on_Autopilot_clicked();

    void deviceDiscovered(const QBluetoothDeviceInfo &device);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_Forward_pressed();

    void on_RorateLeft_pressed();

    void on_Stop_pressed();

    void on_RorateRight_pressed();

    void on_Backward_pressed();

    void on_Forward_released();

    void on_RorateLeft_released();

    void on_RorateRight_released();

    void on_Backward_released();

    void on_ForwardLeft_released();

    void on_ForwardRight_released();

    void on_BottomLeft_released();

    void on_BottomRight_released();

    void on_ForwardLeft_pressed();

    void on_ForwardRight_pressed();

    void on_BottomLeft_pressed();

    void on_BottomRight_pressed();

    void on_dial_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *object, QEvent *event);
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
    QString string;
    QSet<int> activeKeys;
};
#endif // MAINWINDOW_H
