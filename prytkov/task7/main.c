#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

typedef struct queue_node
{
    /* Structure to represent queue node
     * used to store table data */
    char symbol;
    int frequency;
    char *code;
    struct queue_node *next;
}q_node;

typedef struct queue
{
    /* Structure to represent queue
     * Queue was chosen because it supports
     * insertion and deletion in O(1) in worst cases
     * It's really useful when we'll assign codes to symbols in table
     * because we may not to search in all queue,
     * just adding new first element and deleting last (FIFO principle) */
    int queue_size;
    struct queue_node *head, *back;
}queue;

typedef struct heap_node
{
    /* Structure to represent binary heap node */
    char symbol;
    int frequency;
    struct heap_node *left;
    struct heap_node *right;
}node;

typedef struct binary_heap
{
    /* Structure to represent binary heap, actually a binary tree implemented as an array
     * current size - pole that stores current size of heap
     * to reduce realloc using in program
     * data stored as pointers array because it's faster and easier
     * to swap elements by pointers swapping */
    int current_size;
    int max_heap_size;
    node **data;
}heap;

heap *create_heap(int);
heap *heap_init(heap*, queue*);
heap *add_to_heap(heap*, q_node*);
node *new_heap_node(q_node*);
heap *heapify(heap*, int);
node *extract_minimum(heap*);
int insert_node(heap*, node*);
int swap_items(node**, node**);
node *create_huffman_tree(heap*);
int tree_height(int);
queue *create_table();
int print_table(queue*);
int create_codes(node*, queue*, char*, int);
queue *assign_codes(node*, queue*);
bool current_size_is_one(heap*);
bool is_leaf(node*);
q_node *new_queue_node(char, int, char*);
queue *create_queue();
queue *enqueue(queue*, char, int, char*);
queue *dequeue(queue*);
char *encode_message(queue*, char*);
char *get_string();
int delete_queue(queue*);
void delete_tree(node*);
void hint();

int main()
{
    int result;
    heap *heap;
    queue *table;
    node *root;
    char *message, *encoded_message;
    result = SetConsoleOutputCP(CP_UTF8);
    if (result == 0)
        return 1;
    hint();
    table = create_table();
    if (table == NULL)
        return 2;
    heap = create_heap(table->queue_size);
    if (heap == NULL)
        return 3;
    heap = heap_init(heap, table);
    if (heap == NULL)
        return 4;
    root = create_huffman_tree(heap);
    if (root == NULL)
        return 5;
    table = assign_codes(root, table);
    if (table == NULL)
        return 6;
    result = print_table(table);
    if (result != 0)
        return 7;
    printf("Введите сообщение, которое хотите закодировать: ");
    message = get_string();
    if (message == NULL)
        return 8;
    encoded_message = encode_message(table, message);
    if (encoded_message == NULL)
        return 9;
    printf("Закодированное сообщение: %s\n", encoded_message);
    delete_tree(root);
    result = delete_queue(table);
    if (result != 0)
        return 10;
    free(message);
    free(encoded_message);
    return 0;
}

char *encode_message(queue *table, char *input_msg)
{
    /* Realisation of algorithm which encodes input message
     * Argument table - queue, table that stores codes, frequencies and codes for each symbol
     * Argument input_msg - message, that shall be encoded
     * Upon successful completion function shall return pointer to encoded string
     * Otherwise, NULL shall ne returned */

    if (table == NULL || input_msg == NULL)
        return NULL;
    int message_length, max_code_length, encoded_message_length, current_position = 0;
    int i, j, k;
    char temp, *encoded_msg;
    q_node *current = table->head;
    message_length = strlen(input_msg);
    max_code_length = tree_height(table->queue_size);
    encoded_message_length = message_length * max_code_length + 1;
    encoded_msg = (char*)malloc(sizeof(char) * encoded_message_length);
    if (encoded_msg == NULL)
        return NULL;
    for (i = 0; i < message_length; i++)
    {
        for (j = 0; j < table->queue_size; j++)
        {
            if (current->symbol == input_msg[i])
            {
                k = 0;
                temp = current->code[k];
                while (temp != '\0')
                {
                    encoded_msg[current_position] = current->code[k];
                    current_position++;
                    k++;
                    temp = current->code[k];
                }
                current = table->head;
                break;
            }
            current = current->next;
        }
    }
    encoded_msg[encoded_message_length] = '\0';
    return encoded_msg;
}

queue *assign_codes(node *root, queue *table)
{
    /* Realisation of algorithm which assigns codes to table
     * Argument root - root of built Huffman tree
     * Argument table - queue, table for which poles codes will be assigned
     * Upon a successful completion function shall return pointer to modified table with codes for each symbol
     * If an error occurred in processing, NULL shall be returned */

    int result, max_code_length, id = 0;
    char *temp_code;
    if (root == NULL || table == NULL)
        return NULL;
    max_code_length = tree_height(table->queue_size);
    temp_code = (char*)malloc(sizeof(char) * (max_code_length + 1));
    if (temp_code == NULL)
        return NULL;
    result = create_codes(root, table, temp_code, id);
    if (result != 0)
        return NULL;
    free(temp_code);
    return table;
}

int create_codes(node *root, queue *data, char *code, int id)
{
    /* Realisation of recursive algorithm which walks through the Huffman tree
     * Argument root - root of Huffman tree
     * Argument data - queue, table with data
     * Argument code - temporary string to store codes while walking through the tree
     * Argument id - current id(index) in temporary code string
     * Upon a successful completion function shall return 0
     * If error occurred while walking left - 1 shall be returned
     * If error occurred while walking right - 2 shall be returned
     * If error occurred in dequeue operation - 3 shall be returned
     * If error occurred in allocating memory to code pole in table  - 4 shall be returned
     * If error occurred in enqueue operation - 5 shall be returned */

    int result;
    char *new_code;
    if (root->left != NULL)
    {
        code[id] = '0';
        result = create_codes(root->left, data, code, id + 1);
        if (result != 0)
            return 1;
    }
    if (root->right != NULL)
    {
        code[id] = '1';
        result = create_codes(root->right, data, code, id + 1);
        if (result != 0)
            return 2;
    }
    if (is_leaf(root))
    {
        data = dequeue(data);
        if (data == NULL)
            return 3;
        code[id] = '\0';
        new_code = (char*)malloc(sizeof(char) * (tree_height(data->queue_size) + 1));
        if (new_code == NULL)
            return 4;
        new_code = strcpy(new_code, code);
        data = enqueue(data, root->symbol, root->frequency, new_code);
        if (data == NULL)
            return 5;
    }
    return 0;
}

node *create_huffman_tree(heap *heap)
{
    /* Realisation of algorithm which builds Huffman tree
     * Argument heap - heap, table which stores symbols and frequencies
     * Upon successful completion function shall return pointer to root of built Huffman tree (actually last node in heap)
     * Otherwise, NULL shall be returned */

    int result;
    node *parent, *left_child, *right_child;
    q_node temp;
    temp.symbol = '#';
    if (heap == NULL)
        return NULL;
    while (!current_size_is_one(heap))
    {
        left_child = extract_minimum(heap);
        if (left_child == NULL)
            return NULL;
        right_child = extract_minimum(heap);
        if (right_child == NULL)
            return NULL;
        temp.frequency = left_child->frequency + right_child->frequency;
        parent = new_heap_node(&temp);
        if (parent == NULL)
            return NULL;
        parent->left = left_child;
        parent->right = right_child;
        result = insert_node(heap, parent);
        if (result != 0)
            return NULL;
    }
    return extract_minimum(heap);
}

node *extract_minimum(heap *heap)
{
    /* Realisation of algorithm which extracts minimum element(actually first as we built min-heap) of queue and deletes it
     * Argument heap - heap
     * Upon successful completion function shall return extracted element
     * If first arg is a NULL pointer or error occurred in heapify function, NULL shall be returned */

    if (heap == NULL)
        return NULL;
    node *result = heap->data[0];
    heap->data[0] = heap->data[heap->current_size - 1];
    heap->current_size--;
    heap = heapify(heap, 0); //After extracting we must restore heap properties
    if (heap == NULL)
        return NULL;
    return result;
}

int insert_node(heap *heap, node *inserting_node)
{
    /* Realisation of algorithm which inserts element into heap
     * Argument heap - heap
     * Argument inserting_node - heap node to insert
     * Upon successful completion function shall return 0
     * If argument heap is a NULL pointer - 1 shall be returned
     * If argument inserting_node is a NULL pointer - 2 shall be returned */

    int id;
    if (heap == NULL)
        return 1;
    if (inserting_node == NULL)
        return 2;
    id = heap->current_size;
    ++(heap->current_size);
    while (id != 0 && inserting_node->frequency < heap->data[(id - 1) / 2]->frequency)
    {
        heap->data[id] = heap->data[(id - 1) / 2];
        id = (id - 1) / 2;
    }
    heap->data[id] = inserting_node;
    return 0;
}

bool current_size_is_one(heap *heap)
{
    /* Realisation of function which defines is current size of heap is 1
     * Argument heap - heap
     * Upon a successful completion function shall return true or false, depending on current heap size */

    return heap->current_size == 1 ? true : false;
}

bool is_leaf(node *current)
{
    /* Realisation of function which defines is tree node a leaf (node without children)
    * Argument current - current node for check
    * Upon a successful completion function shall return true or false, depending on availability of left and right child
    * of current tree node */

    return current->left == NULL && current->right == NULL ? true : false;
}

heap *heap_init(heap *heap, queue *data)
{
    /* Realisation of heap-initialisation algorithm
     * Argument heap - heap for initialization
     * Argument data - queue with data, table in our case
     * Upon a successful completion function shall return pointer to initialised heap
     * Otherwise, NULL shall be returned */

    if (heap == NULL || data == NULL)
        return NULL;
    int n;
    q_node *current = data->head;
    for (int i = 0; i < heap->max_heap_size; i++)
    {
        heap = add_to_heap(heap, current);
        if (heap == NULL)
            return NULL;
        current = current->next;
    }
    n = heap->current_size / 2 - 1;
    for (int i = n; i >= 0; --i)
    {
        heap = heapify(heap, i);
        if (heap == NULL)
            return NULL;
    }
    return heap;
}

heap *heapify(heap *heap, int id)
{
    /* Realisation of algorithm which restores min-heap properties (in our case)
     * Argument heap - heap to heapify
     * Argument id - index of element for whose subtree min-heap properties shall be restored
     * Upon a successful completion, function returns pointer to heap with restored properties
     * Otherwise, NULL shall be returned */

    if (heap == NULL)
        return NULL;
    int minimum = id, result;
    int left = 2 * id + 1;
    int right = 2 * id + 2;
    if (left < heap->current_size && heap->data[left]->frequency < heap->data[minimum]->frequency)
        minimum = left;
    if (right < heap->current_size && heap->data[right]->frequency < heap->data[minimum]->frequency)
        minimum = right;
    if (minimum != id)
    {
        result = swap_items(&heap->data[minimum], &heap->data[id]);
        if (result != 0)
            return NULL;
        heap = heapify(heap, minimum);
        if (heap == NULL)
            return NULL;
    }
    return heap;
}

int swap_items(node **first, node **second)
{
    /* Realisation of two heap-nodes swapping algorithm
     * Argument first - pointer to pointer to first node (swapping pointers is faster then copying all information)
     * Argument second - pointer to pointer to second node
     * Upon successful completion function returns 0
     * If first argument points to NULL, 1 shall be returned
     * If second argument points to NULL, 2 shall be returned */

    if (*first == NULL)
        return 1;
    if (*second == NULL)
        return 2;
    node *temp = *first;
    *first = *second;
    *second = temp;
    return 0;
}

heap *add_to_heap(heap *heap, q_node *data)
{
    /* Realisation of algorithm which adds new node to heap
     * Argument heap - heap
     * Argument data - data which shall be added
     * Upon a successful completion function shall return pointer to modified heap
     * If an error occurred while creating new node or one of the args points to NULL , NULL shall be returned */

    if (heap == NULL || data == NULL)
        return NULL;
    heap->data[heap->current_size] = new_heap_node(data);
    if (heap->data[heap->current_size] == NULL)
        return NULL;
    ++(heap->current_size);
    return heap;
}

node *new_heap_node(q_node *data)
{
    /* Realisation of algorithm which creates new node with data, passed as an argument
     * Argument data - data which shall be added into new node
     * Upon a successful completion function shall return new initialised with data from arg data
     * If allocating error occurred or data-argument is NULL, NULL shall be returned */

    if (data == NULL)
        return NULL;
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL)
        return NULL;
    new_node->frequency = data->frequency;
    new_node->symbol = data->symbol;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

heap *create_heap(int heap_size)
{
    /* Realisation of algorithm, which creates heap
     * Argument heap_size - size of creating heap
     * Upon a successful completion, function shall return pointer to new created heap
     * Otherwise, NULL shall be returned */

    heap *new_heap = (heap*)malloc(sizeof(heap));
    if (new_heap == NULL)
        return NULL;
    new_heap->data = (node**)malloc(sizeof(node*) * heap_size);
    if (new_heap->data == NULL)
        return NULL;
    new_heap->current_size = 0;
    new_heap->max_heap_size = heap_size;
    return new_heap;
}

int tree_height(int start_elements_count)
{
    /* Realisation of function, which returns binary tree height
     * Argument start_elements_count - count of leaves, in our case - count of table nodes */

    return (int)log2(start_elements_count) + 1;
}

queue *enqueue(queue *data, char symbol, int frequency, char *code)
{
    /* Realisation of enqueue algorithm, adds new queue node to back of queue
     * Argument data - pointer to queue
     * Argument symbol - symbol which shall be inserted into new queue node
     * Argument frequency - frequency which shall be inserted into new queue node
     * Argument code - code which shall be inserted into new queue node, must be NULL, if code doesn't exists
     * Upon a successful completion function shall return pointer to queue
     * If first argument is NULL or allocation error occurred, NULL shall be returned */

    if (data == NULL)
        return NULL;
    q_node *temp = new_queue_node(symbol, frequency, code);
    if (temp == NULL)
        return NULL;
    if (data->back == NULL)
    {
        data->head = data->back = temp;
        data->queue_size++;
        return data;
    }
    data->back->next = temp;
    data->back = temp;
    data->queue_size++;
    return data;
}

queue *dequeue(queue *data)
{
    /* Realisation of algorithm which do dequeue operation (removes first node)
     * Argument data - queue, table in our case
     * Upon successful completion function shall return pointer to modified queue
     * If first argument is a NULL pointer, NULL shall be returned */

    if (data == NULL)
        return NULL;
    q_node *temp;
    if (data->head == NULL)
        return data;
    temp = data->head;
    data->head = data->head->next;
    if (data->head == NULL)
        data->back = NULL;
    free(temp);
    data->queue_size--;
    return data;
}

queue *create_queue()
{
    /* Realisation of algorithm, which creates queue
     * No arguments
     * Upon successful completion function shall return pointer to created queue
     * If allocation error occurred, NULL shall be returned */

    queue *new_queue = (queue*)malloc(sizeof(queue));
    if (new_queue == NULL)
        return NULL;
    new_queue->head = new_queue->back = NULL;
    new_queue->queue_size = 0;
    return new_queue;
}

q_node *new_queue_node(char symbol, int frequency, char *code)
{
    /* Realisation of algorithm, which creates new queue node
     * Argument symbol - symbol, which shall be inserted into new node
     * Argument frequency - frequency, which shall be inserted into new node
     * Argument code - code, which shall be inserted into new node, if no code to insert, argument shall be NULL
     * Upon successful completion, function shall return pointer to new created queue node
     * If allocation error occurred, NULL shall be returned */

    q_node *new_node = (q_node*)malloc(sizeof(q_node));
    if (new_node == NULL)
        return NULL;
    new_node->symbol = symbol;
    new_node->frequency = frequency;
    new_node->code = code;
    new_node->next = NULL;
    return new_node;
}

queue *create_table()
{
    /* Realisation of algorithm, which provides table-data input and creates new table
     * No arguments
     * Upon successful completion function shall return pointer to table, stored as queue
     * Otherwise, NULL shall be returned */

    queue *new_table;
    char temp;
    int frequency;
    fflush(stdin);
    new_table = create_queue();
    if (new_table == NULL)
        return NULL;
    while (1)
    {
        printf("Введите символ: ");
        scanf("%c", &temp);
        if (temp == '\n')
        {
            system("cls");
            return new_table;
        }
        else
        {
            printf("Введите частоту: ");
            scanf("%d", &frequency);
            fflush(stdin);
            new_table = enqueue(new_table, temp, frequency, NULL);
            if (new_table == NULL)
                return NULL;
        }
        system("cls");
    }
}

int print_table(queue *table)
{
    /* Realisation of algorithm which prints data in table format
     * Argument table - table, which stored as queue
     * Upon successful completion,function shall return 0
     * If argument is a NULL pointer - 1 shall be returned */

    if (table == NULL)
        return 1;
    q_node *current = table->head;
    printf("%-7s\t%-7s\t%-7s\n", "Символ", "Частота", "Код");
    while (current != NULL)
    {
        printf("'%c'\t%d\t%s\n", current->symbol, current->frequency, current->code);
        current = current->next;
    }
    return 0;
}

char *get_string()
{
    /* Realisation of algorithm, which gets string with unknown length from stdin
     * No arguments
     * Upon successful completion, function returns pointer to new string
     * Otherwise, NULL shall be returned */

    int length = 0, curr_size = 1;
    char temp;
    char *string = (char*)malloc(sizeof(char));
    if (string == NULL)
        return NULL;
    while (1)
    {
        scanf("%c", &temp);
        switch (temp)
        {
            case EOF:
                return NULL;
            case '\n':
            {
                string[length] = '\0';
                return string;
            }
            default:
            {
                string[length++] = temp;
                if (length >= curr_size)
                {
                    curr_size *= 2; //We double the current size to reduce realloc use
                    string = (char*)realloc(string, curr_size * sizeof(char));
                    if (string == NULL)
                        return NULL;
                }
            }
        }
    }
}

int delete_queue(queue *data)
{
    /* Realisation of algorithm which delete queue
     * Argument data - queue for deletion
     * Upon successful completion function shall return 0
     * If first argument is a NULL pointer - 1 shall be returned */

    if (data == NULL)
        return 1;
    q_node *current = data->head, *temp;
    while (current != NULL)
    {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(data);
    return 0;
}

void delete_tree(node *root)
{
    /* Realisation of recursive tree-deletion algorithm
     * Argument root - root of tree for deletion
     * Void function, no returning value */

    if (root != NULL)
    {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

void hint()
{
    /* Hint for user */

    printf("Необходимо вводить символы по одному,\n");
    printf("если вы ввели последний символ и частоту,\n");
    printf("то при запросе ввести следующий символ просто нажмите 'ENTER'\n");
    printf("Если ваше сообщение содержит пробел, его тоже необходимо ввести как символ\n");
}