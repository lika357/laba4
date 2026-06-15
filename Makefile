CC = clang++

CFLAGS = -Wall -Wextra -std=c++20 -I include

SRCS = tests/test_main.cpp tests/tests.cpp tests/assert.cpp

FORMAT_FILES = include/*.hpp tests/*.cpp tests/*.hpp main.cpp gui/*.hpp

TARGET = test_runner

SFML_INCLUDE = $(USERPROFILE)/vcpkg/installed/x64-windows/include
SFML_LIB = $(USERPROFILE)/vcpkg/installed/x64-windows/lib
SFML_BIN = $(USERPROFILE)/vcpkg/installed/x64-windows/bin

all: format $(TARGET)
	./$(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

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
	$(CC) -std=c++20 main.cpp \
		-I include \
		-I $(SFML_INCLUDE) \
		-L $(SFML_LIB) \
		-lsfml-graphics \
		-lsfml-window \
		-lsfml-system \
		-luser32 \
		-o main.exe

copy_dll:
	copy $(SFML_BIN)\sfml-graphics-3.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\sfml-window-3.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\sfml-system-3.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\freetype.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\libpng16.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\z.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\bz2.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\brotlidec.dll . >nul 2>&1 || echo DLL already exists
	copy $(SFML_BIN)\brotlicommon.dll . >nul 2>&1 || echo DLL already exists
	copy C:\Windows\Fonts\arial.ttf . >nul 2>&1 || echo Font already exists

run:
	./main.exe

clean:
	del $(TARGET).exe main.exe 2>nul
	del *.obj *.dll arial.ttf 2>nul

.PHONY: all clean format gui run copy_dll check_sfml