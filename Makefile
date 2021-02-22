##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## compilation
##

## Aliases
ECHO	=	   /bin/echo -e
DEFAULT =	   "\033[00m"

## Print colors
DEFAULT =	   "\e[0m"
BOLD	=	   "\e[1m"
DIM		=	   "\e[2m"
UNDLN   =	   "\e[4m"
SHINE   =	   "\e[5;37m"
RODE	=	   "\e[9;37m"

BLACK   =	   "\e[30m"
RED		=	   "\e[31m"
GREEN   =	   "\e[32m"
YELLOW  =	   "\e[33m"
BLUE	=	   "\e[34m"
MAGEN   =	   "\e[35m"
CYAN	=	   "\e[36m"
WHITE   =	   "\e[1;37m"
## !Print colors

## Shortcut / unity of variables
CC			=	@gcc

INCLUDE		=	-I include

C_FLAGS		=	-W -Wall -Wextra  $(INCLUDE) # -pedantic # very strict

RM_FLAGS	=	*.gcda *.gcno src/*.gcda src/*.gcno

RM			=	@rm -rf
## !Shortcut / unity of variables

## Source
SRC_DIR		=	./src/

SRC			=	${SRC_DIR}main.c	\
				# ${SRC_DIR}example.c

OBJ			=	$(SRC:.c=.o)

NAME		=	executable
## Source

## Assembly

ASSEMBLER	=	@nasm
ASM_FORMAT	=	-f elf64

LINKER_DYN	=	@ld -shared -Bsymbolic -Bsymbolic-functions #-lc # tiret petit l comme avec gcc lib donc include libc

ASM_DIR		=	./src/

ASM_SRC		=	${ASM_DIR}strchr.asm	\
				${ASM_DIR}memset.asm	\
				${ASM_DIR}memcpy.asm	\
				${ASM_DIR}putstr.asm	\
				${ASM_DIR}strlen.asm	\
				${ASM_DIR}strcmp.asm	\
				${ASM_DIR}memmove.asm	\
				${ASM_DIR}getMax.asm	\
				${ASM_DIR}getMin.asm

ASM_OBJ		=	$(ASM_SRC:.asm=.o)

ASM_NAME	=	libasm.so

## !Assembly

## Tests
TEST_NAME	=	unit_tests

TEST_FLAGS	=   --coverage -lcriterion -ldl

TEST_DIR	=	./tests/

TEST_FILES	=	\
				$(TEST_DIR)tests_memmove.c	\
				# $(TEST_DIR)tests_memcpy.c	\
				# $(TEST_DIR)tests_strcmp.c	\
				# $(TEST_DIR)tests_memset.c	\
				# $(TEST_DIR)tests_rindex.c	\
				# $(TEST_DIR)tests_strcasecmp.c	\
				# $(TEST_DIR)tests_strchr.c	\
				# $(TEST_DIR)tests_strcspn.c	\
				# $(TEST_DIR)tests_strlen.c	\
				# $(TEST_DIR)tests_strncmp.c	\
				# $(TEST_DIR)tests_strpbrk.c	\
				# $(TEST_DIR)tests_strstr.c	\

TEST_OBJ	=	$(TEST_FILES:.c=.o)
## !Tests
## !Aliases

## Rules

## Messages
MSG_POST_BUILD	=	@$(ECHO) $(BOLD) $(YELLOW) Built $(NAME) $(WHITE) "\t$(C_FLAGS)" $(DEFAULT)

MSG_BUILD_SUCCESS	=	$(ECHO) $(BOLD) $(GREEN)"\n-> BUILD SUCCESS"$(YELLOW)"\n\t\t\t"

MSG_BUILD_FAILURE	=	$(ECHO) $(BOLD) $(RED)"\n-> BUILD FAILED"$(YELLOW)"\n\t\t\t"

MSG_COMPILATION_SUCCESS	=	$(ECHO) -n $(BOLD) $(GREEN)"  [OK] "$(WHITE)

MSG_COMPILATION_FAILURE	=	$(ECHO) -n $(BOLD) $(RED)"  [KO] "$(WHITE)

MSG_CLEAN	=	$(ECHO) $(BOLD) $(GREEN)✓" CLEAN "

MSG_FCLEAN	=	$(ECHO) $(BOLD) $(GREEN)✓" FULL CLEAN "
## !Messages


all:		asm

asm:		$(ASM_OBJ)
			$(LINKER_DYN) -o $(ASM_NAME) $(ASM_OBJ)	\
			&& ($(MSG_BUILD_SUCCESS) $(ASM_NAME)$(DEFAULT)) \
			|| ($(MSG_BUILD_FAILURE) $(ASM_NAME)$(DEFAULT))
			@($(ECHO))
			@($(ECHO))

$(NAME):	asm $(OBJ)
			@$(ECHO)
			$(MSG_POST_BUILD)
			@$(ECHO)
			$(CC) -o $(NAME) $(OBJ)  $(ASM_OBJ) $(LD_FLAGS) \
			&& ($(MSG_BUILD_SUCCESS) ; LD_PRELOAD=./$(ASM_NAME) ./$(NAME)) \
			|| $(MSG_BUILD_FAILURE)
			@$(ECHO)

clean:
			$(RM) $(RM_FLAGS)
			$(RM) $(OBJ)
			$(RM) $(ASM_OBJ)
			$(RM) $(TEST_OBJ)
			@($(MSG_CLEAN)$(NAME)$(DEFAULT))
			@($(MSG_CLEAN)$(ASM_NAME)$(DEFAULT))
			@($(ECHO))
			@($(ECHO))


fclean:
			$(RM) $(OBJ)
			$(RM) $(RM_FLAGS)
			$(RM) $(NAME)
			@($(MSG_FCLEAN)$(NAME)$(DEFAULT))
			$(RM) $(TEST_NAME)
			$(RM) $(TEST_OBJ)
			@($(MSG_FCLEAN)$(TEST_NAME)$(DEFAULT))
			$(RM) $(ASM_NAME)
			$(RM) $(ASM_OBJ)
			@($(MSG_FCLEAN)$(ASM_NAME)$(DEFAULT))
			@($(ECHO))
			@($(ECHO))

re:		fclean all

tests_run:	re $(TEST_OBJ)
			@$(ECHO)
			$(CC) -o $(TEST_NAME) $(TEST_OBJ) $(TEST_FLAGS) $(C_FLAGS) $(LD_FLAGS) \
			&& ($(MSG_BUILD_SUCCESS) $(TEST_NAME)$(DEFAULT)) \
			|| ($(MSG_BUILD_FAILURE) $(TEST_NAME)$(DEFAULT))
			@$(ECHO)
			@if [ -f $(TEST_NAME) ] && [ -f $(ASM_NAME) ]; \
			then \
				./$(TEST_NAME) ; \
			fi
			@$(ECHO)
			@$(ECHO)

debug:		C_FLAGS += -g
debug:		ASSEMBLER += -g
debug:		re

%.o :		%.c
			$(CC) -c -o $@ $^ $(C_FLAGS) \
			&& $(MSG_COMPILATION_SUCCESS) \
			|| $(MSG_COMPILATION_FAILURE) \
			&& $(ECHO) $(BOLD) $< | rev | cut -d'/' --fields="1 2" | rev

%.o :		%.asm
			$(ASSEMBLER) $(ASM_FORMAT) -o $@ $^ \
			&& $(MSG_COMPILATION_SUCCESS) \
			|| $(MSG_COMPILATION_FAILURE) \
			&& $(ECHO) $(BOLD) $< | rev | cut -d'/' --fields="1 2" | rev

.PHONY:		all title clean fclean re tests_run debug lib asm
## !Rules
