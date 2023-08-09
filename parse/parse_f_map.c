#include "../include/cub3d.h"

int validate_final_map(t_game *game)
{
    if (check_map_chars(game) == FALSE)
    {
        printf("CHECK MAP CHARS\n");
        return (FALSE);
    }
    if (check_empty_lines(game) == FALSE)
    {
        printf("CHECK EMPTY LINES\n");
        return (FALSE);
    }
    if (check_map_walls(game) == FALSE)
    {
        printf("CHECK MAP WALLS\n");
        return (FALSE);
    }
    if (check_player(game) == FALSE || check_player_position(game) == FALSE)
    {
        printf("CHECK PLAYER\n");
        return (FALSE);
    }
    return (TRUE);
}

int check_validate_map(t_game *game)
{
    int i;
    int j;

    game->map.height = game->map.line_count - 8;
    if (game->map.height < 3)
        return (err_msg(MAPTOOSMALL, 0));
    game->f_map = ft_calloc(game->map.height + 1, sizeof(char *));
    if (game->f_map == NULL)
        return (err_msg(MALLOCFAIL, 0));
    i = 0;
    j = game->map.line_count - game->map.height;
    while (game->map.map[j] != NULL)
    {
        game->f_map[i] = rem_nl(game->map.map[j]);
        j++;
        i++;
    }
    if (validate_final_map(game) == FALSE)
        return (FALSE);
    else
        return (TRUE);
}