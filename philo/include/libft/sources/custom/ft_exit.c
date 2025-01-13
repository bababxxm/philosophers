/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:44:09 by sklaokli          #+#    #+#             */
/*   Updated: 2024/12/17 16:49:20 by sklaokli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_exit(char *s, bool status)
{
	if (status == EXIT_SUCCESS)
	{
		if (!s)
			exit(EXIT_SUCCESS);
		while (*s)
			write(STDOUT_FILENO, s++, 1);
		write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (status == EXIT_FAILURE)
	{
		if (!s)
			exit(EXIT_SUCCESS);
		while (*s)
			write(STDERR_FILENO, s++, 1);
		write(STDERR_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
