// ui.c
#include <stdio.h>
#include "raylib.h"

#include "types.h"


Rectangle DrawCenteredButtons(int i, const char **button_text, int button_count, Vector2 mouse_pos, Ui* ui)
{
  const int screen_width = ui->screen_rec.width;
  const int screen_height = ui->screen_rec.height;

  const int button_height = screen_height / 10;
  const int button_width = screen_width / 2;
  const int button_spacing = button_height / 4;
  const int text_size = button_height * 3/4;

  Rectangle button_rec = (Rectangle){
    screen_width / 2 - button_width / 2,
    screen_height / 2 - (button_count * button_height + (button_count - 1) * button_spacing) / 2 + i * (button_height + button_spacing),
    button_width,
    button_height
  };


  // Draw button
  Color button_color = CheckCollisionPointRec(mouse_pos, button_rec) ? GRAY : DARKGRAY;
  DrawRectangleRec(button_rec, button_color);
  DrawRectangleLinesEx(button_rec, 2, BLACK);
  
  // Draw text centered
  int text_width = MeasureText(button_text[i], text_size);
  DrawText(button_text[i], button_rec.x + (button_rec.width - text_width) / 2, button_rec.y + text_size / 4, text_size, WHITE);

  return button_rec;
}

Rectangle DrawHorizontalButtons(int i, const char **button_text, int button_count, Vector2 mouse_pos, Ui* ui)
{
  const int screen_width = ui->screen_rec.width;
  const int screen_height = ui->screen_rec.height;

  const int button_height = screen_height / 27;
  const int button_width = screen_width / 19;
  const int button_spacing = button_width / 10;
  const int text_size = button_height * 0.5f;

  // Horizontal layout
  float total_width = button_count * button_width + (button_count - 1) * button_spacing;
  
  Rectangle button_rec = (Rectangle){
    screen_width / 2 - total_width / 2 + i * (button_width + button_spacing),
    screen_height - button_height - 20,
    button_width,
    button_height
  };

  // Draw button
  Color button_color = CheckCollisionPointRec(mouse_pos, button_rec) ? GRAY : DARKGRAY;
  DrawRectangleRec(button_rec, button_color);
  DrawRectangleLinesEx(button_rec, 2, BLACK);
  
  // Draw text centered
  int text_width = MeasureText(button_text[i], text_size);
  DrawText(button_text[i], button_rec.x + (button_rec.width - text_width) / 2, button_rec.y + (button_rec.height - text_size) / 2, text_size, WHITE);

  return button_rec;
}


void MainMenu(Ui* ui, App* app)
{
  const char* button_text[] = {"Play Game", "Settings", "How To Play", "Exit Game"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);
  Vector2 mouse_pos = GetMousePosition();

  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rec = DrawCenteredButtons(i, button_text, button_count, mouse_pos, ui);

    if(!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(mouse_pos, button_rec))
      continue;

    switch ((MainMenuButtons)i)
    {
      case START_NEW_GAME:
        app->state = GameState;
        PlaySound(audio.click);
        break;
      case SETTINGS:
        app->prev_state = MainMenuState;
        app->state = SettingsState;
        PlaySound(audio.click);
        break;
      case HOWTOPLAY:
        app->state = HowToPlayState;
        PlaySound(audio.click);
        break;
      case EXIT_GAME:
        app->should_close = true;
        PlaySound(audio.click);
        break;
    }
  }
}


void PauseMenu(Ui* ui, App* app, Game* game, Inventory* inv, Map map[])
{
  const char* button_text[] = {"Continue", "Settings", "Exit To Menu"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);
  Vector2 mouse_pos = GetMousePosition();

  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rec = DrawCenteredButtons(i, button_text, button_count, mouse_pos, ui);

    if(!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(mouse_pos, button_rec))
      continue;

    switch ((PauseMenuButtons)i)
    {
      case PAUSE_CONTINUE:
        app->state = GameState;
        app->paused = !app->paused;
        PlaySound(audio.click);
        break;
      case PAUSE_SETTINGS:
        app->prev_state = PausedState;
        app->state = SettingsState;
        PlaySound(audio.click);
        break;
      case PAUSE_EXIT_GAME:
        app->state = MainMenuState;
          
        memset(game, 0, sizeof(Game));
        memset(inv, 0, sizeof(Inventory));
        memset(map, 0, sizeof(Map) * 1000);

        PlaySound(audio.click);
        GameInitialization(ui, app, game, inv, map);
        break;
    }
  }
}


void SettingsMenu(Ui* ui, App* app, Game* game)
{
  const char* button_text[] = {"Back", "Difficulty"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);
  Vector2 mouse_pos = GetMousePosition();

  const int score_width = ui->screen_rec.width*2/3;
  const int score_height = ui->screen_rec.height/5;
  const int score_x = ui->screen_rec.width/2 - score_width/2;
  const int score_y = ui->screen_rec.height/10;
  const int text_size = 30;

  // Not actually showing score... 
  // I just stole this from the gameover menu and couldnt be bothered renaming it :3
  const Rectangle score_rec = (Rectangle) {
    score_x,
    score_y,
    score_width,
    score_height
  };

  DrawRectangleRec(score_rec, LIGHTGRAY);
  DrawRectangleLinesEx(score_rec, 3, BLACK);

  const char* temp_text2 = "Game was designed to be played on a 1080p monitor... anything else might break the UI";
  int text_width = MeasureText(temp_text2, text_size-10);
  DrawText(temp_text2, score_x + (score_width - text_width) / 2, score_y + text_size / 4, text_size-10, BLACK);

  const char* temp_text = "If you came looking for the volume control... too bad? >:3";
  text_width = MeasureText(temp_text, text_size);
  DrawText(temp_text, score_x + (score_width - text_width) / 2, score_y + 75, text_size, BLACK);

  const char* temp_text3 = "Also F11 is bound to toggle fullscreen";
  text_width = MeasureText(temp_text3, text_size+10);
  DrawText(temp_text3, score_x + (score_width - text_width) / 2, score_y + 150, text_size+10, BLACK);

   // Draw current difficulty above buttons
  const char* difficulty_text = "";
  switch (game->difficulty) {
    case EASY: difficulty_text = "Current Difficulty: EASY"; break;
    case MEDIUM: difficulty_text = "Current Difficulty: MEDIUM"; break;
    case HARD: difficulty_text = "Current Difficulty: HARD"; break;
  }
  
  int diff_x = ui->screen_rec.width / 2 - MeasureText(difficulty_text, 30) / 2;
  int diff_y = score_y + score_height + 50;
  DrawText(difficulty_text, diff_x, diff_y, 30, BLACK);

  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rec = DrawCenteredButtons(i, button_text, button_count, mouse_pos, ui);

    if(!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(mouse_pos, button_rec))
      continue;

    switch ((SettingsMenuButtons)i)
    {
      case SETTINGS_BACK:
        if (app->prev_state == PausedState)
          app->state = PausedState;
        else if (app->prev_state == MainMenuState)
          app->state = MainMenuState;
        else
          app->state = GameOverState;
        PlaySound(audio.click);
        break;

      case SETTINGS_DIFFICULTY:
        if (game->difficulty == EASY)
          game->difficulty = MEDIUM;

        else if (game->difficulty == MEDIUM)
          game->difficulty = HARD;

        else if (game->difficulty == HARD)
          game->difficulty = EASY;

        PlaySound(audio.click);
        break;
    }
  }
}


void GameOverMenu(Ui* ui, App* app, Game* game, Inventory* inv, Map map[])
{
  const char* button_text[] = {"Play Again?", "Exit To Menu"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);
  Vector2 mouse_pos = GetMousePosition();

  const int score_width = ui->screen_rec.width*2/3;
  const int score_height = ui->screen_rec.height/5;
  const int score_x = ui->screen_rec.width/2 - score_width/2;
  const int score_y = ui->screen_rec.height/10;
  const int text_size = score_height-10;

  const Rectangle score_rec = (Rectangle) {
    score_x,
    score_y,
    score_width,
    score_height
  };

  DrawRectangleRec(score_rec, LIGHTGRAY);
  DrawRectangleLinesEx(score_rec, 3, BLACK);

  int text_width = MeasureText(TextFormat("Score: %d", game->score), text_size);
  DrawText(TextFormat("Score: %d", game->score), score_x + (score_width - text_width) / 2, score_y + text_size / 8, text_size, BLACK);


  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rec = DrawCenteredButtons(i, button_text, button_count, mouse_pos, ui);

    if(!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(mouse_pos, button_rec))
      continue;

    switch ((GameOverMenuButtons)i)
    {
      case OVER_PLAY_AGAIN:
        app->state = GameState;
          
        memset(game, 0, sizeof(Game));
        memset(inv, 0, sizeof(Inventory));
        memset(map, 0, sizeof(Map) * 1000);

        PlaySound(audio.click);
        GameInitialization(ui, app, game, inv, map);
        break;

      case OVER_EXIT_GAME:
        app->state = MainMenuState;
          
        memset(game, 0, sizeof(Game));
        memset(inv, 0, sizeof(Inventory));
        memset(map, 0, sizeof(Map) * 1000);

        PlaySound(audio.click);
        GameInitialization(ui, app, game, inv, map);
        break;
    }
  }
}


void HelpMenu(Ui* ui, App* app)
{
  int text_size = 20;
  
  Rectangle panel = (Rectangle) {
    ui->screen_rec.x + 50,
    ui->screen_rec.y + 50,
    ui->screen_rec.width - 100,
    ui->screen_rec.height - 100
  };
  
  DrawRectangleRec(panel, LIGHTGRAY);
  DrawRectangleLinesEx(panel, 5, BLACK);
  
  // Title
  DrawText("COLOR MIXING GUIDE (The game is paused)", panel.x + 20, panel.y + 20, 2*text_size, BLACK);
  
  // Close button
  Rectangle close_btn = (Rectangle) {
    panel.x + panel.width - 50, 
    panel.y + 20,
    30,
    30
  };
  DrawRectangleRec(close_btn, RED);
  DrawText("X", close_btn.x + 9, close_btn.y + 4, 20, WHITE);
  
  Vector2 mouse_pos = GetMousePosition();
  if (CheckCollisionPointRec(mouse_pos, close_btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    PlaySound(audio.click);
    app->state = (app->paused) ? PausedState : GameState;
  }
  
  // Color list
  int start_y = panel.y + 80;
  int line_height = panel.height / 16;
  int color_box_size = 30;
  int text_box_width = 150;
  
  Colors all_colors[] = {
    Red, Green, Blue,
    Yellow, Magenta, Cyan,
    Orange, Rose, Chartreuse, SpringGreen, Azure, Violet,
    White, Gray, Black
  };
  int color_count = sizeof(all_colors) / sizeof(all_colors[0]);
  
  // Draw color info
  for (int i = 0; i < color_count; i++)
  {
    int y = start_y + i * line_height;
    
    // Color swatch with outline
    Rectangle color_rect = {panel.x + 20, y, color_box_size, color_box_size};
    DrawRectangleRec(color_rect, GetFlowerColor(all_colors[i]));
    DrawRectangleLinesEx(color_rect, 2, BLACK);
    
    // Color name in box
    Rectangle name_box = {panel.x + 70, y, text_box_width, color_box_size};
    DrawRectangleRec(name_box, WHITE);
    DrawRectangleLinesEx(name_box, 1, BLACK);
    DrawText(ColorToString(all_colors[i]), name_box.x + 10, name_box.y + 7, text_size, BLACK);
    
    // RGB values
    Color c = GetFlowerColor(all_colors[i]);
    char rgb_text[50];
    sprintf(rgb_text, "RGB: (%d, %d, %d)", c.r, c.g, c.b);
    DrawText(rgb_text, panel.x + 240, y + 10, text_size, BLACK);
    
    // HEX values
    char hex_text[20];
    sprintf(hex_text, "#%02X%02X%02X", c.r, c.g, c.b);
    DrawText(hex_text, panel.x + 500, y + 10, text_size, BLACK);
  }
  
  // Mixing formulas section (right side)
  int formula_x = panel.x + panel.width / 2 + 50;
  DrawText("MIXING FORMULAS", formula_x, panel.y + 20, 2*text_size, BLACK);
  
  // Same color makes seed
  DrawText("Same Colors:", formula_x, panel.y + 70, text_size, BLACK);
  DrawText("Color + Same Color = Seed", formula_x, panel.y + 100, text_size, BLACK);
  
  // Primary mixes
  DrawText("Primaries:", formula_x, panel.y + 140, text_size, BLACK);
  DrawText("Red + Green = Yellow", formula_x, panel.y + 170, text_size, BLACK);
  DrawText("Red + Blue = Magenta", formula_x, panel.y + 195, text_size, BLACK);
  DrawText("Green + Blue = Cyan", formula_x, panel.y + 220, text_size, BLACK);
  
  // Secondary mixes
  DrawText("Secondaries:", formula_x, panel.y + 260, text_size, BLACK);
  DrawText("Yellow + Magenta = Red", formula_x, panel.y + 290, text_size, BLACK);
  DrawText("Yellow + Cyan = Green", formula_x, panel.y + 315, text_size, BLACK);
  DrawText("Magenta + Cyan = Blue", formula_x, panel.y + 340, text_size, BLACK);
  
  // Primary + Secondary (Tertiary colors)
  DrawText("Tertiary Colors:", formula_x, panel.y + 380, text_size, BLACK);
  DrawText("Red + Yellow = Orange", formula_x, panel.y + 410, text_size, BLACK);
  DrawText("Red + Magenta = Rose", formula_x, panel.y + 435, text_size, BLACK);
  DrawText("Green + Yellow = Chartreuse", formula_x, panel.y + 460, text_size, BLACK);
  DrawText("Green + Cyan = SpringGreen", formula_x, panel.y + 485, text_size, BLACK);
  DrawText("Blue + Magenta = Violet", formula_x, panel.y + 510, text_size, BLACK);
  DrawText("Blue + Cyan = Azure", formula_x, panel.y + 535, text_size, BLACK);
  
  // Opposites make black
  DrawText("Opposites = Black:", formula_x, panel.y + 575, text_size, BLACK);
  DrawText("Red + Cyan", formula_x, panel.y + 605, text_size, BLACK);
  DrawText("Green + Magenta", formula_x, panel.y + 630, text_size, BLACK);
  DrawText("Blue + Yellow", formula_x, panel.y + 655, text_size, BLACK);
  
  // Tertiary combinations make white
  DrawText("Tertiary Combos = White:", formula_x, panel.y + 695, text_size, BLACK);
  DrawText("Any Tertiary + Any Tertiary", formula_x, panel.y + 725, text_size, BLACK);
  DrawText("(except same color -> Seed)", formula_x, panel.y + 750, text_size, BLACK);
  DrawText("Orange+Rose=White, etc.", formula_x, panel.y + 775, text_size, BLACK);
  
  // Special cases
  DrawText("Grayscale:", formula_x, panel.y + 815, text_size, BLACK);
  DrawText("White + Black = Gray", formula_x, panel.y + 845, text_size, BLACK);
  DrawText("White + Any = White", formula_x, panel.y + 870, text_size, BLACK);
  DrawText("Black + Any = Black", formula_x, panel.y + 895, text_size, BLACK);
}


void HowToPlay(Ui* ui, App* app)
{
  int text_size = 30;
  
  Rectangle panel = (Rectangle) {
    ui->screen_rec.x + 50,
    ui->screen_rec.y + 50,
    ui->screen_rec.width - 100,
    ui->screen_rec.height - 100
  };
  
  DrawRectangleRec(panel, LIGHTGRAY);
  DrawRectangleLinesEx(panel, 5, BLACK);
  
  // Title
  DrawText("HOW TO PLAY", panel.x + 20, panel.y + 20, 2*text_size, BLACK);
  
  // Close button
  Rectangle close_btn = (Rectangle) {
    panel.x + panel.width - 50, 
    panel.y + 20,
    30,
    30
  };

  DrawRectangleRec(close_btn, RED);
  DrawText("X", close_btn.x + 9, close_btn.y + 6, 20, WHITE);

  Vector2 mouse_pos = GetMousePosition();
  if (CheckCollisionPointRec(mouse_pos, close_btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    PlaySound(audio.click);
    app->state = MainMenuState;
  }
  
  // Content area
  int content_x = panel.x + 20;
  int content_y = panel.y + 100;
  int line_spacing = 30;
  
  DrawText("Build up a platform and plant your seeds and mix colors to get new ones", content_x, content_y, text_size, BLACK);
  
  DrawText("There are requests of flowers that need to be deposited on the gray starting square", content_x, content_y + line_spacing * 2, text_size, BLACK);
  
  DrawText("Every flower deposited gains one point", content_x, content_y + line_spacing * 4, text_size, BLACK);
  
  DrawText("Deposit as many flowers as you can before the timer runs out", content_x, content_y + line_spacing * 6, text_size, BLACK);

  DrawText("You gain more platforms for every deposit you make", content_x, content_y + line_spacing * 8, text_size, BLACK);
  
  DrawText("15 seconds is added to the timer for every deposit", content_x, content_y + line_spacing * 10, text_size, BLACK);
  
  DrawText("As you progress the deposits will be harder and harder", content_x, content_y + line_spacing * 12, text_size, BLACK);
  
  DrawText("The toolbar buttons can be accessed via keys 1 through 4", content_x, content_y + line_spacing * 14, text_size, BLACK);
  
  DrawText("The scroll-wheel can be used to scroll through selected seeds", content_x, content_y + line_spacing * 16, text_size, BLACK);

  DrawText("You can shift + click flowers into the crafting menu which makes it less annoying", content_x, content_y + line_spacing * 18, text_size, BLACK);

  DrawText("Note: The Game was balanced around playing on hard mode and is thus the recommended difficulty", content_x, content_y + line_spacing * 23, text_size, BLACK);

  DrawText("But no shame in reducing the difficulty ofc", content_x, content_y + line_spacing * 24, text_size, BLACK);

  DrawText("Good luck! And at least try and have fun, and if you arent... then pretend like you do", content_x, content_y + line_spacing * 26, text_size, BLACK);
}


void DrawToolbar(Ui* ui, Game* game)
{
  const char* button_text[] = {"Plant", "Harvest", "Build", "Craft"};
  const int button_count = sizeof(button_text) / sizeof(*button_text);
  Vector2 mouse_pos = GetMousePosition();

  for(int i = 0; i < button_count; i++)
  {
    Rectangle button_rec = DrawHorizontalButtons(i, button_text, button_count, mouse_pos, ui);

    // Highlight active tool
    if (game->tool == i)
      DrawRectangleLinesEx(button_rec, 3, GREEN);

    if(!IsMouseButtonReleased(MOUSE_LEFT_BUTTON) || !CheckCollisionPointRec(mouse_pos, button_rec))
      continue;

    switch ((ToolbarButtons)i)
    {
      case PLANT:
        game->tool = PlantTool;
        PlaySound(audio.click);
        break;
      case HARVEST:
        game->tool = HarvestTool;
        PlaySound(audio.click);
        break;
      case BUILD:
        game->tool = SegmentTool;
        PlaySound(audio.click);
        break;
      case CRAFT:
        game->tool = CraftingTool;
        PlaySound(audio.click);
        break;
    }
  }
}


void InventoryHelp(Game* game, Inventory* inv, CraftingStation* craft, Rectangle panel, bool is_flowers)
{  
  Vector2 mouse_pos = GetMousePosition();
  
  const char* color_names[] = {
    "RGB", "Red", "Green", "Blue", 
    "Yellow", "Magenta", "Cyan",
    "Orange", "Chartreuse", "SpringGreen",
    "Azure", "Violet", "Rose",
    "White", "Gray", "Black"
  };

  // Build array of available items sorted by count (largest first)
  struct Item {
    int color_idx;
    int count;
  };
  
  struct Item available[COLOR_COUNT];
  int available_count = 0;
  
  for (int i = 0; i < COLOR_COUNT; i++)
  {
    int count = is_flowers ? inv->flowers[i] : inv->seeds[i];
    if (count > 0)
    {
      available[available_count].color_idx = i;
      available[available_count].count = count;
      available_count++;
    }
  }
  
  // Sort by count (largest first)
  for (int i = 0; i < available_count - 1; i++)
  {
    for (int j = 0; j < available_count - i - 1; j++)
    {
      if (available[j].count < available[j + 1].count)
      {
        struct Item temp = available[j];
        available[j] = available[j + 1];
        available[j + 1] = temp;
      }
    }
  }
  
  // Handle scroll wheel only for seeds
  float wheel = GetMouseWheelMove();
  if (wheel != 0 && available_count > 0 && !is_flowers)
  {
    // Find current selection position
    int current_pos = -1;
    for (int i = 0; i < available_count; i++)
    {
      if (available[i].color_idx == game->selected_color && 
          game->selected_flower == is_flowers)  // FIX: == not !
      {
        current_pos = i;
        break;
      }
    }
    
    if (current_pos >= 0)
    {
      // Scroll through sorted list
      if (wheel > 0) // Scroll up - select higher count (toward index 0)
        current_pos = (current_pos - 1 + available_count) % available_count;
      else if (wheel < 0) // Scroll down - select lower count (toward end)
        current_pos = (current_pos + 1) % available_count;
      
      game->selected_color = available[current_pos].color_idx;
      game->selected_flower = is_flowers;
    }
    else if (available_count > 0)
    {
      // Select first item if none selected
      game->selected_color = available[0].color_idx;
      game->selected_flower = is_flowers;
    }
  }

  // Draw items
  int y = panel.y + 35;
  int line_height = 30;
  
  for (int i = 0; i < available_count; i++)
  {
    int color_idx = available[i].color_idx;
    int count = available[i].count;
    
    Rectangle rec = (Rectangle) {
      panel.x + 10,
      y,
      panel.width - 20,
      25
    };

    DrawRectangleRec(rec, WHITE);
    DrawText(TextFormat("%s: %d", color_names[color_idx], count), panel.x + 15, y + 3, 18, GetFlowerColor(color_idx));
    
    // Click to select
    if (CheckCollisionPointRec(mouse_pos, rec) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      game->selected_flower = is_flowers;
      game->selected_color = color_idx;

      if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
      {
        if (!craft->slot1_filled)
        {
          craft->slot1 = game->selected_color;
          inv->flowers[game->selected_color]--;
          craft->slot1_filled = true;
          game->selected_flower = false;
        }
        else if (!craft->slot2_filled)
        {
          craft->slot2 = game->selected_color;
          inv->flowers[game->selected_color]--;
          craft->slot2_filled = true;
          game->selected_flower = false;
        }
      }
    }
    
    // Highlight selected
    if (game->selected_color == color_idx && game->selected_flower == is_flowers)
      DrawRectangleLinesEx(rec, 2, GREEN);
    
    y += line_height;
  }
}

void DrawInventory(Ui* ui, Inventory* inv, Game* game, CraftingStation* craft)
{
  Rectangle panel = (Rectangle) {
    // Very specific values i know... dont worry about it :3
    // Just to get rid of "magic numbers" while keeping it the same size when i did testing...
    // Terrible coding but better than the "magic numbering" :D
    ui->screen_rec.width * (85.0f/96.0f),
    ui->screen_rec.height / 54.0f,
    ui->screen_rec.width * (5.0f/48.0f),
    ui->screen_rec.height * (26.0f/27.0f)
  };  

  // Split panel vertically
  Rectangle seed_panel = (Rectangle) {
    panel.x,
    panel.y + 45,
    panel.width,
    (panel.height - 60) / 2
  };
  Rectangle flower_panel = (Rectangle) {
    panel.x,
    panel.y + seed_panel.height + 55,
    panel.width,
    (panel.height - 60) / 2
  };
  
  // Draw panel backgrounds
  DrawRectangleRec(seed_panel, LIGHTGRAY);  // Light gray
  DrawRectangleRec(flower_panel, LIGHTGRAY);
  DrawRectangleLinesEx(seed_panel, 2, BLACK);
  DrawRectangleLinesEx(flower_panel, 2, BLACK);
  
  // Draw titles with solid backgrounds
  DrawRectangle(seed_panel.x, seed_panel.y, seed_panel.width, 30, BLACK);
  DrawText("SEEDS", seed_panel.x + 10, seed_panel.y + 5, 20, WHITE);
  
  DrawRectangle(flower_panel.x, flower_panel.y, flower_panel.width, 30, BLACK);
  DrawText("FLOWERS", flower_panel.x + 10, flower_panel.y + 5, 20, WHITE);
  
  // Draw segments counter above everything
  Rectangle segment_rect = {
    panel.x,
    panel.y,
    panel.width,
    35
  };
  DrawRectangleRec(segment_rect, LIGHTGRAY);
  DrawRectangleLinesEx(segment_rect, 2, BLACK);
  DrawText(TextFormat("Tiles: %d", inv->segments), panel.x + 10, panel.y + 7, 20, BLACK); 

  // Draw seeds (top panel)
  bool is_flowers = false;
  InventoryHelp(game, inv, craft, seed_panel, is_flowers);
  
  // Draw flowers (bottom panel)
  is_flowers = true;
  InventoryHelp(game, inv, craft, flower_panel, is_flowers);
}


void DrawCraftingStation(Ui* ui, Inventory* inv, Game* game, CraftingStation* craft)
{
  const float x = ui->screen_rec.width / 2;
  const float y = ui->screen_rec.height / 2;
  const float width = ui->screen_rec.width / 5;
  const float height = ui->screen_rec.height / 5;

  Rectangle area = (Rectangle) {
    x - width / 2,
    y - height / 2,
    width,
    height
  };
  
  DrawRectangleRec(area, (Color){100, 100, 100, 200});
  DrawText("CRAFTING AREA", area.x + 10, area.y + 10, 20, WHITE);

  const float slot_size = area.width/5;
  
  // Draw slots
  Rectangle slot1 = (Rectangle) {
    area.x + area.width * 1/10,
    area.y + area.height / 2 - slot_size / 2, 
    slot_size,
    slot_size
  };
  Rectangle slot2 = (Rectangle) {
    area.x + area.width * 4/10,
    area.y + area.height / 2 - slot_size / 2,
    slot_size,
    slot_size
  };
  Rectangle result = (Rectangle) {
    area.x + area.width * 7/10,
    area.y + area.height / 2 - slot_size / 2,
    slot_size,
    slot_size
  };
  
  // Draw slots
  DrawRectangleRec(slot1, craft->slot1_filled ? GetFlowerColor(craft->slot1) : DARKGRAY);
  DrawRectangleRec(slot2, craft->slot2_filled ? GetFlowerColor(craft->slot2) : DARKGRAY);
  
  // Calculate result if both slots filled
  if (craft->slot1_filled && craft->slot2_filled && !craft->result_filled)
  {
    craft->result = MixColors(craft->slot1, craft->slot2);
    craft->result_filled = true;
  }
  
  DrawRectangleRec(result, craft->result_filled ? GetFlowerColor(craft->result) : DARKGRAY);
  
  DrawRectangleLinesEx(slot1, 2, BLACK);
  DrawRectangleLinesEx(slot2, 2, BLACK);
  DrawRectangleLinesEx(result, 2, BLACK);
  
  // Draw operators
  DrawText("+", area.x + area.width * 7/20 - slot_size / 9, area.y + area.height / 2 - slot_size / 4, slot_size / 2, WHITE);
  DrawText("=", area.x + area.width * 13/20 - slot_size / 9, area.y + area.height / 2 - slot_size / 4, slot_size / 2, WHITE);
  
  Vector2 mouse_pos = GetMousePosition();
  
  // Click to place selected flower in slot
  if (game->selected_flower && inv->flowers[game->selected_color] > 0)
  {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      if (CheckCollisionPointRec(mouse_pos, slot1) && !craft->slot1_filled)
      {
        craft->slot1 = game->selected_color;
        inv->flowers[game->selected_color]--;
        craft->slot1_filled = true;
        game->selected_flower = false;
      }
      else if (CheckCollisionPointRec(mouse_pos, slot2) && !craft->slot2_filled)
      {
        craft->slot2 = game->selected_color;
        inv->flowers[game->selected_color]--;
        craft->slot2_filled = true;
        game->selected_flower = false;
      }
    }
  }
  
  // Click result to craft
  if (craft->result_filled && CheckCollisionPointRec(mouse_pos, result) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    // Consume flowers, create seed
    inv->seeds[craft->result]++;
    
    // Clear slots
    craft->slot1_filled = false;
    craft->slot2_filled = false;
    craft->result_filled = false;
  }
  
  // Clear button
  Rectangle clear_btn = {area.x + area.width - 80, area.y + 10, 70, 25};
  DrawRectangleRec(clear_btn, (Color){255, 100, 100, 255});
  DrawText("Clear", clear_btn.x + 10, clear_btn.y + 5, 18, WHITE);
  
  if (CheckCollisionPointRec(mouse_pos, clear_btn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
  {
    if (craft->slot1_filled)
      inv->flowers[craft->slot1]++;

    if (craft->slot2_filled)
      inv->flowers[craft->slot2]++;

    if (inv->flowers[RGB] > 0)
      inv->flowers[RGB] = 0;

    craft->slot1_filled = false;
    craft->slot2_filled = false;
    craft->result_filled = false;
  }
}


void DrawTimer(Game* game)
{
  // Convert frames to minutes:seconds
  int total_seconds = game->timer_frames / 60;
  int minutes = total_seconds / 60;
  int seconds = total_seconds % 60;
  int text_size = 40;
  
  // Format as MM:SS
  char timer_text[10];
  sprintf(timer_text, "%02d:%02d", minutes, seconds);
  
  // It wasnt centered so i had to do this... or else i would die
  int text_width = MeasureText(TextFormat("%02d:%02d", minutes, seconds), text_size);

  // Draw at top of screen
  DrawText(timer_text, GetScreenWidth() / 2 - text_width/2, 20, text_size, (game->timer_frames < 60 * 30) ? RED : WHITE); // Red when under 30s
}
