#include "../include/cub3d.h"

void    init_ray(t_ray *ray)
{
	ray->camera_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->deltadist_x = 0;
	ray->deltadist_y = 0;
	ray->wall_dist = 0;
	ray->wall_x = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void    init_map(t_map *map)
{
    map->fd = 0;
    map->line_count = 0;
    map->width = 0;
    map->height = 0;
    map->eom = 0;
    map->path = NULL;
    map->map = NULL;
}

void    init_img(t_img *img)
{
    img->img = NULL;
    img->addr = NULL;
    img->bpp = 0;
    img->line_len = 0;
    img->endian = 0;
}

void    init_rgb(t_rgb *rgb)
{
    rgb->r = 0;
    rgb->g = 0;
    rgb->b = 0;
}

void    init_game(t_game *game)
{
    memset(game, 0, sizeof(t_game));
    game->win_width = WIN_WIDTH;
    game->win_height = WIN_HEIGHT;
    game->mlx = NULL;
    game->win = NULL;
    game->texture_pixels = NULL;
    game->textures = NULL;
    game->f_map = NULL;
    init_ray(&game->ray);
    init_map(&game->map);
    init_img(&game->img);
    init_player(&game->player);
    init_texture(&game->texture);
}