#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX_TABLE_SIZE 256

struct binary_tree
{
    unsigned char byte;
    int is_leaf;
    struct binary_tree *left;
    struct binary_tree *right;
};

struct compressed
{
    char bit;
    struct compressed *next;
};

struct compressed *addCompressedBitToList(struct compressed *cp, char bit)
{
    struct compressed *new_compressed = (struct compressed *)malloc(sizeof(struct compressed));

    new_compressed->bit = bit;

    new_compressed->next = NULL;

    if(cp == NULL)
    {
        cp = new_compressed;

        return cp;
    }

    struct compressed *current = cp;

    while(current->next != NULL)
    {
        current = current->next;
    }

    current->next = new_compressed;

    return cp;
}

struct node
{
    unsigned char binary;
    long long frequency;
    char compressed[16];
    int is_leaf;
    struct node *next;
    struct node *left;
    struct node *right;
};

struct hash_table
{
    struct node *table[MAX_TABLE_SIZE];
};

//  This function creates a Hash Table and turns all of its elements to NULL pointers
struct hash_table *create_hash_table()
{
    struct hash_table *new_ht = (struct hash_table *)malloc(sizeof(struct hash_table));

    int i = 0;

    while (i < MAX_TABLE_SIZE)
    {
        new_ht->table[i] = NULL;
        i++;
    }

    return new_ht;
}

//  This function returns the ASCII value of the character to use it at the Hash Table
int hashKey(unsigned char bin)
{
    return (int)bin;
}

struct hash_table *put(struct hash_table *ht, unsigned char bin)
{
    int hash = hashKey(bin);

    if (ht->table[hash] != NULL) //  This means that we already have this character and should only update its frequency.
    {
        ht->table[hash]->frequency++;
        return ht;
    }

    //  If we dont have the byte at the HT, we create a new element and put on the HT
    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    new_node->binary = bin;

    new_node->frequency = 1;

    new_node->is_leaf = 1;

    ht->table[hash] = new_node;

    return ht;
}

struct hash_table *putCompressed(struct hash_table *ht, unsigned char bin, char *compressed)
{
    int hash = hashKey(bin);

    strcpy(ht->table[hash]->compressed, compressed);

    return ht;
}

struct priority_queue
{
    long long size;
    struct node *head;
};

int is_empty_pq(struct priority_queue *pq)
{
    if (pq->size == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

struct priority_queue *create_priority_queue()
{
    struct priority_queue *new_pq = (struct priority_queue *)malloc(sizeof(struct priority_queue));

    new_pq->size = 0;

    new_pq->head = NULL;

    return new_pq;
}

struct priority_queue *enqueue(struct priority_queue *pq, struct node *node)
{

    struct node *new_node = (struct node *)malloc(sizeof(struct node));

    new_node->frequency = node->frequency;

    new_node->binary = node->binary;

    new_node->is_leaf = node->is_leaf;

    strcpy(new_node->compressed, "");

    if (new_node->is_leaf == 0)
    {
        new_node->left = node->left;

        new_node->right = node->right;
    }
    else
    {
        new_node->left = NULL;

        new_node->right = NULL;
    }

    if ((is_empty_pq(pq)) || (node->frequency <= pq->head->frequency))
    {
        new_node->next = pq->head;

        pq->head = new_node;
    }
    else
    {
        struct node *current = pq->head;

        while (current->next != NULL && current->next->frequency < node->frequency)
        {
            current = current->next;
        }

        new_node->next = current->next;

        current->next = new_node;
    }

    pq->size++;

    return pq;
}

struct node *dequeue(struct priority_queue *pq)
{
    if (is_empty_pq(pq))
    {
        printf("Queue underflow\n");

    }
    else
    {
        struct node *node = pq->head;

        pq->head = pq->head->next;

        node->next = NULL;

        pq->size--;

        return node;
    }
}


int getTreeSize(struct node *pq, int cont)
{
    struct node *current = pq;
    if (current != NULL)
    {
        cont++;
        if(current->is_leaf == 1)
        {
            if(current->binary == '*' || current->binary == '\\')
            {
                cont++;
            }
        }
        cont = getTreeSize(current->left, cont);
        cont = getTreeSize(current->right, cont);
    }

    return cont;
}


struct priority_queue *merge(struct priority_queue *pq)
{
    struct priority_queue *current = pq;

    printf("SIZE: %llu\n", current->size);

    if(current->size == 1)
    {
        struct node *first = dequeue(current);

        struct node *new_node = (struct node *) malloc(sizeof(struct node));

        new_node->is_leaf = 0;

        new_node->frequency = first->frequency;

        new_node->binary = '*';

        new_node->left = first;

        new_node->right = NULL;

        current = enqueue(current, new_node);
    }
    else
    {
        while (current->size > 1)
        {
            struct node *first = dequeue(current);

            struct node *second = dequeue(current);

            long long totalFreq = first->frequency + second->frequency;

            struct node *new_node = (struct node *) malloc(sizeof(struct node));

            new_node->is_leaf = 0;

            new_node->frequency = totalFreq;

            new_node->binary = '*';

            new_node->left = first;

            new_node->right = second;

            current = enqueue(current, new_node);
        }
    }

    return pq;
}

struct priority_queue *sendHTtoEnqueue(struct priority_queue *pq, struct hash_table *ht)
{
    int i = 0;

    while (i < 256)
    {
        if (ht->table[i] != NULL)
        {
            pq = enqueue(pq, ht->table[i]);
        }
        i++;
    }

    return pq;
}

void printTreeToFile(FILE *file, struct node *pq)
{
    struct node *current = pq;

    if (current != NULL)
    {
        if((current->binary == '\\' || current->binary ==  '*') && (current->is_leaf == 1))
        {
            fprintf(file, "%c", '\\');
        }
        fprintf(file, "%c", current->binary);

        printTreeToFile(file, current->left);

        printTreeToFile(file, current->right);
    }
}


void transform(const char *string, FILE *out)
{
    int i;

    // char de auxilio para converter a string em binario para unsigned char
    unsigned char byte = 0;

    //para percorrer somente 8 bits
    for(i=0;i<8;i++)
    {

        //caso o caractere atual da string seja 1
        if(string[i] == '1')
        {

            // comparamos com o a resposta da operacao bitwise OR depois do shift bit;
            byte |= 1 << (7-i);
        }
    }

    fprintf(out, "%c", byte);
}


long long totalBits(struct hash_table *ht)
{
    long long total = 0, i;

    for(i=0;i < MAX_TABLE_SIZE;i++)
    {
        if(ht->table[i] != NULL)
        {
            total += (ht->table[i]->frequency * strlen(ht->table[i]->compressed));
        }
    }

    return total;
}


void createHeader(FILE *out, int treeSize, struct hash_table *ht)
{
    int i;

    unsigned int highestOne = 1 << (sizeof(unsigned int) * 8 - 1);

    char string[18] = "";

    int trashSize = 8 - (totalBits(ht)%8);



    //  int i starts in 29 because we just want the last 3 bits.
    for (i = 29; i < 32; i++)
    {
        if(((trashSize & (highestOne >> i)) > 0 ? 1 : 0) == 0)
        {
            strcat(string, "0");
        }
        else
        {
            strcat(string, "1");
        }
    }

    //  int i starts in 19 because we just want the last 13 bits.
    for (i = 19; i < 32; i++)
    {
        if(((treeSize & (highestOne >> i)) > 0 ? 1 : 0) == 0)
        {
            strcat(string, "0");
        }
        else
        {
            strcat(string, "1");
        }
    }

    char *byte = malloc(sizeof(char *));

    for(i=0;i<8;i++)
    {
        byte[i] = string[i];
    }
    //byte[8] = '\0';

    transform(byte, out);


    for(i=0;i<8;i++)
    {
        byte[i] = string[i+8];
    }
    //byte[8] = '\0';

    transform(byte, out);

}

void printCompressed(struct node *pq)
{
    struct node *current = pq;

    if (current != NULL)
    {
        if (current->is_leaf == 1)
        {
            printf("| CHAR: %c | COMPRESSED: %s\n", current->binary, current->compressed);
        }

        printCompressed(current->left);

        printCompressed(current->right);
    }
}

void searchInTree(struct hash_table *ht, struct node *pq, char *string)
{
    struct node *current = pq;

    if (current != NULL)
    {
        char aux[30] = "";

        strcpy(aux, string);

        if (current->is_leaf == 1)
        {
            if (strlen(current->compressed) == 0)
            {
                strcat(current->compressed, string);

                putCompressed(ht, current->binary, current->compressed);
            }
            return;
        }

        strcat(string, "0");

        searchInTree(ht, current->left, string);

        strcpy(string, aux);

        strcat(string, "1");

        searchInTree(ht, current->right, string);
    }
}

int checkSize(struct compressed *cp)
{
    int cont = 0;

    struct compressed *current = cp;

    while(current != NULL)
    {
        cont++;

        current = current->next;
    }

    return cont;
}

char *transformListToString(struct compressed *cp)
{
    int i = 0;

    char *string = malloc(sizeof(char *));

    struct compressed *current = cp;

    while(current != NULL)
    {
        string[i] = current->bit;

        current = current->next;

        i++;
    }


    return string;

}

void freeList(struct compressed *head)
{
    struct compressed *tmp;

    while (head != NULL)
    {
        tmp = head;

        head = head->next;

        free(tmp);
    }

}

void printList(struct compressed *head)
{
    if(head != NULL)
    {
        printf("%c ", head->bit);
        printList(head->next);
    }
}

void compress(struct hash_table *ht, FILE *in, FILE *out)
{

    printf("COMPRESS\n");

    int i;

    struct compressed *cp = NULL;

    unsigned char byte;

    fseek(in, 0, SEEK_SET);

    while (!feof(in))
    {
        fread(&byte, sizeof(byte), 1, in);

        if (!feof(in))
        {
            int key = hashKey(byte);

            for(i=0;i<strlen(ht->table[key]->compressed);i++)
            {
                cp = addCompressedBitToList(cp, ht->table[key]->compressed[i]);

                if(checkSize(cp) >= 8)   //  WE HAVE A BYTE
                {
                    char *string = transformListToString(cp);
                    transform(string, out);

                    freeList(cp);
                    free(string);

                    cp = NULL;
                }
            }
        }
    }

    //  LIDAREMOS COM O ULTIMO BYTE QUE PODE ESTAR INCOMPLETO
    if(checkSize(cp) > 0)
    {
        for(i=0;;i++)
        {
            cp = addCompressedBitToList(cp, '0');
            if(checkSize(cp) >= 8);
            {
                char *string = transformListToString(cp);
                transform(string, out);

                freeList(cp);
                free(string);
                break;
            }
        }

    }

    free(cp);

    printf("Compression complete!\n");
}

// ESSA FUNÇÂO RECEBE UM UNSIGNED CHAR(BYTE) E O TRANSFORMA NUMA STRING DE SUA REPRESENTACAO BINARIA
char *byteToBinary(unsigned char byte)
{
    char *bin = malloc(sizeof(char *));
    int x;
    for(x=7;x>=0;x--) //começamos pelo ultimo 'bit' da string
    {
        bin[x] = (byte & 1) ? '1' : '0'; // verifica se o ultimo bit do byte é igual ao ultimo bit de 1(0000 0001)
        byte >>= 1; // Dividimos o byte por 2 para podermos comparar o proximo bit
    }
    //bin[8] = '\0';
    return bin;
}


struct binary_tree *create_empty_tree()
{
    return NULL;
}

struct binary_tree *create_binary_tree_node(int is_leaf, unsigned char byte)
{
    struct binary_tree *new_bt = (struct binary_tree *)malloc(sizeof(struct binary_tree));
    new_bt->is_leaf = is_leaf;
    new_bt->byte = byte;
    new_bt->right = NULL;
    new_bt->left = NULL;
    return new_bt;
}

int cont = 0; //variavel global para auxiliar na criação da arvore

struct binary_tree *make_tree(struct binary_tree *bt, FILE *in, int treeSize)
{
    if(cont >= treeSize)
    {
        return bt;
    }
    unsigned char byte;

    fread(&byte, sizeof(byte), 1, in);
    cont++;
    if(byte == '\\')    //  significa que o proximo byte é uma folha (ou * ou \)
    {
        fread(&byte, sizeof(byte), 1, in);
        bt = create_binary_tree_node(1, byte);
        return bt;
    }
    if(byte != '*') //  significa que achamos uma folha
    {
        bt = create_binary_tree_node(1, byte);
        return bt;
    }
    else    //  significa que é um asterisco pertence somente a arvore (não é um do arquivo)
    {
        bt = create_binary_tree_node(0, byte);
        bt->left = make_tree(bt->left, in, treeSize);
        bt->right = make_tree(bt->right, in, treeSize);
    }

}


void printTreePre(struct binary_tree *bt)
{
    if(bt != NULL)
    {
        printf("%c - %d\n", bt->byte, bt->is_leaf);
        printTreePre(bt->left);
        printTreePre(bt->right);
    }
}

int is_bit_set(unsigned char byte, int i)
{
    unsigned char mask = 1<<i;
    return (mask & byte);
}

struct binary_tree *search(struct binary_tree *bt, FILE *out)
{
    if(bt->is_leaf == 1)
    {
        fprintf(out, "%c", bt->byte);
        //printf("%c", bt->byte);
        return NULL;
    }
    else
    {
        return bt;
    }
}


void readFileToDecompress(struct binary_tree *bt, FILE *in, int trashSize, int treeSize, FILE *out)
{
    unsigned char byte;
    int i;
    long long fileLen, j;

    struct compressed *list = NULL;
    struct binary_tree *current = bt;


    fseek(in, 0, SEEK_END); // SEND THE POINTER TO THE END OF THE FILE
    fileLen = ftell(in);    //   GET THE ACTUAL POSITION OF THE POINTER AND SAVE ITS ON A VARIABLE
    fseek(in, 0, SEEK_SET);

    //  VOLTANDO PARA ONDE ESTAVAMOS ANTES DE PEGAR O FILELEN
    for(i=0; i<2 + treeSize;i++)
    {
        fread(&byte, sizeof(byte), 1, in);
    }

    j = ftell(in);

    printf("FIleLen: %llu\n", fileLen);

    printf("J = %llu\n", j);

    for(; j < fileLen - 1; j++)
    {
        fread(&byte, sizeof(byte), 1, in);

        for(i=7;i>=0;i--)
        {
            if(is_bit_set(byte, i) == 0)
            {
                current = search(current->left, out);
            }
            else
            {
                current = search(current->right, out);
            }
            if(current == NULL) //  Significa que achamos o byte na arvore
            {
                current = bt;
            }
        }
    }

    //  DEALING WITH THE LAST BYTE

    fread(&byte, sizeof(byte), 1, in);
    for(i=7;i>=trashSize;i--)
    {
        if(is_bit_set(byte, i) == 0)
        {
            current = search(current->left, out);
        }
        else
        {
            current = search(current->right, out);
        }
        if(current == NULL) //  Significa que achamos o byte na arvore
        {
            current = bt;
        }
    }

    printf("\nDecompression complete!\n");

}

void decompress(FILE *in, FILE *out)
{
    int i, j, k;

    unsigned char byte;
    char twoFirstBytes[16];

    for(i=0, k = 0;i<2;i++)
    {
        fread(&byte, sizeof(byte), 1 ,in);

        for(j=7;j>=0;j--, k++)
        {
            if(is_bit_set(byte, j) == 0)
            {
                twoFirstBytes[k] = '0';
            }
            else
            {
                twoFirstBytes[k] = '1';
            }
        }

        twoFirstBytes[16] = '\0';
    }

    printf("Binary: %s\n", twoFirstBytes);

    //      GETTING THE TRASH SIZE AND THE TREE SIZE
    int trashSize = 0, treeSize = 0;


    for(i=0;i<3;i++)
    {
        if(twoFirstBytes[i] == '1')
        {
            trashSize += pow(2, 2-i);
        }
    }

    for(i=3;i<16;i++)
    {
        if(twoFirstBytes[i] == '1')
        {
            treeSize += pow(2, 15-i);
        }
    }

    printf("Trash: %d\nTree: %d\n", trashSize, treeSize);

    //      READING THE TREE INSIDE THE FILE

    struct binary_tree *bt = create_empty_tree();

    bt = make_tree(bt, in, treeSize);

    //      READING THE FILE TO DECOMPRESS

    readFileToDecompress(bt, in, trashSize, treeSize, out);


}

int main()
{
    FILE *file;

    int option;

    char *filename;

    printf("Select an option:\n\n1) Compress\n2) Decompress\n");

    scanf("%d", &option);

    printf("Type the file name with the extension (the file must be in the same directory):\n");

    scanf("%s", filename);

    file = fopen(filename, "rb");

    if (!file)
    {
        fprintf(stderr, "Could not open specified File\n");

        return 0;
    }
    else
    {
        printf("File opened successfully\n");
    }

    if(option == 2)
    {
        FILE *out = fopen("decompressed", "wb");

        decompress(file, out);

        fclose(out);

        fclose(file);

        return 0;
    }

    unsigned char string;

    struct node *list = NULL;

    struct hash_table *hashTable = create_hash_table();

    while (!feof(file))
    {
        fread(&string, sizeof(string), 1, file);

        if (!feof(file))
        {
            hashTable = put(hashTable, string);
        }
    }

    struct priority_queue *p_queue = create_priority_queue();

    p_queue = sendHTtoEnqueue(p_queue, hashTable);

    p_queue = merge(p_queue);

    int treeSize;

    treeSize = getTreeSize(p_queue->head, 0);

    printf("TREE SIZE: %d\n", treeSize);

    FILE *out;

    strcat(filename, ".huff");

    out = fopen(filename, "wb");

    fseek(file, 0, SEEK_SET); //    SEND THE POINTER TO THE BEGINNING OF THE FILE

    char bin[16] = "";

    searchInTree(hashTable, p_queue->head, bin); //  SENDING THE QUEUE(TREE), THE BYTE WE WANT TO SEARCH AND THE STRING TO RECEIVE THE COMPRESSED BYTE

    createHeader(out, treeSize, hashTable);

    printTreeToFile(out, p_queue->head);

    compress(hashTable, file, out);

    fclose(file);

    fclose(out);

    free(list);

    free(hashTable);

    free(p_queue);

    printf("\nProgram is now closing...\n");

    return 0;
}