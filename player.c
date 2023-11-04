#include <string.h>
#include <stdio.h>
#include <raylib.h>
#include <string.h>
#include <dlfcn.h>

#include "plug.h"

// for now, they are globals
void *handle;
Plug plug = { 0 };
plug_hello_t plug_hello = NULL;
plug_init_t plug_init = NULL;
plug_init_t plug_update = NULL;

// Dynamically loads symbols (functions) of the plug library which contains the code to render a single frame (see plug.c).
// The state is stores in PLug struct (see plug.h)
// This functions loads the functions implemented in the dynamic library libplug.so
bool load_plug()
{
    if (handle) dlclose(handle);

    handle = dlopen("build/libplug.so", RTLD_NOW);
    if (handle == NULL)
    {
        printf("ERROR: could not load libplug.so: %s", dlerror());
        return false;
    }

    plug_init = dlsym(handle, "plug_init");
    if (plug_init == NULL)
    {
        printf("ERROR: could not load symbol plug_init: %s", dlerror());
        return false;
    }

    plug_update = dlsym(handle, "plug_update");
    if (plug_update == NULL)
    {
        printf("ERROR: could not load symbol plug_update: %s", dlerror());
        return 1;
    }

    return true;
}

int main(void)
{
    load_plug();
    plug_init(&plug);

    InitAudioDevice();
    SetMasterVolume(0.5);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // main loop
    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_Q)) break;
        if (IsKeyPressed(KEY_SPACE))
        {
            if (plug.music_playing)
            {
                PauseMusicStream(plug.musica);
                plug.music_playing = false;
            }
            else
            {
                ResumeMusicStream(plug.musica);
                plug.music_playing = true;
            }
        }
        if (IsKeyPressed(KEY_H))  // hot reload
        {
            if(!load_plug()) return 1;
        }

        if (IsFileDropped())
        {
            FilePathList paths = LoadDroppedFiles();
            // printf("File dropped: %s\n", paths.paths[0]);
            strcpy(plug.music_name, GetFileName(paths.paths[0]));
            plug.musica = LoadMusicStream(paths.paths[0]);
            plug.music_loaded = true;
            PlayMusicStream(plug.musica);
            plug.music_playing = true;
            UnloadDroppedFiles(paths);
            SetWindowFocused();
        }
        if (plug.music_loaded)
        {
            UpdateMusicStream(plug.musica);

            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_VOLUME_UP))
            {
                plug.music_volume = plug.music_volume < 1.0 ? plug.music_volume + 0.1 : 1.0;
                SetMusicVolume(plug.musica, plug.music_volume);
                plug.volume_counter = 30;
            }
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_VOLUME_DOWN))
            {
                plug.music_volume = plug.music_volume > 0.0 ? plug.music_volume - 0.1 : 0.0;
                SetMusicVolume(plug.musica, plug.music_volume);
                plug.volume_counter = 30;
            }
        }
        
        // ------- Desenhando -------------
        BeginDrawing();
        {
            plug_update(&plug);
        }
        EndDrawing();
        
    }
    UnloadMusicStream(plug.musica);
    CloseWindow();
    CloseAudioDevice();

    return 0;
}
