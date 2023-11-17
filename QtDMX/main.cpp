//*********************************************************************************************
//* Programme : main.cpp                                                 Date : 17/11/2023
//*--------------------------------------------------------------------------------------------
//* Dernière mise à jour : 17/11/2023
//*
//* Programmeurs : Quentin POLLET                                             Classe : BTSSN2
//*                
//*--------------------------------------------------------------------------------------------
//* But : Créer et lancer le projet pour faire tourner le programme avec l'ihm et les actions relier à celui-ci
//* Programmes associés : QtDMX.h
//*********************************************************************************************

#include "QtDMX.h"
#include <QtWidgets/QApplication>

//---------------------------------------------------------------------------------------------
//* Fonction main pour lancer et faire tourner le programme avec l'him et ces fonctionnalitées associés
//* Paramètres :
//*  - int argc :  représente le nombre total d'arguments passés au programme, y compris le nom du programme lui-même.
//*  - char * argv [] : C'est un tableau de chaînes de caractères (char*) qui contient les arguments individuels passés au programme
//* Valeur de retour : code de retour au système d'exploitation pour signaler à l'environnement d'exécution que l'application s'est terminée normalement
//-------------------------------------------------------------------------------------------

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtDMX w;
    w.show();
    return a.exec();
}
