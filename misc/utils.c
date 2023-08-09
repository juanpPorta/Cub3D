#include "../include/cub3d.h"

int array_size(char **array)
{
    int i;

    i = 0;
    if (!array)
        return (0);
    while (array[i])
        i++;
    return (i);
}

int err_msg(char *msg, int ret)
{
    printf("cub3D %s\n", msg);
    return (ret);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (FALSE);
        i++;
    }
    if (s1[i] != s2[i])
        return (FALSE);
    return (TRUE);
}