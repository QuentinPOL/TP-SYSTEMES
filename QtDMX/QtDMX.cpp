//*********************************************************************************************
//* Programme : QtDMX.cpp                                                 Date : 01/12/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 01/12/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Faire l'implémentation des méthodes / constructeur / constructeur de celle-ci
//* Programmes associés : QtDMX.h (fichier entête de la classe QtDMX)
//*********************************************************************************************

#include "QtDMX.h"

//---------------------------------------------------------------------------------------------
//* Constructeur de la classe QtDMX qui est l'ihm du programme -> cela regroupe l'iniatliation de l'objet PilotageLumiere
// qui va lui même faire l'initlisation de l'interface ainsi que le module pour envoyer des trames DMX grâce à des commandes
// ce qui va permettre  de piloter le changement des couleurs des lumières
// on a aussi l'initialisation des 512 blocks de la trame DMX et dans le constructeur création de PilotageLumiere du timer pour l'envoie de trame régulier (50 ms)
//-------------------------------------------------------------------------------------------
QtDMX::QtDMX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

	//Envoi D'une Trame DMX
	piloteLum = new PilotageLumiere(ui.horizontalSlider->value(), ui.verticalSliderColorRed->value(), ui.verticalSliderColorGreen->value(), ui.verticalSliderColorBlue->value(), ui.verticalSliderColorBlue->value(), 50);

	// Connecter le signal timeout du timer au slot sendTrame
	QObject::connect(&timer, &QTimer::timeout, this, &QtDMX::sendTrame);
	timer.start(piloteLum->getTimer()); // on envoie toutes les 50 ms une trame
}

//---------------------------------------------------------------------------------------------
//* Destructeur de la classe de l'ihm QtDMX 
//---------------------------------------------------------------------------------------------
QtDMX::~QtDMX()
{}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de l'adresse de la lumière du slider dans le label
//* Paramètres :
//*  - int value : variable qui à la valeur du slider de l'adresse de la lumière
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderValueChanged(int value)
{
	ui.labelLampValue->setText(QString::number(value));
	piloteLum->setAdressValue(value);
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur rouge du slider dans le label et change la valeur du rouge de l'objet qui pilote les lumieres
//* Paramètres :
//*  - int value : variable qui à la valeur du slider de la couleur rouge
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorRedChanged(int value)
{
	ui.labelValueRed->setText(QString::number(value));
	piloteLum->setRedValue(value);
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur verte du slider dans le label et change la valeur du vert de l'objet qui pilote les lumieres
//* Paramètres :
//*  - int value : variable qui à la valeur du slider de la couleur verte
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorGreenChanged(int value)
{
	ui.labelValueGreen->setText(QString::number(value));
	piloteLum->setGreenValue(value);
}

// qui ferme la connexion ainsi que libére la librairie DLL


//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur blueue du slider dans le label et change la valeur du bleu de l'objet qui pilote les lumieres
//* Paramètres :
//*  - int value : variable qui à la valeur du slider de la couleur blueue
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorBlueChanged(int value)
{
	ui.labelValueBlue->setText(QString::number(value));
	piloteLum->setBlueValue(value);
}

//---------------------------------------------------------------------------------------------
//* Fonction qui affiche la valeur de la couleur blanche du slider dans le label et change la valeur du blanc de l'objet qui pilote les lumieres
//* Paramètres :
//*  - int value : variable qui à la valeur du slider de la couleur blanche
//---------------------------------------------------------------------------------------------
void QtDMX::onSliderColorWhiteChanged(int value)
{
	ui.labelValueWhite->setText(QString::number(value));
	piloteLum->setWhiteValue(value);
}

//---------------------------------------------------------------------------------------------
//* Fonction qui envoie une trame si l'interface est ouverte et donc que la libraire DLL est chargée (de la classe pilotagelumiere)
// Ainsi que des couleurs sélectionnées (grâce au méthode get de la classe pilotagelumiere qui récupére la valeur des attributs rgbw de celle ci
// Enfin on fait le changement de couleur de la lumière en question (dans l'attribut de la classe pilotageLumiere -> addrssLight) on va donc appeler la méthode sendTrame() de cette même classe
// Mais on va vérifier avant si la checkbox est coché ou no  pour faire un défilement automatique des couleurs et ensuite une fois qu'on à fait tout cela on envoie la trame DMX
//---------------------------------------------------------------------------------------------
void QtDMX::sendTrame()
{
	if (piloteLum->isInterfaceOpen() > 0)
	{
		// Voici un exemple de comment est construite la trame ainsi que comment elle est construite
		// exemple si la lumiere est sur le canal 12, alors l'octet dmxBlock[12] contient
		// un ensemble de 8 bits representant les informations à envoyer à la lumiere : intensite couleur ect
		// Attention une lumiere peut avoir plusieur cannaux
		// exemple une led 3 couleurs aura 3 cannaux pour rouge vert bleu
		// donc la deuxieme lampe devra etre configure sur un canal 4

		// Si on veut faire un défilement de couleur automatique
		if (ui.checkBox->isChecked())
		{
			int time = QTime::currentTime().msecsSinceStartOfDay();  // Obtient le temps actuel en millisecondes
			piloteLum->setRedValue((time / 10) % 256);    // Dégradé rouge
			piloteLum->setGreenValue((time / 15) % 256);  // Dégradé vert
			piloteLum->setBlueValue((time / 20) % 256);   // Dégradé bleu
			piloteLum->setWhiteValue((time / 25) % 256);   // Dégradé bleu
		}

		piloteLum->sendTrame(); // On ennvoie la trame
	}
}