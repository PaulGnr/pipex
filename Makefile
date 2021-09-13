SRCDIR	= src

BONUSSRCDIR	= bonus

OBJDIR	= obj

BONUSOBJDIR	= bonusobj

SRCS	= $(SRCDIR)/main.c

BONUSSRCS	= 

OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUSOBJS	= $(BONUSSRCS:$(BONUSSRCDIR)/%.c=$(BONUSOBJDIR)/%.o)

INCLUDE	= -I include/ -I libft/include/

LIB		= libft/libft.a

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror -fsanitize=address

RM		= rm -rf

NAME	= pipex

BONUS	= bonus

all		: $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME)	: $(OBJS)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB) -o $@

$(BONUSOBJDIR)/%.o : $(BONUSSRCDIR)/%.c
	@mkdir -p $(BONUSOBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BONUS)	: $(BONUSOBJS)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(BONUSOBJS) $(INCLUDE) $(LIB) -o pipex

clean	:
	$(RM) libft/obj
	$(RM) $(BONUSOBJDIR)
	$(RM) $(OBJDIR)

fclean	: clean
	$(RM) $(LIB)
	$(RM) $(NAME)
	$(RM) checker

re		: fclean all
