# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abettini <abettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 16:16:09 by abettini          #+#    #+#              #
#    Updated: 2024/01/24 15:49:43 by abettini         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#----------------------------------------------

NOCOL = \e[0m
GREEN = \e[1;92m
RED = \e[1;31m
CYAN = \e[1;36m
BULE = \e[1;34m
YELL = \e[0;33m
TCOL = $(CYAN)
RMD = $(GREEN)successfully $(RED)removed$(NOCOL)
CMP = $(GREEN)successfully compiled$(NOCOL)
ALC = $(YELL)already compiled$(NOCOL)

#----------------------------------------------

CC = cc

RM = rm -rf

NAME = philo

CFLAGS = -Wall -Werror -Wextra -g

TFLAG = -lpthread

SRC = main.c \
	philo_main.c \
	philo_life.c \
	philo_death.c \
	philo_other.c \
	philo_utils.c \
	err_check.c

OBJ = $(SRC:.c=.o)

#----------------------------------------------

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAG) $(OBJ) $(TFLAG) -o $(NAME)
		echo "$(TCOL)$(NAME) $(CMP)"

clean:
	$(RM) $(OBJ)
	echo "$(TCOL)object files $(RMD)"
		

fclean: clean
		if [ -f $(NAME) ]; then\
			$(RM) $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

re: fclean all

.PHONY: all re clean fclean

.SILENT:
