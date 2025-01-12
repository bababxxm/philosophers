/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 13:44:13 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/12 00:16:41 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	is_invalid_input(char *input)
{
	if (ft_is_invalid_int(ft_atol(input)))
		return (true);
	while (*input)
	{
		if (!ft_isdigit(*input) || *input == '-')
			return (true);
		input++;
	}
	return (false);
}

// bool	is_invalid_input(t_data data, char *ptr, long nbr)
// {
// 	int	i;
// 	int	sign_cnt;

// 	i = 0;
// 	sign_cnt = 0;
// 	if (ft_is_invalid_int(nbr) || has_duplicate(data.a, nbr))
// 		return (true);
// 	while (ptr[i])
// 	{
// 		if (!ft_isdigit(ptr[i]) && !ft_issign(ptr[i]))
// 			return (true);
// 		if (ptr[i] == '+' || ptr[i] == '-')
// 		{
// 			if (i != 0 || !ptr[i + 1])
// 				return (true);
// 			sign_cnt++;
// 		}
// 		if (sign_cnt > 1)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }
