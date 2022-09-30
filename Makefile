
##------------------------------------------------------------------------------##
## 								 THE TARGET										##
##------------------------------------------------------------------------------##
TARGET	:= FT_CONTAINERS

##------------------------------------------------------------------------------##
##								HEADERS											##
##------------------------------------------------------------------------------##


##------------------------------------------------------------------------------##
##								SOURCES											##
##------------------------------------------------------------------------------##
SRC	:=			TestTemplate/Logfile/Logfile.cpp TestTemplate/Timer/Timer.cpp main.cpp

# Src directory
SRC_DIR		:=	./tester/
# Subdirectories of src
SRCS_SUBDIR	:=	./tester/TestTemplate/ ./tester/TestTemplate/Logfile/ ./tester/TestTemplate/Timer/
# Full paths sources
SRCS		:= $(addprefix $(SRC_DIR), $(SRC))


##----------------------------------------------------------------------------------##
##								OBJECTS												##
##----------------------------------------------------------------------------------##
OBJ := $(SRCS:.cpp=.o)
# Objects directory
OBJ_DIR	:= obj/
# From str to obj/
OBJS := $(subst $(SRC_DIR), $(OBJ_DIR), $(OBJ))


##----------------------------------------------------------------------------------##
##							 OBJ_DIR CREATION										##
##----------------------------------------------------------------------------------##
MKDIR_P	:= mkdir -p
# Objects directory creation
NEWSUBDIR = $(MKDIR_P) $(addsuffix ;, $(subst $(SRC_DIR), $(OBJ_DIR), $(listObj)))


##------------------------------------------------------------------------------##
##									PRINT										##
##------------------------------------------------------------------------------##
ECHO	:= echo
# colors
RED		:= \033[1;31m
YEL		:= \033[1;33m
BLU		:= \033[1;34m
WHITE	:= \033[1;37m
GREEN	:= \033[1;32m
RESET	:= \033[0m


##------------------------------------------------------------------------------##
##								COMPILATION										##
##------------------------------------------------------------------------------##
CC		:= g++-12

# Compilation flags
CFLAGS	:= -Wall -Wextra -Werror -std=c++98 -g -fsanitize=leak
# explicit compilation
$(OBJ_DIR)%.o: %.cpp 
	@$(CC) $(CFLAGS) $(INCLUDE)  -c $< -o $@
# vpath
VPATH := $(SRC_DIR) $(OBJ_DIR) $(SRCS_SUBDIR)


##------------------------------------------------------------------------------##
##									MAKE RULES									##
##------------------------------------------------------------------------------##
all:	$(OBJ_DIR) $(TARGET)

$(OBJ_DIR):
	@ mkdir -p $(OBJ_DIR)
	$(foreach listObj, $(SRCS_SUBDIR), $(NEWSUBDIR))

$(TARGET):	$(SRCS) $(OBJS)
	@ $(ECHO) "$(GREEN) $(TARGET) compiled with success!$(RESET)"
	@ $(CC) $(CFLAGS) $(OBJS) -o $(TARGET) 

clean:
	@ $(ECHO) "\n $(RED)removing:\n		$(RESET) $(TARGET) *.o $(RESET)"
	@ rm -rf $(OBJS)
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ $(ECHO) "		$(RESET) $(TARGET)\n"
	@ rm -rf $(TARGET)

re: fclean all

.PHONY: all clean fclean re
    
