#include<raylib.h>
#include<iostream>
using namespace std;

// This function is used to map a number
float map(float value, float fromMin, float fromMax, float toMin, float toMax) {
    // Ensure that the value is within the input range
    value = min(max(value, fromMin), fromMax);
    return (value - fromMin) / (fromMax - fromMin) * (toMax - toMin) + toMin;
}

int is_in_set(float a, float b){
	// This is value of z
	float x = a;
	float y = b;
	for(int i=0;i<100;i++){
		float xx = x*x-y*y-0.835f;  // This constant is real part of julia set
		float yy = 2*x*y-0.831f;    // This constant is imaginary part of julia set

		x = xx;
	  y = yy;

		if(abs(x + y) >= 10.0f){
			return i;
		}
	}
	return 255;
}

// This function is used to create array of pixels which contains Mandelbrot Set
Texture2D getMandelSetTexture(int width, int height, float zoom, float lr, float ud){
	RenderTexture2D canvas = LoadRenderTexture(width, height);
	BeginTextureMode(canvas);
		for(int i=0;i<width;i++){
			for(int j=0;j<height;j++){

				// This is value of c
				float a = map(i, 0, width, (-2+(lr))+zoom, (1+(lr))-zoom); // real part
        float b = map(j, 0, height, (-2+(ud))+zoom, (1+(ud))-zoom);	// imaginary part

				int n = is_in_set(a, b);
				n = map(n, 0, 99, 0, 255);

				// n = map(n, 0, 100, 0, 256); // this mapping gives different border effect.
				// Coloring Pixels

				Color pixelColor = {(unsigned char)n, (unsigned char)n, (unsigned char)n, 255};
        //Color pixelColor = ColorFromHSV(n, 1.0f, 1.0f);
				DrawPixel(i,j,pixelColor);
			}
		}
	EndTextureMode();
	return canvas.texture;
}

int main(){
	int windowWidth = 900;
	int windowHeight = 900; 
	InitWindow(windowWidth, windowHeight,"Julia Set");

	// Variables
	float zoom = -0.5f;
	float lr = 0.6f;
	float ud = 0.3f;
	Texture2D texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);

	while(!WindowShouldClose()){
		BeginDrawing();
  		ClearBackground(WHITE);

			// Click events
			// Zoom In and OUT
			if(IsKeyPressed(KEY_A)){
				// Zooming
				zoom+=0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}
			if(IsKeyPressed(KEY_S)){
				// Unzooming
				zoom-=0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}
			// LEFT and RIGHT
			if(IsKeyPressed(KEY_LEFT)){
				lr -= 0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}
			if(IsKeyPressed(KEY_RIGHT)){
				lr += 0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}
			// UP and DOWN
			if(IsKeyPressed(KEY_UP)){
				ud -= 0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}
			if(IsKeyPressed(KEY_DOWN)){
				ud += 0.1f;
				texture = getMandelSetTexture(windowWidth, windowHeight, zoom, lr, ud);
			}


			DrawTexture(texture, 0,0, WHITE);
			DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 10, BLACK);
			DrawText(TextFormat("ZOOM: %0.2f", zoom), 10, 20, 10, BLACK);
			DrawText(TextFormat("L-R: %0.2f", lr), 10, 30, 10, BLACK);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
