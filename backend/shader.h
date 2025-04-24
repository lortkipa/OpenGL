#pragma once


unsigned compileShader(const char* path, const int type);

unsigned linkProgram(const unsigned shader1, const unsigned shader2);

unsigned createShaderProgram(const char* vertPath, const char* fragPath);
