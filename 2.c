#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <Windows.h>

typedef struct materials materials;
typedef struct items items;
typedef struct foods foods;
typedef struct users users;
typedef struct inventory inventory;
typedef struct inventory_item inventory_item;
typedef struct mobs mobs;
typedef struct maps maps;
typedef struct shelter shelter;
typedef struct productors productors;
typedef struct map_steps map_steps;
typedef struct incount incount;

typedef struct materials { //재료
    char* name; //이름
    int count; //갯수
    int value; //가치(각 재료마다의 배율)
} materials;

typedef struct items { //제작 아이템(장비)
    char* name; //이름
    int count; //갯수
    char* type; //장비타입
    materials materials; //재료
    int attack_value; //공격력
    int defense_value; //방어력
    int used_number; //내구도
    int mining_value; //채굴능력
    int logging_value; //벌목능력
} items;

typedef struct foods {
    char* name;
    int hunger_value;
    int health_value;
    int water_value;
} foods;

typedef struct inventory_item {
    materials material; //재료
    items item; //아이템
    foods food; //음식
    int material_count; //재료 아이템 갯수
    int item_count; //장비 아이템 갯수
    int food_count; //음식 아이템 갯수
    int is_material; //재료인지 여부
    int is_food; //음식인지 여부
    int is_item; //장비인지 여부
}inventory_item;

typedef struct inventorys {
    inventory_item* items; //인벤토리 아이템
    int inventory_count; //인벤토리 들어있는 칸
    int inven_max_count; //인벤토리 최대 칸 수
} inventorys;

typedef struct mobs { //적
    char* name;
    int health; //체력
    int attack; //공격력
    materials material; //떨어트릴 아이템
    items item[4]; //가진 아이템
} mobs;

typedef struct productors { //제작도구(작업대, 제련기 등등)
    char* name;
    materials materials[3]; //재료(필요 재료 및 입력, 출력 될 재료들)
    int value; //가치
    int inputs; //입력된 재료 갯수
    int outputs; //출력될 재료 갯수
} productors;

typedef struct shelter { //쉼터(기지)
    char* map;
    productors productor[10]; //설치된 제작도구
} shelter;

typedef struct maps { //지역
    char* name;
    map_steps* dunjeon; //던전 맵 (링크드 리스트로)
    shelter shelter; //쉼터
} maps;

typedef struct map_steps { //던전
    incount* random_incount; //상황들
    map_steps* link; //연결리스트
} map_steps;

typedef struct users { //유저
    int health; //체력
    int water; //목마름
    int temperature;  //온도
    int fatigue_value; //피로도
    int inventory_num; //인벤토리 갯수
    int attack; //유저 공격력
    int defense; //유저 방어력
    int mining_value; //유저 채굴능력
    int logging_value; //유저 벌목능력
    int is_shelter;
    maps place;
    inventorys* inventory; //인벤토리
    items equip_item[4]; //장비 아이템
} users;

typedef struct incount { //랜덤 인카운터 (주어질 상황)
    int number; //번호
    char* text; //주어질 상황(파일)
    items item; //주어질 아이템
    materials material; //주어질 재료
    users user; //유저
    mobs mob; //적
    incount* link;
} incount;

// 테두리와 텍스트 출력 함수
void print_border() {
    printf("+--------------------------------------------------+\n");
}

// 문자열 복사 함수
char* str_copy(const char* source) {
    char* tmp = (char*)malloc(strlen(source) + 1);
    strcpy(tmp, source);
    return tmp;
}

void print_status(users* user) {
    print_border();
    printf("| 체력: %d | 목마름: %d |  온도: %d  | 피로도: %d  |\n", user->health, user->water, user->temperature, user->fatigue_value);
    print_border();
}

void print_equip_item(users* user) {
    print_border();
    printf("| 무기: %s | 모자: %s | 갑옷: %s | 신발: %s |\n", user->equip_item[0].name, user->equip_item[1].name, user->equip_item[2].name, user->equip_item[3].name);
    print_border();
}

void print_mob_status(mobs* mob) {
    print_border();
    printf("| 이름: %s | 체력: %s | 공격력: %d |\n", mob->name, mob->health, mob->attack);
    print_border();
}

void print_user_status(users* user) {
    print_border();
    printf("| 공격력: %d | 방어력: %d | 채굴능력: %d | 벌목능력: %d |\n", user->attack, user->defense, user->mining_value, user->logging_value);
    print_border();
}

void material_list(materials* material) {
    material[0].name = str_copy("나무");
    material[1].name = str_copy("돌");
    material[2].name = str_copy("철");

    material[0].value = 1;
    material[1].value = 2;
    material[2].value = 3;
}

// 아이템 리스트 초기화
void item_list(items* item) { // 아이템 종류들

    // 나무 아이템
    item[0].name = str_copy("나무 칼");
    item[1].name = str_copy("나무 도끼");
    item[2].name = str_copy("나무 곡괭이");
    item[3].name = str_copy("나무 모자");
    item[4].name = str_copy("나무 갑옷");
    item[5].name = str_copy("나무 신발");

    item[0].type = str_copy("무기");
    item[1].type = str_copy("도구");
    item[2].type = str_copy("도구");
    item[3].type = str_copy("모자");
    item[4].type = str_copy("갑옷");
    item[5].type = str_copy("신발");

    item[0].attack_value = 7 * 1; // 나무 칼
    item[1].attack_value = 5 * 1; // 나무 도끼
    item[2].attack_value = 3 * 1; // 나무 곡괭이
    item[3].defense_value = 4 * 1; // 나무 모자
    item[4].defense_value = 6 * 1; // 나무 갑옷
    item[5].defense_value = 3 * 1; // 나무 신발
    item[1].logging_value = 5 * 1; // 나무 도끼
    item[2].logging_value = 2 * 1; // 나무 곡괭이
    item[1].mining_value = 2 * 1; // 나무 도끼
    item[2].mining_value = 5 * 1; // 나무 곡괭이

    // 돌 아이템
    item[6].name = str_copy("돌 칼");
    item[7].name = str_copy("돌 도끼");
    item[8].name = str_copy("돌 곡괭이");
    item[9].name = str_copy("돌 모자");
    item[10].name = str_copy("돌 갑옷");
    item[11].name = str_copy("돌 신발");

    item[6].type = str_copy("무기");
    item[7].type = str_copy("도구");
    item[8].type = str_copy("도구");
    item[9].type = str_copy("모자");
    item[10].type = str_copy("갑옷");
    item[11].type = str_copy("신발");

    item[6].attack_value = 7 * 2; // 돌 칼
    item[7].attack_value = 5 * 2; // 돌 도끼
    item[8].attack_value = 3 * 2; // 돌 곡괭이
    item[9].defense_value = 4 * 2; // 돌 모자
    item[7].logging_value = 5 * 2; // 돌 도끼
    item[8].logging_value = 2 * 2; // 돌 곡괭이
    item[7].mining_value = 2 * 2; // 돌 도끼
    item[8].mining_value = 5 * 2; // 돌 곡괭이
    item[10].defense_value = 6 * 2; // 돌 갑옷
    item[11].defense_value = 3 * 2; // 돌 신발

    // 철 아이템
    item[12].name = str_copy("철 칼");
    item[13].name = str_copy("철 도끼");
    item[14].name = str_copy("철 곡괭이");
    item[15].name = str_copy("철 모자");
    item[16].name = str_copy("철 갑옷");
    item[17].name = str_copy("철 신발");

    item[12].type = str_copy("무기");
    item[13].type = str_copy("도구");
    item[14].type = str_copy("도구");
    item[15].type = str_copy("모자");
    item[16].type = str_copy("갑옷");
    item[17].type = str_copy("신발");

    item[12].attack_value = 7 * 3; // 철 칼
    item[13].attack_value = 5 * 3; // 철 도끼
    item[14].attack_value = 3 * 3; // 철 곡괭이
    item[15].defense_value = 4 * 3; // 철 모자
    item[13].logging_value = 5 * 3; // 철 도끼
    item[14].logging_value = 2 * 3; // 철 곡괭이
    item[13].mining_value = 2 * 3; // 철 도끼
    item[14].mining_value = 5 * 3; // 철 곡괭이
    item[16].defense_value = 6 * 3; // 철 갑옷
    item[17].defense_value = 3 * 3; // 철 신발

    //기타 도구
    item[18].name = str_copy("횃불");
    item[19].name = str_copy("모닥불");
    item[20].name = str_copy("나침반");
    item[21].name = str_copy("지도");

    item[18].type = str_copy("기타도구");
    item[19].type = str_copy("기타도구");
    item[20].type = str_copy("기타도구");
    item[21].type = str_copy("기타도구");

    //기타 무기
    item[22].name = str_copy("활");

    item[22].type = str_copy("무기");

    item[22].attack_value = 15;
}

void food_list(foods* food) {
    //음식 이름
    food[0].name = str_copy("햄버거");
    food[1].name = str_copy("샌드위치");
    food[2].name = str_copy("음료수");
    food[3].name = str_copy("물");
    food[4].name = str_copy("생고기");
    food[5].name = str_copy("구운고기");
    food[6].name = str_copy("사과");

    //음식 배고픔
    food[0].hunger_value = 80;
    food[1].hunger_value = 50;
    food[4].hunger_value = 10;
    food[5].hunger_value = 80;
    food[6].hunger_value = 20;

    //음식 목마름
    food[2].water_value = 70;
    food[3].water_value = 100;

    //음식 체력
    food[0].health_value = 30;
    food[1].health_value = 30;
    food[4].health_value = -20;
    food[5].health_value = 50;
    food[6].health_value = 10;
}

void mob_list(mobs* mob) {
    mob[0].name = str_copy("약한좀비");
    mob[1].name = str_copy("좀비");
    mob[2].name = str_copy("강화좀비");
    mob[3].name = str_copy("곰");
    mob[4].name = str_copy("토끼");
    mob[5].name = str_copy("도둑");
    mob[6].name = str_copy("무장한강도");

    mob[0].health = 20;
    mob[1].health = 50;
    mob[2].health = 100;
    mob[3].health = 80;
    mob[4].health = 20;
    mob[5].health = 50;
    mob[6].health = 100;

    mob[0].attack = 5;
    mob[1].attack = 20;
    mob[2].attack = 50;
    mob[3].attack = 20;
    mob[4].attack = 5;
    mob[5].attack = 25;
    mob[6].attack = 70;
}

void map_list(maps* map) {
    map[0].name = "도시";
    map[1].name = "숲";
    map[2].name = "폐광산";
}


void inven_list(inventorys* inven) {
    inven->inventory_count = 0;
    inven->inven_max_count = 5;
    inven->items = (inventory_item*)malloc(sizeof(inventory_item) * inven->inven_max_count);
}

void user_start_set(users* user, items* item, maps* map) {
    user->health = 100;
    user->water = 100;
    user->temperature = 36;
    user->fatigue_value = 0;
    user->attack = 1;
    user->defense = 0;
    user->mining_value = 1;
    user->logging_value = 1;
    user->inventory_num = 5;
    user->is_shelter = 0;
    user->place = map[0];

    inven_list(&user->inventory);

    // 장비 아이템 초기화
    user->equip_item[0].name = str_copy("주먹");
    user->equip_item[0].attack_value = 1;
    user->equip_item[0].logging_value = 1;
    user->equip_item[0].mining_value = 1;
    user->equip_item[0].type = str_copy("무기");
    for (int i = 1; i < 4; i++) {
        user->equip_item[i].name = str_copy("없음");
        user->equip_item[i].attack_value = 0;
        user->equip_item[i].defense_value = 0;
        user->equip_item[i].mining_value = 0;
        user->equip_item[i].logging_value = 0;
    }
}

// 장비 장착 함수
void equip_item(users* user, items item, char* window) { //장비 장착
    int slot = -1;
    if (strcmp(item.type, "무기") == 0 || strcmp(item.type, "기타도구") == 0 || strcmp(item.type, "도구") == 0) {
        slot = 0;
        user->attack = 1;
        user->logging_value = 1;
        user->mining_value = 1;
    }
    else if (strcmp(item.type, "모자") == 0) {
        slot = 1;
        user->defense -= user->equip_item[1].defense_value;
    }
    else if (strcmp(item.type, "갑옷") == 0) {
        slot = 2;
        user->defense -= user->equip_item[2].defense_value;
    }
    else if (strcmp(item.type, "신발") == 0) {
        slot = 3;
        user->defense -= user->equip_item[3].defense_value;
    }
    if (slot != -1) {
        user->equip_item[slot] = item;
        user->attack += item.attack_value;
        user->defense += item.defense_value;
        user->mining_value += item.mining_value;
        user->logging_value += item.logging_value;
        window = "장착되었습니다.";
    }
    else {
        window = "장비 장착에 실패했습니다.";
    }
}

void add_inven(inventorys* inv, inventory_item item) {
    for (int i = 0; i < inv->inven_max_count; i++) { //인벤토리 최대 칸 안에서 중복 검색
        if (inv->items[i].is_material && strcmp(inv->items[i].material.name, item.material.name) == 0) {
            inv->items[i].material_count += item.material_count;
            return;
        }
        else if (!inv->items[i].is_material && strcmp(inv->items[i].item.name, item.item.name) == 0) {
            inv->items[i].item_count += item.item_count;
            return;
        }
        else if (!inv->items[i].is_material && strcmp(inv->items[i].food.name, item.food.name) == 0) {
            inv->items[i].food_count += item.food_count;
            return;
        }
    }

    inv->items = realloc(inv->items, (inv->inventory_count + 1) * sizeof(inventory_item)); //동적 재할당(인벤토리 아이템 칸 증가)
    inv->items[inv->inventory_count] = item;
    inv->inventory_count++;
}

void remove_inven(inventorys* inv, const char* name, int count, char* window) {
    for (int i = 0; i < inv->inven_max_count; i++) {
        if (inv->items[i].is_material && strcmp(inv->items[i].material.name, name) == 0 && inv->items[i].material_count >= count) {
            inv->items[i].material_count -= count;
            if (inv->items[i].material_count == 0) {
                for (int j = i; j < inv->inventory_count - 1; j++) {
                    inv->items[j] = inv->items[j + 1];
                }
                inv->items = realloc(inv->items, (inv->inventory_count - 1) * sizeof(inventory_item));
                inv->inventory_count--;
            }
            return;
        }
        else if (!inv->items[i].is_material && strcmp(inv->items[i].item.name, name) == 0 && inv->items[i].item_count >= count) {
            inv->items[i].item_count -= count;
            if (inv->items[i].item_count == 0) {
                for (int j = i; j < inv->inventory_count - 1; j++) {
                    inv->items[j] = inv->items[j + 1];
                }
                inv->items = realloc(inv->items, (inv->inventory_count - 1) * sizeof(inventory_item));
                inv->inventory_count--;
            }
            return;
        }
        else if (!inv->items[i].is_material && strcmp(inv->items[i].food.name, name) == 0 && inv->items[i].food_count >= count) {
            inv->items[i].food_count -= count;
            if (inv->items[i].food_count == 0) {
                for (int j = i; j < inv->inventory_count - 1; j++) {
                    inv->items[j] = inv->items[j + 1];
                }
                inv->items = realloc(inv->items, (inv->inventory_count - 1) * sizeof(inventory_item));
                inv->inventory_count--;
            }
            return;
        }
    }
    window = "해당 아이템을 찾을 수 없거나 갯수가 부족합니다.";
}

void print_inven(users* user) {
    printf("| 인벤토리:\n");
    for (int i = 0; i < user->inventory->inventory_count; i++) {
        inventory_item* inven_item = &user->inventory[i].items;
        if (inven_item->is_item) {
            printf("%s x%d\n", inven_item->item.name, inven_item->item_count);
        }
        if (inven_item->is_material) {
            printf("%s x%d\n", inven_item->material.name, inven_item->material_count);
        }
        if (inven_item->is_food) {
            printf("%s x%d\n", inven_item->food.name, inven_item->food_count);
        }
    }
}

void free_list(materials* material, items* item, foods* food, mobs* mob, int material_count, int item_count, int food_count, int mob_count) {
    for (int i = 0; i < item_count; i++) {
        free(item[i].name);
        free(item[i].type);
    }
    for (int i = 0; i < material_count; i++) {
        free(material[i].name);
    }
    for (int i = 0; i < food_count; i++) {
        free(food[i].name);
    }
    for (int i = 0; i < mob_count; i++) {
        free(mob[i].name);
    }
}

void is_command(int* is_move, int* is_product, int* is_sheltermove, int* is_equip, int* is_using, int* is_log, int* is_mine, int* is_attack, int* is_deffend, int move, int product, int sheltermove, int equip, int using, int log, int mine, int attack, int deffend) {

    *is_move = move; //이동
    *is_product = product; //제작
    *is_sheltermove = sheltermove; //쉘터이동
    *is_equip = equip; //장비 장착
    *is_using = using; //아이템사용
    *is_log = log; //벌목
    *is_mine = mine; //채굴
    *is_attack = attack; //공격
    *is_deffend = deffend; //방어
} //사용가능 커맨드 분류

void print_center(const char* message) {
    int width = 50; // 화면 너비
    int padding = (width - strlen(message)) / 2; // 메시지를 중앙에 배치하기 위한 좌우 여백 계산
    print_border();
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", message);
    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("\n");
    print_border();
}

void cann_command(int is_move, int is_product, int is_sheltermove, int is_equip, int is_using, int is_log, int is_mine, int is_attack, int is_deffend) {
    if (is_move) printf("이동 ");
    if (is_product) printf("제작 ");
    if (is_sheltermove) printf("쉘터이동 ");
    if (is_equip) printf("장비착용 ");
    if (is_using) printf("아이템사용 ");
    if (is_log) printf("벌목 ");
    if (is_mine) printf("채광 ");
    if (is_attack) printf("공격 ");
    if (is_deffend) printf("방어 ");
    printf("\n");
} //사용가능 커맨드 문자열 추가

//커맨드 작동
void command(char* input, int *command_check, int* is_move, int* is_product, int* is_sheltermove, int* is_equip, int* is_using, int* is_log, int* is_mine, int* is_attack, int* is_deffend, int *command_type, char* window, users* user, maps* map, items* item, materials* material, foods* food, productors* productor, shelter* shel, inventory_item* inventory_items, map_steps* map_step1, map_steps* map_step2, map_steps* map_step3, map_steps* map_step4) {
    (*command_check)++;
    if (strcmp(input, "이동") == 0) { //이동 입력
        if (*is_move != 1) { //이동이 불가능할 때, 이동을 입력시
            strcpy(window, "| >>불가능한 명령입니다.");
            (*command_check)--;
            return;
        }
        else { //현재 이동 가능한 지역 안내
            strcpy(window, "| >>현재 이동 가능한 지역: 도시, 숲, 폐광산");
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            *command_type = 0;
            return;
        }
    } //도시 선택시
    else if (strcmp(input, "도시") == 0 && *command_type == 0) {
        if (user->is_shelter == 1) { 
            if (strcmp(shel->map, "도시") != 0) { //쉘터 위치가 도시가 아니면 피로도 증가
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[0]; //도시 도착
        *command_type = 1;
        strcpy(window, "| >>이용 가능한 장소: 던전, 파밍");
        return;
    } //숲 선택시
    else if (strcmp(input, "숲") == 0 && *command_type == 0) {

        if (user->is_shelter == 1) { //쉘터 위치가 숲이 아니면 피로도 증가
            if (strcmp(shel->map, "숲") != 0) {
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[1]; //숲 도착
        *command_type = 1;
        strcpy(window , "| >>이용 가능한 장소: 던전, 파밍");
        return;
    }
    else if (strcmp(input, "폐광산") == 0 && *command_type == 0) {

        if (user->is_shelter == 1) {
            if (strcmp(shel->map, "폐광산") != 0) { //쉘터 위치가 광산이 아니면 피로도 증가
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>이동하다 피로도가 쌓여 죽었습니다.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[2]; //폐광산 도착
        *command_type = 1;
        strcpy(window, "| >>이용 가능한 장소: 던전, 파밍");
        return;
    }
    else if (strcmp(input, "취소") == 0 && *command_type == 0) { //이동 취소 시
        if (user->is_shelter == 0) { //쉘터 없는경우 가능한 명령어
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
        }
        else if (user->is_shelter == 1) { //쉘터 있는 경우 가능한 명령어
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
        }
        *command_type = -1;
        strcpy(window, "| >>취소되었습니다.");
        return;
    }
    else if (strcmp(user->place.name, "도시") == 0 && strcmp(input, "파밍") == 0 && *command_type == 1) { //도시에서 파밍지역 선택
        strcpy(window, "| >>현재 위치한 곳은 도시 파밍지 입니다.(음식, 물 파밍 가능)");

        *command_type = -1;
    }
    else if (strcmp(user->place.name, "도시") == 0 && strcmp(input, "던전") == 0 && *command_type == 1) { //도시에서 던전 선택
        srand(time(NULL));
        int random = rand() % 4;
        if (random == 0) {
            user->place.dunjeon = map_step1;
        }
        else if (random == 1) {
            user->place.dunjeon = map_step2;
        }
        else if (random == 2) {
            user->place.dunjeon = map_step3;
        }
        else if (random == 3) {
            user->place.dunjeon = map_step4;
        }
        strcpy(window, "| >>도시 던전 입장");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
        return;
    }
    else if (strcmp(user->place.name, "숲") == 0 && strcmp(input, "파밍") == 0 && *command_type == 1) { //숲에서 파밍지역 선택
        strcpy(window, "| >>현재 위치한 곳은 숲 파밍지 입니다.(나무 파밍 가능)");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 1, 0, 0, 0);
        *command_type = -1;
    }
    else if (strcmp(user->place.name, "숲") == 0 && strcmp(input, "던전") == 0 && *command_type == 1) { //숲에서 던전지역 선택
        srand(time(NULL));
        int random = rand() % 4;
        if (random == 0) {
            user->place.dunjeon = map_step1;
        }
        else if (random == 1) {
            user->place.dunjeon = map_step2;
        }
        else if (random == 2) {
            user->place.dunjeon = map_step3;
        }
        else if (random == 3) {
            user->place.dunjeon = map_step4;
        }
        strcpy(window, "| >>숲 던전 입장");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
    }
    else if (strcmp(user->place.name, "폐광산") == 0 && strcmp(input, "파밍") == 0 && *command_type == 1) { //폐광산에서 파밍지역 선택
        strcpy(window, "| >>현재 위치한 곳은 광산 파밍지 입니다.(돌, 철, 석탄 파밍 가능)");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 1, 0, 0);
        *command_type = -1;
    }
    else if (strcmp(user->place.name, "폐광산") == 0 && strcmp(input, "던전") == 0 && *command_type == 1) { //폐광산에서 던전 선택
        srand(time(NULL));
        int random = rand() % 4;
        if (random == 0) {
            user->place.dunjeon = &map_step1;
        }
        else if (random == 1) {
            user->place.dunjeon = &map_step2;
        }
        else if (random == 2) {
            user->place.dunjeon = &map_step3;
        }
        else if (random == 3) {
            user->place.dunjeon = &map_step4;
        }
        user->place.dunjeon = map_step1;
        user->place.dunjeon->random_incount = map_step1->random_incount;
        strcpy(window, "| >>폐광산 던전 입장");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
        return;
    }
    else { //없는 단어 입력
        strcpy(window, "| >>잘못입력되었습니다.");
        (*command_check)--;
        return;
    }
    if (strcmp(input, "제작") == 0) { //제작 입력
        if (*is_product != 1) {
            strcpy(window, "| >>불가능한 명령입니다.");
            return;
        }
        else {
            strcpy(window, "| >>현재 제작 가능한 물품: ");
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            *command_type = 0;
            return;
        }

    }
    else if (strcmp(input, "쉘터이동") == 0 || command_type == 2) { //쉘터이동 선택
        if (*is_sheltermove == 1) {
            if (user->is_shelter == 1) {
                for (int i = 0; i < 3; i++) { //쉘터 지은 지역 검색
                    if (strcmp(shel->map, map[i].name) == 0) {
                        user->place = map[i]; //지역이동
                    }
                }
                strcpy(window,  "| >>쉘터로 이동했습니다.");
                is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 1, 0, 1, 1, 0, 0, 0, 0); //쉘터 이동 후 사용 가능한 명령어
            }
            else { //쉘터가 없을 때
                strcpy(window, "| >>지어진 쉘터가 없습니다.");
                return;
        }
            }
        else { //쉘터 이동 안될 때 입력
            strcpy(window, "| >>불가능한 명령입니다.");
        }
    }
    else if (strcmp(input, "장비착용") == 0 || command_type == 3) { //장비착용 선택
        if (*is_equip == 1) {
            if (command_type == 3) {
                remove_inven(&user->inventory, input, 1, window); //인벤토리에서 아이템 제거
                for (int i = 0; i < 23; i++) {
                    if (input == item[i].name) {
                        if (strcmp(item[i].type, "무기") == 0 || strcmp(item[i].type, "기타도구") == 0 || strcmp(item[i].type, "도구") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[0];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "모자") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[1];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "갑옷") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[2];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "신발") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[3];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        equip_item(user, item[i], window);
                    }
                }
                if (user->is_shelter == 0) { //장비종료 후 커맨드 사용가능한 경우의 수가 다양함. 조심.
                    is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
                }
                else if (user->is_shelter == 1) {
                    is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
                }
                *command_type = -1;
                return;
            }
            *command_type = 3;
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 0, 0, 0, 1, 0, 0, 0, 0, 0);
            window = "인벤토리 장비 중 하나를 적어주세요.";
            return;
        }
        else {
            window = "불가능한 명령입니다.";
        }
    }
    else if (strcmp(input, "아이템사용") == 0 || command_type == 4) { //아이템 사용
        if (*is_using == 1) {

        }
        else {
            window = "불가능한 명령입니다.";
        }
    }
    else if (strcmp(input, "벌목") == 0 || command_type == 5) { //벌목
        if (*is_log == 1) {
            window = "벌목 완료(나무 2개)";
            inventory_item items_;
            items_.is_material = 1;
            items_.material = material[0];
            items_.material_count = 2;
            add_inven(&user->inventory, items_);
            user->fatigue_value += (30 / user->logging_value);
            if (user->fatigue_value > 100) {
                window = "벌목하다 피로도가 쌓여 죽었습니다.";
            }
            *command_type = -1;
            return;
        }
        else {
            window = "불가능한 명령입니다.";
            return;
        }
    }
    else if (strcmp(input, "채광") == 0 || command_type == 6) { //채굴
        if (*is_mine == 1) { //.
            window = "채굴 완료";
            inventory_item items_;
            items_.is_material = 1;
            int random_num = 0;
            random_num = rand() % 10;
            if (random_num <= 1) {

            }
        }
        else {
            window = "불가능한 명령입니다.";
        }
    }
    else if (strcmp(input, "공격") == 0 || command_type == 7) {
        if (*is_attack == 1) { // 공격
            user->place.dunjeon->random_incount->mob.health -= user->attack;
            user->health -= user->place.dunjeon->random_incount->mob.attack;
            //다음 라운드로 진행 (연결리스트)
            if (user->place.dunjeon->random_incount->mob.health < 0) { //승리
                user->place.dunjeon->random_incount = user->place.dunjeon->random_incount->link;
                //보상
                inventory_item items_;
                items_.item = user->place.dunjeon->random_incount->item;
                items_.material = user->place.dunjeon->random_incount->material;

                //던전 종료
                if (user->place.dunjeon->random_incount->link == NULL) {
                    window = "던전 완료";
                    if (user->is_shelter == 0) { //쉘터 있는 경우
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
                    }
                    else if (user->is_shelter == 1) { //쉘터 없는 경우
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
                    }
                    return;
                }
            }
            else if (user->health < 0) { //패배
                window = "몬스터에 의해 처치당하였습니다.";
            }
        }
        else {
            window = "불가능한 명령입니다.";
        }
    }
    else if (strcmp(input, "방어") == 0 || command_type == 8) {
        if (*is_deffend == 1) { //방어
            user->place.dunjeon->random_incount->mob.health -= (user->attack / 2); //공격력의 절반만큼 데미지 입힘
            user->health -= (user->place.dunjeon->random_incount->mob.attack - user->defense); //방어력만큼 데미지 경감
            if (user->place.dunjeon->random_incount->mob.health < 0) { //승리
                user->place.dunjeon->random_incount = user->place.dunjeon->random_incount->link; //다음라운드 진행 (연결리스트)
                //보상
                inventory_item items_;
                items_.item = user->place.dunjeon->random_incount->item;
                items_.material = user->place.dunjeon->random_incount->material;

                if (user->place.dunjeon->random_incount->link == NULL) { //던전종료 (연결리스트 마지막)
                    window = "던전 완료";
                    if (user->is_shelter == 0) { //쉘터 있는 경우
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
                    }
                    else if (user->is_shelter == 1) { //쉘터 없는 경우
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
                    }
                    return;
                }
            }
            else if (user->health < 0) { //패배
                window = "몬스터에 의해 처치당하였습니다.";
                return;
            }
        }
        else { //방어 불가능할 때 방어 입력 시,
            window = "불가능한 명령입니다.";
            (*command_check)--;
            return;
        }
    }
    else { //명령어에 없는 단어 입력시
        window = "| >>잘못된 입력입니다.";
        (*command_check)--;
        return;
    }
}

int main() {
    srand(time(NULL));
    materials* material;
    items* item;
    foods* food;
    mobs* mob;
    users* user = NULL;
    maps map[3];
    productors* productor;
    shelter* shel;
    inventory* inven = NULL;
    inventory_item* inven_item;

    map_steps* map_step;
    incount* incounts;

    incount* incounts11;
    incount* incounts12;
    incount* incounts13;
    incount* incounts14;

    incount* incounts21;
    incount* incounts22;
    incount* incounts23;
    incount* incounts24;

    incount* incounts31;
    incount* incounts32;
    incount* incounts33;
    incount* incounts34;

    incount* incounts41;
    incount* incounts42;
    incount* incounts43;
    incount* incounts44;

    map_steps* map_step1;
    map_steps* map_step2;
    map_steps* map_step3;
    map_steps* map_step4;

    int is_move = 0;
    int is_product = 0;
    int is_sheltermove = 0;
    int is_equip = 0;
    int is_using = 0;
    int is_log = 0;
    int is_mine = 0;
    int is_attack = 0;
    int is_deffend = 0;

    char* window[20];
    char* window_src;
    int command_check = 0;
    int command_type = -1;
    char* can_command = " ";
    char input_command[50] = " ";

    int random_num = 0;

    window_src = (char*)malloc(50 * sizeof(char));

    map_step1 = (map_steps*)malloc(sizeof(map_steps));
    map_step2 = (map_steps*)malloc(sizeof(map_steps));
    map_step3 = (map_steps*)malloc(sizeof(map_steps));
    map_step4 = (map_steps*)malloc(sizeof(map_steps));

    material_list(&material);
    item_list(&item);
    food_list(&food);
    mob_list(&mob);
    map_list(&map);

    incounts11 = (incount*)malloc(sizeof(incount));
    incounts11->link = NULL;
    incounts11->mob = mob[0];
    incounts11->material = material[2];
    incounts11->material.count = 2;

    incounts12 = (incount*)malloc(sizeof(incount));
    incounts12->mob = mob[0];
    incounts12->item = item[4];
    incounts12->item.count = 1;
    incounts12->link = NULL;

    incounts13 = (incount*)malloc(sizeof(incount));
    incounts13->item = item[0];
    incounts13->material = material[0];
    incounts13->item.count = 1;
    incounts13->material.count = 4;
    incounts13->link = NULL;

    incounts14 = (incount*)malloc(sizeof(incount));
    incounts14->mob = mob[1];
    incounts14->item = item[11];
    incounts14->item.count = 1;
    incounts14->link = NULL;
    
    incounts21 = (incount*)malloc(sizeof(incount));
    incounts21->mob = mob[2];
    incounts21->material = material[1];
    incounts21->material.count = 2;
    incounts21->item = item[6];
    incounts21->item.count = 1;
    incounts21->link = NULL;

    incounts22 = (incount*)malloc(sizeof(incount));
    incounts22->mob = mob[1];
    incounts22->item = item[2];
    incounts22->item.count = 1;
    incounts22->material = material[0];
    incounts22->material.count = 2;

    incounts23 = (incount*)malloc(sizeof(incount));
    incounts23->mob = mob[2];
    incounts23->material = material[2];
    incounts23->material.count = 4;
    incounts23->link = NULL;

    incounts24 = (incount*)malloc(sizeof(incount));
    incounts24->mob = mob[2];
    incounts24->item = item[13];
    incounts24->item.count = 1;
    incounts24->link = NULL;

    incounts31 = (incount*)malloc(sizeof(incount));
    incounts31->mob = mob[4];
    incounts31->item = item[1];
    incounts31->item.count = 1;
    incounts31->link = NULL;

    incounts32 = (incount*)malloc(sizeof(incount));
    incounts32->mob = mob[5];
    incounts32->item = item[10];
    incounts32->item.count = 1;
    incounts32->link = NULL;

    incounts33 = (incount*)malloc(sizeof(incount));
    incounts33->mob = mob[3];
    incounts33->material = material[2];
    incounts33->material.count = 4;
    incounts33->link = NULL;

    incounts34 = (incount*)malloc(sizeof(incount));
    incounts34->mob = mob[3];
    incounts34->item = item[15];
    incounts34->item.count = 1;
    incounts34->link = NULL;

    incounts41 = (incount*)malloc(sizeof(incount));
    incounts41->mob = mob[5];
    incounts41->material = material[1];
    incounts41->material.count = 5;
    incounts41->link = NULL;

    incounts42 = (incount*)malloc(sizeof(incount));
    incounts42->mob = mob[3];
    incounts42->item = item[13];
    incounts42->item.count = 1;
    incounts42->link = NULL;

    incounts43 = (incount*)malloc(sizeof(incount));
    incounts43->mob = mob[2];
    incounts43->material = material[2];
    incounts43->material.count = 8;
    incounts43->link = NULL;

    incounts44 = (incount*)malloc(sizeof(incount));
    incounts44->mob = mob[6];
    incounts44->item = item[12];
    incounts44->material = material[2];
    incounts44->item.count = 1;
    incounts44->material.count = 10;


    map_step1->random_incount = incounts11;
    map_step2->random_incount = incounts12;
    map_step3->random_incount = incounts13;
    map_step4->random_incount = incounts14;

    map_step1->link = map_step2;
    map_step2->link = map_step3;
    map_step3->link = map_step4;
    map_step4->link = map_step1;

    srand(time(NULL));
    random_num = rand() % 4;
    if (random_num == 0) {
        incounts11->link = incounts21;
        incounts12->link = incounts24;
        incounts13->link = incounts22;
        incounts14->link = incounts23;

        incounts21->link = incounts33;
        incounts22->link = incounts32;
        incounts23->link = incounts31;
        incounts24->link = incounts34;
        
        incounts31->link = incounts44;
        incounts32->link = incounts41;
        incounts33->link = incounts43;
        incounts34->link = incounts42;
    }
    else if (random_num == 1) {
        incounts11->link = incounts23;
        incounts12->link = incounts21;
        incounts13->link = incounts24;
        incounts14->link = incounts22;
        
        incounts21->link = incounts31;
        incounts22->link = incounts33;
        incounts23->link = incounts34;
        incounts24->link = incounts32;
        
        incounts31->link = incounts42;
        incounts32->link = incounts43;
        incounts33->link = incounts44;
        incounts34->link = incounts41;
    }
    else if (random_num == 2) {
        incounts11->link = incounts24;
        incounts12->link = incounts22;
        incounts13->link = incounts23;
        incounts14->link = incounts21;

        incounts21->link = incounts34;
        incounts22->link = incounts31;
        incounts23->link = incounts32;
        incounts24->link = incounts33;

        incounts31->link = incounts43;
        incounts32->link = incounts42;
        incounts33->link = incounts41;
        incounts34->link = incounts44;
    }
    else if (random_num == 3) {
        incounts11->link = incounts22;
        incounts12->link = incounts23;
        incounts13->link = incounts21;
        incounts14->link = incounts24;

        incounts21->link = incounts32;
        incounts22->link = incounts34;
        incounts23->link = incounts33;
        incounts24->link = incounts31;

        incounts31->link = incounts41;
        incounts32->link = incounts44;
        incounts33->link = incounts42;
        incounts34->link = incounts43;
    }

    map[0].dunjeon = map_step1;
    map[1].dunjeon = map_step2;
    map[2].dunjeon = map_step3;


    for (int i = 0; i < 20; i++) {
        window[i] = "|                                                  |"; //정보 화면 초기설정
    }
    inven = NULL;
    user_start_set(&user, &item, &map);
    
    is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0); //사용가능 명령어 초기설정

    

    //게임 시작
    while (1) {
        print_center("생존 게임");
        print_status(&user);
        print_equip_item(&user);
        print_user_status(&user);
        if (command_type == -2) {
            print_mob_status(&user->place.dunjeon->random_incount->mob);
        }
        for (int i = 0; i < 20; i++) {
            printf("%s\n", window[i]);
        }
        print_border();
        print_inven(&user);
        print_border();
        printf("| 현재 가능한 명령어>> ");
        cann_command(is_move, is_product, is_sheltermove, is_equip, is_using, is_log, is_mine, is_attack, is_deffend);

        printf("| 입력>> ");
        gets_s(input_command, 10);
        printf("\n");
        print_border();

        command(&input_command, &command_check, &is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, &command_type, window_src, &user, &map, item, material, food, &productor, &shel, &inven_item, &map_step1, &map_step2, &map_step3, &map_step4); //커맨드 작동


        if (command_check == 0) { //커맨드 입력 실패
            system("cls");
            continue;
        }
        else if (command_check == 9) { //정보창 최대사용
            for (int i = 0; i < 20; i++) {
                window[i] = "|                                                  |"; //정보 화면 초기화
            }
            command_check = 0;
            system("cls");
        }
        else { //다음 턴
            window[command_check] = window_src;
            system("cls");
        }
    }

    free_list(material, item, food, mob, 3, 23, 7, 7);
    free(user->inventory->items);
    free(incounts11);
    free(incounts12);
    free(incounts13);
    free(incounts14);
    free(incounts21);
    free(incounts22);
    free(incounts23);
    free(incounts24);
    free(incounts31);
    free(incounts32);
    free(incounts33);
    free(incounts34);
    free(map_step1);
    free(map_step2);
    free(map_step3);
    free(map_step4);
    return 0;
}