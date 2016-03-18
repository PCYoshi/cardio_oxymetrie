//
// Created by joseph on 16/03/16.
//

#include <stdio.h>
#include <stdlib.h>

#include "fenetre.h"

int initFenetre(Fenetre* fenetre)
{
	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		puts("Erreur chargement SDL.");
		return -1;
	}

	putenv("SDL_VIDEO_CENTERED=1");
	fenetre->screen = SDL_SetVideoMode(FENETRE_LARGEUR, FENETRE_HAUTEUR, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(fenetre->screen == NULL)
	{
		puts("Erreur création fenetre.");
	}

	SDL_WM_SetCaption("Oxymètre de pouls", NULL);

	if(TTF_Init() == -1)
	{
		puts("Erreur chargement SDL_ttf.");
		return -1;
	}

	fenetre->font = TTF_OpenFont("Instruction.otf", 40);
	if(fenetre->font == NULL)
	{
		puts("Erreur chargement police Instruction.otf.");
		return -1;
	}

	fenetre->colorSpo2.r = COULEUR_SPO2_R;
	fenetre->colorSpo2.g = COULEUR_SPO2_V;
	fenetre->colorSpo2.b = COULEUR_SPO2_B;

	fenetre->colorBpm.r = COULEUR_BPM_R;
	fenetre->colorBpm.g = COULEUR_BPM_V;
	fenetre->colorBpm.b = COULEUR_BPM_B;

	fenetre->colorAcr.r = COULEUR_ACR_R;
	fenetre->colorAcr.g = COULEUR_ACR_V;
	fenetre->colorAcr.b = COULEUR_ACR_B;

	fenetre->colorAcir.r = COULEUR_ACIR_R;
	fenetre->colorAcir.g = COULEUR_ACIR_V;
	fenetre->colorAcir.b = COULEUR_ACIR_B;

	fenetre->colorFondEcran.r = COULEUR_FOND_ECRAN_R;
	fenetre->colorFondEcran.g = COULEUR_FOND_ECRAN_V;
	fenetre->colorFondEcran.b = COULEUR_FOND_ECRAN_B;

	fenetre->txtSpo2 = TTF_RenderText_Shaded(fenetre->font, "SPO2", fenetre->colorSpo2, fenetre->colorFondEcran);
	fenetre->txtBpm = TTF_RenderText_Shaded(fenetre->font, "BPM", fenetre->colorBpm, fenetre->colorFondEcran);
	fenetre->txtAcr = TTF_RenderText_Shaded(fenetre->font, "AC-R", fenetre->colorAcr, fenetre->colorFondEcran);
	fenetre->txtAcir = TTF_RenderText_Shaded(fenetre->font, "AC-IR", fenetre->colorAcir, fenetre->colorFondEcran);

	fenetre->pxSPO2 = SDL_CreateRGBSurface(SDL_HWSURFACE, POINT_LARGEUR, POINT_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->pxBPM = SDL_CreateRGBSurface(SDL_HWSURFACE, POINT_LARGEUR, POINT_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->pxACR = SDL_CreateRGBSurface(SDL_HWSURFACE, POINT_LARGEUR, POINT_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->pxACIR = SDL_CreateRGBSurface(SDL_HWSURFACE, POINT_LARGEUR, POINT_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->bgCourbe = SDL_CreateRGBSurface(SDL_HWSURFACE, COURBE_LONGUEUR, COURBE_HAUTEUR, 32, 0, 0, 0, 0);
	fenetre->zeroCourbe = SDL_CreateRGBSurface(SDL_HWSURFACE, COURBE_LONGUEUR, 1, 32, 0, 0, 0, 0);

	SDL_FillRect(fenetre->pxSPO2, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_SPO2));
	SDL_FillRect(fenetre->pxBPM, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_BPM));
	SDL_FillRect(fenetre->pxACR, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ACR));
	SDL_FillRect(fenetre->pxACIR, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ACIR));
	SDL_FillRect(fenetre->bgCourbe, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_FOND_COURBE));
	SDL_FillRect(fenetre->zeroCourbe, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_ZERO_COURBE));

	return 0;
}

void deleteFenetre(Fenetre* fenetre)
{
	TTF_CloseFont(fenetre->font);
	TTF_Quit();
	SDL_FreeSurface(fenetre->pxSPO2);
	SDL_FreeSurface(fenetre->pxBPM);
	SDL_FreeSurface(fenetre->pxACR);
	SDL_FreeSurface(fenetre->pxACIR);
	SDL_FreeSurface(fenetre->bgCourbe);
	SDL_FreeSurface(fenetre->zeroCourbe);
	SDL_FreeSurface(fenetre->txtSpo2);
	SDL_FreeSurface(fenetre->txtBpm);
	SDL_FreeSurface(fenetre->txtAcr);
	SDL_FreeSurface(fenetre->txtAcir);
	SDL_Quit();
}

void clearFenetre(Fenetre* fenetre)
{
	SDL_FillRect(fenetre->screen, NULL, SDL_MapRGB(fenetre->screen->format, COULEUR_FOND_ECRAN));

	SDL_Rect pos;
	pos.x = COURBE_OFFSET_X;
	pos.y = COURBE_OFFSET_Y / 2;

	for(int i = 0; i < 4; i++)
	{
		SDL_BlitSurface(fenetre->bgCourbe, NULL, fenetre->screen, &pos);
		pos.y += COURBE_HAUTEUR / 2;
		SDL_BlitSurface(fenetre->zeroCourbe, NULL, fenetre->screen, &pos);
		pos.y += COURBE_HAUTEUR / 2 + COURBE_OFFSET_Y;
	}
}

void drawCourbe(Fenetre* fenetre, int numCourbe, DataBuffer* dataBuffer)
{
	SDL_Rect pos;
	pos.x = COURBE_OFFSET_X;
	int y = (COURBE_OFFSET_Y + COURBE_HAUTEUR) * ( 0.5 + numCourbe-1);

	SDL_Surface* px = NULL;
	float coeff = 0;

	switch(numCourbe)
	{
		case 1:
			px = fenetre->pxSPO2;
			coeff = COEFF_BPM;
			break;
		case 2:
			px = fenetre->pxBPM;
			coeff = COEFF_BPM;
			break;
		case 3:
			px = fenetre->pxACR;
			coeff = COEFF_ACR;
			break;
		case 4:
			px = fenetre->pxACIR;
			coeff = COEFF_ACIR;
			break;
	}

	for(int i = 0; i < COURBE_LONGUEUR; i++)
	{
		pos.y = y - atBuffer(dataBuffer, i) * coeff;
		SDL_BlitSurface(px, NULL, fenetre->screen, &pos);
		pos.x++;
	}
}

void drawValeurs(Fenetre* fenetre, SDL_Surface* label, int valeur, char* txt, SDL_Color couleur, int num)
{
	SDL_Surface* valeurSurface = NULL;
	SDL_Rect pos;
	char string[4];

	pos.x = TEXTE_OFFSET_X - label->w / 2;
	pos.y = (COURBE_HAUTEUR + COURBE_OFFSET_Y) * (0.5 + num-1) - label->h / 2 - TEXTE_GAP_Y / 2;
	SDL_BlitSurface(label, NULL, fenetre->screen, &pos);

	sprintf(string, txt, valeur);
	valeurSurface = TTF_RenderText_Shaded(fenetre->font, string, couleur, fenetre->colorFondEcran);
	pos.x = TEXTE_OFFSET_X - valeurSurface->w / 2;
	pos.y = (COURBE_HAUTEUR + COURBE_OFFSET_Y) * (0.5 + num-1) - valeurSurface->h / 2 + TEXTE_GAP_Y / 2;
	SDL_BlitSurface(valeurSurface, NULL, fenetre->screen, &pos);
	SDL_FreeSurface(valeurSurface);
}