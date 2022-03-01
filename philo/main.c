/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aymoulou <aymoulou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:20:18 by aymoulou          #+#    #+#             */
/*   Updated: 2022/02/27 15:26:44 by aymoulou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	error_handling(int ac)
{
	if (ac < 4)
	{
		ft_putstr_fd("\e[1;91mError: Too few arguments\e[0m", 2);
		return (1);
	}
	else if (ac > 5)
	{
		ft_putstr_fd("\e[1;91mError: Too many arguments\e[0m", 2);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	t_args	args;
	int		index;

	philo = NULL;
	index = 0;
	args.eat = 0;
	if (error_handling(--ac) || args_init(ac, av, &args))
		return (1);
	pthread_mutex_init(&args.is_dead, NULL);
	pthread_mutex_init(&args.print, NULL);
	pthread_mutex_lock(&args.is_dead);
	philo = philo_init(&args);
	if (!philo)
		return (1);
	pthread_mutex_lock(&args.is_dead);
	while (index < args.philo_number)
		pthread_mutex_destroy(&philo[index++].fork);
	pthread_mutex_destroy(&args.print);
	free(philo);
	return (0);
}
