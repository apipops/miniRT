/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ankhabar <ankhabar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 17:20:38 by ankhabar          #+#    #+#             */
/*   Updated: 2023/04/27 17:22:47 by ankhabar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	ft_atof_aux(const char *nptr)
{
	double	res;
	double	decimal;

	res = 0;
	decimal = 0.1;
	while ('0' <= *nptr && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr == '.')
	{
		nptr++;
		while ('0' <= *nptr && *nptr <= '9')
		{
			res += (*nptr - '0') * decimal;
			decimal /= 10;
			nptr++;
		}
	}
	return (res);
}

double	ft_atof(const char *nptr)
{
	double	res;
	int		sign;

	sign = 1;
	while ((*nptr == ' ') || ('\t' <= *nptr && *nptr <= '\r'))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	res = ft_atof_aux(nptr);
	res *= sign;
	return (res);
}

// to test ft_atof
// void	test()
// {
// 	int		i;
// 	char	*temp;
// 	char	**test;

// 	i = 0;
// 	temp = "-50.0,0,20";
// 	test = ft_split(temp, ',');
// 	while (test[i])
// 		printf("[%f]\n", ft_atof(test[i++]));
// 	printf("[%f]\n", ft_atof("5.111"));
// 	printf("[%f]\n", atof("50.0"));
// 	printf("[%f]\n", atof("50"));
// }
