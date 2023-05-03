/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:02:23 by ankhabar          #+#    #+#             */
/*   Updated: 2023/05/03 13:11:20 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	invalid_param_number(int code, char **params)
{
	int	i;

	i = 0;
	while (params[i])
		i++;
	(void)code;
	if (i != code)
	{
		ft_dprintf(2, FRED"Error\n"ERRPARAM"\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	invalid_chars(char *str)
{
	int		i;
	bool	decimal_flag;

	i = 0;
	decimal_flag = false;
	while (str[i] != '\0')
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ','
			&& str[i] != '-' && str[i] != '+')
		{
			if (str[i] == '.' && decimal_flag == false)
				decimal_flag = true;
			else
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

bool	not_valid_parameter(char *to_check, double min, double max)
{
	if (invalid_chars(to_check))
	{
		ft_dprintf(2, FRED"Error\n"ERRCHAR"\n");
		return (EXIT_FAILURE);
	}
	if (ft_atof(to_check) < min || ft_atof(to_check) > max)
	{
		ft_dprintf(2, FRED"Error\n"ERRRANGE"\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	not_valid_number_of_commas(char *to_check)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (to_check[i] != '\0')
	{
		if (to_check[i++] == ',')
			count++;
	}
	if (count != 2)
	{
		ft_dprintf(2, FRED"Error\n"ERRCOMMAS"\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	not_valid_range(char *to_check, double min, double max)
{
	char	**tab;
	int		i;

	if (not_valid_number_of_commas(to_check))
		return (EXIT_FAILURE);
	tab = ft_split(to_check, ',');
	if (tab[2] == NULL || tab[3] != NULL)
		return (free_tab(tab), EXIT_FAILURE);
	i = 0;
	while (tab[i])
	{
		if (not_valid_parameter(tab[i++], min, max))
			return (free_tab(tab), EXIT_FAILURE);
	}
	return (free_tab(tab), EXIT_SUCCESS);
}
