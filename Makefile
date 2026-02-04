##
## EPITECH PROJECT, 2026
## G-PDG-300-MPL-3-1-PDGRUSH4-5
## File description:
## Makefile
##

NAME = MyGKrellm

UNAME_S := $(shell uname -s)

# ===== Compiler =====
ifeq ($(UNAME_S),Darwin)
	CXX = clang++
	BREW_PREFIX = /opt/homebrew
	CXXFLAGS = -Wall -Wextra -Werror -std=c++17 \
		-Iinclude -Iinclude/Core -Iinclude/Displays -Iinclude/Interfaces -Iinclude/Modules \
		-I$(BREW_PREFIX)/include
	LDFLAGS = -L$(BREW_PREFIX)/lib \
		-lncurses \
		-lsfml-graphics -lsfml-window -lsfml-system
else
	CXX = g++
	CXXFLAGS = -Wall -Wextra -Werror -std=c++17 \
		-Iinclude -Iinclude/Core -Iinclude/Displays -Iinclude/Interfaces -Iinclude/Modules \
		-I/usr/local/include
	LDFLAGS = -L/usr/local/lib \
		-lncurses \
		-lsfml-graphics-s -lsfml-window-s -lsfml-system-s \
		-lfreetype -lGL -lX11 -lXrandr -lXcursor -lXi -ludev -lpthread
endif

# ===== Sources =====
SRC =	src/main.cpp \
		src/Core/MonitorCore.cpp \
		src/Modules/HostUserModule.cpp \
		src/Modules/OSKernelModule.cpp \
		src/Modules/DateTimeModule.cpp \
		src/Modules/CPU_Module.cpp \
		src/Modules/RAM_Module.cpp \
		src/Modules/BatteryModule.cpp \
		src/Modules/UptimeModule.cpp \
		src/Displays/NcursesDisplay.cpp \
		src/Displays/SFMLDisplay.cpp

OBJ = $(SRC:.cpp=.o)

# ===== Rules =====
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
