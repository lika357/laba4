CC = clang++

CFLAGS = -Wall -Wextra -std=c++20 -I include

SRCS = tests/test_main.cpp tests/tests.cpp tests/assert.cpp

FORMAT_FILES = include/*.hpp include/*.cpp tests/*.cpp tests/*.hpp main.cpp gui/*.hpp

TARGET = test_runner

SFML_INCLUDE = $(USERPROFILE)/vcpkg/installed/x64-windows/include
SFML_LIB = $(USERPROFILE)/vcpkg/installed/x64-windows/lib
SFML_BIN = $(USERPROFILE)/vcpkg/installed/x64-windows/bin

ifeq ($(OS),Windows_NT)
    RM = del /Q
    COPY = copy
    NULL = >nul 2>&1
    EXE = .exe
    FONT_PATH = C:/Windows/Fonts/arial.ttf
else
    RM = rm -f
    COPY = cp
    NULL = 2>/dev/null
    EXE =
    FONT_PATH = /usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf
endif

all: format $(TARGET)
	./$(TARGET)$(EXE)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@$(EXE) $^ include/exceptions.cpp

format:
	clang-format -i $(FORMAT_FILES)

check_sfml:
	@if [ ! -f "$(SFML_INCLUDE)/SFML/Graphics.hpp" ]; then \
		echo "SFML not found, installing..." && \
		vcpkg install sfml; \
	else \
		echo "SFML installed"; \
	fi

gui: check_sfml copy_dll
	$(CC) -std=c++20 main.cpp include/exceptions.cpp \
		-I include \
		-I $(SFML_INCLUDE) \
		-L $(SFML_LIB) \
		-lsfml-graphics \
		-lsfml-window \
		-lsfml-system \
		-luser32 \
		-o main$(EXE)

copy_dll:
	$(COPY) $(SFML_BIN)/sfml-graphics-3.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/sfml-window-3.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/sfml-system-3.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/freetype.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/libpng16.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/z.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/bz2.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/brotlidec.dll . $(NULL) || echo DLL already exists
	$(COPY) $(SFML_BIN)/brotlicommon.dll . $(NULL) || echo DLL already exists
	$(COPY) $(FONT_PATH) . $(NULL) || echo Font already exists

run:
	./main$(EXE)

clean:
	$(RM) $(TARGET)$(EXE) main$(EXE) 2>/dev/null
	$(RM) *.obj *.dll arial.ttf 2>/dev/null

.PHONY: all clean format gui run copy_dll check_sfml