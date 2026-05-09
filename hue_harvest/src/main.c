// main.c
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include "raylib.h"

#include "types.h"

#include "ui.c"
#include "game.c"
#include "debug.c"


Audio audio = {0};

int main(void)
{
  Ui ui = {0};
  App app = {0};
  Game game = {0};
  Inventory inv = {0};
  CraftingStation craft = {0};
  Map map[1000];
  memset(map, 0, sizeof(Map) * 1000);

  SetRandomSeed(time(NULL));

  Initialization(&ui, &app, &game, &inv, map);

  while (!WindowShouldClose() && !app.should_close)
  {
    BeginDrawing();
    ClearBackground(SKYBLUE);
    UpdateMusicStream(audio.bg_music);

    if (app.debug)
      debug(&ui, &app);

    if (IsKeyPressed(KEY_ONE)) game.tool = PlantTool;
    if (IsKeyPressed(KEY_TWO)) game.tool = HarvestTool;
    if (IsKeyPressed(KEY_THREE)) game.tool = SegmentTool;
    if (IsKeyPressed(KEY_FOUR)) game.tool = CraftingTool;


    if (!(game.timer_frames > 0))
      app.state = GameOverState;

    // I am ashamed that this is how i handle audio
    // nvm you never get to see how bad it once was >:3
    // But could still be better if i paused and resumed sound instead
    if (game.timer_frames <= 540 && !IsSoundPlaying(audio.tick_fast))
      PlaySound(audio.tick_fast);
    if (game.timer_frames > 540)
      StopSound(audio.tick_fast);

    if (game.timer_frames <= 1800 && !IsSoundPlaying(audio.tick_slow))
      PlaySound(audio.tick_slow);
    if (game.timer_frames > 1800)
      StopSound(audio.tick_slow);

    if (IsKeyPressed(KEY_ESCAPE))
    {
      if (app.state == GameState || app.state == PausedState)
      {
        app.paused = !app.paused;
    
        if (app.paused)
          app.state = PausedState;
        else
          app.state = GameState;
      }

      else if (app.state == HowToPlayState)
        app.state = MainMenuState;

      else if (app.state == HelpState)
        app.state = GameState;
    }

    if (IsKeyPressed(KEY_F11))
      ToggleFullscreen();

    switch (app.state)
    {
      case MainMenuState:
        MainMenu(&ui, &app);
        break;

      case GameState:
        ResumeSound(audio.tick_fast);
        ResumeSound(audio.tick_slow);
        CameraUpdate(&game);
        BeginMode2D(game.camera);

        RenderGame(&game, map);
        DrawPlayer(&game, map);

        // I love nested switch statements :D
        // Spaget... my favourite pasta
        switch (game.tool)
        {
          case PlantTool:
            Planting(&game, &inv, map);
            EndMode2D();
            break;

          case HarvestTool:
            Harvesting(&game, &inv, map);
            EndMode2D();
            break;

          case SegmentTool:
            DrawMap(&game, &inv, map);
            EndMode2D();
            break;
        
          case CraftingTool:
            EndMode2D();
            DrawCraftingStation(&ui, &inv, &game, &craft);
            break;
        }

        CheckRequest(&app, &game, &inv, map);
        DrawInventory(&ui, &inv, &game, &craft);
        DrawTimer(&game);
        DrawRequest(&app, &game, &inv);
        DrawToolbar(&ui, &game);
        break;

      case PausedState:
        PauseSound(audio.tick_fast);
        PauseSound(audio.tick_slow);
        PauseMenu(&ui, &app, &game, &inv, map);
        break;

      case GameOverState:
        PauseSound(audio.tick_fast);
        PauseSound(audio.tick_slow);
        GameOverMenu(&ui, &app, &game, &inv, map);
        break;

      case HelpState:
        PauseSound(audio.tick_fast);
        PauseSound(audio.tick_slow);
        HelpMenu(&ui, &app);
        break;

      case SettingsState:
        PauseSound(audio.tick_fast);
        PauseSound(audio.tick_slow);
        SettingsMenu(&ui, &app, &game);
        break;

      case HowToPlayState:
        HowToPlay(&ui, &app);
        break;
    }

    EndDrawing();
  }

  UnloadAudio();
  CloseWindow();
  return 0;
}
