#ifndef _LIAISONMETEO_H
#define _LIAISONMETEO_H
#include <QObject>
#include <QUdpSocket>
#include <QFile>

class LiaisonMeteo : public QObject {
    Q_OBJECT

private:
    QUdpSocket *udpSocket;
    static const int lgTrame[16];
    unsigned char dataEnCours[16];
    unsigned char dataComplete[16];
    QString trame; // trame en sous forme de chaine hexa
    int index;
    int type;
    bool flagTrace; // Pour créer un fichier de simulation
    QFile trace;

public:
    LiaisonMeteo(int);
    ~LiaisonMeteo();
    void initReseauMeteo(int);
    QString getTrame(void);
    unsigned char* getDataComplete(void);
    int getType(void);
    void setFlagTrace(bool);

private:
    bool testChecksum(void);

private slots:
    void readDatagram();

signals:
    void dataOK(void);
};
#endif
