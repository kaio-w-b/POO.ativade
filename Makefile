# Nome do executável
TARGET = loja_de_roupas

# Compilador
CXX = g++

# Flags de compilação
CXXFLAGS = -std=c++11 -Wall

# Arquivos fonte
SRCS = sistema_loja_roupas.cpp

# Objetos
OBJS = $(SRCS:.cpp=.o)

# Regra de compilação
$(TARGET): $(OBJS)
    $(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Regra de geração de objetos
%.o: %.cpp
    $(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
    $(RM) $(TARGET) $(OBJS)

# Phony target para evitar conflitos com arquivos de mesmo nome
.PHONY: clean
