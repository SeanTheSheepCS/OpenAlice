CXX=g++-8
CXXFLAGS=-std=c++17
VPATH=../code:../code/screens:../code/screens/subscreens:../code/engine/primitive_classes:../code/engine/advanced_classes/number_display_module:../code/engine/advanced_classes/player_object_module:../code/engine/advanced_classes/tile_map_module:../code/actors

OBJ = main.o save_game_helper.o save_file.o main_menu_screen.o farm_screen.o market_screen.o oae_screen.o start_game_screen.o credits_screen.o drawable_object.o textured_object.o textured_button_object.o number_display.o number_display_texture_pack.o tile_map.o player_object.o oae_animation.o oae_animation_instance.o oae_animated_object.o object_with_texture_map.o trigger_zone.o world_object.o collision_box.o texture_bank.o oae_animation_bank.o alice.o market_offer.o market_offer_list.o initialize_texture_bank.o 

alice_game: $(OBJ)
	$(CXX) -std=c++17 -o $@ $^ -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++fs -lX11

%.o: %.c
	$(CXX) -std=c++17 -c -o $@ 

clean:
	rm *.o
