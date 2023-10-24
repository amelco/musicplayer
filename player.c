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

typedef enum {
    POPUP_DRAGDROP = 0,
} Popup_Type;

void draw_popup(Popup_Type type, char* text)
{
    int width = 500;
    int height = 200;
    int x = (WINDOW_WIDTH/2)-(width/2);
    int y = (WINDOW_HEIGHT/2)-(height/2);
    int textSize = MeasureText(text, BUTTON_TEXT_SIZE);
    switch (type)
    {
        case POPUP_DRAGDROP:
            DrawRectangleLinesEx((Rectangle){ x, y, width, height }, 3, DARKGRAY);
            DrawText(text, x+x/2, y+height/3, 20, BUTTON_TEXT_COLOR);
            DrawText("Press X to close", x+x/2, y+height/3+30, 10, BUTTON_TEXT_COLOR);
            break;
        default:
            break;
    }
}


int main(void)
{
    // Inicializando
    InitAudioDevice();
    SetMasterVolume(0.1);
    Music musica = LoadMusicStream("./music.mp3");
    PlayMusicStream(musica);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Definindo componentes gráficos da janela
    Button botao_abrir_arquivo = {{ 10, 10, 50, 20 }, BUTTON_COLOR, "Abrir arquivo"};
    Button botao_sair = {{ 750, 560, 50, 20 }, BUTTON_COLOR, "Sair"};

    // TODO: persistir o estado da aplicação em uma estrutura
    bool opening_file = false;

    // main loop
    while (!WindowShouldClose())
    {
        // ------- Atualizando -------------
        if(IsKeyDown(KEY_Q))
            break;
        if (IsKeyDown(KEY_X))
        {
            opening_file = false;
        }

        if (isButtonHovered(&botao_abrir_arquivo))
        {
            
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                opening_file = true;
            }
        }
        if (isButtonHovered(&botao_sair))
        {
            if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            {
                // Sai do main loop
                break;
            }
        }

        UpdateMusicStream(musica);

        // ------- Desenhando -------------
        BeginDrawing();
        {
            ClearBackground(BLACK);
            draw_button(&botao_abrir_arquivo);
            draw_button(&botao_sair);
            
        }

        if (opening_file)
        {
            draw_popup(POPUP_DRAGDROP, "Drag & Drop music file here");
        }
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
