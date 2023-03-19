# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abettini <abettini@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 16:16:09 by abettini          #+#    #+#              #
#    Updated: 2023/03/19 16:31:14 by abettini         ###   ########.fr        #
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

SRC = philosophers.c

all: $(NAME)

$(NAME): comp

libcomp:
		@make -C Libft

comp: libcomp
	$(CC) $(FLAGS) $(SRC) $(LIBFT) -o $(NAME)
	echo "$(TCOL)$(NAME) $(CMP)"

libclean:
		@make clean -C Libft

clean:		libclean

libfclean:
		@make fclean -C Libft

fclean:   	libfclean
		if [ -f $(NAME) ]; then\
			rm -rf $(NAME);\
			echo "$(TCOL)$(NAME) $(RMD)";\
		fi

.PHONY: all re clean fclean

.SILENT: