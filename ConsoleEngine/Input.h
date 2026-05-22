#pragma once

extern bool currentKeyState[256];
extern bool previousKeyState[256];

extern int UsingKeys[];

extern void UpdateKeyStates();

extern bool GetKeyDown(int key);
extern bool GetKeyUp(int key);
extern bool GetKey(int key);