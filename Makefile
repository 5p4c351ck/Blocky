cc = g++
cflags = -Iexternal/imgui -Iexternal/imgui/backends -I/usr/include -Isrc
lflags = -L/usr/lib -lvulkan -lglfw
target = blocky
SRCS = main.cpp external/imgui/imgui.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_widgets.cpp \
	   external/imgui/imgui_tables.cpp external/imgui/backends/imgui_impl_vulkan.cpp external/imgui/backends/imgui_impl_glfw.cpp \
	   external/imgui/imgui_demo.cpp src/CellularAutomata.cpp src/grid.cpp src/Tensor.cpp
	   
OBJS = $(SRCS:.cpp=.o)



all: $(target)

%.o : %.cpp
	$(cc) -c -g $< -o $@ $(cflags)

$(target): $(OBJS) 
	$(cc) $^ -o $@ $(lflags)

clean:
	rm $(OBJS) $(target)
