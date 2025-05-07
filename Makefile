CXX := clang++
LINKER := -lglfw -lGL -lm -lX11 -lpthread -lXrandr -ldl -lassimp
SRC := src
SHADER := src/shader/shader.cpp
CAMERA := src/camera
MODEL := src/model/model.cpp
MESH := src/model/mesh.cpp
OUT := gl
BUILD := build

run: $(OUT)
	./$(BUILD)/$(OUT)

$(OUT): $(SRC)/main.cpp $(SHADER) $(MODEL) $(SRC)/glad.c $(MESH)
	if [ ! -d "$(BUILD)" ]; then mkdir $(BUILD); fi
	$(CXX) $^ $(LINKER) -o $(BUILD)/$(OUT)

clean:
	rm -rf $(BUILD)
