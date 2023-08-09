#include "../include/cub3d.h"

/*In summary, the get_texture_index function determines the index of the
texture to use for the wall slice that will be rendered on the screen.
It checks the side of intersection (vertical or horizontal) and the direction
of the ray to determine which texture (West, East, South, or North) should
be used for the wall segment. The determined texture index is then stored
in the game->texture.index variable for later use in rendering.*/
/*
  | |
  | |
  | |
  | |
  | |       *   (Texture Index: WEST)
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
void	get_texture_index(t_game *game, t_ray *ray)
{
	// Determine the index of the texture to use for the wall slice
    // This function selects the appropriate texture index based on the
    // direction of the ray and the side of the wall.

	// Check if the intersection side is a vertical wall (side == 0)
	if (ray->side == 0)
	{
	    // If the ray's direction is pointing to the left (dir_x < 0), use the West texture
        // Otherwise, use the East texture
		if (ray->dir_x < 0)
			game->texture.index = WEST;
		else
			game->texture.index = EAST;
	}
	else // If the intersection side is a horizontal wall (side == 1)
	{
		// If the ray's direction is pointing downwards (dir_y > 0), use the South texture
        // Otherwise, use the North texture
		if (ray->dir_y > 0)
			game->texture.index = SOUTH;
		else
			game->texture.index = NORTH;
	}
}
