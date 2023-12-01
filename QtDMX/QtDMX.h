#pragma once

//*********************************************************************************************
//* Programme : QtDMX.h                                                 Date : 01/12/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 01/12/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Cr�er la classe QtDMX et d�clarer les m�thodes / constructeur / desctructeur de celle-ci
//* Programmes associ�s : PilotageLumiere.h
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
    QTimer timer;  // D�clarer le QTimer comme un membre de la classe
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
