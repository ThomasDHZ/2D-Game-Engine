#pragma once
#include <inttypes.h>

typedef struct time_state {
	float delta;
	float now;
	float last;

	float frame_last;
	float frame_delay;
	float frame_time;

	float frame_rate;
	uint32_t frame_count;
} Time_State;

void time_init(uint32_t frame_rate);
void time_update(void);
void time_update_late(void);
