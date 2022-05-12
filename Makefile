# Makefile based on Lionnel lacassagne

# -- File list ----------
FILE =nrutil.c SD.c morpho.c mouvement.c main.c
# -- Paths ----------
INC_PATH = include
SRC_PATH = src
OBJ_PATH = obj
EXE_PATH = exe

# -- OS ----------
OS = Ubuntu

# -- Config ----------
# if CONFIG = CLI  (Command Line Interface, no Apple Framework)
CONFIG = CL

# -- Macros ----------
CC = gcc
AR = ar -rc

# -- Flags ----------
C_DEBUG_FLAGS = -g -Wall -Wextra
C_OPTIMISATION_FLAGS = -O3 -fstrict-aliasing
C_ARCH_FLAGS = -msse4.2
C_OS_FLAGS = -D$(OS)
C_CONFIG_FLAGS = -D$(CONFIG)
C_INC_FLAGS = -I$(INC_PATH)

CFLAGS = $(C_DEBUG_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
CFLAGS = $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS) $(C_INC_FLAGS) $(LIB_INC_PATH)
LDFLAGS = $(C_OPTIMISATION_FLAGS) $(C_ARCH_FLAGS) $(C_OS_FLAGS) $(C_CONFIG_FLAGS)$(C_INC_FLAGS) $(LIB_LIB_PATH)

# -- Final product ----------
PRODUCT   = projet.exe

# -- src and obj List ----------
SRC = $(addprefix ${SRC_PATH}/, $(FILE))
OBJ = $(addprefix ${OBJ_PATH}/, $(addsuffix .o, $(basename $(FILE))))

# -- Base rules ----------
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#-----Main rule ----------
$(EXE_PATH)/$(PRODUCT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS) $(OPTFLAGS) $(CFG) $(INC) $(LIB) -lm

# -- Other stuff ----------
depend:
	makedepend $(CFLAGS) -Y $(SRC)

clean:
	rm -f $(OBJ)
	rm -f ${LIB_PATH}/${PRODUCT}

tar:
	tar -cvf poiAV.tar Makefile src include
	gzip -9 poiAV.tar
# DO NOT DELETE