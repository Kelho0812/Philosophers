NAME = Philosophers

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

${NAME} : ${OBJECTS} $(LIBFT) $(PRINTF)
	@${CC} ${CFLAGS} ${OBJECTS} -o ${NAME} $(LIBFT) $(PRINTF)
	@echo "Philosophers created"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "Philosophers objects created"

$(ODIR):
	@mkdir -p $@	

$(LIBFT) :
	@cd ./include/libft/ && make bonus -s
	@echo "libft.a created"

$(PRINTF) :
	@cd ./include/ft_printf/ && make -s
	@echo "prinft.a created"

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "Philosophers objects deleted"
	@cd ./include/libft/ && make clean -s
	@echo "libft objects deleted"
	@cd ./include/ft_printf/ && make clean -s
	@echo "ft_printf objects deleted"

fclean : clean
	@${RM} ${NAME}
	@echo "Philosophers deleted"
	@cd ./include/libft/ && make fclean -s
	@echo "libft.a deleted"
	@cd ./include/ft_printf/ && make fclean -s
	@echo "ft_printf.a deleted"

re : fclean all