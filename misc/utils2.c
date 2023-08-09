#include "../include/cub3d.h"

char    *rem_nl(char *line)
{
    char    *new_line;
    int     i;

    i = 0;
    if (!line)
        return (NULL);
    new_line = NULL;
    if (ft_strchr(line, '\n'))
        new_line = malloc(sizeof(char) * (ft_strlen(line)));
    else
        new_line = malloc(sizeof(char) * (ft_strlen(line) + 1));
    if (!new_line)
        return (NULL);
    while (line[i] != '\0' && line[i] != '\n')
    {
        new_line[i] = line[i];
        i++;
    }
    new_line[i] = '\0';
    return (new_line);
}

void    free_char_array(char **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    if (array)
    {
        free(array);
        array = NULL;
    }
}

void    free_int_array(int *array)
{
    if (array) {
        free(array);
    }
}

void    free_void_array(void **array)
{
    int i;

    i = 0;
    if (!array)
        return ;
    while (array[i])
    {
        free(array[i]);
        i++;
    }
    if (array)
    {
        free(array);
        array = NULL;
    }
}
