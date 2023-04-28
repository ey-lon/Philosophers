# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abettini <abettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 16:16:09 by abettini          #+#    #+#              #
#    Updated: 2023/04/28 15:12:12 by abettini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)

#----------------------------------------------

CC = cc

RM = rm -rf

NAME = philo

SRC = main.c \
	philo_life.c \
	philo_death.c \
	philo_other.c \
	philo_utils.c \
	err_check.c

CFLAGS = -Wall -Werror -Wextra -g

TFLAG = -lpthread

#----------------------------------------------

all: $(NAME)

$(NAME):
	$(CC) $(SRC) $(TFLAG) -o $(NAME)
	echo "$(TCOL)$(NAME) $(CMP)"

clean:

fclean: clean
		if [ -f $(NAME) ]; then\
			$(RM) $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

re: fclean all

.PHONY: $(NAME) all re clean fclean

.SILENT: