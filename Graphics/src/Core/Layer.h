#pragma once

#include <string>

#include "Events/Event.h"

class Layer
{
public:
	Layer() = default;
	Layer(const std::string& name)
		: m_Name(name) {}
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	//TODO: virtual void OnUpdate(Timestep ts);
	virtual void OnUpdate() {}
	virtual void OnUIRender() {}
	virtual void OnDetach() {}
	virtual void OnEvent(Event& e) {}
private:
	std::string m_Name;
};