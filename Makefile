.PHONY: all clean

CC = g++
CFLAGS= -fdiagnostics-color=always -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef			\
		-Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs 		\
		-Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual	\
		-Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers \
		-Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual 			\
		-Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel 		\
		-Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE


BUILD_DIR = build
DOCS_DIR = docs
NON_CODE_DIRS = $(BUILD_DIR) $(DOCS_DIR) .vscode .git
TARGET = main.exe


CD = $(shell cd)
DOCS_TARGET=$(DOCS_DIR)\\docs_generated



NESTED_CODE_DIRS_CD = $(shell dir /S /B /AD | findstr /V /I "$(NON_CODE_DIRS)")
NESTED_CODE_DIRS = $(NESTED_CODE_DIRS_CD:$(CD)\\%=%)



FILES_FULL = $(shell dir /s /a /b *.cpp)
FILES = $(FILES_FULL:$(CD)\\%=%)

MAKE_DIRS = $(NESTED_CODE_DIRS:%=$(BUILD_DIR)\\%)
OBJ = $(FILES:%=$(BUILD_DIR)\\%)
DEPENDS = $(OBJ:%.cpp=%.d)
OBJECTS = $(OBJ:%.cpp=%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@$(CC) $^ -o $@

$(BUILD_DIR):
	@if not exist $@ md $@

$(MAKE_DIRS): | $(BUILD_DIR)
	@if not exist $@ md $@

-include $(DEPENDS)

$(BUILD_DIR)\\%.o: %.cpp | $(MAKE_DIRS)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

.PHONY: doxygen dox

doxygen dox: $(DOCS_TARGET) $(TARGET)

$(DOCS_TARGET): $(FILES) | $(DOCS_DIR)
	@echo "Doxygen generated %date% %time%" > $(DOCS_TARGET)
	@doxygen.exe docs/Doxyfile

$(DOCS_DIR):
	@if not exist $@ md $@

clean:
	@del *.o /a /s
	@del *.d /a /s
	@del $(TARGET)
	@del $(DOCS_TARGET)

