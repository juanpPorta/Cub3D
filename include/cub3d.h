#ifndef CUBED_H
# define CUBED_H
// Libraries
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include <X11/X.h>
// Window Size (640 x 480)
# define WIN_WIDTH 640
# define WIN_HEIGHT 480
// Texture Size (64 x 64)
# define TEX_SIZE 64 // Size of textures in pixels (64 x 64)
// BOOL
# define TRUE 1
# define FALSE 0
// Map
# define SPEED 0.025
# define ROT_SPEED 0.07
// Error Messages
# define USAGE "Usage: ./cub3d <map_of_your_choice.cub>\n"
# define NOTCUB "Error: File is not a .cub file\n"
# define NOTXMP "Error: File is not a .xpm file\n"
# define ISDIR "Error: File is a directory\n"
# define NOFILE "Error: File does not exist or missing permissions\n"
# define NOARG "Error: No file given\n"
# define INVRGB "Error: Invalid RGB value\n"
# define INVMAP "Error: Invalid map\n"
# define INVMAPCHAR "Error: Invalid map character\n"
# define INVNUMPLAYER "Error: Invalid number of players\n"
# define INVTEXTURE "Error: Invalid texture\n"
# define MISSINGTEXTURE "Error: Missing texture\n"
# define MISSINGRGB "Error: Missing RGB value\n"
# define INVPLAYERPOS "Error: Invalid player position\n"
# define MAPTOOSMALL "Error: Map is too small\n"
# define MAPMISSINGWALLS "Error: Map is missing walls\n"
# define MALLOCFAIL "Error: Malloc failed\n"
# define MLXFAIL "Error: MLX failed\n"
# define MLXWINFAIL "Error: MLX window failed\n"
# define MLXIMGFAIL "Error: MLX image failed\n"

enum e_direction
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef struct s_rgb
{
	int r;  // Red component of RGB color
	int g;  // Green component of RGB color
	int b;  // Blue component of RGB color
} t_rgb;

typedef struct s_ray
{
	double camera_x;     // Camera plane coordinate for the current column
	double dir_x;        // X-direction of the ray
	double dir_y;        // Y-direction of the ray
	int map_x;           // Map grid position (X-coordinate)
	int map_y;           // Map grid position (Y-coordinate)
	int step_x;          // Step direction along the X-axis
	int step_y;          // Step direction along the Y-axis
	double sidedist_x;   // Distance to the next X-side of the grid
	double sidedist_y;   // Distance to the next Y-side of the grid
	double deltadist_x;  // Delta distance along the X-axis
	double deltadist_y;  // Delta distance along the Y-axis
	double wall_dist;    // Distance to the wall hit by the ray
	double wall_x;       // Exact position of the wall hit
	int side;            // Flag indicating which side of the wall was hit (0 for X, 1 for Y)
	int line_height;     // Height of the wall slice to render
	int draw_start;      // Starting pixel for rendering the wall slice
	int draw_end;        // Ending pixel for rendering the wall slice
} t_ray;

typedef struct s_map
{
	int fd;               // File Descriptor of the map file
	int line_count;       // Number of lines in the map file
	int width;            // Max Width of Visual Map to make a square map
	int height;           // Height of Visual Map
	int eom;              // End of Map flag
	char *path;           // Path to the map file
	char **map;           // Parsed map data (with textures and RGB)
} t_map;

typedef struct s_texture
{
	char *north;          // Path to the north-facing wall texture
	char *south;          // Path to the south-facing wall texture
	char *east;           // Path to the east-facing wall texture
	char *west;           // Path to the west-facing wall texture
	t_rgb floor;          // RGB color of the floor
	t_rgb ceiling;        // RGB color of the ceiling
	int x;                // X-coordinate of the texture on the wall
	int y;                // Y-coordinate of the texture on the wall
	int size;             // Size of the texture
	int index;            // Index of the current texture being used
	double pos;           // Position of the texture on the wall
	double step;          // Step size for texture mapping
	unsigned long hex_floor;    // Hexadecimal color of the floor (converted from RGB)
	unsigned long hex_ceiling;  // Hexadecimal color of the ceiling (converted from RGB)
} t_texture;

typedef struct s_player
{
	int dir;              // Player's direction (0: N, 1: E, 2: S, 3: W)
	double pos_x;         // Player's position on the X-axis
	double pos_y;         // Player's position on the Y-axis
	double dir_x;         // Player's direction vector along the X-axis
	double dir_y;         // Player's direction vector along the Y-axis
	double plane_x;       // Player's camera plane vector along the X-axis
	double plane_y;       // Player's camera plane vector along the Y-axis
	int has_moved;        // Flag indicating if the player has moved
	int move_x;           // Player's movement along the X-axis
	int move_y;           // Player's movement along the Y-axis
	int rotate;           // Player's rotation direction (positive or negative)
	double	speed;		  // Player's movement speed
} t_player;

typedef struct s_img
{
	void *img;            // Image data pointer
	int *addr;            // Address of the image data
	int bpp;              // Bits per pixel
	int line_len;         // Line length in bytes
	int endian;           // Endianness of the image data
} t_img;

typedef struct s_game
{
	int win_width;        // Width of the game window
	int win_height;       // Height of the game window
	void *mlx;            // MLX pointer for graphics handling
	void *win;            // Window pointer for graphics handling
	int **texture_pixels; // Array to store pixel data for textures
	int **textures;       // Array of texture data
	char **f_map;         // Parsed final map data
	t_map map;            // Map data structure
	t_player player;      // Player data structure
	t_ray ray;            // Ray data structure
	t_texture texture;    // Texture data structure
	t_img img;            // Image data structure
} t_game;

// main.c
int		end_game(t_game *game);
int		parse_args(t_game *game, char **argv);
// utils/free.c
void    free_texture_struct(t_texture *texture);
void    free_img_struct(t_img *img);
void    free_map_struct(t_map *map);
void    free_structs(t_game *game);
void    free_exit(t_game *game, int exit_code);
// utils/utils.c
int		array_size(char **array);
int 	err_msg(char *msg, int ret);
int 	ft_strcmp(char *s1, char *s2);
// utils/utils2.c
void    free_void_array(void **array);
void    free_int_array(int *array);
void    free_char_array(char **array);
char    *rem_nl(char *line);
// init/init_game.c
void    init_game(t_game *game);
void    init_rgb(t_rgb *rgb);
void    init_img(t_img *img);
void    init_map(t_map *map);
void    init_ray(t_ray *ray);
// init/init_player.c
void	init_player_north_south(t_player *player);
void	init_player_east_west(t_player *player);
void    init_player_pos(t_game *game);
void    init_player(t_player *player);
// init/init_mlx.c
void    init_mlx(t_game *game);
// init/textures.c
void    init_texture(t_texture *texture);
void	init_texture_img(t_game *game, t_img *image, char *path);
void	init_textures(t_game *game);
int		*xpm_to_img(t_game *game, char *path);
// parse/check_utils.c
int		ext_check_cub(char *file);
int 	ext_check_xpm(char *file);
int 	is_valid_file(char *file);
int 	check_arg(char **argv);
// parse/f_map_finalize.c
void    resize_line(t_game *game, int i);
void    make_map_square(t_game *game);
void    fill_spaces_set_dimensions(t_game *game);
// parse/load_full_map.c
int 	get_line_count(char *path);
int		load_info(t_game *game, char *path);
void	fill_map(t_game *game, int row, int col, int i);
// parse/map_wall_checks.c
int  	check_top_bottom(t_game *game);
int  	check_sides(t_game *game);
int  	check_offsets(t_game *game);
int  	check_map_walls(t_game *game);
// parse/parse_f_map.c
int 	validate_final_map(t_game *game);
int 	check_validate_map(t_game *game);
// parse/parse_f_map2.c
int  	check_map_chars(t_game *game);
int  	check_player(t_game *game);
int  	check_player_position(t_game *game);
int  	check_empty_lines(t_game *game);
// parse/parse_rgb.c
unsigned long   rgb_to_hex(t_game *game, char *type);
int 	load_rgb(t_game *game, char **rgb, char *type);
int 	valid_rgb(t_game *game, char *line);
int 	get_rgb(t_game *game, char *line);
int 	check_validate_rgb(t_game *game);
// parse/parse_textures.c
int 	valid_texture(char *line);
int		check_validate_textures(t_game *game);
char	*get_text(char *line);
// raycast/draw_frame.c
void	set_image_pixel(t_img *image, int x, int y, int color);
void	set_frame_image_pixel(t_game *game, t_img *image, int x, int y);
void	init_img_new(t_game *game, t_img *image, int width, int height);
void	draw_frame(t_game *game);
// raycast/init_text_pixels.c
void    init_texture_pixels(t_game *game);
// raycast/raycast_utils.c
void	init_raycast(t_game *game, t_ray *ray, int x);
void	set_dda(t_game *game, t_ray *ray);
void	perform_dda(t_game *game, t_ray *ray);
void	get_line_height(t_game *game, t_ray *ray);
void	update_texture_pixels(t_game *game, t_ray *ray, int x);
// raycast/raycast_utils2.c
void	get_texture_index(t_game *game, t_ray *ray);
// raycast/raycast.c
void	raycast(t_game *game);
// raycast/render_frame.c
void	render_frame(t_game *game);
int		render(t_game *game);
// movement/key_input.c
int		key_press_handler(int key, t_game *game);
int		key_release_handler(int key, t_game *game);
void	key_input(t_game *game);
// movement/move_player.c
int		move_player(t_game *game);
// movement/check_valid_move.c
bool	is_valid_pos(t_game *game, double x, double y);
int 	check_movement(t_game *game, double new_x, double new_y);
// movement/rotate_player.c
int		rotate_left_right(t_game *game, double rotspeed);
int 	rotate_player(t_game *game, double rot_dir);
// misc/debug_utils.c
void 	print_map(t_game *game);
void 	print_rgb(t_game *game);
void 	print_final_map(t_game *game);
void 	print_textures(t_game *game);
void 	print_player(t_game *game);

#endif