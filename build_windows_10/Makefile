IPATH=D:/SFML-2.5.1-64/include
_INCLUDES=SFML/Graphics.hpp SFML/Window.hpp SFML/Audio.hpp 
INCLUDES=$(patsubst %,$(IPATH)/%,$(_INCLUDES))

LPATH=D:/SFML-2.5.1-64/lib

CXX=C:/mingw64-gcc-7.3.0/bin/g++.exe
CXXFLAGS=-std=c++17 -I$(IPATH) -D STABLE_DRAW_MODE

VPATH=../code:../code/screens:../code/screens/subscreens:../code/engine/primitive_classes:../code/engine/advanced_classes/number_display_module:../code/engine/advanced_classes/player_object_module:../code/engine/advanced_classes/tile_map_module:../code/actors

OBJ = main.o save_game_helper.o save_file.o main_menu_screen.o farm_screen.o market_screen.o oae_screen.o start_game_screen.o credits_screen.o drawable_object.o textured_object.o textured_button_object.o number_display.o tile_map.o player_object.o oae_animation.o oae_animation_instance.o oae_animated_object.o object_with_texture_map.o trigger_zone.o world_object.o collision_box.o texture_bank.o oae_animation_bank.o alice.o market_offer.o market_offer_list.o initialize_texture_bank.o 

alice_game: $(OBJ)
	$(CXX) -std=c++17 -o $@ $^ -L$(LPATH) -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

%.o: %.c $(INCLUDES)
	$(CXX) -D STABLE_DRAW_MODE -std=c++17 -c -o $@ 

clean:
	del *.o
