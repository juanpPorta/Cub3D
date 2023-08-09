#include "../include/cub3d.h"

int	rotate_left_right(t_game *game, double rotspeed)
{
	t_player	*p;
	double		tmp_x;

	p = &game->player;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
}

int rotate_player(t_game *game, double rot_dir)
{
    int		moved;
	double	rotspeed;

	moved = 0;
	rotspeed = ROT_SPEED * rot_dir;
	moved += rotate_left_right(game, rotspeed);
	return (moved);
}