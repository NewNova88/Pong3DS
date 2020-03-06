#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <3ds.h>
#include <citro2d.h>
#include <assert.h>

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
	Paddle paddle;
	C2D_SpriteSheet sprsht;
	C3D_RenderTarget* top;

	unsigned int j1 = 0;
	unsigned int hiScore = 0;
	bool isPaused = true;

	init(&ball, &paddle, &sprsht, &top);

	while(aptMainLoop())
	{
		hidScanInput();

		if(isPaused)
		{
			if(hidKeysDown() & KEY_START)
			{
				isPaused = false;
				consoleClear();
			}
			else if(hidKeysDown() & KEY_SELECT)
			{
				printf("Quiting...");
				break;
			}
		}
		else
		{
			if(hidKeysDown() & KEY_START){
				isPaused = true;
			}
			else if(hidKeysDown() & KEY_SELECT)
			{
				printf("Quiting...");
				break;
			}
			else if(hidKeysDown() & KEY_L)
			{
				paddle.v+=1;
				if(paddle.v == 7)
					paddle.v = 1;
			}
			else if(hidKeysHeld() & KEY_UP){
				if(paddle.sprite.params.pos.y > SCREEN_HEIGHT-(paddle.sprite.params.pos.h / 2.0f) || (paddle.sprite.params.pos.y > paddle.sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle.sprite, 0, -paddle.v);
			}
			else if(hidKeysHeld() & KEY_DOWN){
				if(paddle.sprite.params.pos.y < SCREEN_HEIGHT-(paddle.sprite.params.pos.h / 2.0f) || (paddle.sprite.params.pos.y < paddle.sprite.params.pos.h / 2.0f))
					C2D_SpriteMove(&paddle.sprite, 0, paddle.v);
			}


			if(ball.sprite.params.pos.y-2.0f <= 0+1.0f || ball.sprite.params.pos.y+2.0f >= SCREEN_HEIGHT-1.0f)
				ball.dy = -ball.dy;

			else if(ball.sprite.params.pos.x+2.0f == SCREEN_WIDTH)
			{
				ball.dx = -ball.dx;
				j1++;
			}
			else if(ball.sprite.params.pos.x-2.0f == paddle.sprite.params.pos.x+1.0f)
			{
					if(((ball.sprite.params.pos.y +2.0f > paddle.sprite.params.pos.y -20.0f) && (ball.sprite.params.pos.y-2.0f < paddle.sprite.params.pos.y +20.0f)))
					{
						if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.x - 15.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y -12.0f))
						{
							ball.dy = -1.9f;
						}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.y + 12.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y + 15.0f))
						{
							ball.dy = 1.9f;
						}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.y - 11.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y -8.0f))
						{
							ball.dy = -1.6f;
						}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.y + 8.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y + 11.0f))
						{
							ball.dy = 1.6f;
						}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.y - 7.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y -4.0f))
						{
							ball.dy = -1.3f;

						}
						else if((ball.sprite.params.pos.y + 2.0f >= paddle.sprite.params.pos.y + 4.0f && ball.sprite.params.pos.y - 2.0f <= paddle.sprite.params.pos.y + 7.0f))
						{
							ball.dy = 1.3f;
						}
						ball.dx = -ball.dx;
					}
					else
					{
						C2D_SpriteSetPos(&ball.sprite, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f);
						C2D_SpriteSetPos(&paddle.sprite, 4, SCREEN_HEIGHT/2.0f);
						j1 = 0;
						ball.dy = 1;
						isPaused=true;

					}
			}

			C2D_SpriteMove(&ball.sprite, ball.dx, ball.dy);

			if(j1 > hiScore)
				hiScore = j1;
			printf("\x1b[1;0HScore j1 = %d\nHi-Score = %d\npaddle.v = %d\nPosition balle X = %f\nPosition balle Y = %f\nSpeedBallX = %f\nSpeedBallY = %f\n\nCPU : %f\nGPU : %f\n",
			j1, hiScore, paddle.v, ball.sprite.params.pos.x, ball.sprite.params.pos.y, ball.dx, ball.dy, C3D_GetProcessingTime()*6.0f, C3D_GetDrawingTime()*6.0f);
		}

		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f));
		C2D_SceneBegin(top);
		C2D_DrawSprite(&ball.sprite);
		C2D_DrawSprite(&paddle.sprite);
		C3D_FrameEnd(0);
		C2D_Flush();

	}
	C2D_SpriteSheetFree(sprsht);
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	romfsExit();
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

	C2D_SpriteFromSheet(&paddle->sprite, *sprsht, 1);
	C2D_SpriteSetCenter(&paddle->sprite, 0.5f, 0.5f);
	C2D_SpriteSetPos(&paddle->sprite, 4, SCREEN_HEIGHT/2.0f);


	ball->dx = 1.0f;
	ball->dy = 1.0f;

	paddle->v = 3;

	printf("\x1b[1;0HPRESS START");


}
