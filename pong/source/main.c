/*
	Logiciel : PONG3DS
	Type : Jeu
	Version : 1.2
	Auteur : Pierre Barbillon
	Bibliothèque : devkitpro 3ds
	Description :
		Ce jeu a été créé dans le cadre du projet tutoré 4.
		C'est une sorte d'adaptation de pong. Ce n'est qu'un proof-of-concept.
		Le jeu sera probablement amélioré.
		Dans la version présente, il n'y a qu'un mode 2 joueurs sur la même console.
		Le joueur 1 contrôle la raquette de gauche avec la croix directionnelle ou le stick analogique.
		Le joueur 2 contrôle la raquette de droite avec les boutons X et B.
		La vitesse du joueur 1 peut aller de 1 à 6, et s'augmente en appuyant sur la touche L.
		La vitesse du joueur 2 peut aller de 1 à 6 et s'augmente en appuyant sur la touche R.

	Bug connus :
		Dans un cas très spécifique, la balle peut longer le haut ou le bas de l'écran.
		C'est peut-être dû à la façon dont sont gêrées les collisions.
		La façon d'engendrer le bug est très difficile.
		Il faudrait que la balle atteigne un coin de l'écran et que la raquette du joueur en question la touche.
		Le bug est mineur, et arrive rarement.

	Remerciements :
		Je remercie les développeurs experts du Discord officiel du HomeBrew Launcher pour m'avoir aidé à résoudre les différents problèmes.
		Je remercie également l'équipe de DevKitPro qui a créé cette bibliothèque OpenSource et libre.

*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include <assert.h>
/*
	Taille de l'écran
*/
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

typedef struct Ball {
	float dx, dy;
	C2D_Sprite sprite;
} Ball;

typedef struct Paddle {
  int v;
	C2D_Sprite sprite;
} Paddle;

void init(Ball *ball, Paddle *paddle, C2D_SpriteSheet *sprsht, C3D_RenderTarget* *top);

int main(int argc, char* argv[])
{
	Ball ball;
	Paddle paddle[2];
	C2D_SpriteSheet sprsht;
	C3D_RenderTarget* top;
	init(&ball, paddle, &sprsht, &top);

	int j1 = 0; //Points du joueur 1
	int j2 = 0; //Point du joueur 2
	bool isPaused = true; //Permet de vérifier si le jeu est mis en pause (mis à true pour pouvoir commencer quand tout le monde est prêt)

	/*
		Boucle de jeu principale géré par la fonction aptMainLoop()
	*/
	while(aptMainLoop())
	{
		hidScanInput(); //On scanne les boutons appuyés à chaque passage de boucle

		/*
			Lorsque le jeu est en pause
		*/
		if(isPaused)
		{
			if(hidKeysDown() & KEY_START) //Si le bouton START est appuyé
			{
				isPaused = false; //Le jeu n'est plus en pause
				consoleClear(); //On efface la console pour les messages suivants
			}
			else if(hidKeysDown() & KEY_SELECT) //Si le bouton SELECT est appuyé
			{
				printf("Quiting..."); //On écrit qu'on quitte le jeu
				break; //Quitte le jeu et reviens au HomeBrew Launcher
			}
		}
		else //Si le jeu n'est pas en pause
		{
			if(hidKeysDown() & KEY_START){ //Si le bouton START est appuyé
				isPaused = true; //Le jeu se met en pause
			}
			else if(hidKeysDown() & KEY_SELECT) //Si le bouton SELECT est appuyé
			{
				printf("Quiting..."); //On écrit qu'on quitte le jeu
				break; //Quitte le jeu et reviens au HomeBrew Launcher
			}
			else if(hidKeysDown() & KEY_R) //Si le bouton R est appuyé
			{
				paddle[1].v+=1; //On augmente la vitesse de déplacement du joueur 2 de 1
				if(paddle[1].v == 7) //Si la vitesse du joueur 2 est égale à 7
					paddle[1].v = 1; //On remet la vitesse du joueur 2 à 1
			}
			else if(hidKeysDown() & KEY_L) //Si le bouton L est appuyé
			{
				paddle[0].v+=1; //On augmente la vitesse de déplacement du joueur 1 de 1
				if(paddle[0].v == 7) //Si la vitesse du joueur 1 est égale à 7
					paddle[0].v = 1; //On remet la vitesse du joueur 1 à 1
			}
			/*
				Déplacements du joueur 1
			*/
			else if(hidKeysHeld() & KEY_UP){ //Si la touche directionnelle haut est maintenue (ou le pad analogique gauche est vers le haut)
				/*
					Si le haut du sprite du J1 est inférieur au haut de l'écran
					 ou que le bas du sprite du J1 est supérieur au bas de l'écran
				*/
				if(paddle[0].sprite.params.pos.y > SCREEN_HEIGHT-(paddle[0].sprite.params.pos.h / 2.0f)
					|| (paddle[0].sprite.params.pos.y > paddle[0].sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle[0].sprite, 0, -paddle[0].v); //On bouge le sprite vers le haut
			}
			else if(hidKeysHeld() & KEY_DOWN){ //Si la touche directionnelle bas est maintenue (ou le pad analogique gauche est vers le bas)
				/*
					Si le haut du sprite du J1 est inférieur au haut de l'écran
					 ou que le bas du sprite du J1 est supérieur au bas de l'écran
				*/
				if(paddle[0].sprite.params.pos.y < SCREEN_HEIGHT-(paddle[0].sprite.params.pos.h / 2.0f)
					|| (paddle[0].sprite.params.pos.y < paddle[0].sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle[0].sprite, 0, paddle[0].v); //On bouge le sprite vers le bas
			}
			/*
				Déplacements du joueur 2
			*/
			if(hidKeysHeld() & KEY_X) //Si la touche X est maintenue
				/*
					Si le haut du sprite du J2 est inférieur au haut de l'écran
					 ou que le bas du sprite du J2 est supérieur au bas de l'écran
				*/
				if(paddle[1].sprite.params.pos.y>SCREEN_HEIGHT-(paddle[1].sprite.params.pos.h / 2.0f)
					|| (paddle[1].sprite.params.pos.y>paddle[1].sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle[1].sprite, 0, -paddle[1].v); //On bouge le sprite vers le haut
			if(hidKeysHeld() & KEY_B) //Si la touche B est maintenue
				/*
					Si le haut du sprite du J2 est inférieur au haut de l'écran
					 ou que le bas du sprite du J2 est supérieur au bas de l'écran
				*/
				if(paddle[1].sprite.params.pos.y<SCREEN_HEIGHT-(paddle[1].sprite.params.pos.h / 2.0f)
					|| (paddle[1].sprite.params.pos.y<paddle[1].sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle[1].sprite, 0, paddle[1].v); //On bouge le sprite vers le bas

			/*
				Gestion des collisions des joueurs
			*/
			for(int i=1; i>=0; i--)
			{
				//Si la coordonnée X de la balle est inférieure à celle du joueur
				if((i==1 && (ball.sprite.params.pos.x < paddle[i].sprite.params.pos.x)) || (i==0 && (ball.sprite.params.pos.x > paddle[i].sprite.params.pos.x)))
					C2D_SpriteMove(&ball.sprite, ball.dx, ball.dy); //On bouge le sprite aux vitesses X et Y (en pixel)
				//Sinon si la coordonnée X de la balle est égale à celle du joueur
				else if(ball.sprite.params.pos.x == paddle[i].sprite.params.pos.x)
				{
					//Si les coordonnées Y de la balle se situent entre le haut et le bas du sprite
					if(((ball.sprite.params.pos.y +2.0f > paddle[i].sprite.params.pos.y -20.0f)
					&& (ball.sprite.params.pos.y-2.0f < paddle[i].sprite.params.pos.y +20.0f)))
					{
						/*
							Les collisions sont gêrées comme la version ATARI 2600 de pong
						*/
						//Si la balle touche le bout extrême haut de la barre du joueur
						if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y - 15.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y -12.0f))
							{
								ball.dy = -1.9f; //La "vitesse" de la balle est augmentée et la direction de la balle est mise vers le haut
							}
						//Si la balle touche le bout extrême bas de la barre du joueur
						else if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y + 12.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y + 15.0f))
							{
								ball.dy = 1.9f; //La "vitesse" de la balle est augmentée et la direction de la balle est mise vers le bas
							}
						//Et ainsi de suite par rapport au centre
						else if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y - 11.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y -8.0f))
							{
								ball.dy = -1.6f;
							}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y + 8.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y + 11.0f))
							{
								ball.dy = 1.6f;
							}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y - 7.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y -4.0f))
							{
								ball.dy = -1.3f;

							}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle[i].sprite.params.pos.y + 4.0f
							&& ball.sprite.params.pos.y - 2.0f <= paddle[i].sprite.params.pos.y + 7.0f))
							{
								ball.dy = 1.3f;
							}

						ball.dx = -ball.dx; //On change la direction de la balle

					}
				}
				//Sinon, si les coordonnées X de la balle sont supérieures à la droite ou la gauche de l'écran
				else
				{
					if(ball.sprite.params.pos.x+2.0f >=SCREEN_WIDTH)
					{
						C2D_SpriteSetPos(&ball.sprite, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f); //On reset la position de la balle au centre de l'écran
						ball.dx = -ball.dx; //On change la direction de la balle
						j1++; //Comme ici, la droite de l'écran correspond au J2, c'est la J1 qui a gagné donc on incrémente le nombre de points du J1 de 1
						ball.dy = 1; //La vitesse de la balle est remise à deux et sa direction est vers le bas
					}
					else if(ball.sprite.params.pos.x-2.0f <= 0)
					{
						C2D_SpriteSetPos(&ball.sprite, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
						ball.dx = -ball.dx;
						j2++;
						ball.dy = 1;
					}
				}
			}

			if(ball.sprite.params.pos.y-2.0f < 0 || ball.sprite.params.pos.y+2.0f > SCREEN_HEIGHT) //Si la balle touche le haut ou le bas de l'écran
				ball.dy = -ball.dy; //On change la direction de la balle (mais pas la vitesse)

			/*
				Affichage des scores du J1 et du J2, des vitesses de déplacement des joueurs, des coordonnées de la balle (temps réel)
				et de la vitesse Y de la balle (pour vérifier les changements de vitesse lors de la collision de la balle avec les joueurs)
			*/
			printf("\x1b[1;0HScore j1 = %d\nScore j2 = %d\npaddle[0].v = %d\npaddle[1].v = %d\nPosition balle X = %f\nPosition balle Y = %f\nSpeedBallX = %f\nSpeedBallY = %f\n\nCPU : %f\nGPU : %f\n", j1, j2, paddle[0].v, paddle[1].v, ball.sprite.params.pos.x, ball.sprite.params.pos.y, ball.dx, ball.dy, C3D_GetProcessingTime()*6.0f, C3D_GetDrawingTime()*6.0f);

			/*
				Comportement lors de la victoire du joueur 1
			*/
			if(j1==15){ //Si le joueur 1 a 15 points
				consoleClear(); //On efface la console pour afficher les nouveaux messages
				printf("j1 win\n"); //On affiche que le joueur 1 a gagné
				printf("Press START to replay, press SELECT to quit"); //On indique quel boutons pour continuer ou pour quitter le jeu
				j1 = 0; //Les points du joueur 1 sont mis à 0
				j2 = 0; //Les points du joueur 2 sont mis à 0
				//On réinitialise la vitesse de la balle
				ball.dy = 1;
				ball.dx = -1; //Ici on met la direction X de la balle vers la gauche
				isPaused = true; //On met le jeu en pause
				C2D_SpriteSetPos(&paddle[0].sprite, 4, SCREEN_HEIGHT/2.0f); //On reset la position du J1
				C2D_SpriteSetPos(&paddle[1].sprite, SCREEN_WIDTH-4.0f, SCREEN_HEIGHT/2.0f); //On reset la position du J2
			}
			/*
				Comportement lors de la victoire du joueur 2
				Très similaire à celle du joueur 1.
			*/
			else if(j2==15){
				consoleClear();
				printf("j2 win\n");
				printf("Press START to replay, press SELECT to quit");
				j1 = 0;
				j2 = 0;
				ball.dy = 1;
				ball.dx = 1; //Ici on met la direction X de la balle vers la droite
				isPaused = true;
				C2D_SpriteSetPos(&paddle[0].sprite, 4, SCREEN_HEIGHT/2.0f);
				C2D_SpriteSetPos(&paddle[1].sprite, SCREEN_WIDTH-4.0f, SCREEN_HEIGHT/2.0f);
			}
			C3D_FrameBegin(C3D_FRAME_SYNCDRAW); //Début de la frame
			C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f)); //On efface à chaque passage de boucle l'écran du haut (évite les bug d'affichage)
			C2D_SceneBegin(top); //Le rendu 2D commence à l'écran du haut
			for(int i = 0; i < 2; ++i)
				C2D_DrawSprite(&paddle[i].sprite); //On dessine les joueurs
			C2D_DrawSprite(&ball.sprite); //On dessine la balle
			C3D_FrameEnd(0); //Fin de la frame
			C2D_Flush(); //On flush les buffers 2D
		}
	}
	/*
		Une fois la boucle de jeu terminée (lorsqu'on appuie sur SELECT pour quitter le jeu)
	*/
	C2D_SpriteSheetFree(sprsht); //Libération de la spritesheet en mémoire
	C2D_Fini(); //Déinitialisation du rendu 2D
	C3D_Fini(); //Déinitialisation du rendu 3D
	gfxExit(); //Déinitialisation du rendu graphique général et libération des écrans
	romfsExit(); //Déinitialisation et libération des data
	return 0;
}
void init(Ball *ball, Paddle *paddle, C2D_SpriteSheet *sprsht, C3D_RenderTarget* *top){

	romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	*top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);

	*sprsht = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!*sprsht) svcBreak(USERBREAK_PANIC);

	C2D_SpriteFromSheet(&ball->sprite, *sprsht, 0);
	C2D_SpriteSetCenter(&ball->sprite, 0.5f, 0.5f);
	C2D_SpriteSetPos(&ball->sprite, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);

	C2D_SpriteFromSheet(&paddle[0].sprite, *sprsht, 1);
	C2D_SpriteSetCenter(&paddle[0].sprite, 0.5f, 0.5f);
	C2D_SpriteSetPos(&paddle[0].sprite, 4, SCREEN_HEIGHT/2.0f);

	/*
		Création du joueur 2
	*/
	C2D_SpriteFromSheet(&paddle[1].sprite, *sprsht, 1); //Dans la troisième case du tableau, on charge le sprite à l'indice 1 de la spritesheet (correspond à la barre)
	C2D_SpriteSetCenter(&paddle[1].sprite, 0.5f, 0.5f); //On initialise le centre du sprite
	C2D_SpriteSetPos(&paddle[1].sprite, SCREEN_WIDTH-4.0f, SCREEN_HEIGHT/2.0f); //On le place à droite de l'écran et au milieu du y

	ball->dx = 1.0f;
	ball->dy = 1.0f;

	paddle[0].v = 3;
	paddle[1].v = 3;

	printf("\x1b[1;0HPRESS START");


}
