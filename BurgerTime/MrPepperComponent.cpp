#pragma once

#include "MrPepperComponent.h"
#include "Components/TransformComponent/TransformComponent.h"
#include "Time/TimeManager.h"
#include "Components/AnimationComponent/AnimationComponent.h"
#include "Components\CollisionComponent\CollisionComponent.h"
#include "PlatformComponent.h"
#include "Components/RigidBodyComponent/RigidBodyComponent.h"
#include "Components/ColliderComponent/ColliderComponent.h"
#include "Components\ColliderComponent\CircleCollider\CircleCollider.h"

MrPepperComponent::MrPepperComponent(BTEngine::GameObject* pOwner)
	: BaseComponent{ pOwner }, m_IsDead{ false }
	, m_HorizontalSpeed{ 50.0f }
	, m_VerticalSpeed{ 50.0f }
	, m_State{ MrPepperState::down }
	, m_IsOnLadder{ false }
	, m_pAnimationComponent{ nullptr }
	, m_pTransformComponent{ nullptr }
	, m_pRigidBodyComponent{ nullptr }
	, m_LadderCounter{ 0 }
{
}

void MrPepperComponent::Initialize()
{
	m_pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	//m_pTransformComponent->SetSize(50.0f, 50.0f);
	m_pAnimationComponent = GetGameObject()->GetComponent<AnimationComponent>();
	m_pRigidBodyComponent = GetGameObject()->GetComponent<RigidBodyComponent>();

	InitializeAnimations();
	InitializeCollisionCallbacks();
}

void MrPepperComponent::InitializeAnimations() {

	Animation runDownAnimation{};
	runDownAnimation.SetSpriteSheet("spritesheet.png");
	runDownAnimation.m_AmountOfColumns = 2;
	runDownAnimation.m_AmountOfRows = 1;

	runDownAnimation.m_CellWidth = 16;
	runDownAnimation.m_CellHeigth = 16;
	runDownAnimation.m_AnimationFramesPerSecond = 10;

	Animation runRightAnimation{ IVector2{48, 0} };
	runRightAnimation.SetSpriteSheet("spritesheet.png");
	runRightAnimation.m_AmountOfColumns = 2;
	runRightAnimation.m_AmountOfRows = 1;

	runRightAnimation.m_CellWidth = 16;
	runRightAnimation.m_CellHeigth = 16;
	runRightAnimation.m_AnimationFramesPerSecond = 10;
	runRightAnimation.m_FlipHorizontal = true;

	Animation runLeftAnimation{ IVector2{48, 0} };
	runLeftAnimation.SetSpriteSheet("spritesheet.png");
	runLeftAnimation.m_AmountOfColumns = 2;
	runLeftAnimation.m_AmountOfRows = 1;

	runLeftAnimation.m_CellWidth = 16;
	runLeftAnimation.m_CellHeigth = 16;
	runLeftAnimation.m_AnimationFramesPerSecond = 10;

	Animation runUpAnimation{ IVector2{96, 0} };
	runUpAnimation.SetSpriteSheet("spritesheet.png");
	runUpAnimation.m_AmountOfColumns = 2;
	runUpAnimation.m_AmountOfRows = 1;

	runUpAnimation.m_CellWidth = 16;
	runUpAnimation.m_CellHeigth = 16;
	runUpAnimation.m_AnimationFramesPerSecond = 10;


	m_pAnimationComponent->AddAnimation(0, runDownAnimation)
		->AddAnimation(1, runUpAnimation)
		->AddAnimation(2, runLeftAnimation)
		->AddAnimation(3, runRightAnimation);
}

void MrPepperComponent::InitializeCollisionCallbacks() {

	CircleCollider* collider = GetGameObject()->GetComponent<CircleCollider>();

	assert(collider != nullptr);

	collider->SetCollisionCallback([&](BTEngine::GameObject* pOtherObject, TriggerAction action) {
			
			OnTriggerCallback(pOtherObject, action);
	
		});
}


void MrPepperComponent::OnTriggerCallback(BTEngine::GameObject* pOtherObject, TriggerAction action) {
	if (action == TriggerAction::Enter) {

		if (pOtherObject->GetTag().compare("ladder") == 0) {
			m_LadderCounter += 1;
		}
	}
	else if (action == TriggerAction::Leave) {

		if (pOtherObject->GetTag().compare("ladder") == 0) {

			m_LadderCounter -= 1;
		}
	}

	if (m_LadderCounter > 0) {
		m_IsOnLadder = true;
		m_pRigidBodyComponent->SetGravityEnabled(false);
	}
	else {
		m_IsOnLadder = false;
		m_pRigidBodyComponent->SetGravityEnabled(true);
	}

}

void MrPepperComponent::Update()
{

}

void MrPepperComponent::FixedUpdate()
{
	
}

void MrPepperComponent::MoveLeft() 
{
	//m_pTransformComponent->Translate(-m_HorizontalSpeed * TimeManager::GetDeltaTime(), 0.0f);
	m_pRigidBodyComponent->SetVelocity({ -100.0f, 0.0f });
	m_pAnimationComponent->SetPlayAnimation((int)MrPepperState::left);
}

void MrPepperComponent::MoveRight()
{
	m_pRigidBodyComponent->SetVelocity({ 100.0f, 0.0f });
	//m_pTransformComponent->Translate(m_HorizontalSpeed * TimeManager::GetDeltaTime(), 0.0f);
	m_pAnimationComponent->SetPlayAnimation((int)MrPepperState::right);
}

void MrPepperComponent::MoveUp()
{
	m_pRigidBodyComponent->SetVelocity({ 0.0f, -100.0f });
	//m_pTransformComponent->Translate(0.0f, -m_VerticalSpeed * TimeManager::GetDeltaTime());
	m_pAnimationComponent->SetPlayAnimation((int)MrPepperState::up);
}

void MrPepperComponent::MoveDown()
{
	m_pRigidBodyComponent->SetVelocity({ 0.0f, 100.0f });
	//m_pTransformComponent->Translate(0.0f, m_VerticalSpeed * TimeManager::GetDeltaTime());
	m_pAnimationComponent->SetPlayAnimation((int)MrPepperState::down);
}

void MrPepperComponent::Die() {
	m_IsDead = true;
	Notify(*this, Event::PLAYER_DIE);
}
