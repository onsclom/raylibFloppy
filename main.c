#include <stdio.h>
#include <raylib.h>

#define WIDTH 1000
#define HEIGHT 800
#define GRAVITY 4.0f
#define FLAPSTRENGTH 1.5f

struct Bird {
	float x;
	float y;
	float yVel;
};

int main() {
	InitWindow(WIDTH,HEIGHT,"floppy");
	Texture2D birdSheet = LoadTexture("art/bird-sheet.png");

	int gameStarted = 0;
	double lastTime = 0;
	double birdTime = 0;
	int birdFrame = 0;
	float birdFlapSpeed = .5;

	struct Bird bird = {100.0f, 100.0f, 0.0f};

	Rectangle frameRec = { birdSheet.width/2.0*birdFrame, 0.0f, birdSheet.width/2, birdSheet.height };
	Rectangle destRec = {0,0,frameRec.width*16, frameRec.height*16};
	Color bgColor = {0x20,0x28,0x3d,0xff};
	printf("hi world\n");

	while (!WindowShouldClose())
	{
		/* ============ */
		/* ==UPDATING== */
		/* ============ */
		double curTime = GetTime();
		double delta =  curTime - lastTime;

		/* bird animation */
		birdTime += delta;
		if (birdTime > birdFlapSpeed) {
			birdTime -= birdFlapSpeed;
		}
		birdFrame = 1;
		if (birdTime > birdFlapSpeed/2.0) {
			birdFrame = 0;
		}


		/* bird physics */
		if (gameStarted)
			bird.yVel += GRAVITY*delta;

		if (IsKeyPressed(KEY_SPACE)) {
			gameStarted = 1;
			bird.yVel = -FLAPSTRENGTH;
		}

		bird.y += bird.yVel;
		destRec.x = bird.x;
		destRec.y = bird.y;

		double angle = bird.yVel * 10;

		lastTime = curTime;

		/* =========== */
		/* ==DRAWING== */
		/* =========== */
		BeginDrawing();
			ClearBackground(bgColor);
			frameRec.x = birdSheet.width/2 * birdFrame;

			Vector2 origin = {destRec.width/2.0f,
												 destRec.height/2.0f};
			DrawTexturePro(birdSheet, frameRec, destRec, origin, angle, WHITE);

			char *fpsString[10];
			sprintf(fpsString, "FPS: %d", GetFPS());
			DrawText(fpsString,5,5,64,WHITE);
		EndDrawing();
	}

	/* De-initialize */
	UnloadTexture(birdSheet);
	CloseWindow();

	return 0;
}
