#include <stdlib.h>
#include "raylib.h"
#include <console.h>

void UpdateDrawFrame(void);
int main()
{

    // int screenWidth = 800;
    // int screenHeight = 450;
    // InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // SetTargetFPS(60);
    // while (!WindowShouldClose())
    // {
    //     UpdateDrawFrame();
    // }

    // CloseWindow();

    show_name();
    show_city();
    return EXIT_SUCCESS;
}
void UpdateDrawFrame(void)
{

    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
    //----------------------------------------------------------------------------------
}