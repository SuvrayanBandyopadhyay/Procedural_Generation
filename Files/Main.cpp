
#include"MapGen.h"
#include<iomanip>
#include<fstream>
#include<Windows.h>

using namespace std;
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{

 
  
    /*
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("WINDOW", 380, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;*/
    int n = 7;
    vector<vector<double>> a = gen_map(n);
    
    a = normalize(a);

  
    vector<vector<double>> b = gen_map(n);
    
    b = normalize(b);

    a = mergemap(a, b, 10, 0);
    cout << a.size() << endl;
    
    a = normalize(a);
    cout << a.size() << "," << a[0].size() << endl;
    display(a);
   

 





    system("PAUSE");
}