# musicplayer
A **simple** C music player

My primary objective with this project is to craft an application with minimal dependencies, 
with focus on memory management and structured programming best practices.

At the moment, the project relies solely on raylib for window management and UI event handling. 
I'm designing all graphical elements from the ground up, utilizing raylib's simple shape capabilities.

### How to build
On a terminal, execute: `./build.sh`

### How to run
On a terminal, execute: `./build/player`

## (Simple) Features
- Drag & Drop to load music files
- Show music duration and time played
- Play / Pause
- Volume control
- Progress bar
- Hot reload graphical enviroment (for development mode) in progress
  - Feature heavily inspired by this [fantastic tsoding video](https://youtu.be/Y57ruDOwH1g?si=j-1m7rwtaBbxW80x)


![Simple C Music Player](scmp.png)


## Dependecies
- [raylib](https://www.raylib.com/)
