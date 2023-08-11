#include "../include/cub3d.h"

int	key_press_handler(int key, t_game *game)
{
	if (key == XK_Escape)
		free_exit(game, 0);
	if (key == XK_Left)
		game->player.rotate -= 1;
	if (key == XK_Right)
		game->player.rotate += 1;
	if (key == XK_w)
		game->player.move_y = 1;
	if (key == XK_a)
		game->player.move_x = -1;
	if (key == XK_s)
		game->player.move_y = -1;
	if (key == XK_d)
		game->player.move_x = 1;
	if (key == XK_Shift_L)
		game->player.speed = 0.075;
	return (0);
}

int	key_release_handler(int key, t_game *game)
{
	if (key == XK_Escape)
		free_exit(game, 0);
	if (key == XK_Left && game->player.rotate <= 1)
		game->player.rotate = 0;
	if (key == XK_Right && game->player.rotate >= -1)
		game->player.rotate = 0;
	if (key == XK_w && game->player.move_y == 1)
		game->player.move_y = 0;
	if (key == XK_s && game->player.move_y == -1)
		game->player.move_y = 0;
	if (key == XK_a && game->player.move_x == -1)
		game->player.move_x += 1;
	if (key == XK_d && game->player.move_x == 1)
		game->player.move_x -= 1;
	if (key == XK_Shift_L)
		game->player.speed = SPEED;
	return (0);
}

void	key_input(t_game *game)
{
	mlx_hook(game->win, ClientMessage, NoEventMask, end_game, game);
	mlx_hook(game->win, KeyPress, KeyPressMask, key_press_handler, game);
	mlx_hook(game->win, KeyRelease, KeyReleaseMask, key_release_handler, game);
}