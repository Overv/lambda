#include <lambda_asm.h>
#include <lambda_mem.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct lambda_asm_state* lambda_asm_begin()
{
	struct lambda_asm_state* state = (struct lambda_asm_state*)malloc(sizeof(struct lambda_asm_state));
	state->buffer = (uchar*)malloc(16);
	state->size = 16;
	state->off = 0;
	return state;
}

lambda_func lambda_asm_finish(struct lambda_asm_state* state)
{
	lambda_func f = (lambda_func)lambda_alloc(state->off);
	memcpy(f, state->buffer, state->off);
	free(state->buffer);
	state->buffer = NULL;
	return f;
}

void lambda_asm_code(struct lambda_asm_state* state, uchar code)
{
	if (state->off + 1 >= state->size) {
		state->buffer = (uchar*)realloc(state->buffer, state->size * 2);
		state->size *= 2;
	}

	state->buffer[state->off] = code;
	state->off++;
}

void lambda_asm_value(struct lambda_asm_state* state, int value)
{
	if (state->off + (int)sizeof(int) >= state->size) {
		state->buffer = (uchar*)realloc(state->buffer, state->size * 2);
		state->size *= 2;
	}

	*(int*)&state->buffer[state->off] = value;
	state->off += sizeof(int);
}

void lambda_asm_mov_reg(struct lambda_asm_state* state, int dest, int src)
{
	lambda_asm_code(state, LAMBDA_MOV_REG);
	lambda_asm_code(state, LAMBDA_MOD_REG | (dest << 3) | src);
}

void lambda_asm_mov_val(struct lambda_asm_state* state, int dest, int value)
{
	lambda_asm_code(state, LAMBDA_MOV_VAL);
	lambda_asm_code(state, LAMBDA_MOD_REG | dest);
	lambda_asm_value(state, value);
}

void lambda_asm_pop(struct lambda_asm_state* state, int dest)
{
	lambda_asm_code(state, LAMBDA_POP);
	lambda_asm_code(state, LAMBDA_MOD_REG | dest);
}

void lambda_asm_push(struct lambda_asm_state* state, int src)
{
	lambda_asm_code(state, LAMBDA_PUSH);
	lambda_asm_code(state, LAMBDA_MOD_REG | (6 << 3) | src);
}

void lambda_asm_add_reg(struct lambda_asm_state* state, int dest, int src)
{
	lambda_asm_code(state, LAMBDA_ADD_REG);
	lambda_asm_code(state, LAMBDA_MOD_REG | (dest << 3) | src);
}

void lambda_asm_add_val(struct lambda_asm_state* state, int dest, int value)
{
	lambda_asm_code(state, LAMBDA_ADDSUB_VAL);
	lambda_asm_code(state, LAMBDA_MOD_REG | dest);
	lambda_asm_value(state, value);
}

void lambda_asm_sub_reg(struct lambda_asm_state* state, int dest, int src)
{
	lambda_asm_code(state, LAMBDA_SUB_REG);
	lambda_asm_code(state, LAMBDA_MOD_REG | (dest << 3) | src);
}

void lambda_asm_sub_val(struct lambda_asm_state* state, int dest, int value)
{
	lambda_asm_code(state, LAMBDA_ADDSUB_VAL);
	lambda_asm_code(state, LAMBDA_MOD_REG | (5 << 3) | dest);
	lambda_asm_value(state, value);
}

void lambda_asm_imul_reg(struct lambda_asm_state* state, int dest, int src)
{
	lambda_asm_code(state, LAMBDA_IMUL_REG_1);
	lambda_asm_code(state, LAMBDA_IMUL_REG_2);
	lambda_asm_code(state, LAMBDA_MOD_REG | (dest << 3) | src);
}

void lambda_asm_imul_val(struct lambda_asm_state* state, int dest, int src, int value)
{
	lambda_asm_code(state, LAMBDA_IMUL_VAL);
	lambda_asm_code(state, LAMBDA_MOD_REG | (dest << 3) | src);
	lambda_asm_value(state, value);
}

void lambda_asm_idiv(struct lambda_asm_state* state, int divisor)
{
	lambda_asm_code(state, LAMBDA_IDIV);
	lambda_asm_code(state, LAMBDA_MOD_REG | (7 << 3) | divisor);
}

void lambda_asm_ret(struct lambda_asm_state* state)
{
	lambda_asm_code(state, LAMBDA_RET);
}