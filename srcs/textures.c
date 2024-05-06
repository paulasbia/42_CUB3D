/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolzan- <tbolzan-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:09:59 by tbolzan-          #+#    #+#             */
/*   Updated: 2024/05/06 13:14:16 by tbolzan-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void inicialize_txt(t_main *main)
{
    main->textures.ceiling_color = NULL;
    main->textures.east = NULL;
    main->textures.floor_color = NULL;
    main->textures.north  = NULL;
    main->textures.south  = NULL;
    main->textures.west  = NULL;
    
}

int	save_textures(int *j, char *line, char **filename, int size)
{
	int	flag;
	flag = 0;
	*j += size;
	while (line[*j] == ' ' || line[*j] == '\t')
		(*j)++;
    if (line[*j] == '\n')
    {
        return (-1);
    }
	flag = *j;
	while (line[flag] != '\0' && line[flag] != ' ' && line[flag] != '\t'
		&& line[flag] != '\n')
		flag++;
	*filename = ft_substr(line, (*j), (flag - *j));
	*j = flag;
	return (1);
}

int	compare_args(char *line, int *j, t_main *main)
{
	int	count;
    
	count = 0;
	if (ft_strncmp(&line[*j], "NO ", 3) == 0)
		count += save_textures(j, line, &main->textures.north, 3);
	else if (ft_strncmp(&line[*j], "SO ", 3) == 0)
		count += save_textures(j, line, &main->textures.south, 3);
	else if (ft_strncmp(&line[*j], "WE ", 3) == 0)
		count += save_textures(j, line, &main->textures.west, 3);
	else if (ft_strncmp(&line[*j], "EA ", 3) == 0)
		count += save_textures(j, line, &main->textures.east, 3);
	else if (ft_strncmp(&line[*j], "F ", 2) == 0)
		count += save_textures(j, line, &main->textures.floor_color, 2);
	else if (ft_strncmp(&line[*j], "C ", 2) == 0)
		count += save_textures(j, line, &main->textures.ceiling_color, 2);
	return (count);
}

int	search_and_save_args(t_main *main)
{
	int		i;
	int		j;
	char	*line;
	int		count;

	i = 0;
	count = 0;
	while (main->file_content[i] != NULL)
	{
		if(count == 6)
			break ;
		line = ft_strdup(main->file_content[i]);
		j = 0;
		while (line[j] != '\0' && line[j] != '\n')
		{
			while ((line[j] != '\0' && line[j] == ' ') || line[j] == '\t')
				j++;
			count += compare_args(line, &j, main);
			j++;
		}
		if (line)
			free(line);
		i++;
	}
	main->textures.line_help = i;
	return (count);
}