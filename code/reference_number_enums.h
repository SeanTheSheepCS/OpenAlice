#ifndef REFERENCE_NUMBER_ENUMS_H
#define REFERENCE_NUMBER_ENUMS_H

enum worldObjectReferenceNumbers
{
	WORLD_OBJECT_REF_NUMBER_INVALID = 0,
	WORLD_OBJECT_REF_NUMBER_HOE = 1,
	WORLD_OBJECT_REF_NUMBER_HOUSE = 2,
	WORLD_OBJECT_REF_NUMBER_WELL = 3,
	WORLD_OBJECT_REF_NUMBER_WATERING_CAN = 4,
	WORLD_OBJECT_REF_NUMBER_TOP_BORDER_COLLISION_BOX = 5,
	WORLD_OBJECT_REF_NUMBER_BOTTOM_BORDER_COLLISION_BOX = 6,
	WORLD_OBJECT_REF_NUMBER_LEFT_BORDER_COLLISION_BOX = 7,
	WORLD_OBJECT_REF_NUMBER_RIGHT_BORDER_COLLISION_BOX = 8,

	WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_ONE = 9,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_ONE = 10,
	WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_ONE = 11,
	WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_TWO = 12,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_TWO = 13,
	WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_TWO = 14,
	WORLD_OBJECT_REF_NUMBER_TOMATO_SEED_PACKET_THREE = 15,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_SEED_PACKET_THREE = 16,
	WORLD_OBJECT_REF_NUMBER_CARROT_SEED_PACKET_THREE = 17,

	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE = 18,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE = 19,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE = 20,
	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO = 21,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO = 22,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO = 23,
	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE = 24,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE = 25,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE = 26/*,

	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_ONE_FILLED = 27,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_ONE_FILLED = 28,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_ONE_FILLED = 29,
	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_TWO_FILLED = 30,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_TWO_FILLED = 31,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_TWO_FILLED = 32,
	WORLD_OBJECT_REF_NUMBER_TOMATO_CRATE_THREE_FILLED = 33,
	WORLD_OBJECT_REF_NUMBER_CUCUMBER_CRATE_THREE_FILLED = 34,
	WORLD_OBJECT_REF_NUMBER_CARROT_CRATE_THREE_FILLED = 35
	*/
};

enum textureBankReferenceNumbers
{
	TEXTURE_BANK_REF_NUMBER_INVISIBLE = 0,

	TEXTURE_BANK_REF_NUMBER_OUT_OF_BOUNDS_GRASS = 1,
	TEXTURE_BANK_REF_NUMBER_IN_BOUNDS_GRASS = 2,
	TEXTURE_BANK_REF_NUMBER_UNWATERED_TILLED_DIRT = 3,
	TEXTURE_BANK_REF_NUMBER_WATERED_TILLED_DIRT = 4,

	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE = 5,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_HOE = 6,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN = 7,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_WATERING_CAN_EMPTY = 8,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_SEEDS = 9,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_SEEDS = 10,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_SEEDS = 11,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE = 12,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_TOMATO_CRATE_FILLED = 13,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE = 14,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CUCUMBER_CRATE_FILLED = 15,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE = 16,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_BASE_CARROT_CRATE_FILLED = 17,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE = 18,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_HOE = 19,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_WATERING_CAN = 20,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_WATERING_CAN_EMPTY = 21,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_SEEDS = 22,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_SEEDS = 23,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_SEEDS = 24,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_CRATE = 25,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED = 26,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_CRATE = 27,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED = 28,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_CRATE = 29,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_ONE_CARROT_CRATE_FILLED = 30,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO = 31,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_HOE = 32,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_WATERING_CAN = 33,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_WATERING_CAN_EMPTY = 34,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_SEEDS = 35,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_SEEDS = 36,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_SEEDS = 37,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_CRATE = 38,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED = 39,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_CRATE = 40,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED = 41,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_CRATE = 42,
	TEXTURE_BANK_REF_NUMBER_ALICE_DOWN_WALK_CYCLE_TWO_CARROT_CRATE_FILLED = 43,

	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE = 44,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_HOE = 45,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN = 46,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_WATERING_CAN_EMPTY = 47,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_SEEDS = 48,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_SEEDS = 49,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_SEEDS = 50,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE = 51,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_TOMATO_CRATE_FILLED = 52,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE = 53,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CUCUMBER_CRATE_FILLED = 54,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE = 55,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_BASE_CARROT_CRATE_FILLED = 56,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE = 57,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_HOE = 58,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_WATERING_CAN = 59,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_WATERING_CAN_EMPTY = 60,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_SEEDS = 61,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_SEEDS = 62,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_SEEDS = 63,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_CRATE = 64,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED = 65,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_CRATE = 66,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED = 67,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_CRATE = 68,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_ONE_CARROT_CRATE_FILLED = 69,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO = 70,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_HOE = 71,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_WATERING_CAN = 72,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_WATERING_CAN_EMPTY = 73,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_SEEDS = 74,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_SEEDS = 75,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_SEEDS = 76,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_CRATE = 77,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED = 78,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_CRATE = 79,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED = 80,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_CRATE = 81,
	TEXTURE_BANK_REF_NUMBER_ALICE_UP_WALK_CYCLE_TWO_CARROT_CRATE_FILLED = 82,

	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE = 83,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_HOE = 84,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN = 85,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_WATERING_CAN_EMPTY = 86,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_SEEDS = 87,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_SEEDS = 88,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_SEEDS = 89,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE = 90,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_TOMATO_CRATE_FILLED = 91,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE = 92,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CUCUMBER_CRATE_FILLED = 93,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE = 94,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_BASE_CARROT_CRATE_FILLED = 95,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE = 96,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_HOE = 97,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_WATERING_CAN = 98,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_WATERING_CAN_EMPTY = 99,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_SEEDS = 100,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_SEEDS = 101,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_SEEDS = 102,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_CRATE = 103,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED = 104,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_CRATE = 105,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED = 106,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_CRATE = 107,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_ONE_CARROT_CRATE_FILLED = 108,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO = 109,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_HOE = 110,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_WATERING_CAN = 111,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_WATERING_CAN_EMPTY = 112,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_SEEDS = 113,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_SEEDS = 114,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_SEEDS = 115,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_CRATE = 116,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED = 117,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_CRATE = 118,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED = 119,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_CRATE = 120,
	TEXTURE_BANK_REF_NUMBER_ALICE_LEFT_WALK_CYCLE_TWO_CARROT_CRATE_FILLED = 121,

	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE = 122,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_HOE = 123,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN = 124,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_WATERING_CAN_EMPTY = 125,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_SEEDS = 126,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_SEEDS = 127,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_SEEDS = 128,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE = 129,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_TOMATO_CRATE_FILLED = 130,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE = 131,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CUCUMBER_CRATE_FILLED = 132,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE = 133,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_BASE_CARROT_CRATE_FILLED = 134,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE = 135,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_HOE = 136,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_WATERING_CAN = 137,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_WATERING_CAN_EMPTY = 138,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_SEEDS = 139,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_SEEDS = 140,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_SEEDS = 141,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_CRATE = 142,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_TOMATO_CRATE_FILLED = 143,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_CRATE = 144,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CUCUMBER_CRATE_FILLED = 145,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_CRATE = 146,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_ONE_CARROT_CRATE_FILLED = 147,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO = 148,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_HOE = 149,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_WATERING_CAN = 150,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_WATERING_CAN_EMPTY = 151,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_SEEDS = 152,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_SEEDS = 153,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_SEEDS = 154,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_CRATE = 155,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_TOMATO_CRATE_FILLED = 156,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_CRATE = 157,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CUCUMBER_CRATE_FILLED = 158,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_CRATE = 159,
	TEXTURE_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CYCLE_TWO_CARROT_CRATE_FILLED = 160,

	TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOE = 161,
	TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_HOUSE = 162,
	TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WELL = 163,
	TEXTURE_BANK_REF_NUMBER_WORLD_OBJECT_WATERING_CAN = 164,

	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_BACKGROUND = 165,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BUTTON = 166,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_CREDITS_BUTTON = 167,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_EXIT_BUTTON = 168,

	TEXTURE_BANK_REF_NUMBER_WINDOW_X = 169,

	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_ONE_BACKGROUND_TEXTURE = 170,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_TWO_BACKGROUND_TEXTURE = 171,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SAVE_GAME_THREE_BACKGROUND_TEXTURE = 172,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_DELETE_SAVE_GAME_ICON_TEXTURE = 173,
	TEXTURE_BANK_REF_NUMBER_MAIN_MENU_SCREEN_SELECT_GAME_BACKGROUND = 174,

	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_ONE_TEXTURE = 175,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_TWO_TEXTURE = 176,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_ONE_TEXTURE = 177,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_ONE_TEXTURE = 178,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_ONE_TEXTURE = 179,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_ONE_TEXTURE = 180,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_THREE_HARVEST_TWO_TEXTURE = 181,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FOUR_HARVEST_TWO_TEXTURE = 182,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVEST_TWO_TEXTURE = 183,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_FIVE_HARVESTED_TWO_TEXTURE = 184,
	TEXTURE_BANK_REF_NUMBER_TOMATO_STAGE_SIX_TEXTURE = 185,

	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ONE_TEXTURE = 186,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TWO_TEXTURE = 187,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_THREE_TEXTURE = 188,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FOUR_TEXTURE = 189,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_FIVE_TEXTURE = 190,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SIX_TEXTURE = 191,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_SEVEN_TEXTURE = 192,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_ONE_TEXTURE = 193,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_ONE_TEXTURE = 194,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_ONE_TEXTURE = 195,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_ONE_TEXTURE = 196,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_TWO_TEXTURE = 197,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_TWO_TEXTURE = 198,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_TWO_TEXTURE = 199,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_TWO_TEXTURE = 200,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_EIGHT_HARVEST_THREE_TEXTURE = 201,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_NINE_HARVEST_THREE_TEXTURE = 202,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVEST_THREE_TEXTURE = 203,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_TEN_HARVESTED_THREE_TEXTURE = 204,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_STAGE_ELEVEN_TEXTURE = 205,

	TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_ONE_TEXTURE = 206,
	TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_TWO_TEXTURE = 207,
	TEXTURE_BANK_REF_NUMBER_CARROTS_STAGE_THREE_TEXTURE = 208,

	TEXTURE_BANK_REF_NUMBER_TOMATO_SEED_PACKET_TEXTURE = 209,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_SEED_PACKET_TEXTURE = 210,
	TEXTURE_BANK_REF_NUMBER_CARROT_SEED_PACKET_TEXTURE = 211,

	TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_TEXTURE = 212,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_TEXTURE = 213,
	TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_TEXTURE = 214,

	TEXTURE_BANK_REF_NUMBER_DAY_NIGHT_CIRCLE_TEXTURE = 215,

	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_ZERO_TEXTURE = 216,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_ONE_TEXTURE = 217,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_TWO_TEXTURE = 218,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_THREE_TEXTURE = 219,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_FOUR_TEXTURE = 220,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_FIVE_TEXTURE = 221,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_SIX_TEXTURE = 222,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_SEVEN_TEXTURE = 223,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_EIGHT_TEXTURE = 224,
	TEXTURE_BANK_REF_NUMBER_NUMBER_DISPLAY_NINE_TEXTURE = 225,

	TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_DAY_TEXTURE = 226,
	TEXTURE_BANK_REF_NUMBER_MONEY_SIGN_DISPLAY_TEXTURE = 227,

	TEXTURE_BANK_REF_NUMBER_BACK_TO_MAIN_MENU_BUTTON_TEXTURE = 228,
	TEXTURE_BANK_REF_NUMBER_GO_TO_MARKET_BUTTON_TEXTURE = 229,
	TEXTURE_BANK_REF_NUMBER_BACK_TO_FARM_BUTTON_TEXTURE = 230,

	TEXTURE_BANK_REF_NUMBER_TOMATO_CRATE_ICON_TEXTURE = 231,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_CRATE_ICON_TEXTURE = 232,
	TEXTURE_BANK_REF_NUMBER_CARROT_CRATE_ICON_TEXTURE = 233,
	TEXTURE_BANK_REF_NUMBER_MARKET_SCREEN_PURCHASE_AND_SALE_TAB_BACKGROUND = 234,
	TEXTURE_BANK_REF_NUMBER_MARKET_OFFER_BACKGROUND = 235,
	TEXTURE_BANK_REF_NUMBER_CHECK_ICON = 236,
	TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_BUY = 237,
	TEXTURE_BANK_REF_NUMBER_DISPLAYS_THE_WORD_SELL = 238,
	TEXTURE_BANK_REF_NUMBER_MARKET_SCREEN_BACKGROUND = 239,
	TEXTURE_BANK_REF_NUMBER_CREDITS_SCREEN_BACKGROUND_TEXTURE = 240,
	TEXTURE_BANK_REF_NUMBER_EMPTY_ICON_TEXTURE = 241,
	TEXTURE_BANK_REF_NUMBER_MONEY_ICON_TEXTURE = 242,
	TEXTURE_BANK_REF_NUMBER_TOMATO_ICON_TEXTURE = 243,
	TEXTURE_BANK_REF_NUMBER_CUCUMBER_ICON_TEXTURE = 244,
	TEXTURE_BANK_REF_NUMBER_CARROT_ICON_TEXTURE = 245
};

enum animationBankReferenceNumbers
{
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK = 0,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_HOE = 1,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN = 2,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_WATERING_CAN_EMPTY = 3,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_SEEDS = 4,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_SEEDS = 5,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_SEEDS = 6,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE = 7,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_TOMATO_CRATE_FILLED = 8,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE = 9,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CUCUMBER_CRATE_FILLED = 10,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE = 11,
	ANIMATION_BANK_REF_NUMBER_ALICE_DOWN_WALK_CARROT_CRATE_FILLED = 12,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK = 13,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_HOE = 14,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN = 15,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_WATERING_CAN_EMPTY = 16,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_SEEDS = 17,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_SEEDS = 18,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_SEEDS = 19,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE = 20,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_TOMATO_CRATE_FILLED = 21,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE = 22,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CUCUMBER_CRATE_FILLED = 23,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE = 24,
	ANIMATION_BANK_REF_NUMBER_ALICE_UP_WALK_CARROT_CRATE_FILLED = 25,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK = 26,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_HOE = 27,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN = 28,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_WATERING_CAN_EMPTY = 29,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_SEEDS = 30,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_SEEDS = 31,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_SEEDS = 32,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE = 33,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_TOMATO_CRATE_FILLED = 34,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE = 35,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CUCUMBER_CRATE_FILLED = 36,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE = 37,
	ANIMATION_BANK_REF_NUMBER_ALICE_LEFT_WALK_CARROT_CRATE_FILLED = 38,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK = 39,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_HOE = 40,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN = 41,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_WATERING_CAN_EMPTY = 42,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_SEEDS = 43,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_SEEDS = 44,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_SEEDS = 45,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE = 46,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_TOMATO_CRATE_FILLED = 47,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE = 48,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CUCUMBER_CRATE_FILLED = 49,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE = 50,
	ANIMATION_BANK_REF_NUMBER_ALICE_RIGHT_WALK_CARROT_CRATE_FILLED = 51,
};

#endif
