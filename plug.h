#ifndef PLUG_H
#define PLUG_H

#include <raylib.h>

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

typedef struct
{
    Music musica;
    char music_name[256];
    bool music_loaded;
    bool music_playing;
    float music_volume;
    int volume_counter;

} Plug;

// these are not function signatures
// these are type definitions that points to the implementation of the functions in plug.c
typedef void (*plug_hello_t)(void);
typedef void (*plug_init_t)(Plug *plug);
typedef void (*plug_update_t)(void);

#endif //PLUG_H
