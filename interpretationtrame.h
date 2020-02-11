#ifndef INTERPRETATIONTRAME_H
#define INTERPRETATIONTRAME_H

#include <QtCore/QObject>
#include "clientsocket.h"
#include "bluetoothe.h"

class interpretationtrame: public QObject
{
    Q_OBJECT
public:
    interpretationtrame();
    ClientSocket CS;
    Bluetoothe Ble;

public:
    QString vent_vitesse, vent_direction, temperature_int, temperature_ext, humidite_int, humidite_ext;

private slots:
    void showMessage(const QString &sender, const QString &message);
private:
    void wind();
    void rain();
    void th();
    void mushroom();
    void t();
    void bth();
    void extbth();
    void minute();
    void clock();
};

#endif // INTERPRETATIONTRAME_H
