#include "world/level/block/BlockGrass.h"

#include "client/Crash.h"
#include "util/StringUtils.h"
#include "world/World.h"

u16 iconGrassTop, iconSnowSide;

static void registerIcons(Block* block) {
	const char* path;

	path		 = String_ParseTextureNamePrefix("block", block->name, "_side");
	block->icon	 = Texture_MapAdd(path);
	path		 = String_ParseTextureNamePrefix("block", block->name, "_top");
	iconGrassTop = Texture_MapAdd(path);
	path		 = String_ParseTextureNamePrefix("block", block->name, "_side_snow");
	iconSnowSide = Texture_MapAdd(path);
}
static u32 getBlockColor(Block* b, Direction dir, int x, int y, int z, u8 meta) {
	if (dir == Direction_Top) {
		/*BiomeGen* b = World_GetBiomeGenAt(x, y, z);
		u32 color	= BiomeGen_GetGrassColor(b);*/
		return 7979098;	 // hardcoded grass for now
	} else
		return COLOR_WHITE;
}
static u16 getBlockTexture(Block* block, Direction dir, int x, int y, int z, u8 metadata) {
	switch (dir) {
		case Direction_Top:
			return iconGrassTop;
			break;

		case Direction_Bottom:
			return Block_GetIcon(BLOCKS[BLOCK_DIRT], Direction_North, 0);

		default:
			const Material* mat = World_GetMaterial(x, y + 1, z);
			return mat->id != MATERIAL_SNOW && mat->id != MATERIAL_CRAFTED_SNOW ? block->icon : iconSnowSide;
	}
}

Block* BlockGrass_Init(BlockId id) {
	Block* b = Block_Init("grass_block", id, 0.6f, 0.6f, MATERIAL_GRASS, MAPCOLOR_GRASS);

	b->vptr->registerIcons	 = registerIcons;
	b->vptr->getBlockColor	 = getBlockColor;
	b->vptr->getBlockTexture = getBlockTexture;

	return b;
}