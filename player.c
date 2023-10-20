#include <stdio.h>
#include <raylib.h>

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE  "Music Player"

#define BACKGROUND_COLOR   BLACK
#define TEXT_COLOR         WHITE

#define BUTTON_COLOR       GRAY
#define BUTTON_HOVER_COLOR LIGHTGRAY
#define BUTTON_TEXT_SIZE   10.0
#define BUTTON_TEXT_COLOR  DARKGRAY
#define BUTTON_MARGIN      5

typedef struct
{
    Rectangle rectangle;
    Color color;
    const char* text;
} Button;

//typedef struct
//{
//    Button* list;
//    int quantity;
//    int capacity;
//
//} Button_List;

void draw_button(Button* botao)
{
    int textSize = MeasureText(botao->text, BUTTON_TEXT_SIZE);
    botao->rectangle.width = textSize + 2*BUTTON_MARGIN;
    botao->rectangle.height = BUTTON_TEXT_SIZE + 2*BUTTON_MARGIN;
    DrawRectangleRec(botao->rectangle, botao->color);
    DrawText(botao->text, botao->rectangle.x+BUTTON_MARGIN, botao->rectangle.y+BUTTON_MARGIN, BUTTON_TEXT_SIZE, BUTTON_TEXT_COLOR);
}

int main(void)
{
    // Inicializando
    InitAudioDevice();
    SetMasterVolume(0.2);
    Music music = LoadMusicStream("./music.mp3");
    PlayMusicStream(music);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Definindo componentes gráficos da janela
    Button botao_abrir_arquivo = {{ 10, 10, 50, 20 }, BUTTON_COLOR, "Abrir arquivo"};
    Button botao_sair= {{ 750, 550, 50, 20 }, BUTTON_COLOR, "Sair"};

    // main loop
    while (!WindowShouldClose())
    {
        // ------- Atualizando -------------
        UpdateMusicStream(music);
        Vector2 mouse_pos = GetMousePosition();

        botao_abrir_arquivo.color = BUTTON_COLOR;
        if(CheckCollisionPointRec(mouse_pos, botao_abrir_arquivo.rectangle))
        {
            botao_abrir_arquivo.color = BUTTON_HOVER_COLOR;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                // TODO: abrir janela com caixa de texto para digitar path do arquivo de musica
                botao_abrir_arquivo.color = BLUE;
            }
        }


        // ------- Desenhando -------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            draw_button(&botao_abrir_arquivo);
            draw_button(&botao_sair);
            if(IsKeyDown(KEY_Q))
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
