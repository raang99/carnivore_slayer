#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>
#include <ctime>

//// ȭ�� ũ��
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;
//
//// ��ü ũ��
//const int OBJECT_SIZE = 20;
//
//// ��ü �ӵ�
//const float OBJECT_SPEED = 2.0f;
//
//// ��ü ��ġ
//struct ObjectPosition {
//    float x;
//    float y;
//};
//
//// ��ü ����ü
//struct Object {
//    ObjectPosition position;
//    float angle;
//};
//
//// ��ü ���� �Լ�
//Object CreateObject() {
//    // ������ ��ġ ����
//    float x = static_cast<float>(rand() % SCREEN_WIDTH);
//    float y = static_cast<float>(rand() % SCREEN_HEIGHT);
//
//    // ��ü ���� �� �ʱ�ȭ
//    Object object;
//    object.position = { x, y };
//    object.angle = 0.0f;
//
//    return object;
//}
//
//// ��ü �̵� �Լ�
//void MoveObject(Object& object) {
//    // �ﰢ�� �̿��� �̵�
//    float dx = SCREEN_WIDTH / 2.0f - object.position.x;
//    float dy = SCREEN_HEIGHT / 2.0f - object.position.y;
//    float distance = std::sqrt(dx * dx + dy * dy);
//    float cosAngle = dx / distance;
//    float sinAngle = dy / distance;
//    object.position.x += OBJECT_SPEED * cosAngle;
//    object.position.y += OBJECT_SPEED * sinAngle;
//
//    // ���� ���
//    object.angle = std::atan2(dy, dx) * 180.0f / M_PI;
//}
//
//// SDL �ʱ�ȭ �Լ�
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
//    // SDL �ʱ�ȭ
//    if (!InitializeSDL()) {
//        return -1;
//    }
//
//    // ���� �õ� ����
//    srand(static_cast<unsigned int>(time(nullptr)));
//
//    // ������ ����
//    SDL_Window* window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (window == nullptr) {
//        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << '\n';
//        return -1;
//    }
//
//    // Renderer ����
//    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if (renderer == nullptr) {
//        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << '\n';
//        return -1;
//    }
//
//    // ��ü ����
//    Object object = CreateObject();
//
//    // �̹��� �ε�
//    SDL_Surface* surface = IMG_Load("Resource/plain.png");
//    if (surface == nullptr) {
//        printf("�̹��� ���� �ε� ����: %s\n", IMG_GetError());
//        return 1;
//    }
//
//    // �ؽ�ó ����
//    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
//    if (texture == nullptr) {
//        printf("�ؽ�ó ���� ����: %s\n", SDL_GetError());
//        return 1;
//    }
//
//    // ���ǽ� ����
//    SDL_FreeSurface(surface);
//
//    // �̺�Ʈ ����
//    bool quit = false;
//    while (!quit) {
//        // �̺�Ʈ ó��
//        SDL_Event event;
//        while (SDL_PollEvent(&event) != 0) {
//            if (event.type == SDL_QUIT) {
//                quit = true;
//            }
//        }
//
//        // ���� ����
//        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
//        SDL_RenderClear(renderer);
//
//        // ��ü �̵�
//        MoveObject(object);
//
//        // ��ü ������
//        SDL_Rect objectRect = { static_cast<int>(object.position.x), static_cast<int>(object.position.y), OBJECT_SIZE, OBJECT_SIZE };
//        SDL_RenderCopyEx(renderer, texture, nullptr, &objectRect, object.angle, nullptr, SDL_FLIP_NONE);
//
//        // ������ ������Ʈ
//        SDL_RenderPresent(renderer);
//        SDL_Delay(20);
//    }
//
//    // SDL ����
//    SDL_DestroyRenderer(renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//
//    return 0;
//}