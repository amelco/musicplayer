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

// TODO: criar structs de um bnotao e de uma lista de botoes
//       para desenhar todos de uma vez na tela através de 
//       apenas uma função.
//typedef struct
//{
//    Vector2 pos;
//    const char* text;
//} Button;
//
//typedef struct
//{
//    Button* list;
//    int quantity;
//    int capacity;
//
//} Button_List;

void draw_button(Vector2 pos, const char* text, Color btnCollor)
{
    int textSize = MeasureText(text, BUTTON_TEXT_SIZE);
    DrawRectangle(pos.x, pos.y, textSize + 2*BUTTON_MARGIN, BUTTON_TEXT_SIZE + 2*BUTTON_MARGIN, btnCollor);
    DrawText(text, pos.x+BUTTON_MARGIN, pos.y+BUTTON_MARGIN, BUTTON_TEXT_SIZE, BUTTON_TEXT_COLOR);
}

// TODO: função para obter Rectangle de um botao
//       para user na detecção de colisão corretamente
//Rectangle get_button_rec(Button botao)
//{
//
//}


int main(void)
{
    // Inicializando
    Rectangle botao_abrir = { 10, 10, 50, 20 };
    Color botao_abrir_cor = BACKGROUND_COLOR;

    InitAudioDevice();
    SetMasterVolume(0.2);
    Music music = LoadMusicStream("./music.mp3");
    PlayMusicStream(music);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        // ------- Atualizando -------------
        UpdateMusicStream(music);
        Vector2 mouse_pos = GetMousePosition();

        botao_abrir_cor = BUTTON_COLOR;
        // TODO: pegar o Rectangle correto através da função get_button_rec()
        if(CheckCollisionPointRec(mouse_pos, botao_abrir))
        {
            botao_abrir_cor = BUTTON_HOVER_COLOR;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                // TODO: abrir janela com caixa de texto para digitar path do arquivo de musica
                botao_abrir_cor = BLUE;
            }
        }


        // ------- Desenhando -------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            
            // DrawRectangleRec(botao_abrir, botao_abrir_cor);
            draw_button(CLITERAL(Vector2){botao_abrir.x, botao_abrir.y}, "Abrir arquivo", botao_abrir_cor);


            if(IsKeyDown(KEY_Q))
                break;
        }
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
