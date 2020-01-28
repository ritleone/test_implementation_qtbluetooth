#ifndef _STATIONMETEO_H
#define _STATIONMETEO_H

#include <QObject>
#include "liaisonmeteo.h"
#include "mesure.h"

#define tmp_ext 0x01
#define tmp_int 0x02
#define hum_ext 0x04
#define hum_int 0x08
#define vent_vi 0x10
#define vent_di 0x20
#define minu_ac 0x40
#define date_ac 0x80

class Dialog;
class LiaisonMeteo;

class StationMeteo : public QObject {
    Q_OBJECT

private:
    static const char* typeTrameTexte[16]; // Nom des 9 types de mesure définis
    LiaisonMeteo *lm;       // liaison meteo
    Mesure mesure;          // contient les valeurs numériques de la mesure en cours
    unsigned char *data;    // pointe sur les données brutes de la trame
    bool connexion;
    unsigned int ctrlMesureComplete; // 0:rien 1:tmp_ext 2:tmp_int, etc. 0xff=mesure complète
    unsigned int flagValeurModif;    // indicateur de valeur(s) modifiee(s)
    int typeTrameNum;       // numero de type de trame entre 0 et 15
    bool mesureComplete;    // indicateur mesure complète

public:
    // Texte en clair des différentes mesures
    QString temperature_int, temperature_ext, humidite_int, humidite_ext,\
    vent_vitesse, vent_direction, date_actu, minutes_actu;
    QString trame;  // Contient la trame en hexa à afficher

public:
    StationMeteo();
    ~StationMeteo();

    void connexionStationMeteo(int);
    Mesure getMesure(); // retourne une copie de la mesure créée
    void setModeTrace(bool); // Pour sauvegarder les données brutes dans un fichier (pour le simulateur)
    const char *getTypeTrameTexte();
    int getTypeTrameNum();
    int getFlagValeurModif();
    bool getMesureComplete();
    void setMesureComplete(bool etat);

private:
    void wind();    // type = 0 (voir doc Oregon)
    void rain();    // type = 1
    void th();      // type = 2
    void mushroom();// type = 3
    void t();       // type = 4
    void bth();     // type = 5
    void extbth();  // type = 6
    void minute();  // type = 0xE
    void clock();   // type = 0xF

    void thermo(bool ext);
    void humi(bool ext);
    bool verifModif(void);

public slots:
    void lireTrame();
    void stopCapture();

signals:
    void newValeur(Mesure, QString);
    void newTrame(QString);
};
#endif
