#include "../include/cub3d.h"

/*In summary, the init_texture_pixels function initializes the array texture_pixels,
which is used to store pixel data for the frame's textures. It first checks if
the texture_pixels array already exists and frees its memory if needed.
Then, it allocates memory for the texture_pixels array using ft_calloc, where
each row represents a row of pixels, and each element in the row represents a pixel.
If memory allocation fails at any point, the function calls free_exit to free
resources and exit the program with an error code.*/
void    init_texture_pixels(t_game *game)
{
	// Initialize the texture pixel array for the frame
    // This function initializes the array to store pixel data for the frame's textures.
    int i; // Loop variable for iteration

	// If texture_pixels array already exists, free its memory
    if (game->texture_pixels != NULL) //Reset texture_pixels for next frame
        free_void_array((void **)game->texture_pixels);
	// Allocate memory for the texture_pixels array using ft_calloc
    game->texture_pixels = ft_calloc(game->win_height + 1, sizeof(int *)); //
    if (game->texture_pixels == NULL)
	    // If memory allocation fails, free resources and exit with an error code
        free_exit(game, 1);
    // Iterate through each row (y-coordinate) of the texture_pixels array
    i = 0;
    while (i < game->win_height) // Allocate memory for each row of pixels
    {
	    // Allocate memory for each pixel in the row
        game->texture_pixels[i] = ft_calloc(game->win_width + 1, sizeof(int *)); // Allocate memory for each pixel
        if (game->texture_pixels[i] == NULL)
		    // If memory allocation fails, free resources and exit with an error code
            free_exit(game, 1);
        i++; // Move to the next row
    }
}