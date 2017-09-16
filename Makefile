LEM-IN_NAME = lem-in

LIBRARY = libft/libft.a

LEM_C = find_parameters lem_in links making_rooms making_rooms_second printing finding_path ants additional finding_path_second

LEM-IN_DIR = src/

OBJ_LEM-IN = $(addprefix $(LEM-IN_DIR),$(addsuffix .o,$(LEM_C)))


FLAGS = -Wall -Wextra -Werror

all: lib lem-in 

lib:
	@make -C ./libft

lem-in: $(OBJ_LEM-IN)
	@gcc -o $(LEM-IN_NAME) $(FLAGS) $(OBJ_LEM-IN) $(LIBRARY) 
	@echo "\x1b[32m"lem-in has been made "\x1b[0m"

%.o: %.c
	@gcc $(FLAGS) -c -o $@ $< 

clean:
	@find . -name "*.o" -type f -delete
	@echo "\x1b[31m".o files were deleted "\x1b[0m"

fclean: clean
	@rm -f $(LEM-IN_NAME) $(LIBRARY)
	@echo "\x1b[31m"exec files were deleted "\x1b[0m"

re: fclean all
