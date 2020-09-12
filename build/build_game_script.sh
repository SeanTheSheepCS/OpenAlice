g++-8 -std=c++17 -c ../code/main.cpp ../code/screens/main_menu_screen.cpp ../code/screens/farm_screen.cpp ../code/screens/market_screen.cpp ../code/engine/primitive_classes/drawable_object.cpp ../code/engine/primitive_classes/textured_object.cpp ../code/engine/primitive_classes/textured_button_object.cpp
g++-8 main.o main_menu_screen.o farm_screen.o market_screen.o drawable_object.o textured_object.o textured_button_object.o -lsfml-graphics -lsfml-window -lsfml-system -lstdc++fs -lX11 -o alice_game
