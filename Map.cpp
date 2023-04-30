#include "Map.h"

Map::Map() {
	SDL_Surface* sheet_surface;
	const char* image_path = "Resource/tile.png";
	sheet_surface = IMG_Load(image_path);
	if (!sheet_surface) {
		std::cout << "image file " << image_path << "(open error)" << std::endl;
		exit(0);
	}
	texture_ = SDL_CreateTextureFromSurface(renderer, sheet_surface);
	SDL_FreeSurface(sheet_surface);
}

Map::~Map() {
    SDL_DestroyTexture(texture_);
}
void Map::render() {
    int mapX = cameraX_ / TILE_SIZE;
    int mapY = cameraY_ / TILE_SIZE;

    // ���� ī�޶� ��ġ���� �������� Ÿ���� ���� ��ġ ���
    int startX = -(cameraX_ % TILE_SIZE);
    int startY = -(cameraY_ % TILE_SIZE);

    // ȭ�鿡 �������� Ÿ���� ���� ���
    int tilesX = SCREEN_WIDTH / TILE_SIZE + 1;
    int tilesY = SCREEN_HEIGHT / TILE_SIZE + 1;

    // ȭ�鿡 �������� Ÿ�� �� ������
    for (int y = -1; y < tilesY + 2; y++)
    {
        for (int x = -1; x < tilesX + 2; x++)
        {
            // Ÿ���� �ε��� ���
            int tileX = mapX + x;
            int tileY = mapY + y;

            // Ÿ���� ������ ��ġ ���
            int posX = startX + x * TILE_SIZE;
            int posY = startY + y * TILE_SIZE;

            // Ÿ�� ���� ��踦 ����� ���������� ����


            // Ÿ�� ������
            SDL_Rect dstRect = { posX, posY, TILE_SIZE, TILE_SIZE };
            SDL_RenderCopy(renderer, texture_, nullptr, &dstRect);
        }
    }
}

void Map::setCamera(int x, int y) {
    cameraX_ = x;
    cameraY_ = y;
}