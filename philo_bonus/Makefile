# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nazouz <nazouz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/02 10:43:33 by nazouz            #+#    #+#              #
#    Updated: 2024/03/25 05:11:38 by nazouz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo_bonus

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror

INCLUDES		=	./philosophers_bonus.h

RM				=	rm -f

SRCS				=	\
					./main_bonus.c \
					./parse_bonus.c \
					./data_init_bonus.c \
					./utils/ft_atoi_bonus.c \
					./utils/ft_putstr_fd_bonus.c \
					./utils/ft_strcmp_bonus.c \
					./utils/ft_strdup_bonus.c \
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

re : fclean all