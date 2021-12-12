.PHONY: all re fclean clean obj_dir

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98

INCLUDE = -I ${ROOT_DIR}/${LIBFT_DIR}

NAME = test

OBJ_DIR = .obj
SRC_DIR = 

SOURCES = 
HEADERS = 
OBJECTS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.cpp=.o))

all: obj_dir $(NAME)

obj_dir:
	@if ! [ -d "${OBJ_DIR}" ] ; then mkdir ${OBJ_DIR} ; fi

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $? $(INCLUDE) -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

bonus:
