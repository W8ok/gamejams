// game.c
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include "raylib.h"

#include "types.h"


// Literally just stole the particle stuff... 
// All i did was integrate it with my code
void SpawnParticles(Game* game, Vector2 pos, Color color, int count)
{
  for (int i = 0; i < count && game->particle_count < 255; i++)
  {
    // Lighten the color (add white)
    Color light_color = {
      color.r + (255 - color.r) * 0.2f,
      color.g + (255 - color.g) * 0.2f,
      color.b + (255 - color.b) * 0.2f,
      255
    };
    
    game->particles[game->particle_count] = (Particle){
      pos,
      (Vector2){GetRandomValue(-50, 50)/10.0f, GetRandomValue(-50, 50)/10.0f},
      light_color,  // Use lightened color
      1.0f,
      GetRandomValue(3, 8)
    };

    game->particle_count++;
  }
}

void UpdateParticles(Game* game)
{
  for (int i = 0; i < game->particle_count; i++)
  {
    float alpha = game->particles[i].lifetime * 255;
    DrawCircleV(game->particles[i].position, game->particles[i].size, (Color){game->particles[i].color.r, game->particles[i].color.g, game->particles[i].color.b, (unsigned char)alpha});

    game->particles[i].position.x += game->particles[i].velocity.x;
    game->particles[i].position.y += game->particles[i].velocity.y;
    game->particles[i].lifetime -= 0.02f;
    game->particles[i].velocity.y += 0.1f; // Gravity
    
    // Remove dead particles
    if (game->particles[i].lifetime <= 0)
    {
      game->particles[i] = game->particles[game->particle_count - 1];
      game->particle_count--;
      i--;
    }
  }
}


void CameraUpdate(Game* game)
{
  float smooth_speed = 0.1f; // Adjust for smoothness
  game->camera.target.x += (game->player_rec.x + game->player_rec.width/2 - game->camera.target.x) * smooth_speed;
  game->camera.target.y += (game->player_rec.y + game->player_rec.height/2 - game->camera.target.y) * smooth_speed;
}

void RenderGame(Game* game, Map map[])
{
  for (int i = 0; i <= game->segment_count; i++)
  {
    DrawRectangleRec(map[i].segment_rec, map[i].color);
    DrawRectangleLinesEx(map[i].segment_rec, 1, BLACK);

    // If segment has a plant then render the plant
    if (map[i].planted)
    {
      if (map[i].plant_time > 1)
        map[i].plant_time--;
      else
        map[i].fully_grown = true;

      // Calculate flower size based on growth progress
      // plant_time goes from 600 to 0 (10 seconds at 60 FPS)
      float growth_progress = 1.0f - ((float)map[i].plant_time / GetGrowthTime(map[i].plant_color));
      
      // Make flower grow from 10% to 90% of segment size
      float min_size = map[i].segment_rec.width * 0.1f;
      float max_size = map[i].segment_rec.width * 0.9f;
      float flower_size = min_size + (max_size - min_size) * growth_progress;

      float flower_x = map[i].segment_rec.x + (map[i].segment_rec.width - flower_size) / 2;
      float flower_y = map[i].segment_rec.y + (map[i].segment_rec.height - flower_size) / 2;

      Rectangle flower_rec = (Rectangle) {
        flower_x,
        flower_y,
        flower_size,
        flower_size
      };

      DrawRectangleRec(flower_rec, GetFlowerColor(map[i].plant_color));
    }
  }

  if (game->timer_frames > 0)
    game->timer_frames--;

  UpdateParticles(game);
  DrawRectangleRec(game->player_rec, BLACK);
}


void DrawMap(Game* game, Inventory* inv, Map map[])
{
  if (inv->segments <= 0)
    return;

  int segment_count = game->segment_count;
  int segment_size = game->segment_size;

  Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), game->camera);
  Vector2 snapped_pos = SnapToGrid(mouse_pos, segment_size);

  Rectangle hover_rect = (Rectangle) {
    snapped_pos.x,
    snapped_pos.y, 
    segment_size,
    segment_size
  };

  DrawRectangleRec(hover_rect, (Color){139, 69, 19, 128});

  if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    return;

  // Not on existing segment
  bool can_place = true;
  for (int i = 0; i <= segment_count; i++)
    if (CheckCollisionPointRec(mouse_pos, map[i].segment_rec))
    {
      can_place = false;
      break;
    }

  if (!can_place) return;

  // Next to existing segment  
  bool adjacent = false;
  for (int i = 0; i <= segment_count; i++)
  {
    float left = map[i].segment_rec.x - segment_size;
    float right = map[i].segment_rec.x + segment_size;
    float top = map[i].segment_rec.y - segment_size;
    float bottom = map[i].segment_rec.y + segment_size;
    
    if ((snapped_pos.x == left && snapped_pos.y == map[i].segment_rec.y) ||
        (snapped_pos.x == right && snapped_pos.y == map[i].segment_rec.y) ||
        (snapped_pos.y == top && snapped_pos.x == map[i].segment_rec.x) ||
        (snapped_pos.y == bottom && snapped_pos.x == map[i].segment_rec.x))
      adjacent = true;
    
    if (adjacent) break;
  }

  if (!adjacent) return;

  // Place segment
  segment_count++;
  map[segment_count].segment_rec = hover_rect;
  game->segment_count = segment_count;
  map[segment_count].color = BROWN;
  inv->segments--;
  PlaySound(audio.plant);
}


void DrawPlayer(Game* game, Map map[])
{
  // Garbage code but it works
  // And no im not gonna fix it :3

  Vector2 pos = (Vector2) { game->player_rec.x, game->player_rec.y };
  int speed = game->player_speed;
  int size = game->player_size;

  if (IsKeyDown(KEY_A))
    pos.x -= speed;
  if (IsKeyDown(KEY_D))
    pos.x += speed;
  if (IsKeyDown(KEY_W))
    pos.y -= speed;
  if (IsKeyDown(KEY_S))
    pos.y += speed;

  game->player_rec = (Rectangle) {
    pos.x,
    pos.y,
    size,
    size
  };
}


void Planting(Game* game, Inventory* inv, Map map[])
{
  Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), game->camera);
  Vector2 snapped_pos = SnapToGrid(mouse_pos, game->segment_size);
  snapped_pos.x += game->segment_size/2;
  snapped_pos.y += game->segment_size/2;

  game->selected_flower = false;

  if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    return;

  // Check if we have seeds of the selected color
  if (inv->seeds[game->selected_color] <= 0)
    return;

  for (int i = 1; i <= game->segment_count; i++)
    if (CheckCollisionPointRec(mouse_pos, map[i].segment_rec))
    {
      if (map[i].planted)
        break;

      // Plant the selected color
      map[i].planted = true;
      map[i].plant_color = game->selected_color;  // Store what color we planted
      map[i].plant_time = GetGrowthTime(game->selected_color);  // Different times per color
      inv->seeds[game->selected_color]--;
      PlaySound(audio.plant);
      SpawnParticles(game, snapped_pos, BROWN, 8);
      break;
    }
}


void Harvesting(Game* game, Inventory* inv, Map map[])
{
  Vector2 mouse_pos = GetScreenToWorld2D(GetMousePosition(), game->camera);
  Vector2 snapped_pos = SnapToGrid(mouse_pos, game->segment_size);
  snapped_pos.x += game->segment_size/2;
  snapped_pos.y += game->segment_size/2;

  if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    return;

  for (int i = 1; i <= game->segment_count; i++)
    if (CheckCollisionPointRec(mouse_pos, map[i].segment_rec))
    {
      if (!map[i].fully_grown)
        break;

      // Harvest the flower color that was planted
      Colors harvested_color = map[i].plant_color;
      
      map[i].planted = false;
      map[i].fully_grown = false;

      // Get seeds back (maybe more for complex colors?)
      // No current future me decided to make it difficutly based wait nvm that was for the flower yield
      inv->seeds[harvested_color] += GetSeedYield(harvested_color);
      PlaySound(audio.harvest);
      SpawnParticles(game, snapped_pos, GetFlowerColor(harvested_color), 12);
      
      // Get flowers
      if (harvested_color == RGB)
      {
        Colors primary_colors[] = {Red, Green, Blue};
        Colors random_primary = primary_colors[GetRandomValue(0, 2)];
        inv->flowers[random_primary]++;
        break;
      }

      inv->flowers[harvested_color] += GetFlowerYield(game); 
      break;
    }
}


void DrawRequest(App* app, Game* game, Inventory* inv)
{
  // Panel for request info
  Rectangle panel = {20, 20, 300, 120};
  DrawRectangleRec(panel, LIGHTGRAY);
  DrawRectangleLinesEx(panel, 2, BLACK);
  
  DrawText(TextFormat("Request #%d", game->request_number), panel.x + 10, panel.y + 10, 20, BLACK);
  
  // Draw color swatch
  Rectangle color_swatch = {panel.x + 10, panel.y + 35, 30, 30};
  DrawRectangleRec(color_swatch, GetFlowerColor(game->current_request.requested_color));
  DrawRectangleLinesEx(color_swatch, 2, BLACK);
  
  // I love my totally readable code :3
  DrawText(TextFormat("%s flowers", ColorToString(game->current_request.requested_color)), panel.x + 50, panel.y + 35, 20, BLACK);
  DrawText(TextFormat("%d/%d", inv->flowers[game->current_request.requested_color], game->current_request.requested_amount), panel.x + 50, panel.y + 60, 18, BLACK);
  
  // Score display
  DrawText(TextFormat("Score: %d", game->score), panel.x + 10, panel.y + 90, 20, BLACK);
  
  // Help button
  Rectangle help_btn = {panel.x + 200, panel.y + 90, 80, 25};
  bool help_hover = CheckCollisionPointRec(GetMousePosition(), help_btn);
  Color help_color = help_hover ? GRAY : LIGHTGRAY;
  
  DrawRectangleRec(help_btn, help_color);
  DrawRectangleLinesEx(help_btn, 2, BLACK);
  DrawText("Help", help_btn.x + 20, help_btn.y + 5, 18, BLACK);
  
  if (help_hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    app->state = HelpState;
}


void GenerateNewRequest(Game* game)
{
  game->request_number++;
  
  int request_tier = (game->request_number - 1) / 3;
  
  switch (request_tier)
  {
    case 0: // Tier 1: Only primaries
      game->current_request.requested_color = (Colors[3]){
        Red, Green, Blue
      }[GetRandomValue(0, 2)];
      break;
    
    case 1: // Tier 2: Only secondaries
      game->current_request.requested_color = (Colors[3]){
        Yellow, Magenta, Cyan
      }[GetRandomValue(0, 2)];
      break;
    
    case 2: // Tier 3: Primaries + Secondaries
      game->current_request.requested_color = (Colors[6]){
        Red, Green, Blue,
        Yellow, Magenta, Cyan
      }[GetRandomValue(0, 5)];
      break;
    
    case 3: // Tier 4: Only tertiaries
      game->current_request.requested_color = (Colors[6]){
        Orange, Chartreuse, SpringGreen,
        Azure, Violet, Rose
      }[GetRandomValue(0, 5)];
      break;
    
    case 4: // Tier 5: All except specials
      game->current_request.requested_color = (Colors[12]){
        Red, Green, Blue, 
        Yellow, Magenta, Cyan,
        Orange, Chartreuse, SpringGreen,
        Azure, Violet, Rose
      }[GetRandomValue(0, 11)];
      break;
    
    default: // Tier 6+: All colors
      game->current_request.requested_color = (Colors[15]){
        Red, Green, Blue, 
        Yellow, Magenta, Cyan,
        Orange, Chartreuse, SpringGreen,
        Azure, Violet, Rose,
        White, Gray, Black
      }[GetRandomValue(0, 14)];
      break;
  }
  
  game->current_request.requested_amount = 1 + (game->request_number / 3);
  game->current_request.reward = 60 * 15;
}


// Eventually i wanna make this so the player have to deposit it
// Instead of it being taken from the inventory automatically
bool DrawDepositButton(Game* game, Map map[])
{
  Vector2 player_center = (Vector2) {
    game->player_rec.x + game->player_rec.width/2,
    game->player_rec.y + game->player_rec.height/2
  };
  
  // Check if player is on the starting segment
  bool can_deposit = CheckCollisionPointRec(player_center, map[0].segment_rec);
  
  // Draw button at top-left
  Rectangle btn = {20, 150, 100, 40};
  bool hover = CheckCollisionPointRec(GetMousePosition(), btn);
  
  Color btn_color = can_deposit ? (hover ? GRAY : LIGHTGRAY) : DARKGRAY;
  DrawRectangleRec(btn, btn_color);
  DrawRectangleLinesEx(btn, 2, BLACK);
  
  DrawText("Deposit", btn.x + 10, btn.y + 10, 20, BLACK);
  
  // Return true if clicked and conditions met
  return can_deposit && hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void CheckRequest(App* app, Game* game, Inventory* inv, Map map[])
{
  if (app->init) // Not even god can handle this level of bad code
  {
    GenerateNewRequest(game);
    app->init = false;
  }

  // Try to deposit if button clicked
  if (DrawDepositButton(game, map))
  {
    PlaySound(audio.click);
    if (inv->flowers[game->current_request.requested_color] >= game->current_request.requested_amount)
    {
      // Complete request
      game->score += game->current_request.requested_amount;
      inv->flowers[game->current_request.requested_color] -= game->current_request.requested_amount;
      game->timer_frames += game->current_request.reward;
      inv->segments++;
      PlaySound(audio.reward);
      GenerateNewRequest(game);
    }
  }
}
