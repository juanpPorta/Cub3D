#include "../include/cub3d.h"
/*In summary, the set_image_pixel function allows you to set the color of a
specific pixel at the given (x, y) coordinates within an image. It calculates
the index of the pixel in the image's address array based on the coordinates
and the image's line length, and then assigns the provided color value to that
pixel in the image.*/
/*
  | |
  | |
  | |
  | |
  | |    *
  | |
  | |
  | |
  | |
  | |
  | |
  | |
  | |
  | |
*/
void	set_image_pixel(t_img *image, int x, int y, int color)
{
    // Set a pixel in the image with a given color
    // This function sets the color of a pixel at the specified (x, y) coordinates
    // within an image.
	int	pixel; // Index of the pixel in the image's address array
	// Calculate the index of the pixel in the image's address array
    // The image's line_len specifies the number of bytes in a row, and each pixel is 4 bytes.
	pixel = y * (image->line_len / 4) + x;
	// Assign the specified color value to the pixel in the image's address array
	image->addr[pixel] = color;
}
/*In summary, the set_frame_image_pixel function sets a pixel in the frame
image based on the texture data retrieved from the texture_pixels array.
If the texture pixel has a non-black color, it sets the corresponding color
in the frame image. If the pixel is in the upper half of the screen, it's
set to the ceiling color, and if it's in the lower half of the screen, it's
set to the floor color. This function is responsible for creating the final
frame image that will be displayed on the screen.*/
/*
  | |
  | |
  | |
  | |
  | |    *
  | |   ***
  | | *****
  | |*******
  | | *******
  | |   ***
  | |    *
  | |
  | |
  | |
*/
void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y)
{
	// Set a pixel in the frame image using texture data or background colors
    // This function sets a pixel in the frame image based on the texture data
    // from the texture_pixels array, or assigns ceiling/floor colors if the pixel
    // is part of the background.
	if (game->texture_pixels[y][x] > 0)
		// If the texture pixel has a non-black color, set the corresponding color in the frame image
		set_image_pixel(image, x, y, game->texture_pixels[y][x]);
	else if (y < game->win_height / 2)
        // If the pixel is in the upper half of the screen, set it to the ceiling color
		set_image_pixel(image, x, y, game->texture.hex_ceiling);
	else if (y < game->win_height -1)
        // If the pixel is in the lower half of the screen, set it to the floor color
		set_image_pixel(image, x, y, game->texture.hex_floor);
}
/*In summary, the init_img_new function initializes a new image structure
with the provided width and height. It uses the init_img function to set
initial values for the image structure. Then, it creates a new image using
the mlx_new_image function from the provided width and height. If the image
creation is successful, it retrieves important information about the image,
such as its data address, bits per pixel (bpp), line length, and endianness,
which are stored in the image structure for later use in rendering. If the
image creation fails, the function calls free_exit to free resources and
exit the program with an error code.*/
void	init_img_new(t_game *game, t_img *image, int width, int height)
{
	// Initialize a new image structure
    // This function initializes a new image structure using the provided dimensions.	
	
	// Initialize the image structure using the init_img function
	init_img(image);
    // Create a new image using the mlx_new_image function from the provided width and height
	image->img = mlx_new_image(game->mlx, width, height);
    // Check if the image creation was successful
	if (image->img == NULL)
	    // If not, free resources and exit the program with an error code
		free_exit(game, 1);
	// Get the address of the image data, its bits per pixel (bpp), line length, and endianness
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return ;
}
/*In summary, the draw_frame function is responsible for drawing the entire
frame of the game screen. It initializes an image structure to store the frame
data, creates a new image with the dimensions of the game window, iterates
through each pixel on the screen, sets the pixel color using the
set_frame_image_pixel function, puts the frame image onto the game window
using mlx_put_image_to_window, and finally, destroys the frame image to
free resources. This function effectively renders the game scene and displays
it on the screen.*/
void    draw_frame(t_game *game)
{
	// Draw the entire frame of the game screen
    // This function iterates through each pixel of the screen and draws the frame.
    t_img	image; // Holds the image data for the frame
	int		x; // Loop variables for x and y coordinates
	int		y; // Loop variables for x and y coordinates

	image.img = NULL; // Initialize the image structure
	// Initialize a new image with the dimensions of the game window
	init_img_new(game, &image, game->win_width, game->win_height);
	// Iterate through each row (y-coordinate) of the screen
	y = 0;
	while (y < game->win_height)
	{
		// Iterate through each column (x-coordinate) of the screen
		x = 0;
		while (x < game->win_width)
		{
            // Set the pixel at the current (x, y) coordinates in the frame image
			set_frame_image_pixel(game, &image, x, y);
			x++; // Move to the next column
		}
		y++; // Move to the next row
	}
    // Put the frame image onto the game window using mlx_put_image_to_window
	mlx_put_image_to_window(game->mlx, game->win, image.img, 0, 0);
    // Destroy the frame image to free resources
	mlx_destroy_image(game->mlx, image.img);
}
