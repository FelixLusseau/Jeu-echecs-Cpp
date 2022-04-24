CC = g++ #x86_64-w64-mingw32-g++ 
CFLAGS ?= -Wall -Wextra -Werror -g -pipe -pedantic
LDLIBS ?= 

INCLUDE_PATH = ./includes

TARGET   = echecs

SRCDIR   = src
OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCLUDE_PATH)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)
	@echo "Linking complete !"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDE_PATH)

doc:	
	@doxygen Doxyfile > /dev/null 2>&1
	@echo "Documentation generated !"

.PHONY: clean cov
clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(TARGET)
