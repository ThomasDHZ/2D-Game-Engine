#pragma once
#include "CTypedef.h"

typedef struct time_state {
	float delta;
	float now;
	float last;

	float frame_last;
	float frame_delay;
	float frame_time;

	float frame_rate;
	uint32 frame_count;
} Time_State;

void time_init(float frame_rate);
void time_update(void);
void time_update_late(void);
