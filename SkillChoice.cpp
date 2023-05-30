#include "SkillChoice.h"
#define _CRT_SECURE_NO_WARNINGS
SkillChoice::SkillChoice() {
	font_ = TTF_OpenFont("Resource/arose.ttf", 24);
    if (font_ == nullptr)
    {
        SDL_Log("��Ʈ ���� ����: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_Quit();
        exit(-1);
    }
    explain_font = TTF_OpenFont("Resource/arose.ttf", 15);
    if (explain_font == nullptr)
    {
        SDL_Log("��Ʈ ���� ����: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        TTF_Quit();
        SDL_Quit();
        exit(-1);
    }
    images[HP_MAX] = new Texture("Resource/skills/hp_max_.png");
    wcscpy_s(SKILL_EXPLAIN[HP_MAX][0], L"�ִ�ü�� 10% ����");
    images[HEAL] = new Texture("Resource/skills/heal_.png");
    wcscpy_s(SKILL_EXPLAIN[HEAL][0], L"�ʴ� ȸ�� 5����");
    images[SPEED] = new Texture("Resource/skills/speed_.png");
    wcscpy_s(SKILL_EXPLAIN[SPEED][0], L"�̵��ӵ� ����");
    images[SEARCH] = new Texture("Resource/skills/search_.png");
    wcscpy_s(SKILL_EXPLAIN[SEARCH][0], L"�����۽������ ����");
    images[GROWTH] = new Texture("Resource/skills/growth_.png");
    wcscpy_s(SKILL_EXPLAIN[GROWTH][0], L"����ġ���淮 ����");
    images[BASIC] = new Texture("Resource/skills/basic_.png");
    wcscpy_s(SKILL_EXPLAIN[BASIC][1], L"��Ÿ�� 20% ����");
    wcscpy_s(SKILL_EXPLAIN[BASIC][2], L"��Ÿ�� 20% ����");
    wcscpy_s(SKILL_EXPLAIN[BASIC][3], L"��Ÿ�� 20% ����");
    images[HORN] = new Texture("Resource/skills/horn_.png");
    wcscpy_s(SKILL_EXPLAIN[HORN][0], L"���� �Է� �����մϴ�.");
    wcscpy_s(SKILL_EXPLAIN[HORN][1], L"��Ÿ�� 20% ����");
    wcscpy_s(SKILL_EXPLAIN[HORN][2], L"���ݹ��� ����");
    wcscpy_s(SKILL_EXPLAIN[HORN][3], L"��Ÿ�� 30% ����");
    images[ELECTRIC] = new Texture("Resource/skills/electric_.png");
    wcscpy_s(SKILL_EXPLAIN[ELECTRIC][0], L"���ڱ����� ���� �����մϴ�.");
    wcscpy_s(SKILL_EXPLAIN[ELECTRIC][1], L"���ݹ��� ����");
    wcscpy_s(SKILL_EXPLAIN[ELECTRIC][2], L"������ 5 ����");
    wcscpy_s(SKILL_EXPLAIN[ELECTRIC][3], L"�����ֱ� 20% ����");
    images[FREEZE] = new Texture("Resource/skills/freeze_.png");
    wcscpy_s(SKILL_EXPLAIN[FREEZE][0], L"�ñ⸦ ���߽��� �����մϴ�.");
    wcscpy_s(SKILL_EXPLAIN[FREEZE][1], L"��Ÿ�� 20% ����");
    wcscpy_s(SKILL_EXPLAIN[FREEZE][2], L"���ݹ��� ����");
    wcscpy_s(SKILL_EXPLAIN[FREEZE][3], L"��Ÿ�� 20% ����");
    images[THUNDER] = new Texture("Resource/skills/thunder_.png");
    wcscpy_s(SKILL_EXPLAIN[THUNDER][0], L"���ڸ� ������ �����մϴ�.");
    wcscpy_s(SKILL_EXPLAIN[THUNDER][1], L"��Ÿ�� 30% ����");
    wcscpy_s(SKILL_EXPLAIN[THUNDER][2], L"��Ÿ�� 30% ����");
    wcscpy_s(SKILL_EXPLAIN[THUNDER][3], L"��Ÿ�� 30% ����");
    images[TIDE] = new Texture("Resource/skills/tide_.png");
    wcscpy_s(SKILL_EXPLAIN[TIDE][0], L"�ĵ��� ������ �����մϴ�.");
    wcscpy_s(SKILL_EXPLAIN[TIDE][1], L"��Ÿ�� 20% ����");
    wcscpy_s(SKILL_EXPLAIN[TIDE][2], L"���ݹ��� ����");
    wcscpy_s(SKILL_EXPLAIN[TIDE][3], L"������ 10 ����");

    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        int buttonX, buttonY;
        buttonX = BACK_X + BUTTON_WIDTH * i;
        buttonY = BACK_Y;
        buttons_[i] = { buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT };
    }
    reset_flag = true;
}
SkillChoice::~SkillChoice() {
    TTF_CloseFont(font_);
    TTF_CloseFont(explain_font);
}
void SkillChoice::handleEvents(User* user, std::vector<Attack*>* attack) {
    SDL_Event event;
    if (reset_flag) {
        set_rand_choice(*attack);
        reset_flag = false;
    }
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_running = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX = event.button.x;
            int mouseY = event.button.y;
            for (int i = 0; i < BUTTON_COUNT; i++)
            {
                if (mouseX >= buttons_[i].x && mouseX <= buttons_[i].x + buttons_[i].width &&
                    mouseY >= buttons_[i].y && mouseY <= buttons_[i].y + buttons_[i].height)
                {
                    reset_flag = true;
                    if (choices[i] == HP_MAX)
                        user->hp_max();
                    else if (choices[i] == HEAL)
                        user->heal();
                    else if (choices[i] == SPEED)
                        user->speed_up();
                    else if (choices[i] == SEARCH)
                        user->search();
                    else if (choices[i] == GROWTH)
                        user->growth();
                    else if(choices[i] > 4)
                        (*attack)[choices[i] - 0x5]->levelup();
                    user->levelup_flag = false;
                    SDL_Event keyEvent;
                    break;
                }
            }
        }
        break;
        }
    }
}

void SkillChoice::render(User *user, std::vector<Attack*>* attack) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    for (int i = 0; i < BUTTON_COUNT; i++)
    {
        //back
        SDL_Rect rect = { buttons_[i].x, buttons_[i].y, buttons_[i].width, buttons_[i].height };
        SDL_RenderFillRect(renderer, &rect);
        
        //image
        images[choices[i]]->set_drect(buttons_[i].x + BUTTON_PADDING, buttons_[i].y + BUTTON_PADDING, 160, 160);
        images[choices[i]]->render();
        //label
        wchar_t* text = SKILL_LABEL[choices[i]];
   
        SDL_Surface* labelSurface = TTF_RenderUTF8_Blended(font_, CW2A(text, CP_UTF8), {255, 255, 255});
        if (labelSurface != nullptr)
        {
            SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
            if (labelTexture != nullptr)
            {
                SDL_Rect labelRect = { buttons_[i].x + BUTTON_PADDING, TEXT_Y + BUTTON_PADDING, labelSurface->w, labelSurface->h};
                SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
                SDL_DestroyTexture(labelTexture);
            }
            SDL_FreeSurface(labelSurface);
        }
        //explain
        if(choices[i] < 0x5)
            text = SKILL_EXPLAIN[choices[i]][0];
        else {
            int level = get_skill_level(choices[i], *attack);
            text = SKILL_EXPLAIN[choices[i]][level];
        }

        labelSurface = TTF_RenderUTF8_Blended(explain_font, CW2A(text, CP_UTF8), { 255, 255, 255 });
        if (labelSurface != nullptr)
        {
            SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(renderer, labelSurface);
            if (labelTexture != nullptr)
            {
                SDL_Rect labelRect = { buttons_[i].x + BUTTON_PADDING , TEXT_Y + BUTTON_PADDING + EXPLAIN_PADDING, labelSurface->w, labelSurface->h };
                SDL_RenderCopy(renderer, labelTexture, nullptr, &labelRect);
                SDL_DestroyTexture(labelTexture);
            }
            SDL_FreeSurface(labelSurface);
        }
    }
    SDL_RenderPresent(renderer);
}

void SkillChoice::set_rand_choice(std::vector<Attack*> attack) {
    for (int i = 0; i < 3; i++)
        choices[i] = 0xff;
    while (true) {
        choices[0] = rand() % SKILL_COUNT;
        if (choices[0] > 0x4) {
            if (attack[choices[0] - 0x5]->level >= 4)
                continue;
        }
        break;
    }
    while (true) {
        choices[1] = rand() % SKILL_COUNT;
        if (choices[0] == choices[1])
            continue;
        if (choices[1] > 0x4)
            if (attack[choices[1] - 0x5]->level >= 4)
                continue;
        break;
    }

    while (true) {
        choices[2] = rand() % SKILL_COUNT;
        if (choices[0] == choices[2] || choices[1] == choices[2])
            continue;
        if (choices[2] > 0x4)
            if (attack[choices[2] - 0x5]->level >= 4)
                continue;
        break;
    }
}

int SkillChoice::get_skill_level(int skill, std::vector<Attack*> attack) {
    int active_num = skill - 0x5;
    return attack[active_num]->level;
}
