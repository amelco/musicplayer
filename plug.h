#ifndef PLUG_H
#define PLUG_H

#include <raylib.h>

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
