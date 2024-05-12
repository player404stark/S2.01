#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <QObject>
#include "modele.h"
#include "lecteurVue.h"

class Presentation : public QObject
{
    Q_OBJECT
public:
    explicit Presentation(QObject *parent = nullptr);

private:
    Modele* _leModele;
    lecteurVue* _laVue;

public:
    Presentation();

    Modele *getModele();
    lecteurVue *getVue();

    void setModel(Modele* m);
    void setVue(lecteurVue* v);

public slots:
    void demanderAvancer();
    void demanderReculer();
    void demanderDepartArretAuto();
    void demanderChangerVitesse();
    void demanderChangerMode();

signals:
    void s_avancer();
    void s_reculer();
    void s_departArret();
    void s_changerVitesse();
    void s_changerMode();
};

#endif // PRESENTATION_H
