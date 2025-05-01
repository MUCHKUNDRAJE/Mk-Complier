#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
      INT,
    STRING,
    FLOAT,
    BOOL
} DataTypeSymbol;

typedef struct SymbolEntry {
    char* identifier;        
    DataTypeSymbol type;           
    struct SymbolEntry* next; 
} SymbolEntry;

#define TABLE_SIZE 100

SymbolEntry* symbolTable[TABLE_SIZE];


unsigned int hash(const char* str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}

void insertSymbol(const char* identifier, DataTypeSymbol type) {
    unsigned int index = hash(identifier);

    SymbolEntry* newEntry = (SymbolEntry*)malloc(sizeof(SymbolEntry));
    newEntry->identifier = strdup(identifier);
    newEntry->type = type;
    newEntry->next = symbolTable[index];
    symbolTable[index] = newEntry;
}

DataTypeSymbol lookupType(const char* identifier) {
    unsigned int index = hash(identifier);
    SymbolEntry* entry = symbolTable[index];

    while (entry) {
        if (strcmp(entry->identifier, identifier) == 0) {
            return entry->type;
        }
        entry = entry->next;
    }

    return (DataTypeSymbol)-1  ; 
}
const char* getTypeName(DataTypeSymbol type) {
    return type == INT ? "int" : "string";
}

void printSymbolTable() {
    printf("Symbol Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        SymbolEntry *entry  = symbolTable[i];
        while (entry != NULL) {
            printf("Identifier: %s, Data Type: %s\n", entry->identifier, getTypeName(entry->type));
            entry = entry->next;
        }
    }
}