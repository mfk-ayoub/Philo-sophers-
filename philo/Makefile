# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ayel-mou <ayel-mou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/27 21:28:48 by ayel-mou          #+#    #+#              #
#    Updated: 2024/11/18 21:33:45 by ayel-mou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS= -Wall -Wextra -Werror -I. -g3 -fsanitize=address
NAME=philo
SRCDIR=.
BINDIR=bin
OBJ=$(patsubst $(SRCDIR)/%.c, $(BINDIR)/%.o, $(wildcard $(SRCDIR)/*.c))

vpath %.c src

all : $(NAME)

$(NAME) : $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(BINDIR) :
	mkdir -p $@

$(BINDIR)/%.o : %.c | $(BINDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm -rf $(BINDIR)
fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re
.SECONDARY: