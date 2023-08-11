#include "../include/cub3d.h"

/*Player's Direction Vector (dir_x and dir_y): These variables represent
the direction in which the player is facing. They form a vector that points
from the player's position into the game world.

Camera Plane (plane_x and plane_y): The camera plane is a concept used in
raycasting to simulate a player's field of view. It's a 2D plane that is
perpendicular to the player's direction vector. The camera plane is positioned 
in front of the player and determines how much of the game world is visible to
the player.

- plane_x represents the X-coordinate of the camera plane.
It determines the "width" of the player's field of view. A larger
value will create a narrower field of view, while a smaller value will
create a wider field of view.
- plane_y represents the Y-coordinate of the camera plane.
It interacts with the player's direction vector to create a sense of
perspective and depth.

Rendering: When rendering the scene, the camera plane, player's direction vector,
and other parameters are used to cast rays from the player's position into the
game world. These rays simulate the player's line of sight, and their intersections
with walls and objects are used to create the 3D effect on the 2D screen.*/

void init_player_north_south(t_player *player)
{
    // Initialize the player's direction vectors and camera plane based on facing North or South
    
    if (player->dir == 'S') // If the player is facing South
    {
        player->dir_x = 0;   // Set the player's direction vector in the X-axis to 0
        player->dir_y = 1;   // Set the player's direction vector in the Y-axis to 1
        player->plane_x = -0.70;  // Set the camera plane's X-coordinate to create perspective distortion
        player->plane_y = 0;      // Set the camera plane's Y-coordinate to 0
    }
    else if (player->dir == 'N') // If the player is facing North
    {
        player->dir_x = 0;   // Set the player's direction vector in the X-axis to 0
        player->dir_y = -1;  // Set the player's direction vector in the Y-axis to -1
        player->plane_x = 0.70;   // Set the camera plane's X-coordinate to create perspective distortion
        player->plane_y = 0;      // Set the camera plane's Y-coordinate to 0
    }
    else
    {
        return; // If the player's direction is neither North nor South, return without making changes
    }
}

void init_player_east_west(t_player *player)
{
    // Initialize the player's direction vectors and camera plane based on facing East or West
    
    if (player->dir == 'W') // If the player is facing West
    {
        player->dir_x = -1;  // Set the player's direction vector in the X-axis to -1
        player->dir_y = 0;   // Set the player's direction vector in the Y-axis to 0
        player->plane_x = 0; // Set the camera plane's X-coordinate to 0
        player->plane_y = -0.70;   // Set the camera plane's Y-coordinate to create perspective distortion
    }
    else if (player->dir == 'E') // If the player is facing East
    {
        player->dir_x = 1;   // Set the player's direction vector in the X-axis to 1
        player->dir_y = 0;   // Set the player's direction vector in the Y-axis to 0
        player->plane_x = 0; // Set the camera plane's X-coordinate to 0
        player->plane_y = 0.70;    // Set the camera plane's Y-coordinate to create perspective distortion
    }
    else
    {
        return; // If the player's direction is neither East nor West, return without making changes
    }
}

void init_player_pos(t_game *game)
{
    // Initialize the player's direction and camera plane vectors based on their initial facing direction
    
    init_player_north_south(&game->player);  // Set direction vectors and camera plane for North/South
    init_player_east_west(&game->player);     // Set direction vectors and camera plane for East/West
}

void    init_player(t_player *player)
{
    player->dir = 0;
    player->pos_x = 0;
    player->pos_y = 0;
    player->dir_x = 0;
    player->dir_y = 0;
    player->plane_x = 0;
    player->plane_y = 0;
    player->has_moved = 0;
    player->move_x = 0;
    player->move_y = 0;
    player->rotate = 0;
    player->speed = SPEED;
}