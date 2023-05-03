/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 12:28:09 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 12:51:46 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	which_type_identifier(char *str)
{
	if (ft_strncmp(str, "A", 2) == 0)
		return (0);
	else if (ft_strncmp(str, "C", 2) == 0)
		return (1);
	else if (ft_strncmp(str, "L", 2) == 0)
		return (2);
	else if (ft_strncmp(str, "sp", 3) == 0)
		return (3);
	else if (ft_strncmp(str, "pl", 3) == 0)
		return (4);
	else if (ft_strncmp(str, "cy", 3) == 0)
		return (5);
	else if (str == NULL)
		return (6);
	return (-1);
}

void	parse_line(t_elements *elements, char *line)
{
	int			id;
	char		*tmp;
	char		**words;
	static bool	(*funcs[6])(t_elements *, char **) = {ambient, camera, light,
		sphere, plane, cylinder};

	tmp = ft_strtrim(line, '\n');
	words = ft_split(tmp, ' ');
	free(tmp);
	id = which_type_identifier(words[0]);
	if (id == -1)
		error(words, elements, ERRITI);
	if (id != 6 && funcs[id](elements, words) == EXIT_FAILURE)
		error(words, elements, ERRIPN);
	free_tab(words);
}

void	elements_init(t_elements *elements)
{
	elements->ambient = NULL;
	elements->camera = NULL;
	elements->lights_head = NULL;
	elements->objects_head = NULL;
}

void	parsing(int fd)
{
	t_elements	elements;
	char		*buff;

	elements_init(&elements);
	buff = get_next_line(fd);
	while (buff != NULL)
	{
		parse_line(&elements, buff);
		buff = get_next_line(fd);
	}
	// testinggggggggggggggggggggggggggggggggggggg
	// t_objects *tmp = elements.objects_head;
	// while (tmp->next != NULL)
	// {
	// 	printf("x of an object==[%f]\n", tmp->colors.x);
	// 	printf("id of an object==[%d]\n", tmp->id);
	// 	tmp = tmp->next;
	// }
	// printf("x of an object==[%f]\n", tmp->colors.x);
	// printf("id of an object==[%d]\n", tmp->id);
	free_structures(&elements); // remove when mixing branches
}

// todo:	change output of errors to STDERR everywhere
//			use perror when possible
// to run: /minirt test.rt
int	main(int ac, char *av[])
{
	int	fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
			return (perror("Error at opening"), 1);
		parsing(fd);
		close(fd);
	}
	else
		printf(BWHITE"Second argument required."RESET"\n");
	return (0);
}
