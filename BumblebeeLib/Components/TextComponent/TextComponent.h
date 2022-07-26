#pragma once
#include "Components/BaseComponent.h"
#include "Font.h"
#include "RGBColor.h"
#include <memory>

class TextComponent :
    public BaseComponent
{
public:
	TextComponent(BTEngine::GameObject* pOwner);
	virtual ~TextComponent() = default;
	virtual void Update() override;
	virtual void FixedUpdate() override;
	virtual void Initialize() override;

	TextComponent* SetText(const std::string& text);
	TextComponent* SetFont(std::shared_ptr<BTEngine::Font> font);

	void SetColor(const RGBColor& color);
	void SetColor(Uint8 r, Uint8 g, Uint8 b);

private:
	bool m_NeedsUpdate;
	std::string m_Text;
	std::shared_ptr<BTEngine::Font> m_Font;
	RGBColor m_Color;
};

