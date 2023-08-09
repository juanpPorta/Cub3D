#include "../include/cub3d.h"

/*In summary, the raycast function is responsible for performing the raycasting
process to render the scene on the game screen. It iterates through each column
of the screen, and for each column, it initializes ray properties using init_raycast,
sets up the DDA algorithm using set_dda, performs the DDA algorithm to find the
exact intersection point with walls using perform_dda, calculates line height
and other properties for rendering using get_line_height, updates the texture
pixels for the current column using update_texture_pixels, and finally moves
to the next column. This function essentially computes the information needed
for rendering each column of the scene based on the raycasting technique.*/
void    raycast(t_game *game)
{
	// Perform raycasting to render the scene
    // This function initiates the raycasting process for rendering the scene.
    t_ray   ray; // Ray structure to hold ray properties
    int     x; // Loop variable for the x-coordinate of the screen

    x = 0;
    // Initialize the ray structure using the ray in the game structure
    ray = game->ray;
    // Iterate through each column of the screen
    while(x < game->win_width)
    {
	    // Initialize ray properties for the current column
        init_raycast(game, &ray, x);
        // Set up the DDA algorithm to find the intersection point with walls
        set_dda(game, &ray);
        // Perform the DDA algorithm to find the exact intersection point
        perform_dda(game, &ray);
        // Calculate line height and other properties for rendering
        get_line_height(game, &ray);
        // Update texture pixels for the current column
        update_texture_pixels(game, &ray, x);
        x++; // Move to the next column
    }
}