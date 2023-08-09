#include "../include/cub3d.h"

void    init_mlx(t_game *game)
{
    game->mlx = mlx_init();
    if (game->mlx == NULL)
    {
        err_msg(MLXFAIL, 1);
        free_exit(game, 1);
    }
    game->win = mlx_new_window(game->mlx, game->win_width, game->win_height, "Cub3D");
    if (game->win == NULL)
    {
        err_msg(MLXWINFAIL, 1);
        free_exit(game, 1);
    }
}