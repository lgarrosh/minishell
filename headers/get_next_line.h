/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgarrosh <lgarrosh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:08:23 by lgarrosh          #+#    #+#             */
/*   Updated: 2022/06/06 13:54:48 by lgarrosh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# define BUFFER_SIZE 10

char		*get_next_line(int fd);
char		*ft_line(char **buff);
char		*ft_new_buff(char *buff);
void		ft_free(void **ch);
long int	ft_read(char **buff, long int i, int fd);

#endif //GET_NEXT_LINE_H
