#pragma once

#include <stdbool.h>


void window_create(const int width, const int height, const char* title);

void window_updateState(void);

bool window_isOpen(void);

bool window_keyPressed(int key);

void window_close(void);

void window_destroy(void);
