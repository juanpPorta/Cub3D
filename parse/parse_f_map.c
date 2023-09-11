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
    if (check_player_position(game) == FALSE || check_player(game) == FALSE)
    {
        printf("CHECK PLAYER\n");
        return (FALSE);
    }
    return (TRUE);
}

static void find_finalmap_dimensions(t_game *game)
{
    int i;

    i = 0;
    while (game->map.map[i])
    {

        if (game->map.map[i][0] == '\0' || ft_isalpha(game->map.map[i][0]))
            i++;
        else if (game->map.map[i][0] == '1' || game->map.map[i][0] == ' ')
        {
            game->map.height++;
            i++;
        }
        else
            i++;

    }
}

int check_validate_map(t_game *game)
{
    int i;
    int j;

    find_finalmap_dimensions(game);
    printf("MAP HEIGHT 1: %d\n", game->map.height);
    // game->map.height = game->map.line_count - 8;
    printf("MAP HEIGHT 2: %d\n", game->map.height);
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