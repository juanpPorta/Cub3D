#include "../include/cub3d.h"
// Initialize a texture structure with default values
void    init_texture(t_texture *texture)
{
	// Set texture paths to NULL
    texture->north = NULL;
    texture->south = NULL;
    texture->east = NULL;
    texture->west = NULL;
	// Initialize floor and ceiling colors using init_rgb function
    init_rgb(&texture->floor);
    init_rgb(&texture->ceiling);
	// Set texture properties to default values
    texture->x = 0;
    texture->y = 0;
    texture->size = TEX_SIZE;
    texture->index = 0;
    texture->pos = 0;
    texture->step = 0;
    texture->hex_floor = 0x0;
    texture->hex_ceiling = 0x0;
}
/*In this context, the mlx_get_data_addr function is used to retrieve various
information about the image data and set up the image structure to correctly
access the pixel data. The parameters passed to mlx_get_data_addr are:

image->img: The image data obtained from mlx_xpm_file_to_image.

&image->bpp: A pointer to an integer that will hold the number of bits per pixel.

&image->line_len: A pointer to an integer that will hold the number of bytes in each
image row.

&image->endian: A pointer to an integer that will hold the endianess of the pixel data.

After calling mlx_get_data_addr, the image->addr pointer will point to the start of
the pixel data, and the other values (image->bpp, image->line_len, and image->endian)
will be populated with the appropriate values for the image's properties.

By using image->addr, you can access individual pixel values within the image and
manipulate them to render the image on the screen or perform other graphical
operations. Each pixel's color values can be read or modified through this pointer.*/
void	init_texture_img(t_game *game, t_img *image, char *path)
{
	// Initialize the image structure using init_img function to default values
	init_img(image);
	// Load the XPM image from the given path using mlx_xpm_file_to_image
	image->img = mlx_xpm_file_to_image(game->mlx, path, &game->texture.size,
			&game->texture.size);
	// Check if the image loading was successful, if not, free resources and exit
	if (image->img == NULL)
		free_exit(game, 1);
	// Get image data address and related information using mlx_get_data_addr
	image->addr = (int *)mlx_get_data_addr(image->img, &image->bpp,
			&image->line_len, &image->endian);
	return ;
}
// Convert an XPM image to an integer buffer and return the buffer
int	*xpm_to_img(t_game *game, char *path)
{
	t_img	tmp;
	int		*buffer;
	int		x;
	int		y;
    // Initialize a temporary image structure and load the XPM image
	init_texture_img(game, &tmp, path);
	// Allocate memory for the buffer to store the image data
	buffer = ft_calloc(1,
			sizeof * buffer * game->texture.size * game->texture.size);
	if (!buffer)
		free_exit(game, 1);
	// Copy image data from the temporary image structure to the buffer
	y = 0;
	while (y < game->texture.size)
	{
		x = 0;
		while (x < game->texture.size)
		{
			buffer[y * game->texture.size + x]
				= tmp.addr[y * game->texture.size + x];
			++x;
		}
		y++;
	}
	// Destroy the temporary image using mlx_destroy_image
	mlx_destroy_image(game->mlx, tmp.img);
	return (buffer);
}
// Initialize game textures using XPM images
void	init_textures(t_game *game)
{
	// Allocate memory for an array of texture buffers
	game->textures = ft_calloc(5, sizeof * game->textures);
	if (!game->textures)
	{
        err_msg(MALLOCFAIL, 1);
        free_exit(game, 1);
    }
	// Load XPM images into texture buffers and store them in the game structure
	game->textures[NORTH] = xpm_to_img(game, game->texture.north);
	game->textures[SOUTH] = xpm_to_img(game, game->texture.south);
	game->textures[EAST] = xpm_to_img(game, game->texture.east);
	game->textures[WEST] = xpm_to_img(game, game->texture.west);
}