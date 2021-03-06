//
// Created by joseph on 16/03/16.
//

#ifndef IHM_FENETRE_H
#define IHM_FENETRE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "dataBuffer.h"
#include "button.h"

#define FENETRE_TITRE " Oxymètre de pouls - © ISEN 2015/2016 - Joseph CAILLET and Thomas COUSSOT \0"
#define FENETRE_TITRE_LONGUEUR strlen(FENETRE_TITRE)
#define FENETRE_TITRE_ALARME_SYMBOLE '*'
#define FENETRE_TITRE_ALARME_SYMBOLE_LONGUEUR 15

#define FENETRE_HAUTEUR 880
#define FENETRE_LARGEUR 1000

#define COURBE_LONGUEUR TAILLE_BUFFER
#define COURBE_HAUTEUR 150
#define COURBE_OFFSET_Y 50
#define COURBE_OFFSET_X FENETRE_LARGEUR - COURBE_LONGUEUR - COURBE_OFFSET_Y / 2

#define POINT_HAUTEUR 3
#define POINT_LARGEUR 3

#define TEXTE_OFFSET_X (COURBE_OFFSET_X) / 2
#define TEXTE_GAP_Y 50

#define COULEUR_SPO2_R 231
#define COULEUR_SPO2_V 76
#define COULEUR_SPO2_B 60
#define COULEUR_SPO2 COULEUR_SPO2_R, COULEUR_SPO2_V, COULEUR_SPO2_B

#define COULEUR_BPM_R 46
#define COULEUR_BPM_V 204
#define COULEUR_BPM_B 113
#define COULEUR_BPM COULEUR_BPM_R, COULEUR_BPM_V, COULEUR_BPM_B

#define COULEUR_ACR_R 52
#define COULEUR_ACR_V 152
#define COULEUR_ACR_B 219
#define COULEUR_ACR COULEUR_ACR_R, COULEUR_ACR_V, COULEUR_ACR_B

#define COULEUR_ACIR_R 52
#define COULEUR_ACIR_V 152
#define COULEUR_ACIR_B 219
#define COULEUR_ACIR COULEUR_ACIR_R, COULEUR_ACIR_V, COULEUR_ACIR_B

#define COULEUR_FOND_ECRAN_R 39
#define COULEUR_FOND_ECRAN_V 40
#define COULEUR_FOND_ECRAN_B 34
#define COULEUR_FOND_ECRAN COULEUR_FOND_ECRAN_R, COULEUR_FOND_ECRAN_V, COULEUR_FOND_ECRAN_B

#define COULEUR_FOND_ECRAN_ALARME_R 211
#define COULEUR_FOND_ECRAN_ALARME_V 84
#define COULEUR_FOND_ECRAN_ALARME_B 0
#define COULEUR_FOND_ECRAN_ALARME COULEUR_FOND_ECRAN_ALARME_R, COULEUR_FOND_ECRAN_ALARME_V, COULEUR_FOND_ECRAN_ALARME_B

#define COULEUR_FOND_COURBE 44, 62, 80
#define COULEUR_ZERO_COURBE 200,200,200

#define COEFF_SPO2 1.5
#define COEFF_BPM 0.5
#define COEFF_ACR 0.0366
#define COEFF_ACIR COEFF_ACR

#define EASTER_ALPHA 90

struct Button;
typedef struct Button Button;

struct Fenetre
{
	SDL_Surface* screen;

	SDL_Surface* pxSPO2;
	SDL_Surface* pxBPM;
	SDL_Surface* pxACR;
	SDL_Surface* pxACIR;

	SDL_Surface* bgCourbe;
	SDL_Surface* zeroCourbe;
	SDL_Surface* alarmeBackground;

	SDL_Surface* easterImage;

	TTF_Font* font;
	SDL_Surface* txtSpo2;
	SDL_Surface* txtBpm;
	SDL_Surface* txtAcr;
	SDL_Surface* txtAcir;

	SDL_Color colorSpo2;
	SDL_Color colorBpm;
	SDL_Color colorAcr;
	SDL_Color colorAcir;
	SDL_Color colorFondEcran;
	SDL_Color colorFondEcranAlarme;

	Button alarmeBas;
	Button alarmeHaut;

	int statusAlarme;
	int easterStatus;
	bool displayACvalues;
};
typedef struct Fenetre Fenetre;

int initFenetre(Fenetre* fenetre, bool displayACvalues);
void deleteFenetre(Fenetre* fenetre);
void clearFenetre(Fenetre* fenetre);
void drawCourbe(Fenetre* fenetre, int numCourbe, DataBuffer* dataBuffer, int offsetOrigin);
void drawValeurs(Fenetre* fenetre, SDL_Surface* label, int valeur, char* txt, SDL_Color couleur, int num);
void updFenetreTitre(Fenetre* fenetre);
void doSomeMagic(Fenetre* fenetre);
void updEasterState(Fenetre* fenetre, SDL_Event* event, int op);

#endif //IHM_FENETRE_H
