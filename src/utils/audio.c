/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:51:03 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 14:17:34 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Sound playback.
**
** This used to be system("aplay -q file &"), which hands the job to a shell
** that forks aplay, backgrounds it and exits. The player is then reparented
** to init, so it outlives the game: quitting any way other than the clean
** path left the music running, and the only cleanup was a pkill in
** game_over that a crash or a kill -9 never reaches.
**
** Here aplay is a direct child, and PR_SET_PDEATHSIG asks the kernel to
** kill it as soon as this process dies, whatever the reason. No orphans,
** no pkill, and no shell spawned per sound.
*/

#include "../../include/main.h"
#include <sys/prctl.h>
#include <signal.h>

/*
** SIGCHLD to SIG_IGN so finished players are reaped by the kernel instead
** of piling up as zombies -- the game fires one per shot.
*/
void	ft_audio_init(void)
{
	signal(SIGCHLD, SIG_IGN);
}

static void	run_aplay(const char *wav)
{
	prctl(PR_SET_PDEATHSIG, SIGKILL);
	if (getppid() == 1)
		_exit(0);
	execlp("aplay", "aplay", "-q", wav, (char *)NULL);
	_exit(0);
}

void	ft_play(const char *wav)
{
	if (fork() != 0)
		return ;
	run_aplay(wav);
}

/*
** aplay cannot loop, so a supervisor child restarts it forever. Both the
** supervisor and each aplay carry PR_SET_PDEATHSIG, so the whole chain
** dies with the game.
*/
void	ft_play_loop(const char *wav)
{
	pid_t	child;

	if (fork() != 0)
		return ;
	prctl(PR_SET_PDEATHSIG, SIGKILL);
	if (getppid() == 1)
		_exit(0);
	signal(SIGCHLD, SIG_DFL);
	while (1)
	{
		child = fork();
		if (child == 0)
			run_aplay(wav);
		if (child < 0)
			_exit(1);
		waitpid(child, NULL, 0);
	}
}
