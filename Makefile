NAME = philo

LIBFT = ./include/libft/libft.a

PRINTF = ./include/ft_printf/libftprintf.a

CC = cc

CFLAGS = -Werror -Wall -Wextra -g

RM = rm -rf

SDIR := src
ODIR := obj

SOURCES := 
OBJECTS := $(patsubst $(SDIR)/%.c, $(ODIR)/%.o, $(SOURCES))

all : ${NAME}

${NAME} : ${OBJECTS}
	@${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	@echo "philo created"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "philo objects created"

$(ODIR):
	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "philo objects deleted"

fclean : clean
	@${RM} ${NAME}
	@echo "philo deleted"

re : fclean all