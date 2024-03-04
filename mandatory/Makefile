# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 10:43:33 by nazouz            #+#    #+#              #
#    Updated: 2024/03/03 17:51:20 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -pthread -g

INCLUDES		=	./philosophers.h

RM				=	rm -f

SRCS				=	\
					./main.c \
					./parse.c \
					./data_init.c \
					./utils/ft_atoll.c \
					./utils/ft_putstr_fd.c \
					./philosophers.c \
					./philosophers_actions.c \
					./utils.c

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