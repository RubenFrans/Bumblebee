#pragma once
#include "Components/BaseComponent.h"
#include <functional>
#include "Structs/structs.h"


class BTEngine::GameObject;
class TransformComponent;

class IngredientPartComponent
	: public BaseComponent
{
public:
	IngredientPartComponent(BTEngine::GameObject* pOwner);
	virtual ~IngredientPartComponent() = default;
	IngredientPartComponent(const IngredientPartComponent& other) = delete;
	IngredientPartComponent(IngredientPartComponent&& other) = delete;
	IngredientPartComponent& operator=(const IngredientPartComponent& other) = delete;
	IngredientPartComponent& operator=(IngredientPartComponent&& other) = delete;

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;

	void OnTriggerCallback(BTEngine::GameObject* pOtherObject, TriggerAction action);
	bool IsSteppedOn();

private:

	void InitializeCollisions();

	bool m_SteppedOver;
	FVector2 m_SteppedOnPosOffset;
	std::function<void(BTEngine::GameObject* pOtherObject, TriggerAction action)> m_TriggerCallback;
	TransformComponent* m_pTransformComponent;
};

