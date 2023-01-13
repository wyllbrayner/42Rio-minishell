/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wjuneo-f <wjuneo-f@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 21:22:43 by glima-de          #+#    #+#             */
/*   Updated: 2022/04/27 12:30:57 by wjuneo-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>

void	init_sigaction(struct sigaction *action, void (*handler)(int), int sig);
void	handler_int(int sig);
void	handler_int_fork(int sig);
void	handler_quit_fork(int sig);
#endif
