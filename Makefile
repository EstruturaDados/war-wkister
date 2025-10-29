# Makefile para exemplos de Ponteiros - Estrutura de Dados
# Compilador e flags específicas para ponteiros
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0 -Wpointer-arith -Wcast-align
LDFLAGS =

# Diretórios
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Encontra todos os arquivos .c recursivamente
SOURCES = $(shell find $(SRCDIR) -name '*.c')
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES:./%=%))
TARGETS = $(patsubst $(SRCDIR)/%.c,$(BINDIR)/%,$(SOURCES:./%=%))

# Permite compilar um arquivo específico: make file=exemplo.c
ifeq ($(file),)
all: dirs $(TARGETS)
else
# Permite compilar arquivo em subpasta
FILE_PATH = $(file)
FILE_NAME = $(notdir $(FILE_PATH))
FILE_BASE = $(basename $(FILE_NAME))
FILE_OBJ = $(OBJDIR)/$(FILE_BASE).o
FILE_BIN = $(BINDIR)/$(FILE_BASE)
all: dirs build_file

# Detecta se o arquivo tem main
HAS_MAIN := $(shell grep -c 'int main' $(FILE_PATH))

build_file:
ifeq ($(HAS_MAIN),0)
	@echo "Compilando apenas o objeto de $(FILE_PATH) (sem main)"
	$(CC) $(CFLAGS) -c $(FILE_PATH) -o $(FILE_OBJ)
else
	@echo "Compilando e linkando $(FILE_PATH) (possui main)"
	$(CC) $(CFLAGS) -c $(FILE_PATH) -o $(FILE_OBJ)
	$(CC) $(LDFLAGS) $(FILE_OBJ) -o $(FILE_BIN)
endif
endif

# Cria diretórios necessários
dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

# Regra para compilar objetos de arquivos em subpastas
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para criar executáveis de objetos em subpastas
$(BINDIR)/%: $(OBJDIR)/%.o
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $< -o $@

# Limpa arquivos compilados e temporários
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Limpeza completa: remove objetos, binários e arquivos temporários comuns
cleanall:
	rm -rf $(OBJDIR) $(BINDIR) *.o *~ core a.out *.exe *.out *.obj *.gch

# Executa todos os programas compilados
run: all
	@for exe in $(BINDIR)/*; do \
		if [ -x "$$exe" ]; then \
			echo "=== Executando $$exe ==="; \
			"$$exe"; \
			echo; \
		fi \
	done

# Executa com valgrind para verificar vazamentos de memória
valgrind: all
	@for exe in $(BINDIR)/*; do \
		if [ -x "$$exe" ]; then \
			echo "=== Verificando $$exe com valgrind ==="; \
			valgrind --leak-check=full --show-leak-kinds=all "$$exe"; \
			echo; \
		fi \
	done

# Compila com debugging extra para ponteiros
debug: CFLAGS += -DDEBUG -fsanitize=address -fno-omit-frame-pointer
debug: LDFLAGS += -fsanitize=address
debug: clean all

.PHONY: all dirs clean run valgrind debug