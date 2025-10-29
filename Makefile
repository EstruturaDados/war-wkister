# Makefile para o projeto War
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O0 -Wpointer-arith -Wcast-align
LDFLAGS =

# Nome do programa
PROG = war

# Diretórios
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Arquivos fonte
SOURCES = war.c
OBJECTS = $(OBJDIR)/war.o
TARGET = $(BINDIR)/$(PROG)

# Regra principal
all: dirs $(TARGET)

# Regra para o arquivo objeto
$(OBJECTS): $(SOURCES)
	@echo "Compilando $(SOURCES)..."
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para o executável
$(TARGET): $(OBJECTS)
	@echo "Linkando $(PROG)..."
	$(CC) $^ $(LDFLAGS) -o $@

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