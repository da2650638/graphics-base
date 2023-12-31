#pragma once

#include <map>

class Input {
public:
	Input() = default;
	~Input() = default;
	
	static bool IsKeyPressed(int keycode);
	static bool IsMouseButtonPressed(int button);
	static std::pair<float, float> GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};