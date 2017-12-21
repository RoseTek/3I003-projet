SRCS	=	$(shell find Src -name '*.c')

OBJS	=	$(SRCS:.c=.o)

NAME	=	Tomo

RM	=	rm -f

CFLAGS	=	-I./Inc -O6

CC	=	gcc

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
