#pragma once

//*********************************************************************************************
//* Programme : QtDMX.h                                                 Date : 01/12/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 01/12/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Créer la classe QtDMX et déclarer les méthodes / constructeur / desctructeur de celle-ci
//* Programmes associés : PilotageLumiere.h
//*********************************************************************************************

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QDateTime>

#include "ui_QtDMX.h"
#include "PilotageLumiere.h"

class QtDMX : public QMainWindow
{
    Q_OBJECT

public:
    QtDMX(QWidget *parent = nullptr);
    ~QtDMX();

    PilotageLumiere* piloteLum;
    QTimer timer;  // Déclarer le QTimer comme un membre de la classe
private:
    Ui::QtDMXClass ui;

public slots:
    void onSliderValueChanged(int value); // Valeur des adresses des lampes

    void onSliderColorRedChanged(int value); // Valeur decimal de la couleur rouge
    void onSliderColorGreenChanged(int value); // Valeur decimal de la couleur vert
    void onSliderColorBlueChanged(int value); // Valeur decimal de la couleur bleu
    void onSliderColorWhiteChanged(int value); // Valeur decimal de la couleur blanche

    void sendTrame();
};
