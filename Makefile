# Makefile for C Programming Challenges

# Define the C compiler
CC = gcc
# Define compiler flags
CFLAGS = -Wall -Wextra -std=c99

# --- Project 1: WAR Estruturado ---
WN_SRC = WAR_Estruturado/Novice/main.c
WN_BIN = WAR_Estruturado/Novice/main
war-novice:
	@echo "--- Compiling and running WAR Estruturado: Novice Challenge ---"
	$(CC) $(CFLAGS) $(WN_SRC) -o $(WN_BIN)
	@./$(WN_BIN)

WA_SRC = WAR_Estruturado/Adventurer/main.c
WA_BIN = WAR_Estruturado/Adventurer/main
war-adventurer:
	@echo "--- Compiling and running WAR Estruturado: Adventurer Challenge ---"
	$(CC) $(CFLAGS) $(WA_SRC) -o $(WA_BIN)
	@./$(WA_BIN)

WM_SRC = WAR_Estruturado/Master/main.c
WM_BIN = WAR_Estruturado/Master/main
war-master:
	@echo "--- Compiling and running WAR Estruturado: Master Challenge ---"
	$(CC) $(CFLAGS) $(WM_SRC) -o $(WM_BIN)
	@./$(WM_BIN)

# --- Project 2: Jogo de Sobrevivência (Survival Game) ---
SN_SRC = Jogo_de_Sobrevivencia/Novice/main.c
SN_BIN = Jogo_de_Sobrevivencia/Novice/main
survival-novice:
	@echo "--- Compiling and running Survival Game: Novice Challenge ---"
	$(CC) $(CFLAGS) $(SN_SRC) -o $(SN_BIN)
	@./$(SN_BIN)

SA_SRC = Jogo_de_Sobrevivencia/Adventurer/main.c
SA_BIN = Jogo_de_Sobrevivencia/Adventurer/main
survival-adventurer:
	@echo "--- Compiling and running Survival Game: Adventurer Challenge ---"
	$(CC) $(CFLAGS) $(SA_SRC) -o $(SA_BIN)
	@./$(SA_BIN)

SM_SRC = Jogo_de_Sobrevivencia/Master/main.c
SM_BIN = Jogo_de_Sobrevivencia/Master/main
survival-master:
	@echo "--- Compiling and running Survival Game: Master Challenge ---"
	$(CC) $(CFLAGS) $(SM_SRC) -o $(SM_BIN)
	@./$(SM_BIN)

# --- Project 3: Tetris Stack ---
TN_SRC = Tetris_Stack/Novice/main.c
TN_BIN = Tetris_Stack/Novice/main
tetris-novice:
	@echo "--- Compiling and running Tetris Stack: Novice Challenge ---"
	$(CC) $(CFLAGS) $(TN_SRC) -o $(TN_BIN)
	@./$(TN_BIN)

TA_SRC = Tetris_Stack/Adventurer/main.c
TA_BIN = Tetris_Stack/Adventurer/main
tetris-adventurer:
	@echo "--- Compiling and running Tetris Stack: Adventurer Challenge ---"
	$(CC) $(CFLAGS) $(TA_SRC) -o $(TA_BIN)
	@./$(TA_BIN)

TM_SRC = Tetris_Stack/Master/main.c
TM_BIN = Tetris_Stack/Master/main
tetris-master:
	@echo "--- Compiling and running Tetris Stack: Master Challenge ---"
	$(CC) $(CFLAGS) $(TM_SRC) -o $(TM_BIN)
	@./$(TM_BIN)

# --- Project 4: Detective Quest ---
DN_SRC = Detective_Quest/Novice/main.c
DN_BIN = Detective_Quest/Novice/main
detective-novice:
	@echo "--- Compiling and running Detective Quest: Novice Challenge ---"
	$(CC) $(CFLAGS) $(DN_SRC) -o $(DN_BIN)
	@./$(DN_BIN)

DA_SRC = Detective_Quest/Adventurer/main.c
DA_BIN = Detective_Quest/Adventurer/main
detective-adventurer:
	@echo "--- Compiling and running Detective Quest: Adventurer Challenge ---"
	$(CC) $(CFLAGS) $(DA_SRC) -o $(DA_BIN)
	@./$(DA_BIN)

DM_SRC = Detective_Quest/Master/main.c
DM_BIN = Detective_Quest/Master/main
detective-master:
	@echo "--- Compiling and running Detective Quest: Master Challenge ---"
	$(CC) $(CFLAGS) $(DM_SRC) -o $(DM_BIN)
	@./$(DM_BIN)

# --- Clean Command ---
clean:
	@echo "--- Cleaning up compiled files ---"
	@rm -f $(WN_BIN) $(WA_BIN) $(WM_BIN) $(SN_BIN) $(SA_BIN) $(SM_BIN) $(TN_BIN) $(TA_BIN) $(TM_BIN) $(DN_BIN) $(DA_BIN) $(DM_BIN)
	@echo "Cleanup complete."

.PHONY: all clean war-novice war-adventurer war-master survival-novice survival-adventurer survival-master tetris-novice tetris-adventurer tetris-master detective-novice detective-adventurer detective-master
