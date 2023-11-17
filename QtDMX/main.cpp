//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Derni�re mise � jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Cr�er et lancer le projet pour faire tourner le programme avec l'ihm et les actions relier � celui-ci
//* Programmes associ�s : QtDMX.h
//*********************************************************************************************

#include "QtDMX.h"
#include <QtWidgets/QApplication>

//---------------------------------------------------------------------------------------------
//* Fonction main pour lancer et faire tourner le programme avec l'him et ces fonctionnalit�es associ�s
//* Param�tres :
//*  - int argc :  repr�sente le nombre total d'arguments pass�s au programme, y compris le nom du programme lui-m�me.
//*  - char * argv [] : C'est un tableau de cha�nes de caract�res (char*) qui contient les arguments individuels pass�s au programme
//* Valeur de retour : code de retour au syst�me d'exploitation pour signaler � l'environnement d'ex�cution que l'application s'est termin�e normalement
//-------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDMX w;
    w.show();
    return a.exec();
}
