CC = gcc -Wall -Werror -Wextra
NAME = game_of_life

all: clean
	$(CC) $(NAME).c -o $(NAME)
	./$(NAME)

clean: 
	rm -rf $(NAME) *.o *.out
