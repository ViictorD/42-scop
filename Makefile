NAME = scop

CC = gcc

CFLAGS = -Wall -Wextra -Werror

FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

LIB_FILES = -lft -lglfw3 -lGLEW

INCLUDE_DIR = -I ./includes -I ./library/glfw/include  -I ./library/glew/include -I ./libft/glfw/deps/glad

DIR_OBJ = ./obj/

LIBFT_DIR = ./library/libft

DIR_LIB = -L ./library/libft/ -L ./library/glfw/build/src -L ./library/glew/build/cmake/build/lib/

SRC_DIR = ./srcs/

FILES = main.c \
			loader.c \
			init.c \
			window.c \
			model.c

SRCS = $(addprefix $(SRC_DIR), $(FILES)) $(addprefix $(SRC_DIR), $(MAIN))

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(FILES)) $(patsubst %.c, $(DIR_OBJ)%.o, $(MAIN))

DEP_OBJ = src_msg \
			$(OBJS)

RM = /bin/rm -rf

all: mkdirobj $(DEP_OBJ)
		@ make -C $(LIBFT_DIR)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -o $(NAME) $(OBJS) $(DIR_LIB) $(LIB_FILES) $(FRAMEWORK)
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< $(INCLUDE_DIR) 
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ make clean -C $(LIBFT_DIR)
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ make fclean -C $(LIBFT_DIR)
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME)
	@ $(RM) $(NAME).dSYM
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src functions:"

debug: mkdirobj
	@ make -C $(LIBFT_DIR)
	@ /bin/echo -n "Archiving object in $(NAME):"
	@ $(CC) $(CFLAGS) $(SRCS) -I$(INCLUDE_DIR) -I /Users/vdarmaya/.brew/include -o $(NAME) -L $(DIR_LIB) -L $(DIR_LIB2) $(LIB_FILES) $(FRAMEWORK)
	@ echo " \033[32mAll done!\033[0m"

.PHONY : all clean fclean re mkdirobj src_msg debug