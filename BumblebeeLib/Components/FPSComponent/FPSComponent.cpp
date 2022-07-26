
#include "FPSComponent.h"
#include "Time/TimeManager.h"
#include "GameObject/GameObject.h"
#include "Components/TextComponent/TextComponent.h"

FPSComponent::FPSComponent(BTEngine::GameObject* pOwner)
    : BaseComponent{ pOwner }, m_CurrentFps{}
{
}

void FPSComponent::Update()
{
    m_CurrentFps = 1.0f / TimeManager::GetDeltaTime();

    TextComponent* tc = GetGameObject()->GetComponent<TextComponent>();

    if (!tc)
        return;

    tc->SetText(std::to_string(int(m_CurrentFps)) + " FPS");

}

void FPSComponent::FixedUpdate()
{
}

void FPSComponent::Initialize()
{
}

float FPSComponent::GetFPS()
{
    return m_CurrentFps;
}
