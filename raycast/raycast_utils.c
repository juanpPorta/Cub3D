#include "../include/cub3d.h"

/*In summary, the init_raycast function initializes the properties of the ray
structure, which will be used for raycasting calculations. It calculates the
camera plane's position, calculates the direction vectors for the ray, sets the
starting map grid coordinates based on the player's position, and calculates
the delta distances required for the Digital Differential Analysis (DDA) algorithm
used to find intersections with walls.*/
/*
  | |
  | | Camera Plane
  | |   /
  | |  /
  | | /    *
  | |/    /
  | |    /
  | |   /
  | |  /
  | | /
  | |/
  | |
  | | Player

*/
void	init_raycast(t_game *game, t_ray *ray, int x)
{
	// Initialize ray properties with default values (All 0's)
	init_ray(ray);
	// Calculate camera plane and direction vectors for the ray
    // Calculate the horizontal position of the camera plane
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
    // Calculate the direction vectors for the ray based on player direction
    // and camera plane
	ray->dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	// Initialize map coordinates and delta distances for DDA algorithm
    // Initialize the starting map grid coordinates based on player's position
    ray->map_x = (int)game->player.pos_x;
	ray->map_y = (int)game->player.pos_y;
	// Calculate the delta distances for both horizontal and vertical steps
    // in the DDA algorithm. These are the distances between adjacent grid cells
    // in the direction of the ray.
	ray->deltadist_x = fabs(1 / ray->dir_x);
	ray->deltadist_y = fabs(1 / ray->dir_y);
}

/*In summary, the set_dda function sets up the parameters required for the
Digital Differential Analysis (DDA) algorithm to determine the intersection
point of the ray with the walls in the game map. It calculates the step direction
for both the x-axis and y-axis based on the ray's direction, and calculates the
initial distances to the next vertical and horizontal grid lines (walls) based
on the player's position relative to the grid cells.*/
/*
  | |
  | |
  | |
  | |
  | | <--- Wall
  | |
  | |
  | |
  | |
  | |
*/
void	set_dda(t_game *game, t_ray *ray)
{
	// Perform DDA algorithm to find the intersection point with walls
    // This function sets up the step direction and side distances for the
    // Digital Differential Analysis (DDA) algorithm, which is used to find
    // the intersection point with walls.

    // Check if the ray's horizontal direction is pointing to the left
	if (ray->dir_x < 0)
	{
		ray->step_x = -1; // Set the step direction for x-axis to move left
		ray->sidedist_x = (game->player.pos_x - ray->map_x) * ray->deltadist_x;
		// Calculate the initial distance to the first vertical grid line (wall)
        // based on the player's position relative to the grid cell.
	}
	else
	{
		ray->step_x = 1; // Set the step direction for x-axis to move right
		ray->sidedist_x = (ray->map_x + 1.0 - game->player.pos_x) * ray->deltadist_x;
	    // Calculate the initial distance to the first vertical grid line (wall)
        // based on the player's position relative to the grid cell.
	}
	// Check if the ray's vertical direction is pointing upwards
	if (ray->dir_y < 0)
	{
		ray->step_y = -1; // Set the step direction for y-axis to move up
		ray->sidedist_y = (game->player.pos_y - ray->map_y) * ray->deltadist_y;
	    // Calculate the initial distance to the first horizontal grid line (wall)
        // based on the player's position relative to the grid cell.
	}
	else
	{
		ray->step_y = 1; // Set the step direction for y-axis to move down
		ray->sidedist_y = (ray->map_y + 1.0 - game->player.pos_y) * ray->deltadist_y;
	    // Calculate the initial distance to the first horizontal grid line (wall)
        // based on the player's position relative to the grid cell.
	}
}

/*In summary, the perform_dda function uses the Digital Differential Analysis
(DDA) algorithm to iteratively step through the grid cells to find the point
of intersection with a wall. It compares the distances to the next vertical
and horizontal grid lines and updates the ray's position accordingly. The
function also checks for valid map boundaries and terminates the loop if the
ray is out of bounds or if it hits a wall. If a wall is hit, the hit flag is set
to indicate a successful intersection.*/
/*
  | | <--- Wall
  | |
  | |
  | |
  | |
  | | <--- Wall
  | |
  | |
  | |
  | |
  | | <--- Wall
  | |
  | |
*/
void	perform_dda(t_game *game, t_ray *ray)
{
	// Perform DDA algorithm to find the intersection point with walls
    // This loop iterates through the grid cells to find the point of intersection
    // with a wall, using the Digital Differential Analysis (DDA) algorithm.
	int	hit; // Flag to indicate if a wall hit occurred

	hit = 0; // Initialize the hit flag to indicate no wall hit
	while (hit == 0)
	{
		// Compare the distances to the next vertical grid line and horizontal grid line
		if (ray->sidedist_x < ray->sidedist_y)
		{
			// Move to the next vertical grid cell
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // Set the side to indicate a vertical wall intersection
		}
		else
		{
			// Move to the next horizontal grid cell
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // Set the side to indicate a horizontal wall intersection
        }

		// Check if the ray's coordinates are within a valid map range
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > game->map.height - 0.25
			|| ray->map_x > game->map.width - 1.25)
			break ; // Break the loop if the ray is out of map bounds
		// Check if the grid cell contains a wall (block with value greater than '0')
		else if (game->f_map[ray->map_y][ray->map_x] > '0')
			hit = 1; // Set the hit flag to indicate a wall hit
	}
}

/*In summary, the get_line_height function calculates various properties
related to the rendering of a wall segment on the screen. It calculates
the wall distance based on the side of intersection, determines the height
of the wall slice to be rendered, calculates the vertical range on the screen
where the wall will be drawn, and calculates the precise position of the wall
slice within the grid cell to ensure correct texture alignment.*/
/*
  | |
  | |
  | |
  | |
  | |       *
  | |      ***
  | |    *****
  | |   *******
  | |  *********
  | | ***********
  | |*************
  | |*************
  | |*************
  | |*************
*/
void	get_line_height(t_game *game, t_ray *ray)
{
	// Calculate wall distance and line height for rendering
    // This function calculates properties related to the height of the wall
    // segment that will be rendered on the screen.

    // Determine the wall distance based on the side of intersection
    // If the side is 0 (vertical wall), calculate wall distance using sidedist_x
    // If the side is 1 (horizontal wall), calculate wall distance using sidedist_y
	if (ray->side == 0)
		ray->wall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->wall_dist = (ray->sidedist_y - ray->deltadist_y);
	// Calculate the height of the wall slice to be rendered on the screen
    // The line height is determined by the distance to the wall.	
	ray->line_height = (int)(game->win_height / ray->wall_dist);
	// Calculate the vertical range of the wall slice to be drawn on the screen
    // The draw_start and draw_end values determine where on the screen the wall
    // slice will be rendered.
	ray->draw_start = -(ray->line_height) / 2 + game->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + game->win_height / 2;
	if (ray->draw_end >= game->win_height)
		ray->draw_end = game->win_height - 1;
	// Calculate the exact position of the wall slice within the grid cell
    // This calculates the fractional part of the position to align the texture correctly.
	if (ray->side == 0)
		ray->wall_x = game->player.pos_y + ray->wall_dist * ray->dir_y;
	else
		ray->wall_x = game->player.pos_x + ray->wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x); // Remove the integer part
}

/*In summary, the update_texture_pixels function maps the appropriate texture
onto the wall slice that will be rendered on the screen. It calculates texture
coordinates, handles texture flipping, calculates texture mapping parameters,
iterates through the vertical range of the wall slice, retrieves pixel colors
from the texture, applies shading effects for certain textures, and stores
the resulting pixel colors in the texture_pixels array for later rendering.*/
/*
  | |
  | |
  | |
  | |
  | |       *   (Texture Mapped)
  | |      ***
  | |    *****
  | |   *******
  | |  *********
  | | ***********
  | |*************
  | |*************
  | |*************
  | |*************
*/
void	update_texture_pixels(t_game *game, t_ray *ray, int x)
{
	// Update texture pixels for the current column of the screen
    // This function maps the appropriate texture onto the wall slice
    // and updates the texture_pixels array that stores pixel colors.
	int			y; // Vertical position on the screen
	int			color; // Color of the pixel

	// Determine the texture index for the wall slice
	get_texture_index(game, ray);
	// Calculate the x-coordinate in the texture based on the wall_x value
	game->texture.x = (int)(ray->wall_x * game->texture.size);
    // Handle texture flipping for certain cases (side and direction)
	if ((ray->side == 0 && ray->dir_x < 0)
		|| (ray->side == 1 && ray->dir_y > 0))
		game->texture.x = game->texture.size - game->texture.x - 1;
	// Calculate the step and starting position for the texture mapping
	game->texture.step = 1.0 * game->texture.size / ray->line_height;
	game->texture.pos = (ray->draw_start - game->win_height / 2
			+ ray->line_height / 2) * game->texture.step;
    // Iterate through the wall slice's vertical range on the screen
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
	    // Calculate the y-coordinate in the texture, wrapping around the texture size
		game->texture.y = (int)game->texture.pos & (game->texture.size - 1);
		game->texture.pos += game->texture.step;
		// Retrieve the pixel color from the texture using texture coordinates
		color = game->textures[game->texture.index][game->texture.size * game->texture.y + game->texture.x];
		// Apply shading effect for certain textures (NORTH and EAST)
		if (game->texture.index == NORTH || game->texture.index == WEST)
			color = (color >> 1) & 8355700;
		// Store the pixel color in the texture_pixels array if it's not black
		if (color > 0)
			game->texture_pixels[y][x] = color;
		y++; // Move to the next vertical position
	}
}