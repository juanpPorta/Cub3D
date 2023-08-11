#include "../include/cub3d.h"

int  check_map_chars(t_game *game)
{
    int i;
    int j;

    i = 0;
    if (game->f_map == NULL)
        return (FALSE);
    while (game->f_map[i])
    {
        j = 0;
        while (game->f_map[i][j])
        {
            if (!ft_strchr("01NSEW ", game->f_map[i][j]))
                return (FALSE);
            j++;
        }
        i++;
    }
    return (TRUE);
}
/*Here's why the 0.5 adjustment is used for the player pos_x, pos_y values:

Grid-Based Positioning: The game map is divided into grid cells. Each cell is a
discrete unit, and the positions of objects (including the player) are often
stored as integer values that represent the row and column indices of the grid cells.

Aligning with Grid Cells: When you specify the player's position as
(double)i + 0.5 and (double)j + 0.5, it effectively shifts the player's
position from the corner of the grid cell to the center of the grid cell.
This ensures that the player is placed in the middle of the cell, which provides
a more accurate starting point for rendering and movement calculations.

Raycasting Accuracy: In a raycasting-based game like the one you're developing,
accurate positioning is crucial for the raycasting algorithm to work correctly.
The player's position affects how rays are cast into the game world and how
collisions with walls are detected. Placing the player at the center of the cell
helps with precise raycasting calculations.*/
int  check_player(t_game *game)
{
    int i;
    int j;
    int player_count;

    i = 0;
    player_count = 0;
    while (game->f_map[i])
    {
        j = 0;
        while (game->f_map[i][j])
        {
            if (ft_strchr("NSEW", game->f_map[i][j]))
            {
                player_count++;
                game->player.pos_x = (double)j + 0.5;
                game->player.pos_y = (double)i + 0.5;
                game->player.dir = game->f_map[i][j];
                game->f_map[i][j] = '0';
            }
            j++;
        }
        i++;
    }
    if (player_count != 1)
        return (FALSE);
    return (TRUE);
}

int check_player_position(t_game *game)
{
    int row = (int)(game->player.pos_y);
    int col = (int)(game->player.pos_x);

    if (game->f_map[row][(col + 1)] == '\0'
        || game->f_map[row][(col + 1)] == ' '
        || (col > 0 && game->f_map[row][(col - 1)] == ' ')
        || (row < (game->map.height - 1) && game->f_map[row + 1][col] == ' ')
        || (row > 0 && game->f_map[row - 1][col] == ' '))
    {
        return (FALSE);
    }

    return (TRUE);
}





int  check_empty_lines(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->f_map[i])
    {
        j = 0;
        if (game->f_map[i][0] == '\0')
            return (FALSE);
        while (game->f_map[i][j] && game->f_map[i][j] == ' ')
        {
            if (game->f_map[i][j + 1] == '\0')
                return (FALSE);
            j++;
        }
        i++;
    }
    return (TRUE);
}
