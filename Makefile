HASH_DIR = ./src/
LIST_DIR = ./lib/list/src/
STK_DIR = ./lib/stack/src/
LIB_DIR = ./lib/

CONSTR_DIR = ./

LOGS_DIR = ./logs/
GRAPH_DUMP_DIR = ./lib/list/graph_dumps/
OBJ_DIR = ./obj/

I_FLAG := -I./lib/stack/include/ -I./lib/list/include/ -I./lib/ -I./ -I./include/ -I./config

CC := g++
CFLAGS := -Wno-format -g -fsanitize=address
CFLAGS_NO_SANITIZER := -Wno-format -g

H_TAB_EXE   := hash_table

HASH_SRC    := $(wildcard $(HASH_DIR)*.cpp)
LIST_SRC    := $(wildcard $(LIST_DIR)*.cpp)
STK_SRC    := $(wildcard $(STK_DIR)*.cpp)
LIB_SRC    := $(wildcard $(LIB_DIR)*.cpp)

HASH_OBJ := $(patsubst $(HASH_DIR)%.cpp, $(OBJ_DIR)%.o, $(HASH_SRC))
LIST_OBJ := $(patsubst $(LIST_DIR)%.cpp, $(OBJ_DIR)%.o, $(LIST_SRC))
STK_OBJ  := $(patsubst $(STK_DIR)%.cpp,  $(OBJ_DIR)%.o, $(STK_SRC))
LIB_OBJ  := $(patsubst $(LIB_DIR)%.cpp,  $(OBJ_DIR)%.o, $(LIB_SRC))

ALL_OBJ	 := $(HASH_OBJ) $(LIST_OBJ) $(STK_OBJ) $(LIB_OBJ)

all : $(H_TAB_EXE)	

$(H_TAB_EXE) : $(ALL_OBJ)
	@$(CC) $(CFLAGS) $(ALL_OBJ) -o $(H_TAB_EXE)

$(OBJ_DIR)%.o : $(HASH_DIR)%.cpp
	@$(CC) $(I_FLAG) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o : $(LIST_DIR)%.cpp
	@$(CC) $(I_FLAG) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o : $(STK_DIR)%.cpp
	@$(CC) $(I_FLAG) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o : $(LIB_DIR)%.cpp
	@$(CC) $(I_FLAG) $(CFLAGS) -c $< -o $@

mkdir :
	@mkdir -p $(GRAPH_DUMP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LOGS_DIR)
	@mkdir -p analysis

clean :
	@rm $(H_TAB_EXE) $(OBJ_DIR)*.o 