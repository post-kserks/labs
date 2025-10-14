CXX = g++
CXXFLAGS = -std=c++11 -Iinclude
SRCDIR = src
OBJDIR = obj

SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/bisection.cpp $(SRCDIR)/iteration.cpp $(SRCDIR)/newton.cpp
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = lab4

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean
