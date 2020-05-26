#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



/* Определяем элемент списка */
typedef struct list_node {
    struct list_node *next;
    int *data;
} list_node_t;

/* Определяем сам список */
typedef struct list {
    /*
     * Размер списка хранить не обязательно,
     * он нужен для упрощения работы
     */
    int size;
    /* начало списка */
    list_node_t *head;
    /* конец списка */
    list_node_t *tail;
} list_t;

/* Инициализация массива */
list_t *create_list(void) {
    list_t *lt = malloc(sizeof(list_t));

    lt->size = 0;
    lt->head = NULL;
    lt->tail = lt->head;

    return lt;
}

/* Добавляем элемент в начало списка */
void list_push(list_t *lt, void *data) {
    list_node_t *node = malloc(sizeof(list_node_t));
    node->data = data;
    node->next = lt->head;

    lt->head = node;
    lt->size += 1;
}

/* Извлекаем элемент из начала списка */
void *list_pop(list_t *lt) {
    if (lt->size == 0) {
        /* Список пуст */
        return NULL;
    }

    list_node_t *node = lt->head;
    void *ret_val = node->data;

    lt->size -= 1;
    lt->head = node->next;

    free(node);

    if (lt->size == 0) {
        /* Это был последний элемент */
        lt->head = NULL;
        lt->tail = NULL;
    }

    return ret_val;
}

bool ifIn(list_t *lt, const int *data) {
    list_node_t *node = lt->head;
    while (node != NULL) {
        if (node->data == data) {
            return true;
        }
        node = node->next;
    }
    return false;
}

void print_list(list_t *lt) {
    list_node_t *node = lt->head;
    while (node != NULL) {
        printf("%d", *node->data);

        node = node->next;
        if (node!=NULL){
            printf("%s", " -> ");
        }
    }
    printf("\n");
}

/* Добавляем элемент в конец списка */
void list_push_back(list_t *lt, void *data) {
    list_node_t *node = malloc(sizeof(list_node_t));
    node->data = data;
    if (lt->tail != NULL)
        lt->tail->next = node;
    else {
        lt->head = node;
    }

    lt->tail = node;
    lt->size += 1;
}


unsigned int WordCombination(const char *str) {
    const unsigned VALUE_BYTES = 4;
    unsigned length = strlen(str);
    unsigned int result = 0;

    bool first_part = true;
    union w {
        char w[4];
        unsigned long value;
    };
    union w word;

    for (unsigned i = 0; i < length; i += VALUE_BYTES) {
        memmove(word.w, str + i, VALUE_BYTES * sizeof(char));
        if (first_part) {
            word.value = word.value >> 1;
            first_part = false;
            result ^= word.value;
            word.value = 0;
            continue;
        }
        result ^= word.value;
        word.value = 0;
        first_part = true;
    }

    return result;
}

unsigned int hash(const char *str, const int tableSize) {
    int A = 7;
    int w = 11;
    int m = 1;
    unsigned int K = WordCombination(str);
    int res = ((A * K) >> (w - m)) % tableSize;
    return res;
}


int main() {


    list_t *queue = create_list();
    int data = 5;
    int data2 = 6;
    int data3 = 7;

    list_push_back(queue, &data);
    list_push_back(queue, &data2);

    print_list(queue);
}