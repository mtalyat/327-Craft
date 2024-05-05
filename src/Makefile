#target: dependency list
#	command(s) to build target from dependencies

# C compile command: gcc main.c -Wall -Werror -o main -lncurses
# gcc -lstdc++ OR g++

SOURCES = main.cpp BiomeData.cpp BlockData.cpp Camera.cpp Character.cpp Chunk.cpp Console.cpp CSVFile.cpp CSVObject.cpp Element.cpp ElementButton.cpp ElementList.cpp ElementManager.cpp ElementPanel.cpp ElementText.cpp Engine.cpp EngineData.cpp Entity.cpp Event.cpp GameObject.cpp Inventory.cpp Item.cpp ItemData.cpp ModificationsGroup.cpp Object.cpp Player.cpp Point.cpp Random.cpp Scene.cpp SceneGame.cpp SceneInventory.cpp SceneLoader.cpp SceneMenu.cpp ScenePause.cpp Selector.cpp Sprite.cpp string_converter.cpp StructureData.cpp StructureVariationData.cpp World.cpp

#main, build the program
main: main.cpp
	g++ -Wall -Werror $(SOURCES) -o main -lncursesw

#clean up the objects (delete them)
clean:
	rm -f *- main

#rebuild the projecct
re:
	make clean
	make

#rebuild and run the program normally
run:
	make re
	./main

#clean, build without error checking and run
test: main.cpp
	make clean
	g++ $(SOURCES) -o main -lncursesw
	./main