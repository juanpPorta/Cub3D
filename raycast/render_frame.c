#include "../include/cub3d.h"

/*In summary, the render_frame function coordinates the steps required to render
a single frame of the game scene. It starts by initializing the texture pixel
array for the frame using init_texture_pixels, then initializes the ray structure
for raycasting using init_ray, performs the raycasting process to calculate
rendering information using raycast, and finally draws the final frame using
the calculated rendering information using draw_frame. This function essentially
manages the rendering process to display the game scene on the screen.*/
void    render_frame(t_game *game)
{
	// Render a single frame of the game scene
    // This function coordinates the steps required to render a frame of the game scene.

    // Initialize the texture pixel array for the frame
    init_texture_pixels(game);
	// Initialize the ray structure for raycasting
    init_ray(&game->ray);
    // Perform the raycasting process to calculate rendering information
    raycast(game);
    // Draw the final frame using the calculated rendering information
    draw_frame(game);
}

int render(t_game *game)
{
    // Render the game scene
    // This function renders the game scene by calling render_frame.

	game->player.has_moved += move_player(game);
	if (game->player.has_moved == 0)
		return (0);
    render_frame(game);
    return (0);
}