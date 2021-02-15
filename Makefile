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
DIM	 	=	   "\e[2m"
UNDLN   =	   "\e[4m"
SHINE   =	   "\e[5;37m"
RODE	=	   "\e[9;37m"

BLACK   =	   "\e[30m"
RED	 	=	   "\e[31m"
GREEN   =	   "\e[32m"
YELLOW  =	   "\e[33m"
BLUE	=	   "\e[34m"
MAGEN   =	   "\e[35m"
CYAN	=	   "\e[36m"
WHITE   =	   "\e[1;37m"
## !Print colors

## Shortcut / unity of variables
CC			= 	@gcc

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

NAME		=	binaryname
## Source

## Assembly

ASSEMBLER 	=	@nasm
ASM_FORMAT 	=	-f elf64

LINKER_DYN 	=	@ld -shared -Bsymbolic -Bsymbolic-functions #-lc # tiret petit l comme avec gcc lib donc include libc

ASM_DIR 	=	./src/

ASM_SRC		=	${ASM_DIR}strchr.asm	\
				${ASM_DIR}memset.asm	\
				${ASM_DIR}memcpy.asm	\
				${ASM_DIR}my_putstr.asm	\
				${ASM_DIR}my_strlen.asm	\
				${ASM_DIR}strcmp.asm	\
				${ASM_DIR}memmove.asm	\
				${ASM_DIR}getMax.asm	\
				${ASM_DIR}getMin.asm	\
				## ${ASM_DIR}example.asm	\

ASM_OBJ		=	$(ASM_SRC:.asm=.o)

ASM_NAME 	=	libasm.so

## !Assembly

## Library
# LIB_DIR		=	./lib/

# SRC_LIB		=	linked_list	\
# 				print		\
# 				my			\
# 				file		\

# LIB_PATHS	=   $(LIB_DIR)lib_my			\
# 				$(LIB_DIR)lib_file			\
# 				$(LIB_DIR)lib_linked_list	\
# 				$(LIB_DIR)lib_print			\

# LIBRARIES   =	$(SRC_LIB:%=-l%)

# LD_FLAGS	=	-L$(LIB_DIR) $(LIBRARIES)
## !Library

## Tests
TEST_NAME	=	unit_tests

TEST_FLAGS	=   --coverage -lcriterion -ldl

TEST_DIR	=	./tests/

TEST_FILES	=	$(TEST_DIR)tests_strlen.c	\
				$(TEST_DIR)tests_memcpy.c	\
				$(TEST_DIR)tests_memmov.c	\
				$(TEST_DIR)tests_memset.c	\
				$(TEST_DIR)tests_strchr.c	\
				#  $(TEST_DIR)unit_tests.c

TEST_OBJ	=	$(TEST_FILES:.c=.o)
## !Tests
## !Aliases

## Link dynamically preload

LD_PRELOAD_DIR	= ./src

LD_PRELOAD_SRC	=		\
					# $(LD_DIR)example.c	\

LD_PRELOAD_OBJ	=	$(LD_PRELOAD_SRC:.c=.o)

LD_PRELOAD_NAME	=	my_ld_preload.so

## !Link dynamically preload


## Rules

## Messages
MSG_POST_BUILD	=	@$(ECHO) $(BOLD) $(YELLOW) Built $(NAME) $(WHITE) "\t$(C_FLAGS)" $(DEFAULT)

MSG_BUILD_SUCCESS	= 	$(ECHO) $(BOLD) $(GREEN)"\n-> BUILD SUCCESS !"$(DEFAULT)

MSG_BUILD_FAILURE	=	$(ECHO) $(BOLD) $(RED)"\n-> BUILD FAILED"$(DEFAULT)

MSG_COMPILATION_SUCCESS	=	$(ECHO) -n $(BOLD) $(GREEN)"  [OK] "$(WHITE)

MSG_COMPILATION_FAILURE	=	$(ECHO) -n $(BOLD) $(RED)"  [KO] "$(WHITE)

MSG_CLEAN	=	$(ECHO) $(BOLD) $(GREEN)✓" CLEAN "

MSG_FCLEAN	=	$(ECHO) $(BOLD) $(GREEN)✓" FULL CLEAN "
## !Messages


all:		asm

# lib:
# 			@$(ECHO)
# 			@for MAKE_PATH in $(LIB_PATHS) ; do \
# 				make -C $$MAKE_PATH -s ; \
# 			done

asm:		$(ASM_OBJ)
			$(LINKER_DYN) -o $(ASM_NAME) $(ASM_OBJ)

$(NAME):	 asm $(OBJ)
			@$(ECHO)
			$(MSG_POST_BUILD)
			@$(ECHO)
			$(CC) -o $(NAME) $(OBJ)  $(ASM_OBJ) $(LD_FLAGS) \
			&& ($(MSG_BUILD_SUCCESS) ; LD_PRELOAD=./$(ASM_NAME) ./$(NAME)) \
			|| $(MSG_BUILD_FAILURE)
			@$(ECHO)

clean:
			# @for MAKE_PATH in $(LIB_PATHS) ; do \
			# 	make clean -C $$MAKE_PATH -s ; \
			# done
			$(RM) $(RM_FLAGS)
			$(RM) $(OBJ)
			$(RM) $(ASM_NAME)
			$(RM) $(ASM_OBJ)
			@($(MSG_CLEAN)$(NAME)$(DEFAULT))
			@($(MSG_CLEAN)$(ASM_NAME)$(DEFAULT))

fclean:
			@for MAKE_PATH in $(LIB_PATHS) ; do \
				make fclean -C $$MAKE_PATH -s ; \
			done
			$(RM) $(OBJ)
			$(RM) $(RM_FLAGS)
			$(RM) $(NAME)
			@($(MSG_FCLEAN)$(NAME)$(DEFAULT))
			$(RM) $(TEST_NAME)
			@($(MSG_FCLEAN)$(TEST_NAME)$(DEFAULT))
			$(RM) $(ASM_NAME)
			$(RM) $(ASM_OBJ)
			@($(MSG_FCLEAN)$(ASM_NAME)$(DEFAULT))

re:		fclean all

re_asm:	fclean asm

tests_run:	re_asm $(TEST_OBJ)
			#not finished
			@$(ECHO)
			$(CC) -o $(TEST_NAME) $(TEST_SRC) $(TEST_FILES) $(TEST_FLAGS) $(C_FLAGS) $(LD_FLAGS) \
			&& $(MSG_BUILD_SUCCESS) \
			|| $(MSG_BUILD_FAILURE)
			@$(ECHO)
			@if [ -f $(TEST_NAME) ]; \
			then \
				./$(TEST_NAME) ; \
			fi
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
