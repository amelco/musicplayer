#include <string.h>
#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Music Player"

#define BACKGROUND_COLOR   BLACK
#define TEXT_COLOR         GRAY
#define TEXT_SIZE          20.0

#define BUTTON_COLOR       GRAY
#define BUTTON_HOVER_COLOR LIGHTGRAY
#define BUTTON_TEXT_SIZE   10.0
#define BUTTON_TEXT_COLOR  DARKGRAY
#define BUTTON_MARGIN      5

// UI elements
typedef struct
{
    Rectangle rectangle;
    Color color;
    const char* text;
} Button;

void draw_button(Button* botao)
{
    int textSize = MeasureText(botao->text, BUTTON_TEXT_SIZE);
    botao->rectangle.width = textSize + 2*BUTTON_MARGIN;
    botao->rectangle.height = BUTTON_TEXT_SIZE + 2*BUTTON_MARGIN;
    DrawRectangleRec(botao->rectangle, botao->color);
    DrawText(botao->text, botao->rectangle.x+BUTTON_MARGIN, botao->rectangle.y+BUTTON_MARGIN, BUTTON_TEXT_SIZE, BUTTON_TEXT_COLOR);
}

bool isButtonHovered(Button* botao)
{
    botao->color = BUTTON_COLOR;
    Vector2 mouse_pos = GetMousePosition();
    bool isHovered = CheckCollisionPointRec(mouse_pos, botao->rectangle);
    if(isHovered)
    {
        botao->color = BUTTON_HOVER_COLOR;
    }
    return isHovered;
}


int main(void)
{
    // Inicializando
    InitAudioDevice();
    SetMasterVolume(0.5);
    Music musica = {0};

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Definindo componentes gráficos da janela
    Button botao_sair = {{ WINDOW_WIDTH-50, WINDOW_HEIGHT-40, 50, 20 }, BUTTON_COLOR, "Close"};

    // TODO: persistir o estado da aplicação em uma estrutura
    char music_name[256] = {'\0'};
    bool music_loaded = false;
    bool music_playing = false;

    // main loop
    while (!WindowShouldClose())
    {
        // ------- Atualizando -------------
        if ( (isButtonHovered(&botao_sair) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) || IsKeyPressed(KEY_Q) )
        {
            break;  // exits main loop
        }
        if (IsKeyPressed(KEY_SPACE))
        {
            if (music_playing)
            {
                PauseMusicStream(musica);
                music_playing = false;
            }
            else
            {
                ResumeMusicStream(musica);
                music_playing = true;
            }
        }

        if (IsFileDropped())
        {
            FilePathList paths = LoadDroppedFiles();
            // printf("File dropped: %s\n", paths.paths[0]);
            strcpy(music_name, GetFileName(paths.paths[0]));
            musica = LoadMusicStream(paths.paths[0]);
            music_loaded = true;
            PlayMusicStream(musica);
            music_playing = true;
            UnloadDroppedFiles(paths);
        }
        if (music_loaded)
        {
            UpdateMusicStream(musica);
        }

        // ------- Desenhando -------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            draw_button(&botao_sair);

            DrawText("Drop music file here", 10, WINDOW_HEIGHT/2-30, TEXT_SIZE, BUTTON_TEXT_COLOR);
            if (music_loaded) DrawText("Press SPACE to play/pause", 10, WINDOW_HEIGHT/2, TEXT_SIZE/2., BUTTON_TEXT_COLOR);
            DrawText("Press Q to close", 10, WINDOW_HEIGHT/2+20, TEXT_SIZE/2., BUTTON_TEXT_COLOR);

            if (music_loaded)
            {
                // draw music length and amount played
                DrawText(music_name, 10, 10, 10, BUTTON_TEXT_COLOR);
                char total_time[100] = {'\0'};
                int music_time = GetMusicTimeLength(musica);
                int played_time = GetMusicTimePlayed(musica);
                sprintf(total_time, "Duration: %02d:%02d / %02d:%02d", played_time/60, played_time%60, music_time/60, music_time%60);
                int text_size = MeasureText(total_time, TEXT_SIZE/2.);
                DrawText(total_time, WINDOW_WIDTH/2.-text_size/2., WINDOW_HEIGHT-60, TEXT_SIZE/2., TEXT_COLOR);
            }

        }
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
