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

void show_usage(char* programName)
{
    printf("Usage:\n\t%s [musicFileName]\n", programName);
}

void load_music(char* file_path, Plug* plug)
{
    strcpy(plug->music_name, GetFileName(file_path));
    plug->musica = LoadMusicStream(file_path);
    plug->music_loaded = true;
    PlayMusicStream(plug->musica);
    plug->music_playing = true;
}

int main(int argc, char** argv)
{
    bool hasInputFile = false;
    char musicFilePath[256] = {'\0'};

    if (argc > 2)
    {
        printf("ERROR: Incorrect number of arguments\n");
        show_usage(argv[0]);
        return 1;
    }
    if (argc == 2)
    {
        printf("%s\n", argv[1]);
        strcpy(musicFilePath, argv[1]);
        hasInputFile = true;
    }

    load_plug();
    plug_init(&plug);

    InitAudioDevice();
    SetMasterVolume(1.0);

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
            load_music(paths.paths[0], &plug);
            UnloadDroppedFiles(paths);
            SetWindowFocused();
        }
        if (hasInputFile && !plug.music_loaded) load_music(musicFilePath, &plug);

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
