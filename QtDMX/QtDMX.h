#pragma once

//*********************************************************************************************
//* Programme : QtDMX.h                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Cr�er la classe QtDMX et d�clarer les m�thodes / constructeur / desctructeur de celle-ci
//* Programmes associ�s : DashHard.h | PilotageLumiere.h
//*********************************************************************************************

#include <iostream>
#include <vector>

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QDateTime>

#include "ui_QtDMX.h"
#include <Windows.h>
#include "DashHard.h"
#include "PilotageLumiere.h"

#define DMX_MAXCHANNEL 512

class QtDMX : public QMainWindow
{
    Q_OBJECT

public:
    QtDMX(QWidget *parent = nullptr);
    ~QtDMX();

    HINSTANCE g_dasusbdll;
    typedef int (*DASHARDCOMMAND)(int, int, unsigned char*);
    DASHARDCOMMAND DasUsbCommand;

    int interface_open;
    unsigned char dmxBlock[512];

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

    void sendTrame(); // Envoie d'une trame
};
