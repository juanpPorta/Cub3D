#include "../include/cub3d.h"

int  check_top_bottom(t_game *game)
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
            if (i == 0 || i == game->map.height - 1)
            {
                if (game->f_map[i][j] != '1' && game->f_map[i][j] != ' ')
                    return (FALSE);
            }
            j++;
        }
        i++;
    }
    return (TRUE);
}

int  check_sides(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->f_map[i])
    {
        j = 0;
        while (game->f_map[i][j] == ' ')
            j++;
        if (game->f_map[i][j] != '1')
            return (FALSE);
        if (game->f_map[i][ft_strlen(game->f_map[i]) - 1] != '1')
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int  check_offsets(t_game *game)
{
    int i;
    int j;

    i = 0;
    while (game->f_map[i])
    {
        j = 0;
        while (game->f_map[i][j])
        {
            if (game->f_map[i][j] == '0')
            {
                if (game->f_map[i][j + 1] == ' ' || game->f_map[i][j - 1] == ' ')
                    return (FALSE);
                if (ft_strlen(game->f_map[i + 1]) < j || ft_strlen(game->f_map[i - 1]) < j)
                    return (FALSE);
                if (game->f_map[i + 1][j] == ' ' || game->f_map[i - 1][j] == ' ')
                    return (FALSE);
            }
            j++;
        }
        i++;
    }
    return (TRUE);
}

int  check_map_walls(t_game *game)
{
    if (check_top_bottom(game) == FALSE)
    {
        printf("CHECK TOP BOTTOM\n");
        return (FALSE);
    }
    if (check_sides(game) == FALSE)
    {
        printf("CHECK SIDES\n");
        return (FALSE);
    }
    if (check_offsets(game) == FALSE)
    {
        printf("CHECK OFFSETS\n");
        return (FALSE);
    }
    return (TRUE);
}
