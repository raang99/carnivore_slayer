#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <ctime>

//// 화면 크기
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// 물체 크기
//const int OBJECT_SIZE = 20;
//
//// 물체 속도
//const float OBJECT_SPEED = 2.0f;
//
//// 물체 위치
//struct ObjectPosition {
//    float x;
//    float y;
//};
//
//// 물체 구조체
//struct Object {
//    ObjectPosition position;
//    float angle;
//};
//
//// 물체 생성 함수
//Object CreateObject() {
//    // 랜덤한 위치 생성
//    float x = static_cast<float>(rand() % SCREEN_WIDTH);
//    float y = static_cast<float>(rand() % SCREEN_HEIGHT);
//
//    // 물체 생성 및 초기화
//    Object object;
//    object.position = { x, y };
//    object.angle = 0.0f;
//
//    return object;
//}
//
//// 물체 이동 함수
//void MoveObject(Object& object) {
//    // 삼각비를 이용한 이동
//    float dx = SCREEN_WIDTH / 2.0f - object.position.x;
//    float dy = SCREEN_HEIGHT / 2.0f - object.position.y;
//    float distance = std::sqrt(dx * dx + dy * dy);
//    float cosAngle = dx / distance;
//    float sinAngle = dy / distance;
//    object.position.x += OBJECT_SPEED * cosAngle;
//    object.position.y += OBJECT_SPEED * sinAngle;
//
//    // 각도 계산
//    object.angle = std::atan2(dy, dx) * 180.0f / M_PI;
//}
//
//// SDL 초기화 함수
//bool InitializeSDL() {
//    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
//        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << '\n';
//        return false;
//    }
//
//    return true;
//}
//
//int main(int argc, char* args[]) {
//    // SDL 초기화
//    if (!InitializeSDL()) {
//        return -1;
//    }
//
//    // 랜덤 시드 설정
//    srand(static_cast<unsigned int>(time(nullptr)));
//
//    // 윈도우 생성
//    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (window == nullptr) {
//        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
//        return -1;
//    }
//
//    // Renderer 생성
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == nullptr) {
//        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
//        return -1;
//    }
//
//    // 물체 생성
//    Object object = CreateObject();
//
//    // 이미지 로드
//    SDL_Surface* surface = IMG_Load("Resource/plain.png");
//    if (surface == nullptr) {
//        printf("이미지 파일 로드 실패: %s\n", IMG_GetError());
//        return 1;
//    }
//
//    // 텍스처 생성
//    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
//    if (texture == nullptr) {
//        printf("텍스처 생성 실패: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    // 서피스 해제
//    SDL_FreeSurface(surface);
//
//    // 이벤트 루프
//    bool quit = false;
//    while (!quit) {
//        // 이벤트 처리
//        SDL_Event event;
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // 배경색 설정
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // 물체 이동
//        MoveObject(object);
//
//        // 물체 렌더링
//        SDL_Rect objectRect = { static_cast<int>(object.position.x), static_cast<int>(object.position.y), OBJECT_SIZE, OBJECT_SIZE };
//        SDL_RenderCopyEx(renderer, texture, nullptr, &objectRect, object.angle, nullptr, SDL_FLIP_NONE);
//
//        // 렌더러 업데이트
//        SDL_RenderPresent(renderer);
//        SDL_Delay(20);
//    }
//
//    // SDL 종료
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}