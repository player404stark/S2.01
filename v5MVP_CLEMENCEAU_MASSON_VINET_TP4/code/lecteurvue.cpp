#include "ui_lecteurvue.h"
#include "presentation.h"
#include "ui_apropos.h"
#include "ui_vit.h"
#include <QImage>

lecteurVue::lecteurVue(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lecteurVue)
    , m_MaPresentation(new Presentation())
{
    ui->setupUi(this);

    // Connexions pour les boutons
    /* C'est quoi cette merde ?
    QObject::connect(ui->bSuivant, &QPushButton::clicked, this, [this]() {
        this->demanderAvancer();
        this->m_MaPresentation->demanderChangerModeManuel();
    });
    QObject::connect(ui->bPrecedent, &QPushButton::clicked, this, [this]() {
        this->demanderReculer();
        this->m_MaPresentation->demanderChangerModeManuel();
    });

    QObject::connect(ui->bLancerDiapo, &QPushButton::clicked, this, [this](){
        this->demanderChangerModeAutomatique();
    });

    QObject::connect(ui->bArret, &QPushButton::clicked,this,[this](){
        this->demanderChangerModeManuel();
    });

*/
    QObject::connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(quitterApplication()));


    // Connexions pour les actions du menu
    QObject::connect(ui->actionChargerDiapo, SIGNAL(triggered()), this, SLOT(demanderChargerDiapo()));
    QObject::connect(ui->actionEnleverDiapo, SIGNAL(triggered()), this, SLOT(demanderEnleverDiapo()));
    QObject::connect(ui->actionVitesseDefilement, SIGNAL(triggered()), this, SLOT(demanderChangerVitesse()));

    QObject::connect(ui->actionAPropos, SIGNAL(triggered()), this, SLOT(demanderAPropos()));


    QObject::connect(ui->bSuivant, SIGNAL(clicked()), this, SLOT(demanderAvancer()));
    QObject::connect(ui->bPrecedent, SIGNAL(clicked()), this, SLOT(demanderReculer()));
    QObject::connect(ui->bLancerDiapo, SIGNAL(clicked()), this, SLOT(demanderChangerModeAutomatique()));
    QObject::connect(ui->bArret,SIGNAL(clicked()),this,SLOT(demanderChangerModeManuel()));

    // navigation entre les bouton avec tab
    QWidget::setTabOrder(ui->bPrecedent, ui->bSuivant);
}



lecteurVue::~lecteurVue()
{
    delete ui;
}

Presentation *lecteurVue::getPresentation() const
{
    return m_MaPresentation;
}



void lecteurVue::majPresentation(const QString &titreDiapo, const QString &titreImage, const QString &categorie, const QString &rang, const QString &chemin) {
    qDebug() << "Émission de imageChange avec: " << titreDiapo << titreImage << categorie << rang << chemin;
    ui->titreDiapo->setText(titreDiapo);
    ui->titreImage->setText(titreImage);
    ui->categorieImage->setText(categorie);
    ui->rangImage->setText(rang);
    ui->imageDiapo->setPixmap(QPixmap(chemin));

    ui->imageDiapo->repaint();
}


void lecteurVue::setPresentation(Presentation * p)
{
    m_MaPresentation = p;
    //majPresentation(getPresentation()->getDiapoActuel()); fait planter le prog
}



void lecteurVue::demanderAvancer(){
    qDebug() << "Demande d'avancer";

    getPresentation()->demanderAvancer();
}

void lecteurVue::demanderReculer(){
    qDebug() << "Demande à reculer";
    getPresentation()->demanderReculer();
}


void lecteurVue::demanderChangerVitesse(){
    qDebug() << "Demande à changer la vitesse";
    /*QDialog* vitDialog = new QDialog();
    Ui::vit vitUi;
    vitUi.setupUi(vitDialog);
    vitDialog->exec();
    delete vitDialog;
    qDebug() << "On affiche la fenêtre vitesse";*/
    getPresentation()->demanderChangerVitesse();
}

void lecteurVue::demanderChangerModeAutomatique(){
    qDebug() << "Demande à changer de mode en automatique";
    getPresentation()->demanderChangerModeAutomatique();
}

void lecteurVue::demanderChangerModeManuel(){
    qDebug() << "Demande à changer de mode en Manuel";
    getPresentation()->demanderChangerModeManuel();
}

void lecteurVue::demanderChargerDiapo(){
    qDebug() << "Demande à charger un nouveau diaporama";
    getPresentation()->demanderChargerDiapo();
}

void lecteurVue::demanderEnleverDiapo(){
    qDebug() << "Demande à enlever le diaporama courrant";
    getPresentation()->demanderEnleverDiapo();
}

void lecteurVue::quitterApplication() {
    QApplication::quit();
}

void lecteurVue::demanderAPropos(){
    qDebug() << "On affiche la fenêtre à propos";
    QDialog* aproposDialog = new QDialog();
    Ui::apropos aproposUi;
    aproposUi.setupUi(aproposDialog);
    aproposDialog->exec();
    delete aproposDialog;
}


void lecteurVue::initializeConnections() {
    if (getPresentation() && getPresentation()->getModele()) {
        bool connected = connect(m_MaPresentation->getModele(), &Modele::imageChange, this, &lecteurVue::majPresentation);
        qDebug() << "Connecté ? " << connected;
    }
}

void lecteurVue::majInterface(Modele::UnEtat e)
{
    switch(e)
    {
        case Modele::manuel:
            // Maj des boutons
            ui->actionManuel->setEnabled(false);
            ui->actionAutomatique->setEnabled(true);
            ui->actionVitesseDefilement->setEnabled(true);
            break;
        case Modele::automatique:
            // Maj des boutons
            ui->actionAutomatique->setEnabled(false);
            ui->actionManuel->setEnabled(true);
            ui->actionVitesseDefilement->setEnabled(false);
            break;

    }
}

