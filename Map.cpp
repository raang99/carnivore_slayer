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

    // 현재 카메라 위치에서 렌더링할 타일의 시작 위치 계산
    int startX = -(cameraX_ % TILE_SIZE);
    int startY = -(cameraY_ % TILE_SIZE);

    // 화면에 렌더링할 타일의 개수 계산
    int tilesX = SCREEN_WIDTH / TILE_SIZE + 1;
    int tilesY = SCREEN_HEIGHT / TILE_SIZE + 1;

    // 화면에 렌더링할 타일 맵 렌더링
    for (int y = -1; y < tilesY + 2; y++)
    {
        for (int x = -1; x < tilesX + 2; x++)
        {
            // 타일의 인덱스 계산
            int tileX = mapX + x;
            int tileY = mapY + y;

            // 타일의 렌더링 위치 계산
            int posX = startX + x * TILE_SIZE;
            int posY = startY + y * TILE_SIZE;

            // 타일 맵의 경계를 벗어나면 렌더링하지 않음


            // 타일 렌더링
            SDL_Rect dstRect = { posX, posY, TILE_SIZE, TILE_SIZE };
            SDL_RenderCopy(renderer, texture_, nullptr, &dstRect);
        }
    }
}

void Map::setCamera(int x, int y) {
    cameraX_ = x;
    cameraY_ = y;
}