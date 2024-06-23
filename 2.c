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

typedef struct materials { //���
    char* name; //�̸�
    int count; //����
    int value; //��ġ(�� ��Ḷ���� ����)
} materials;

typedef struct items { //���� ������(���)
    char* name; //�̸�
    int count; //����
    char* type; //���Ÿ��
    materials materials; //���
    int attack_value; //���ݷ�
    int defense_value; //����
    int used_number; //������
    int mining_value; //ä���ɷ�
    int logging_value; //����ɷ�
} items;

typedef struct foods {
    char* name;
    int hunger_value;
    int health_value;
    int water_value;
} foods;

typedef struct inventory_item {
    materials material; //���
    items item; //������
    foods food; //����
    int material_count; //��� ������ ����
    int item_count; //��� ������ ����
    int food_count; //���� ������ ����
    int is_material; //������� ����
    int is_food; //�������� ����
    int is_item; //������� ����
}inventory_item;

typedef struct inventorys {
    inventory_item* items; //�κ��丮 ������
    int inventory_count; //�κ��丮 ����ִ� ĭ
    int inven_max_count; //�κ��丮 �ִ� ĭ ��
} inventorys;

typedef struct mobs { //��
    char* name;
    int health; //ü��
    int attack; //���ݷ�
    materials material; //����Ʈ�� ������
    items item[4]; //���� ������
} mobs;

typedef struct productors { //���۵���(�۾���, ���ñ� ���)
    char* name;
    materials materials[3]; //���(�ʿ� ��� �� �Է�, ��� �� ����)
    int value; //��ġ
    int inputs; //�Էµ� ��� ����
    int outputs; //��µ� ��� ����
} productors;

typedef struct shelter { //����(����)
    char* map;
    productors productor[10]; //��ġ�� ���۵���
} shelter;

typedef struct maps { //����
    char* name;
    map_steps* dunjeon; //���� �� (��ũ�� ����Ʈ��)
    shelter shelter; //����
} maps;

typedef struct map_steps { //����
    incount* random_incount; //��Ȳ��
    map_steps* link; //���Ḯ��Ʈ
} map_steps;

typedef struct users { //����
    int health; //ü��
    int water; //�񸶸�
    int temperature;  //�µ�
    int fatigue_value; //�Ƿε�
    int inventory_num; //�κ��丮 ����
    int attack; //���� ���ݷ�
    int defense; //���� ����
    int mining_value; //���� ä���ɷ�
    int logging_value; //���� ����ɷ�
    int is_shelter;
    maps place;
    inventorys* inventory; //�κ��丮
    items equip_item[4]; //��� ������
} users;

typedef struct incount { //���� ��ī���� (�־��� ��Ȳ)
    int number; //��ȣ
    char* text; //�־��� ��Ȳ(����)
    items item; //�־��� ������
    materials material; //�־��� ���
    users user; //����
    mobs mob; //��
    incount* link;
} incount;

// �׵θ��� �ؽ�Ʈ ��� �Լ�
void print_border() {
    printf("+--------------------------------------------------+\n");
}

// ���ڿ� ���� �Լ�
char* str_copy(const char* source) {
    char* tmp = (char*)malloc(strlen(source) + 1);
    strcpy(tmp, source);
    return tmp;
}

void print_status(users* user) {
    print_border();
    printf("| ü��: %d | �񸶸�: %d |  �µ�: %d  | �Ƿε�: %d  |\n", user->health, user->water, user->temperature, user->fatigue_value);
    print_border();
}

void print_equip_item(users* user) {
    print_border();
    printf("| ����: %s | ����: %s | ����: %s | �Ź�: %s |\n", user->equip_item[0].name, user->equip_item[1].name, user->equip_item[2].name, user->equip_item[3].name);
    print_border();
}

void print_mob_status(mobs* mob) {
    print_border();
    printf("| �̸�: %s | ü��: %s | ���ݷ�: %d |\n", mob->name, mob->health, mob->attack);
    print_border();
}

void print_user_status(users* user) {
    print_border();
    printf("| ���ݷ�: %d | ����: %d | ä���ɷ�: %d | ����ɷ�: %d |\n", user->attack, user->defense, user->mining_value, user->logging_value);
    print_border();
}

void material_list(materials* material) {
    material[0].name = str_copy("����");
    material[1].name = str_copy("��");
    material[2].name = str_copy("ö");

    material[0].value = 1;
    material[1].value = 2;
    material[2].value = 3;
}

// ������ ����Ʈ �ʱ�ȭ
void item_list(items* item) { // ������ ������

    // ���� ������
    item[0].name = str_copy("���� Į");
    item[1].name = str_copy("���� ����");
    item[2].name = str_copy("���� ���");
    item[3].name = str_copy("���� ����");
    item[4].name = str_copy("���� ����");
    item[5].name = str_copy("���� �Ź�");

    item[0].type = str_copy("����");
    item[1].type = str_copy("����");
    item[2].type = str_copy("����");
    item[3].type = str_copy("����");
    item[4].type = str_copy("����");
    item[5].type = str_copy("�Ź�");

    item[0].attack_value = 7 * 1; // ���� Į
    item[1].attack_value = 5 * 1; // ���� ����
    item[2].attack_value = 3 * 1; // ���� ���
    item[3].defense_value = 4 * 1; // ���� ����
    item[4].defense_value = 6 * 1; // ���� ����
    item[5].defense_value = 3 * 1; // ���� �Ź�
    item[1].logging_value = 5 * 1; // ���� ����
    item[2].logging_value = 2 * 1; // ���� ���
    item[1].mining_value = 2 * 1; // ���� ����
    item[2].mining_value = 5 * 1; // ���� ���

    // �� ������
    item[6].name = str_copy("�� Į");
    item[7].name = str_copy("�� ����");
    item[8].name = str_copy("�� ���");
    item[9].name = str_copy("�� ����");
    item[10].name = str_copy("�� ����");
    item[11].name = str_copy("�� �Ź�");

    item[6].type = str_copy("����");
    item[7].type = str_copy("����");
    item[8].type = str_copy("����");
    item[9].type = str_copy("����");
    item[10].type = str_copy("����");
    item[11].type = str_copy("�Ź�");

    item[6].attack_value = 7 * 2; // �� Į
    item[7].attack_value = 5 * 2; // �� ����
    item[8].attack_value = 3 * 2; // �� ���
    item[9].defense_value = 4 * 2; // �� ����
    item[7].logging_value = 5 * 2; // �� ����
    item[8].logging_value = 2 * 2; // �� ���
    item[7].mining_value = 2 * 2; // �� ����
    item[8].mining_value = 5 * 2; // �� ���
    item[10].defense_value = 6 * 2; // �� ����
    item[11].defense_value = 3 * 2; // �� �Ź�

    // ö ������
    item[12].name = str_copy("ö Į");
    item[13].name = str_copy("ö ����");
    item[14].name = str_copy("ö ���");
    item[15].name = str_copy("ö ����");
    item[16].name = str_copy("ö ����");
    item[17].name = str_copy("ö �Ź�");

    item[12].type = str_copy("����");
    item[13].type = str_copy("����");
    item[14].type = str_copy("����");
    item[15].type = str_copy("����");
    item[16].type = str_copy("����");
    item[17].type = str_copy("�Ź�");

    item[12].attack_value = 7 * 3; // ö Į
    item[13].attack_value = 5 * 3; // ö ����
    item[14].attack_value = 3 * 3; // ö ���
    item[15].defense_value = 4 * 3; // ö ����
    item[13].logging_value = 5 * 3; // ö ����
    item[14].logging_value = 2 * 3; // ö ���
    item[13].mining_value = 2 * 3; // ö ����
    item[14].mining_value = 5 * 3; // ö ���
    item[16].defense_value = 6 * 3; // ö ����
    item[17].defense_value = 3 * 3; // ö �Ź�

    //��Ÿ ����
    item[18].name = str_copy("ȶ��");
    item[19].name = str_copy("��ں�");
    item[20].name = str_copy("��ħ��");
    item[21].name = str_copy("����");

    item[18].type = str_copy("��Ÿ����");
    item[19].type = str_copy("��Ÿ����");
    item[20].type = str_copy("��Ÿ����");
    item[21].type = str_copy("��Ÿ����");

    //��Ÿ ����
    item[22].name = str_copy("Ȱ");

    item[22].type = str_copy("����");

    item[22].attack_value = 15;
}

void food_list(foods* food) {
    //���� �̸�
    food[0].name = str_copy("�ܹ���");
    food[1].name = str_copy("������ġ");
    food[2].name = str_copy("�����");
    food[3].name = str_copy("��");
    food[4].name = str_copy("�����");
    food[5].name = str_copy("������");
    food[6].name = str_copy("���");

    //���� �����
    food[0].hunger_value = 80;
    food[1].hunger_value = 50;
    food[4].hunger_value = 10;
    food[5].hunger_value = 80;
    food[6].hunger_value = 20;

    //���� �񸶸�
    food[2].water_value = 70;
    food[3].water_value = 100;

    //���� ü��
    food[0].health_value = 30;
    food[1].health_value = 30;
    food[4].health_value = -20;
    food[5].health_value = 50;
    food[6].health_value = 10;
}

void mob_list(mobs* mob) {
    mob[0].name = str_copy("��������");
    mob[1].name = str_copy("����");
    mob[2].name = str_copy("��ȭ����");
    mob[3].name = str_copy("��");
    mob[4].name = str_copy("�䳢");
    mob[5].name = str_copy("����");
    mob[6].name = str_copy("�����Ѱ���");

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
    map[0].name = "����";
    map[1].name = "��";
    map[2].name = "�󱤻�";
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

    // ��� ������ �ʱ�ȭ
    user->equip_item[0].name = str_copy("�ָ�");
    user->equip_item[0].attack_value = 1;
    user->equip_item[0].logging_value = 1;
    user->equip_item[0].mining_value = 1;
    user->equip_item[0].type = str_copy("����");
    for (int i = 1; i < 4; i++) {
        user->equip_item[i].name = str_copy("����");
        user->equip_item[i].attack_value = 0;
        user->equip_item[i].defense_value = 0;
        user->equip_item[i].mining_value = 0;
        user->equip_item[i].logging_value = 0;
    }
}

// ��� ���� �Լ�
void equip_item(users* user, items item, char* window) { //��� ����
    int slot = -1;
    if (strcmp(item.type, "����") == 0 || strcmp(item.type, "��Ÿ����") == 0 || strcmp(item.type, "����") == 0) {
        slot = 0;
        user->attack = 1;
        user->logging_value = 1;
        user->mining_value = 1;
    }
    else if (strcmp(item.type, "����") == 0) {
        slot = 1;
        user->defense -= user->equip_item[1].defense_value;
    }
    else if (strcmp(item.type, "����") == 0) {
        slot = 2;
        user->defense -= user->equip_item[2].defense_value;
    }
    else if (strcmp(item.type, "�Ź�") == 0) {
        slot = 3;
        user->defense -= user->equip_item[3].defense_value;
    }
    if (slot != -1) {
        user->equip_item[slot] = item;
        user->attack += item.attack_value;
        user->defense += item.defense_value;
        user->mining_value += item.mining_value;
        user->logging_value += item.logging_value;
        window = "�����Ǿ����ϴ�.";
    }
    else {
        window = "��� ������ �����߽��ϴ�.";
    }
}

void add_inven(inventorys* inv, inventory_item item) {
    for (int i = 0; i < inv->inven_max_count; i++) { //�κ��丮 �ִ� ĭ �ȿ��� �ߺ� �˻�
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

    inv->items = realloc(inv->items, (inv->inventory_count + 1) * sizeof(inventory_item)); //���� ���Ҵ�(�κ��丮 ������ ĭ ����)
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
    window = "�ش� �������� ã�� �� ���ų� ������ �����մϴ�.";
}

void print_inven(users* user) {
    printf("| �κ��丮:\n");
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

    *is_move = move; //�̵�
    *is_product = product; //����
    *is_sheltermove = sheltermove; //�����̵�
    *is_equip = equip; //��� ����
    *is_using = using; //�����ۻ��
    *is_log = log; //����
    *is_mine = mine; //ä��
    *is_attack = attack; //����
    *is_deffend = deffend; //���
} //��밡�� Ŀ�ǵ� �з�

void print_center(const char* message) {
    int width = 50; // ȭ�� �ʺ�
    int padding = (width - strlen(message)) / 2; // �޽����� �߾ӿ� ��ġ�ϱ� ���� �¿� ���� ���
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
    if (is_move) printf("�̵� ");
    if (is_product) printf("���� ");
    if (is_sheltermove) printf("�����̵� ");
    if (is_equip) printf("������� ");
    if (is_using) printf("�����ۻ�� ");
    if (is_log) printf("���� ");
    if (is_mine) printf("ä�� ");
    if (is_attack) printf("���� ");
    if (is_deffend) printf("��� ");
    printf("\n");
} //��밡�� Ŀ�ǵ� ���ڿ� �߰�

//Ŀ�ǵ� �۵�
void command(char* input, int *command_check, int* is_move, int* is_product, int* is_sheltermove, int* is_equip, int* is_using, int* is_log, int* is_mine, int* is_attack, int* is_deffend, int *command_type, char* window, users* user, maps* map, items* item, materials* material, foods* food, productors* productor, shelter* shel, inventory_item* inventory_items, map_steps* map_step1, map_steps* map_step2, map_steps* map_step3, map_steps* map_step4) {
    (*command_check)++;
    if (strcmp(input, "�̵�") == 0) { //�̵� �Է�
        if (*is_move != 1) { //�̵��� �Ұ����� ��, �̵��� �Է½�
            strcpy(window, "| >>�Ұ����� ����Դϴ�.");
            (*command_check)--;
            return;
        }
        else { //���� �̵� ������ ���� �ȳ�
            strcpy(window, "| >>���� �̵� ������ ����: ����, ��, �󱤻�");
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            *command_type = 0;
            return;
        }
    } //���� ���ý�
    else if (strcmp(input, "����") == 0 && *command_type == 0) {
        if (user->is_shelter == 1) { 
            if (strcmp(shel->map, "����") != 0) { //���� ��ġ�� ���ð� �ƴϸ� �Ƿε� ����
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[0]; //���� ����
        *command_type = 1;
        strcpy(window, "| >>�̿� ������ ���: ����, �Ĺ�");
        return;
    } //�� ���ý�
    else if (strcmp(input, "��") == 0 && *command_type == 0) {

        if (user->is_shelter == 1) { //���� ��ġ�� ���� �ƴϸ� �Ƿε� ����
            if (strcmp(shel->map, "��") != 0) {
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[1]; //�� ����
        *command_type = 1;
        strcpy(window , "| >>�̿� ������ ���: ����, �Ĺ�");
        return;
    }
    else if (strcmp(input, "�󱤻�") == 0 && *command_type == 0) {

        if (user->is_shelter == 1) {
            if (strcmp(shel->map, "�󱤻�") != 0) { //���� ��ġ�� ������ �ƴϸ� �Ƿε� ����
                if (user->fatigue_value >= 85) {
                    strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                    return;
                }
                else {
                    user->fatigue_value += 15;
                }
            }
        } 
        else {
            if (user->fatigue_value >= 85) {
                strcpy(window, "| >>�̵��ϴ� �Ƿε��� �׿� �׾����ϴ�.");
                return;
            }
            else {
                user->fatigue_value += 15;
            }
        }
        user->place = map[2]; //�󱤻� ����
        *command_type = 1;
        strcpy(window, "| >>�̿� ������ ���: ����, �Ĺ�");
        return;
    }
    else if (strcmp(input, "���") == 0 && *command_type == 0) { //�̵� ��� ��
        if (user->is_shelter == 0) { //���� ���°�� ������ ��ɾ�
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
        }
        else if (user->is_shelter == 1) { //���� �ִ� ��� ������ ��ɾ�
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
        }
        *command_type = -1;
        strcpy(window, "| >>��ҵǾ����ϴ�.");
        return;
    }
    else if (strcmp(user->place.name, "����") == 0 && strcmp(input, "�Ĺ�") == 0 && *command_type == 1) { //���ÿ��� �Ĺ����� ����
        strcpy(window, "| >>���� ��ġ�� ���� ���� �Ĺ��� �Դϴ�.(����, �� �Ĺ� ����)");

        *command_type = -1;
    }
    else if (strcmp(user->place.name, "����") == 0 && strcmp(input, "����") == 0 && *command_type == 1) { //���ÿ��� ���� ����
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
        strcpy(window, "| >>���� ���� ����");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
        return;
    }
    else if (strcmp(user->place.name, "��") == 0 && strcmp(input, "�Ĺ�") == 0 && *command_type == 1) { //������ �Ĺ����� ����
        strcpy(window, "| >>���� ��ġ�� ���� �� �Ĺ��� �Դϴ�.(���� �Ĺ� ����)");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 1, 0, 0, 0);
        *command_type = -1;
    }
    else if (strcmp(user->place.name, "��") == 0 && strcmp(input, "����") == 0 && *command_type == 1) { //������ �������� ����
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
        strcpy(window, "| >>�� ���� ����");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
    }
    else if (strcmp(user->place.name, "�󱤻�") == 0 && strcmp(input, "�Ĺ�") == 0 && *command_type == 1) { //�󱤻꿡�� �Ĺ����� ����
        strcpy(window, "| >>���� ��ġ�� ���� ���� �Ĺ��� �Դϴ�.(��, ö, ��ź �Ĺ� ����)");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 1, 0, 0);
        *command_type = -1;
    }
    else if (strcmp(user->place.name, "�󱤻�") == 0 && strcmp(input, "����") == 0 && *command_type == 1) { //�󱤻꿡�� ���� ����
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
        strcpy(window, "| >>�󱤻� ���� ����");
        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 1, 1);
        *command_type = -2;
        return;
    }
    else { //���� �ܾ� �Է�
        strcpy(window, "| >>�߸��ԷµǾ����ϴ�.");
        (*command_check)--;
        return;
    }
    if (strcmp(input, "����") == 0) { //���� �Է�
        if (*is_product != 1) {
            strcpy(window, "| >>�Ұ����� ����Դϴ�.");
            return;
        }
        else {
            strcpy(window, "| >>���� ���� ������ ��ǰ: ");
            is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 0, 0, 0, 0, 0, 0);
            *command_type = 0;
            return;
        }

    }
    else if (strcmp(input, "�����̵�") == 0 || command_type == 2) { //�����̵� ����
        if (*is_sheltermove == 1) {
            if (user->is_shelter == 1) {
                for (int i = 0; i < 3; i++) { //���� ���� ���� �˻�
                    if (strcmp(shel->map, map[i].name) == 0) {
                        user->place = map[i]; //�����̵�
                    }
                }
                strcpy(window,  "| >>���ͷ� �̵��߽��ϴ�.");
                is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 1, 0, 1, 1, 0, 0, 0, 0); //���� �̵� �� ��� ������ ��ɾ�
            }
            else { //���Ͱ� ���� ��
                strcpy(window, "| >>������ ���Ͱ� �����ϴ�.");
                return;
        }
            }
        else { //���� �̵� �ȵ� �� �Է�
            strcpy(window, "| >>�Ұ����� ����Դϴ�.");
        }
    }
    else if (strcmp(input, "�������") == 0 || command_type == 3) { //������� ����
        if (*is_equip == 1) {
            if (command_type == 3) {
                remove_inven(&user->inventory, input, 1, window); //�κ��丮���� ������ ����
                for (int i = 0; i < 23; i++) {
                    if (input == item[i].name) {
                        if (strcmp(item[i].type, "����") == 0 || strcmp(item[i].type, "��Ÿ����") == 0 || strcmp(item[i].type, "����") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[0];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "����") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[1];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "����") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[2];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        else if (strcmp(item[i].type, "�Ź�") == 0) {
                            inventory_item items_;
                            items_.is_item = 1;
                            items_.item = user->equip_item[3];
                            items_.item_count = 1;
                            add_inven(&user->inventory, items_);
                        }
                        equip_item(user, item[i], window);
                    }
                }
                if (user->is_shelter == 0) { //������� �� Ŀ�ǵ� ��밡���� ����� ���� �پ���. ����.
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
            window = "�κ��丮 ��� �� �ϳ��� �����ּ���.";
            return;
        }
        else {
            window = "�Ұ����� ����Դϴ�.";
        }
    }
    else if (strcmp(input, "�����ۻ��") == 0 || command_type == 4) { //������ ���
        if (*is_using == 1) {

        }
        else {
            window = "�Ұ����� ����Դϴ�.";
        }
    }
    else if (strcmp(input, "����") == 0 || command_type == 5) { //����
        if (*is_log == 1) {
            window = "���� �Ϸ�(���� 2��)";
            inventory_item items_;
            items_.is_material = 1;
            items_.material = material[0];
            items_.material_count = 2;
            add_inven(&user->inventory, items_);
            user->fatigue_value += (30 / user->logging_value);
            if (user->fatigue_value > 100) {
                window = "�����ϴ� �Ƿε��� �׿� �׾����ϴ�.";
            }
            *command_type = -1;
            return;
        }
        else {
            window = "�Ұ����� ����Դϴ�.";
            return;
        }
    }
    else if (strcmp(input, "ä��") == 0 || command_type == 6) { //ä��
        if (*is_mine == 1) { //.
            window = "ä�� �Ϸ�";
            inventory_item items_;
            items_.is_material = 1;
            int random_num = 0;
            random_num = rand() % 10;
            if (random_num <= 1) {

            }
        }
        else {
            window = "�Ұ����� ����Դϴ�.";
        }
    }
    else if (strcmp(input, "����") == 0 || command_type == 7) {
        if (*is_attack == 1) { // ����
            user->place.dunjeon->random_incount->mob.health -= user->attack;
            user->health -= user->place.dunjeon->random_incount->mob.attack;
            //���� ����� ���� (���Ḯ��Ʈ)
            if (user->place.dunjeon->random_incount->mob.health < 0) { //�¸�
                user->place.dunjeon->random_incount = user->place.dunjeon->random_incount->link;
                //����
                inventory_item items_;
                items_.item = user->place.dunjeon->random_incount->item;
                items_.material = user->place.dunjeon->random_incount->material;

                //���� ����
                if (user->place.dunjeon->random_incount->link == NULL) {
                    window = "���� �Ϸ�";
                    if (user->is_shelter == 0) { //���� �ִ� ���
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
                    }
                    else if (user->is_shelter == 1) { //���� ���� ���
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
                    }
                    return;
                }
            }
            else if (user->health < 0) { //�й�
                window = "���Ϳ� ���� óġ���Ͽ����ϴ�.";
            }
        }
        else {
            window = "�Ұ����� ����Դϴ�.";
        }
    }
    else if (strcmp(input, "���") == 0 || command_type == 8) {
        if (*is_deffend == 1) { //���
            user->place.dunjeon->random_incount->mob.health -= (user->attack / 2); //���ݷ��� ���ݸ�ŭ ������ ����
            user->health -= (user->place.dunjeon->random_incount->mob.attack - user->defense); //���¸�ŭ ������ �氨
            if (user->place.dunjeon->random_incount->mob.health < 0) { //�¸�
                user->place.dunjeon->random_incount = user->place.dunjeon->random_incount->link; //�������� ���� (���Ḯ��Ʈ)
                //����
                inventory_item items_;
                items_.item = user->place.dunjeon->random_incount->item;
                items_.material = user->place.dunjeon->random_incount->material;

                if (user->place.dunjeon->random_incount->link == NULL) { //�������� (���Ḯ��Ʈ ������)
                    window = "���� �Ϸ�";
                    if (user->is_shelter == 0) { //���� �ִ� ���
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0);
                    }
                    else if (user->is_shelter == 1) { //���� ���� ���
                        is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 1, 1, 1, 0, 0, 0, 0);
                    }
                    return;
                }
            }
            else if (user->health < 0) { //�й�
                window = "���Ϳ� ���� óġ���Ͽ����ϴ�.";
                return;
            }
        }
        else { //��� �Ұ����� �� ��� �Է� ��,
            window = "�Ұ����� ����Դϴ�.";
            (*command_check)--;
            return;
        }
    }
    else { //��ɾ ���� �ܾ� �Է½�
        window = "| >>�߸��� �Է��Դϴ�.";
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
        window[i] = "|                                                  |"; //���� ȭ�� �ʱ⼳��
    }
    inven = NULL;
    user_start_set(&user, &item, &map);
    
    is_command(&is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, 1, 0, 0, 1, 1, 0, 0, 0, 0); //��밡�� ��ɾ� �ʱ⼳��

    

    //���� ����
    while (1) {
        print_center("���� ����");
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
        printf("| ���� ������ ��ɾ�>> ");
        cann_command(is_move, is_product, is_sheltermove, is_equip, is_using, is_log, is_mine, is_attack, is_deffend);

        printf("| �Է�>> ");
        gets_s(input_command, 10);
        printf("\n");
        print_border();

        command(&input_command, &command_check, &is_move, &is_product, &is_sheltermove, &is_equip, &is_using, &is_log, &is_mine, &is_attack, &is_deffend, &command_type, window_src, &user, &map, item, material, food, &productor, &shel, &inven_item, &map_step1, &map_step2, &map_step3, &map_step4); //Ŀ�ǵ� �۵�


        if (command_check == 0) { //Ŀ�ǵ� �Է� ����
            system("cls");
            continue;
        }
        else if (command_check == 9) { //����â �ִ���
            for (int i = 0; i < 20; i++) {
                window[i] = "|                                                  |"; //���� ȭ�� �ʱ�ȭ
            }
            command_check = 0;
            system("cls");
        }
        else { //���� ��
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