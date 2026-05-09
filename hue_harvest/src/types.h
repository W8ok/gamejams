// types.h
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
  MainMenuState,
  GameState,
  PausedState,
  GameOverState,
  HelpState,
  SettingsState,
  HowToPlayState,
} State;

typedef enum {
  START_NEW_GAME,
  SETTINGS,
  HOWTOPLAY,
  EXIT_GAME,
} MainMenuButtons;

typedef enum {
  PAUSE_CONTINUE,
  PAUSE_SETTINGS,
  PAUSE_EXIT_GAME,
} PauseMenuButtons;

typedef enum {
  OVER_PLAY_AGAIN,
  OVER_EXIT_GAME,
} GameOverMenuButtons;

typedef enum {
  SETTINGS_BACK,
  SETTINGS_DIFFICULTY,
} SettingsMenuButtons;

typedef enum {
  HARD,
  MEDIUM,
  EASY,
} Difficulty;

typedef enum {
  PLANT,
  HARVEST,
  BUILD,
  CRAFT,
} ToolbarButtons;

typedef enum {
  PlantTool,
  HarvestTool,
  SegmentTool,
  CraftingTool,
} Tools;

typedef enum {
  // Primary colors
  RGB,      // The starter seed
  Red,      // From RGB
  Green,    // From RGB  
  Blue,     // From RGB
  
  // Secondary colors (mix 2 primaries)
  Yellow,   // Red + Green
  Magenta,  // Red + Blue
  Cyan,     // Green + Blue
  
  // Tertiary colors (primary + secondary)
  Orange,     // Red + Yellow
  Chartreuse, // Green + Yellow  
  SpringGreen,// Green + Cyan
  Azure,      // Blue + Cyan
  Violet,     // Blue + Magenta
  Rose,       // Red + Magenta
  
  // Special
  White,    // Tertiary mix 
  Gray,     // Black + White
  Black,    // Opposites
  
  COLOR_COUNT
} Colors;

typedef struct {
  Rectangle screen_rec;
  int monitor;
} Ui;

typedef struct {
    Sound click;
    Sound plant;
    Sound harvest;
    Sound craft;
    Sound reward;
    Sound tick_slow;
    Sound tick_fast;
    Music bg_music;
} Audio;
extern Audio audio;

typedef struct {
  State state;
  State prev_state;
  bool paused;
  bool should_close;
  bool debug;
  bool has_savegame;
  bool load_save;
  bool restart_application;
  bool init;
} App;

typedef struct {
  Colors requested_color;
  int requested_amount;
  int time_limit_frames;
  int reward; // Points or time bonus
} Request;

typedef struct {
    Vector2 position;
    Vector2 velocity;
    Color color;
    float lifetime;
    float size;
} Particle;

typedef struct {
  Tools tool;
  Difficulty difficulty;
  Colors selected_color;
  Camera2D camera;
  Rectangle player_rec;
  int player_speed;
  int player_size;
  int segment_count;
  int segment_size;
  double timer_frames;
  bool selected_flower;
  Request current_request;
  int request_number;
  int score;
  Particle particles[255];
  int particle_count;
} Game;

typedef struct {
  Rectangle segment_rec;
  Color color;
  bool planted;
  bool fully_grown;
  Colors plant_color;
  int plant_time;
} Map;

typedef struct {
  int segments;
  int seeds[COLOR_COUNT];
  int flowers[COLOR_COUNT];
} Inventory;

typedef struct {
  //Plants type;
  int Growth;
} Plant;

typedef struct {
  Colors slot1;
  Colors slot2;
  Colors result;
  bool slot1_filled;
  bool slot2_filled;
  bool result_filled;
} CraftingStation;


// Should really be in their own .h file... but cant be bothered stfu :3
void AudioInitialization();
void UnloadAudio();
void WindowInitialization(Ui* ui);
void GameInitialization(Ui* ui, App* app, Game* game, Inventory* inv, Map map[]);
void Initialization(Ui* ui, App* app, Game* game, Inventory* inv, Map* map);

// Helper functions in utilities.c
Colors MixColors(Colors a, Colors b);
Color GetFlowerColor(Colors color);
const char* ColorToString(Colors color);
Vector2 SnapToGrid(Vector2 point, int grid_size);

int GetGrowthTime(Colors color);
int GetSeedYield(Colors color);
int GetFlowerYield(Game* game);

#endif
