#include <stdlib.h>
#include <stdio.h>
#include "modulararray.h"

// modulararrayblock

void* ModularArrayBlock_GetValue(ModularArrayBlock *block, unsigned int index) {

	void *value;
	value = NULL;

	if (index < block->size) {
		value = block->data[index];
	}

	return value;
}


void ModularArrayBlock_SetValue(ModularArrayBlock *block, unsigned int index, void *value) {
	if (index < block->size) {

		block->data[index] = value;
		ModularArrayBlock_SetDataIndex(block, index);
	}
}


unsigned int ModularArrayBlock_GetSize(ModularArrayBlock *block) {
	return block->size;
}


unsigned int ModularArrayBlock_IsFull(ModularArrayBlock *block) {
	unsigned int i;
	for (i = 0; i < block->size; i++) {

		if (block->data[i] == NULL) {
			return 0;
		}
	}

	return 1;
}


void ModularArrayBlock_SetDataIndex(ModularArrayBlock *block, unsigned int data_index) {

	if (data_index > block->data_index) {
		block->data_index = data_index;
	}
}


ModularArrayBlock* ModularArrayBlock_New(unsigned int size) {
	ModularArrayBlock *block;
	block = (ModularArrayBlock*) malloc(sizeof(ModularArrayBlock));

	block->data = (void**) malloc(sizeof(void*) * size);
	block->data_index = 0;
	block->size = size;

	return block;
}


void ModularArrayBlock_Destroy(ModularArrayBlock *block) {

	free(block->data);
	free(block);
}


// modulararray

unsigned int ModularArray_GetSize(ModularArray *array) {

	unsigned int size, i;
	for (i = 0; i < array->block_count; i++) {

		ModularArrayBlock *block;
		block = array->blocks[i];

		size += block->size;
	}

	return size;
}


void ModularArray_AllocateBlock(ModularArray *array) {
	ModularArrayBlock *block;
	block = ModularArrayBlock_New(array->block_size);

	array->blocks = (ModularArrayBlock**) realloc(array->blocks, sizeof(ModularArrayBlock*) * array->block_count + 1);

	array->blocks[array->block_count] = block;
	array->block_count += 1;
}


unsigned int ModularArray_GetBlockkIndex(ModularArray *array, unsigned int index) {

	unsigned int block_index;
	block_index = (unsigned int) ( index / array->block_size );

	return block_index;
}


void* ModularArray_GetValue(ModularArray *array, unsigned int index) {
	void *value;
	value = NULL;

	unsigned int block_index;
	block_index = ModularArray_GetBlockkIndex(array, index);

	if (block_index + 1 <= array->block_count) {
		unsigned int block_address;
		block_address = index % array->block_size;

		ModularArrayBlock *block;
		block = array->blocks[block_index];

		value = ModularArrayBlock_GetValue(block, block_address);
	}

	return value;
}


void ModularArray_SetValue(ModularArray *array, unsigned int index, void *value) {
	unsigned int block_index;
	block_index = ModularArray_GetBlockkIndex(array, index);

	while (array->block_count <= block_index) {
		ModularArray_AllocateBlock(array);
	}

	unsigned int block_address;
	block_address = index % array->block_size;

	ModularArrayBlock *block = array->blocks[block_index];
	ModularArrayBlock_SetValue(block, block_address, value);
}


void* ModularArray_Pop(ModularArray *array) {
	ModularArrayBlock *block;
	block = array->blocks[array->	block_count - 1];

	if (block != NULL) {
		block->data_index--;
	}
}


void ModularArray_Push(ModularArray *array, void *value) {

	unsigned int array_size;
	array_size = ModularArray_GetSize(array);

	return ModularArray_SetValue(array, array_size, value);
}


void* ModularArray_Shift(ModularArray *array) {

	// to do
}


void ModularArray_ForEach(ModularArray *array, void (*callback)(void*)) {
	unsigned int i, j;
	for (i = 0; i < array->block_count; i++) {

		ModularArrayBlock *block;
		block = array->blocks[i];

		for (j = 0; j < block->size; j++) {
			void *value;
			value = ModularArrayBlock_GetValue(block, j);

			if (value != NULL) {
				callback(value);
			}

			else {
				break;
			}
		}
	}
}


ModularArray* ModularArray_New(unsigned int block_size) {
	ModularArray *array;
	array = (ModularArray*) malloc(sizeof(ModularArray));

	array->block_size = block_size;
	ModularArray_AllocateBlock(array);

	return array;
}


void ModularArray_Destroy(ModularArray *array) {
	unsigned int i;
	for (i = 0; i < array->block_count; i++) {
		ModularArrayBlock *block;
		block = array->blocks[i];

		ModularArrayBlock_Destroy(block);
	}

	free(array->blocks);
	free(array);
}
