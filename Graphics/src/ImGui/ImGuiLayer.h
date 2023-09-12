#pragma once

#include "Core/Layer.h"

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer() = default;
	ImGuiLayer(const std::string& name)
		: Layer(name) {}
	virtual ~ImGuiLayer() = default;

	void Begin();
	void End();

	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUIRender() override;
	virtual void OnEvent(Event& e) override;
};