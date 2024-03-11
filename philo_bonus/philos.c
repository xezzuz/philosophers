/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:51:12 by nazouz            #+#    #+#             */
/*   Updated: 2024/03/05 19:30:36 by nazouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(void)
{
	int			i;
	int			id;
	sem_t		*sem;
	int			forks;
	// int			pids[5];

    sem_unlink("/forks");
	sem = sem_open("/forks", O_CREAT, 0644, 5);
	i = 0;
	while (i < 5)
	{
		id = fork();
		if (!id)
			break ;
		i++;
	}
	if (id == 0)
	{
		sem_wait(sem);
		printf("[%d] has taken a fork\n", getpid());
		sem_wait(sem);
		printf("[%d] has taken a fork\n", getpid());
		printf("[%d] is eating\n", getpid());
		sleep(3);
		printf("[%d] is done\n", getpid());
		sem_post(sem);
		sem_post(sem);
	}
	else
	{
		usleep(500);
		// sem_wait(sem);
		// printf("Hello from parent process\n");
		// sem_post(sem);
		i = 0;
		while (1)
		{
			// printf("Waiting for a child\n");
			id = wait(NULL);
			if (id <= 0)
				break ;
			// printf("[%d] Exited\n", id);
		}
		printf("DONE\n");
		sem_close(sem);
        sem_unlink("/forks");
	}
}
