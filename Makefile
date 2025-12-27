CXX := clang++
LINKER := -lglfw -lGL -lm -lX11 -lpthread -lXi -lXrandr -ldl -lassimp
SRC := src
SHADER := src/shader/shader.cpp
CAMERA := src/camera
MODEL := src/model/model.cpp
MESH := src/model/mesh.cpp
OUT := gl
BUILD := build

run: $(OUT)
	./$(BUILD)/$(OUT)

$(OUT): $(SRC)/gl.cpp $(SHADER) $(MODEL) $(SRC)/glad.c $(MESH)
	if [ ! -d "$(BUILD)" ]; then mkdir $(BUILD); fi
        cp -r shaders/ $(BUILD)/
	$(CXX) $^ $(LINKER) -o $(BUILD)/$(OUT)

clean:
	rm -rf $(BUILD)
