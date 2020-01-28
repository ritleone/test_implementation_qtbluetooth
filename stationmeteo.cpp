#include "stationmeteo.h"

const char *StationMeteo::typeTrameTexte[16]= {\
    "wind", "rain", "th", "mushroom", "t", "bth", "extbth",\
    "?", "?", "?", "?", "?", "?", "?", "minute", "clock" };

StationMeteo::StationMeteo () {
    qWarning("Constructeur StationMeteo");
    lm= NULL;
    connexion= false;
    // Contenu d'une mesure: tmp_ext, tmp_int, hum_ext, hum_int, vent_vi, vent_di, minu_ac, date_ac
    // Une mesure sera conctituée au maximum de 8 valeurs mais en réalité cela dépend
    // du nombre de capteurs connectés à la station Oregon
    ctrlMesureComplete= (~(minu_ac | tmp_int | hum_int )) & 0xff;   // def des informations fournies
    flagValeurModif= 0; // mesure inchangée
    mesureComplete= false;
    mesure.initMesure();
    qWarning("ctrlMesureComplete: %02x", ctrlMesureComplete);
}

StationMeteo::~StationMeteo () {
    qWarning("Destructeur StationMeteo");
    if(lm != NULL){
        qWarning("delete LiaisonMeteo");
        delete this->lm;
    }
}

void StationMeteo::connexionStationMeteo(int port) {
    qWarning("new LiaisonMeteo");
    if(connexion == false)    {
        connexion= true;
        this->lm = new LiaisonMeteo(port);
        connect (this->lm, SIGNAL(dataOK()), this, SLOT(lireTrame()));
    }
    else
        qWarning("LiaisonMeteo déja opérationnelle !");
}

void StationMeteo::lireTrame() { 
    typeTrameNum = this->lm->getType();
    this->trame = this->lm->getTrame();
    this->data = this->lm->getDataComplete();
    flagValeurModif= 0;
    switch (typeTrameNum) {
        case 0: this->wind(); break;
        case 1: this->rain(); break;
        case 2: this->th(); break;
        case 3: this->mushroom(); break;
        case 4: this->t(); break;
        case 5: this->bth(); break;
        case 6: this->extbth(); break;
        case 0xe: this->minute(); break;
        case 0xf: this->clock(); break;
        default: qWarning("Trame de type inconnu !");
    }  
    qWarning("%02x != 0 && %02d == %02d", flagValeurModif, ctrlMesureComplete, 0xff);

    if(flagValeurModif != 0){ // si nouvelle valeur
        if(ctrlMesureComplete == 0xff){  // si mesure complète
                mesure.setDate( QDateTime::currentDateTime());
                qWarning("date=%s", mesure.getDate().toString("yyyy-MM-dd HH:mm:ss").toLatin1().data());
                mesureComplete= true;
        }
        emit(newValeur(mesure, trame));
    }
    else {
        qWarning("Nouvelle trame mais aucun changement");
        emit(newTrame(trame));
    }
}

void StationMeteo::stopCapture() {
	disconnect (this->lm,SIGNAL(dataOK()),this,SLOT(lireTrame()));
}

void StationMeteo::wind() { // type 0
    this->vent_direction.clear();
    this->vent_direction.append(((data[5])&0xF) + '0');
    this->vent_direction.append(((data[4]>>4)&0xF) + '0');
    this->vent_direction.append((data[4]&0xF) + '0');
    if(this->vent_direction.toInt() != mesure.getDirectionVent()){
        this->mesure.setDirectionVent(this->vent_direction.toInt());
        ctrlMesureComplete |= vent_di;
        flagValeurModif |= vent_di;
    }
    this->vent_direction.append(" degres");
    this->vent_direction.prepend("Direction vent: "); // 16 carac (afficheur)

    this->vent_vitesse.clear();
    this->vent_vitesse.append(((data[6]>>4)&0xF) + '0');
    this->vent_vitesse.append(((data[6])&0xF) + '0');
    this->vent_vitesse.append('.');
    this->vent_vitesse.append(((data[5]>>4)&0xF) + '0');
    if(this->vent_vitesse.toFloat() != mesure.getVitesseVent()){
        this->mesure.setVitesseVent(this->vent_vitesse.toFloat());
        ctrlMesureComplete |= vent_vi;
        flagValeurModif |= vent_vi;
    }
    this->vent_vitesse.append(" m/s");
    this->vent_vitesse.prepend("Vitesse vent:   "); // 16 carac (afficheur)
    qWarning("Vent!");
}

void StationMeteo::rain(){ // type 1 à faire
    qWarning("Pluie!");
}

void StationMeteo::th() { // type 2
    qWarning("TH!");
}

void StationMeteo::mushroom() { // type 3
    thermo(true);  // extérieur
    humi(true);
    qWarning("Mushroom!");
}

void StationMeteo::t() { // type 4
    qWarning("T!");
}

void StationMeteo::bth() { // type 5
    qWarning("BTH!");
}

void StationMeteo::extbth() { // type 6
    this->thermo(false); // intérieur
    this->humi(false);
    qWarning("EXTBTH!");
}

void StationMeteo::minute() {
    this->minutes_actu.clear();
    this->minutes_actu.append("Minutes:        "); // 16 carac (afficheur)
    this->minutes_actu.append(((data[3]>>4)&0xF) + '0');
    this->minutes_actu.append(((data[3])&0xF) + '0');
    this->minutes_actu.append("'");
    ctrlMesureComplete |= minu_ac;
    flagValeurModif |= minu_ac;
    qWarning("Minute!");
}

void StationMeteo::clock() {
    this->date_actu.clear();
    this->date_actu.append("Date:           "); // 16 carac (afficheur)
    this->date_actu.append(((data[5]>>4)&0xF) + '0');
    this->date_actu.append(((data[5])&0xF) + '0');
    this->date_actu.append("/");
    this->date_actu.append(((data[6]>>4)&0xF) + '0');
    this->date_actu.append(((data[6])&0xF) + '0');
    this->date_actu.append("/");
    this->date_actu.append(((data[7]>>4)&0xF) + '0');
    this->date_actu.append(((data[7])&0xF) + '0');
    this->date_actu.append("  ");
    this->date_actu.append(((data[4]>>4)&0xF) + '0');
    this->date_actu.append(((data[4])&0xF) + '0');
    this->date_actu.append(":");
    this->date_actu.append(((data[3]>>4)&0xF) + '0');
    this->date_actu.append(((data[3])&0xF) + '0');
    ctrlMesureComplete |= date_ac;
    flagValeurModif |= date_ac;
    qWarning("Clock!");
}

void StationMeteo::humi(bool ext) {
    QString humidite;
    humidite.append(((data[6]>>4)&0xF) + '0');
    humidite.append(((data[6])&0xF) + '0');

    if(ext){
        if(humidite.toInt() != mesure.getHumiditeExt()){
            this->mesure.setHumiditeExt(humidite.toInt());
            ctrlMesureComplete |= hum_ext;
            flagValeurModif |= hum_ext;
        }
        this->humidite_ext.clear();
        this->humidite_ext.append("Humidite ext:   ");
        this->humidite_ext.append(humidite);
        this->humidite_ext.append(" %");
    }
    else{
        if(humidite.toInt() != mesure.getHumiditeInt()){
            this->mesure.setHumiditeInt(humidite.toInt());
            ctrlMesureComplete |= hum_int;
            flagValeurModif |= hum_int;
        }
        this->humidite_int.clear();
        this->humidite_int.append("Humidite int:   ");
        this->humidite_int.append(humidite);
        this->humidite_int.append(" %");
    }
}

void StationMeteo::thermo(bool ext) {
    QString temperature;
    if ( ((data[5]>>7)&0x1) == 1)
        temperature.append('-');
    temperature.append(((data[5]>>4)&0x3) + '0');
    temperature.append(((data[5])&0xF) + '0');
    temperature.append(((data[4]>>4)&0xF) + '0');
    temperature.append(".");
    temperature.append(((data[4])&0xF) + '0');
    if(ext){
        if(temperature.toFloat() != mesure.getTemperatureExt()){
            this->mesure.setTemperatureExt(temperature.toFloat());
            ctrlMesureComplete |= tmp_ext;
            flagValeurModif |= tmp_ext;
        }
        this->temperature_ext.clear();
        this->temperature_ext.append("Temperature ext:");
        this->temperature_ext.append(temperature);
        this->temperature_ext.append(" degres");
    }
    else {
        if(temperature.toFloat() != mesure.getTemperatureInt()){
            this->mesure.setTemperatureInt(temperature.toFloat());
            ctrlMesureComplete |= tmp_int;
            flagValeurModif |= tmp_int;
        }
        this->temperature_int.clear();
        this->temperature_int.append("Temperature int:");
        this->temperature_int.append(temperature);
        this->temperature_int.append(" degres");
    }
}

bool StationMeteo::verifModif(){
    bool ret=false;
    qWarning("%02x != 0 && %02d == %02d", flagValeurModif, ctrlMesureComplete, 0xff);
    if((flagValeurModif != 0) && (ctrlMesureComplete == 0xff)) // si nouvelle valeur & mesure complète
        ret= true;
    return ret;
}

Mesure StationMeteo::getMesure(){
    return(mesure);
}

void StationMeteo::setModeTrace(bool mode){
    lm->setFlagTrace(mode);
}

const char* StationMeteo::getTypeTrameTexte(){
    return typeTrameTexte[typeTrameNum];
}

int StationMeteo::getTypeTrameNum(void){
    return typeTrameNum;
}

int StationMeteo::getFlagValeurModif(){
    return flagValeurModif;
}

bool StationMeteo::getMesureComplete(){
    return mesureComplete;
}

void StationMeteo::setMesureComplete(bool etat){
    mesureComplete= etat;
}
