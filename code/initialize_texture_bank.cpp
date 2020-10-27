#include "initialize_texture_bank.h"

void addTextureToTextureBank(int referenceNumber, std::string path, TextureBank* bankToWriteTo)
{
    sf::Texture textureToAdd;
    std::string fullPath = std::string("../sprites/").append(path);
    if(!(textureToAdd.loadFromFile(fullPath)))
    {
        std::cout << "Failed to load texture: " << fullPath << std::endl;
        std::string invalidTexturePath = std::string("../sprites/").append("invalid_texture.png");
        if(!(textureToAdd.loadFromFile(invalidTexturePath)))
        {
            std::cout << "Failed to load texture: " << invalidTexturePath << std::endl;
        }
    }
    bankToWriteTo->saveTextureWithReferenceNumber(referenceNumber, textureToAdd);
}

TextureBank initializeTextureBank()
{
    TextureBank returnValue;    
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS, "grass_out_of_bounds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS, "grass.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT, "dirt_tilled_unwatered.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, "dirt_tilled_watered.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT, "dirt_tilled_watered.png", &returnValue);

    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE, "alice_down_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE, "alice_down_base_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN, "alice_down_base_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN_EMPTY, "alice_down_base_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS, "alice_down_base_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS, "alice_down_base_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS, "alice_down_base_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE, "alice_down_base_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED, "alice_down_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE, "alice_down_base_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED, "alice_down_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE, "alice_down_base_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED, "alice_down_base_carrot_crate_filled.png", &returnValue);
   	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE, "alice_down_walk_cycle_1.png", &returnValue);
   	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_HOE, "alice_down_walk_cycle_1_hoe.png", &returnValue);
   	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_WATERING_CAN, "alice_down_walk_cycle_1_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_WATERING_CAN_EMPTY, "alice_down_walk_cycle_1_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_SEEDS, "alice_down_walk_cycle_1_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_SEEDS, "alice_down_walk_cycle_1_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_SEEDS, "alice_down_walk_cycle_1_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_CRATE, "alice_down_walk_cycle_1_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED, "alice_down_walk_cycle_1_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_CRATE, "alice_down_walk_cycle_1_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED, "alice_down_walk_cycle_1_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_CRATE, "alice_down_walk_cycle_1_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_CRATE_FILLED, "alice_down_walk_cycle_1_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_HOE, "alice_down_walk_cycle_2_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_WATERING_CAN, "alice_down_walk_cycle_2_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_WATERING_CAN_EMPTY, "alice_down_walk_cycle_2_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_SEEDS, "alice_down_walk_cycle_2_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_SEEDS, "alice_down_walk_cycle_2_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_SEEDS, "alice_down_walk_cycle_2_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_CRATE, "alice_down_walk_cycle_2_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED, "alice_down_walk_cycle_2_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_CRATE, "alice_down_walk_cycle_2_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED, "alice_down_walk_cycle_2_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_CRATE, "alice_down_walk_cycle_2_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_CRATE_FILLED, "alice_down_walk_cycle_2_carrot_crate_filled.png", &returnValue);

    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE, "alice_up_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE, "alice_up_base_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN, "alice_up_base_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN_EMPTY, "alice_up_base_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS, "alice_up_base_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS, "alice_up_base_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS, "alice_up_base_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE, "alice_up_base_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED, "alice_up_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE, "alice_up_base_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED, "alice_up_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE, "alice_up_base_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED, "alice_up_base_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE, "alice_up_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_HOE, "alice_up_walk_cycle_1_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_WATERING_CAN, "alice_up_walk_cycle_1_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_WATERING_CAN_EMPTY, "alice_up_walk_cycle_1_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_SEEDS, "alice_up_walk_cycle_1_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_SEEDS, "alice_up_walk_cycle_1_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_SEEDS, "alice_up_walk_cycle_1_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_CRATE, "alice_up_walk_cycle_1_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED, "alice_up_walk_cycle_1_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_CRATE, "alice_up_walk_cycle_1_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED, "alice_up_walk_cycle_1_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_CRATE, "alice_up_walk_cycle_1_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_CRATE_FILLED, "alice_up_walk_cycle_1_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO, "alice_up_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_HOE, "alice_up_walk_cycle_2_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_WATERING_CAN, "alice_up_walk_cycle_2_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_WATERING_CAN_EMPTY, "alice_up_walk_cycle_2_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_SEEDS, "alice_up_walk_cycle_2_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_SEEDS, "alice_up_walk_cycle_2_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_SEEDS, "alice_up_walk_cycle_2_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_CRATE, "alice_up_walk_cycle_2_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED, "alice_up_walk_cycle_2_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_CRATE, "alice_up_walk_cycle_2_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED, "alice_up_cycle_2_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_CRATE, "alice_up_walk_cycle_2_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_CRATE_FILLED, "alice_up_walk_cycle_2_base_carrot_crate_filled.png", &returnValue);

    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE, "alice_left_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE, "alice_left_base_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN, "alice_left_base_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN_EMPTY, "alice_left_base_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS, "alice_left_base_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS, "alice_left_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS, "alice_left_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE, "alice_left_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED, "alice_left_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE, "alice_left_base_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED, "alice_left_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE, "alice_left_base_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED, "alice_left_base_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE, "alice_left_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_HOE, "alice_left_walk_cycle_1_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_WATERING_CAN, "alice_left_walk_cycle_1_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_WATERING_CAN_EMPTY, "alice_left_walk_cycle_1_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_SEEDS, "alice_left_walk_cycle_1_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_SEEDS, "alice_left_walk_cycle_1_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_SEEDS, "alice_left_walk_cycle_1_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_CRATE, "alice_left_walk_cycle_1_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED, "alice_left_walk_cycle_1_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_CRATE, "alice_left_walk_cycle_1_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED, "alice_left_walk_cycle_1_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_CRATE, "alice_left_walk_cycle_1_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_CRATE_FILLED, "alice_left_walk_cycle_1_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO, "alice_left_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_HOE, "alice_left_walk_cycle_2_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_WATERING_CAN, "alice_left_walk_cycle_2_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_WATERING_CAN_EMPTY, "alice_left_walk_cycle_2_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_SEEDS, "alice_left_walk_cycle_2_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_SEEDS, "alice_left_walk_cycle_2_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_SEEDS, "alice_left_walk_cycle_2_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_CRATE, "alice_left_walk_cycle_2_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED, "alice_left_walk_cycle_2_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_CRATE, "alice_left_walk_cycle_2_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED, "alice_left_cycle_2_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_CRATE, "alice_left_walk_cycle_2_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_CRATE_FILLED, "alice_left_walk_cycle_2_base_carrot_crate_filled.png", &returnValue);

    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE, "alice_right_base.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE, "alice_right_base_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN, "alice_right_base_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN_EMPTY, "alice_right_base_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS, "alice_right_base_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS, "alice_right_base_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS, "alice_right_base_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE, "alice_right_base_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED, "alice_right_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE, "alice_right_base_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED, "alice_right_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE, "alice_right_base_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED, "alice_right_base_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE, "alice_right_walk_cycle_1.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_HOE, "alice_right_walk_cycle_1_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_WATERING_CAN, "alice_right_walk_cycle_1_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_WATERING_CAN_EMPTY, "alice_right_walk_cycle_1_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_SEEDS, "alice_right_walk_cycle_1_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_SEEDS, "alice_right_walk_cycle_1_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_SEEDS, "alice_right_walk_cycle_1_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_CRATE, "alice_right_walk_cycle_1_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED, "alice_right_walk_cycle_1_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_CRATE, "alice_right_walk_cycle_1_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED, "alice_right_walk_cycle_1_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_CRATE, "alice_right_walk_cycle_1_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_CRATE_FILLED, "alice_right_walk_cycle_1_carrot_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO, "alice_right_walk_cycle_2.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_HOE, "alice_right_walk_cycle_2_hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_WATERING_CAN, "alice_right_walk_cycle_2_watering_can.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_WATERING_CAN_EMPTY, "alice_right_walk_cycle_2_watering_can_empty.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_SEEDS, "alice_right_walk_cycle_2_tomato_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_SEEDS, "alice_right_walk_cycle_2_cucumber_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_SEEDS, "alice_right_walk_cycle_2_carrot_seeds.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_CRATE, "alice_right_walk_cycle_2_tomato_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED, "alice_right_walk_cycle_2_base_tomato_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_CRATE, "alice_right_walk_cycle_2_cucumber_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED, "alice_right_cycle_2_base_cucumber_crate_filled.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_CRATE, "alice_right_walk_cycle_2_carrot_crate.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_CRATE_FILLED, "alice_right_walk_cycle_2_base_carrot_crate_filled.png", &returnValue);

    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOE, "hoe.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOUSE, "house.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WELL, "well.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WATERING_CAN, "watering_can.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BUTTON, "start_game_button.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_CREDITS_BUTTON, "credits_button.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_EXIT_BUTTON, "exit_button.png", &returnValue);
    addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_WINDOW_X, "x_icon.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_BACKGROUND, "main_menu_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_ONE_BACKGROUND_TEXTURE, "save_one_background.png", &returnValue); 
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_TWO_BACKGROUND_TEXTURE, "save_two_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_THREE_BACKGROUND_TEXTURE, "save_three_background.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE, "delete_save_button.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BACKGROUND, "select_game_screen_picture_frame_background.png", &returnValue);

	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE, "tomato_1_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE, "tomato_2_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_TEXTURE, "tomato_3_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_TEXTURE, "tomato_4_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_TEXTURE, "tomato_5_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE, "tomato_6_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE, "cucumber_1_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE, "cucumber_2_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE, "cucumber_3_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE, "cucumber_4_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE, "cucumber_5_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE, "cucumber_6_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE, "cucumber_7_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_TEXTURE, "cucumber_8_raw.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_TEXTURE, "cucumber_9_raw.png", &returnValue);

	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_TOMATO_SEED_PACKET_TEXTURE, "tomato_seed_packet.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE, "cucumber_seed_packet.png", &returnValue);
	addTextureToTextureBank(TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE, "carrot_seed_packet.png", &returnValue);
    return returnValue;
}
