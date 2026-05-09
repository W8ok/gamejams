// utilities.c
#include <stdbool.h>
#include <math.h>
#include "raylib.h"

#include "types.h"


void AudioInitialization()
{
  InitAudioDevice();
  audio.click = LoadSound("assets/pop.wav");
  //audio.plant = LoadSound("assets/plant_in_dirt.wav");
  audio.plant = LoadSound("assets/pop.wav");
  audio.harvest = LoadSound("assets/pop.wav");
  audio.craft = LoadSound("assets/pop.wav");
  audio.reward = LoadSound("assets/reward.wav");
  audio.tick_slow = LoadSound("assets/slow_cinematic_clock.wav");
  audio.tick_fast = LoadSound("assets/clock_ticking.wav");
  audio.bg_music = LoadMusicStream("assets/music_for_now_ig.mp3");
  
  SetSoundVolume(audio.click, 0.5f);
  SetSoundVolume(audio.plant, 0.3f);
  SetSoundVolume(audio.harvest, 0.3f);
  SetSoundVolume(audio.tick_slow, 0.5f);
  SetSoundVolume(audio.tick_fast, 0.5f);
  SetSoundVolume(audio.reward, 0.3f);
    
  // Start background music
  SetMusicVolume(audio.bg_music, 0.3f);
  PlayMusicStream(audio.bg_music);
}

void UnloadAudio()
{
    UnloadSound(audio.click);
    UnloadSound(audio.plant);
    UnloadSound(audio.harvest);
    UnloadSound(audio.craft);
    UnloadSound(audio.reward);
    UnloadSound(audio.tick_slow);
    UnloadSound(audio.tick_fast);
    UnloadMusicStream(audio.bg_music);
}

void WindowInitialization(Ui* ui)
{
  //SetConfigFlags(FLAG_FULLSCREEN_MODE);
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(0, 0, "Hue Harvest");

  SetExitKey(KEY_NULL);
  SetTargetFPS(60);
  
  BeginDrawing();
  EndDrawing();

  int monitor = GetCurrentMonitor();
  ui->screen_rec = (Rectangle) {
    0,
    0,
    GetMonitorWidth(monitor),
    GetMonitorHeight(monitor)
  };

  ui->monitor = monitor;
}

void GameInitialization(Ui* ui, App* app, Game* game, Inventory* inv, Map map[])
{
  app->init = true;

  inv->seeds[RGB] = 1;
  inv->segments = 8; // Is supposed to be 8 but something is adding 1 everytime i restart so idk
  // nvm.. i somehow fixed it and now its back to 8... idk wtf i did

  game->timer_frames = 60 * 60 * 5; // 5min

  game->segment_count = 0;
  game->segment_size = 100;

  map[0].segment_rec = (Rectangle) { 
    0,
    0,
    game->segment_size,
    game->segment_size
  };

  map[0].color = DARKGRAY;

  game->player_size = 50;
  game->player_speed = 10;
  
  game->player_rec = (Rectangle) {
    game->segment_size / 2 - game->player_size / 2,
    game->segment_size / 2 - game->player_size / 2,
    game->player_size,
    game->player_size
  };

  game->camera.target = (Vector2) { 
    game->player_rec.x - game->player_rec.width / 2,
    game->player_rec.y - game->player_rec.height / 2 
  };

  game->camera.offset = (Vector2){
    ui->screen_rec.width / 2,
    ui->screen_rec.height / 2
  };

  game->camera.rotation = 0.0f;
  game->camera.zoom = 2.0f;
}

void Initialization(Ui* ui, App* app, Game* game, Inventory* inv, Map* map)
{
  app->state = MainMenuState;
  //app->state = GameState;
  app->paused = false;
  app->should_close = false;
  app->debug = false;
  app->has_savegame = false;
  app->load_save = false;


  WindowInitialization(ui);
  GameInitialization(ui, app, game, inv, map);
  AudioInitialization(audio);
}


Colors MixColors(Colors a, Colors b)
{
  if (a == b) return a; // Same color = seed of that color

  // Primary + Primary = Secondary
  if ((a == Red && b == Green) || (a == Green && b == Red)) return Yellow;
  if ((a == Red && b == Blue) || (a == Blue && b == Red)) return Magenta;
  if ((a == Green && b == Blue) || (a == Blue && b == Green)) return Cyan;
  
  // Primary + Secondary (Tertiary colors)
  if ((a == Red && b == Yellow) || (a == Yellow && b == Red)) return Orange;
  if ((a == Red && b == Magenta) || (a == Magenta && b == Red)) return Rose;
  if ((a == Green && b == Yellow) || (a == Yellow && b == Green)) return Chartreuse;
  if ((a == Green && b == Cyan) || (a == Cyan && b == Green)) return SpringGreen;
  if ((a == Blue && b == Magenta) || (a == Magenta && b == Blue)) return Violet;
  if ((a == Blue && b == Cyan) || (a == Cyan && b == Blue)) return Azure;
  
  // Secondary + Secondary
  if ((a == Yellow && b == Magenta) || (a == Magenta && b == Yellow)) return Red;
  if ((a == Yellow && b == Cyan) || (a == Cyan && b == Yellow)) return Green;
  if ((a == Magenta && b == Cyan) || (a == Cyan && b == Magenta)) return Blue;

  // Opposites
  if ((a == Red && b == Cyan) || (a == Cyan && b == Red) || 
      (a == Green && b == Magenta) || (a == Magenta && b == Green) || 
      (a == Blue && b == Yellow) || (a == Yellow && b == Blue)) return Black;

  // Special cases
  if ((a == White && b == Black) || (a == Black && b == White)) return Gray;
  if (a == White || b == White) return White;
  if (a == Black || b == Black) return Black;
  
  return White; // Default fallback
}


Color GetFlowerColor(Colors color)
{
  switch(color) {
    case Red: return (Color){255, 0, 0, 255};
    case Green: return (Color){0, 255, 0, 255};
    case Blue: return (Color){0, 0, 255, 255};

    case Yellow: return (Color){255, 255, 0, 255};
    case Magenta: return (Color){255, 0, 255, 255};
    case Cyan: return (Color){0, 255, 255, 255};

    case Orange: return (Color){255, 128, 0, 255};
    case Rose: return (Color){255, 0, 128, 255};
    case Chartreuse: return (Color){128, 255, 0, 255};
    case SpringGreen: return (Color){0, 255, 128, 255};
    case Azure: return (Color){0, 128, 255, 255};
    case Violet: return (Color){128, 0, 255, 255};

    case White: return (Color){255, 255, 255, 255};
    case Gray: return (Color){128, 128, 128, 255};
    case Black: return (Color){50, 50, 50, 255};
    default: return GRAY;
  }
}


const char* ColorToString(Colors color)
{
  switch(color) {
    case RGB: return "RGB";
    case Red: return "Red";
    case Green: return "Green";
    case Blue: return "Blue";
    case Yellow: return "Yellow";
    case Magenta: return "Magenta";
    case Cyan: return "Cyan";
    case Orange: return "Orange";
    case Chartreuse: return "Chartreuse";
    case SpringGreen: return "Spring Green";
    case Azure: return "Azure";
    case Violet: return "Violet";
    case Rose: return "Rose";
    case White: return "White";
    case Gray: return "Gray";
    case Black: return "Black";
    default: return "Unknown";
  }
}


Vector2 SnapToGrid(Vector2 point, int grid_size)
{
    float snapped_x = floorf(point.x / grid_size) * grid_size;
    float snapped_y = floorf(point.y / grid_size) * grid_size;
    return (Vector2){snapped_x, snapped_y};
} 

// Flower config functions
int GetGrowthTime(Colors color)
{
  switch(color) {
    case RGB: return 300;                               // 5 seconds
    case Red: case Green: case Blue: return 600;        // 10 seconds
    case Yellow: case Magenta: case Cyan: return 900;   // 15 seconds
    case Orange: case Chartreuse: case SpringGreen:
    case Azure: case Violet: case Rose: return 1200;    // 20 seconds
    case White: case Gray: case Black: return 1800;     // 30 seconds
    default: return 600;
  }
}

int GetSeedYield(Colors color)
{
  // How many seeds you get back when harvesting
  // Scrapped this because this idea sucked
  switch(color) {
    /*
    case RGB:     return 1;  // RGB seeds give 1 seed back
    case Red:     return 2;  // Primary colors give 2 seeds
    case Green:   return 2;
    case Blue:    return 2;
    case Yellow:  return 3;  // Secondary colors give 3 seeds
    case Magenta: return 3;
    case Cyan:    return 3;
    case White:   return 5;  // Complex colors give more
    case Black:   return 5;
    */
    // Ive come to the less stupid conclusion that 1 seed is best for everything
    default:      return 1;
  }
}

int GetFlowerYield(Game* game)
{ 
  // How many flowers you get when harvesting
  // Scrapped this because this idea sucked too
  // nvm it no longer sucks and is the basis of my difficulty settings :3
  switch(game->difficulty)
  {
    case HARD: return 1; 
    case MEDIUM: return 2;
    case EASY: return 3;
  }
  // OR make it variable:
  // return 1 + (color - Red);
  // More complex colors give more flowers... 
  // Or perhaps make it variable depending on tool used...
  // Future me if i have time can deal wth that :3
  // Current me from the future relative to the above decided to make it the difficulty
}
