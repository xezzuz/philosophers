# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 10:43:33 by nazouz            #+#    #+#              #
#    Updated: 2024/03/15 21:28:19 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_bonus

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread

INCLUDES		=	./philosophers_bonus.h

RM				=	rm -f

SRCS				=	\
					./main_bonus.c \
					./parse_bonus.c \
					./data_init_bonus.c \
					./utils/ft_atoll_bonus.c \
					./utils/ft_putstr_fd_bonus.c \
					./utils/ft_strjoin_bonus.c \
					./philosophers_bonus.c \
					./philosophers_actions_bonus.c \
					./utils_bonus.c

OBJS			=	$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c $(INCLUDES)
	$(CC) -c $(CFLAGS) $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean :
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
	$(RM) $(NAME) $(NAME_BONUS)

a : all clean

re : fclean all