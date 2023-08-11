#include "../include/cub3d.h"

static int	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * game->player.speed;
	new_y = game->player.pos_y + game->player.dir_y * game->player.speed;
	return (check_movement(game, new_x, new_y));
}

static int	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_x * game->player.speed;
	new_y = game->player.pos_y - game->player.dir_y * game->player.speed;
	return (check_movement(game, new_x, new_y));
}

static int	strafe_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * game->player.speed;
	new_y = game->player.pos_y - game->player.dir_x * game->player.speed;
	return (check_movement(game, new_x, new_y));
}

static int	strafe_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x - game->player.dir_y * game->player.speed;
	new_y = game->player.pos_y + game->player.dir_x * game->player.speed;
	return (check_movement(game, new_x, new_y));
}

int	move_player(t_game *game)
{
	int	moved;

	moved = 0;
	if (game->player.move_y == 1)
		moved += move_forward(game);
	if (game->player.move_y == -1)
		moved += move_backward(game);
	if (game->player.move_x == -1)
		moved += strafe_left(game);
	if (game->player.move_x == 1)
		moved += strafe_right(game);
	if (game->player.rotate != 0)
		moved += rotate_player(game, game->player.rotate);
	return (moved);
}