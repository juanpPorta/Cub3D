#include "../include/cub3d.h"



bool is_valid_pos(t_game *game, double x, double y)
{
    if (x < 0.25 || x >= game->map.width - 1.25 ||
        y < 0.25 || y >= game->map.height - 0.25)
    {
        return (FALSE);
    }
    
    if (game->f_map[(int)y][(int)x] == '0')
    {
        return (TRUE);
    }
    return (FALSE);
}

int check_movement(t_game *game, double new_x, double new_y)
{
    int moved = 0;
    
    if (is_valid_pos(game, new_x, game->player.pos_y))
    {
        game->player.pos_x = new_x;
        moved = 1;
    }
    
    if (is_valid_pos(game, game->player.pos_x, new_y))
    {
        game->player.pos_y = new_y;
        moved = 1;
    }
    
    return moved;
}
