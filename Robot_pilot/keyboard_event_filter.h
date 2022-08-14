#ifndef KEYBOARD_EVENT_FILTER_H
#define KEYBOARD_EVENT_FILTER_H

#include <QObject>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QListWidget>
#include <QKeyEvent>
#include <QDebug>

class Keyboard_event_filter : public QObject
{
    Q_OBJECT
public:
    explicit Keyboard_event_filter(QObject *parent = nullptr);

signals:

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
private:
QBluetoothSocket *socket;
QSet<int> activeKeys;
};
#endif // KEYBOARD_EVENT_FILTER_H
