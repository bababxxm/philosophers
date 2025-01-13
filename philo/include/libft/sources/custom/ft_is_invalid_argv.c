/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_invalid_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:46:11 by sklaokli          #+#    #+#             */
/*   Updated: 2025/01/13 07:27:08 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

bool	ft_is_invalid_argv(int argc, char *argv[])
{
	int	i;

	if (!*argv || !argv)
		return (true);
	i = -1;
	while (++i < argc)
	{
		if (ft_is_empty_str(argv[i]))
			return (true);
	}
	return (false);
}
