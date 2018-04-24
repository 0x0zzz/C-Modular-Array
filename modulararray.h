#ifndef _MODULAR_ARRAY_
#define _MODULAR_ARRAY_


typedef struct {
	void **data;
	unsigned int size;
	unsigned int data_index;
} ModularArrayBlock;

// basic functions`
void* ModularArrayBlock_GetValue(ModularArrayBlock *block, unsigned int index);
void ModularArrayBlock_SetValue(ModularArrayBlock *block, unsigned int index, void *value);

unsigned int ModularArrayBlock_GetSize(ModularArrayBlock *block);
unsigned int ModularArrayBlock_IsFull(ModularArrayBlock *block);
void ModularArrayBlock_SetDataIndex(ModularArrayBlock *block, unsigned int data_index);


// constructor, destructor
ModularArrayBlock* ModularArrayBlock_New(unsigned int size);
void ModularArrayBlock_Destroy(ModularArrayBlock *block);


typedef struct {
	ModularArrayBlock **blocks;
	unsigned int block_count;
	unsigned int block_size;

} ModularArray;

// basic functions
void ModularArray_AllocateBlock(ModularArray *array);
void* ModularArray_GetValue(ModularArray *array, unsigned int index);
void ModularArray_SetValue(ModularArray *array, unsigned int index, void *value);
void* ModularArray_Pop(ModularArray *array);
void ModularArray_Push(ModularArray *array, void *value);
void* ModularArray_Shift(ModularArray *array);
void ModularArray_ForEach(ModularArray *array, void (*callback)(void*));


// constructor, destructor
ModularArray* ModularArray_New();
void ModularArray_Destroy(ModularArray *array);

#endif
