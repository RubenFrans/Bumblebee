
#include "Animation.h"
#include "ResourceManager/ResourceManager.h"
#include "Time/TimeManager.h"


Animation::Animation()
	: Animation{ {0, 0} }
{

}

Animation::Animation(const IVector2& anchorPoint)
	: m_AnimationFramesPerSecond{}
	, m_AnchorPoint{anchorPoint}
	, m_AmountOfColumns{}
	, m_AmountOfRows{}
	, m_CurrentCellColumn{}
	, m_CurrentCellRow{}
	, m_CellWidth{}
	, m_CellHeigth{}
	, m_CurrentFrameTime{}
	, m_FlipHorizontal{ false }
	, m_FlipVertical{ false }
	
{

}

Animation::~Animation()
{

}

void Animation::UpdateCurrentFrame() {

	if (m_CurrentFrameTime > 1.0f / float(m_AnimationFramesPerSecond)) {

		//if (m_CurrentCellColumn / m_AmountOfColumns != 1) {
		if(m_CurrentCellColumn < m_AmountOfColumns){
			m_CurrentCellColumn++;
		}
		else {
			m_CurrentCellRow++;
			m_CurrentCellColumn = 0;
		}

		//if (m_CurrentCellRow / m_AmountOfRows == 1) {
		if(m_CurrentCellRow >= m_AmountOfRows){
			m_CurrentCellRow = 0;
		}

		m_CurrentFrameTime = 0.0f;
	}
	else {
		m_CurrentFrameTime += TimeManager::GetDeltaTime();
	}

}

void Animation::SetSpriteSheet(const std::string& filename)
{
	m_pSpriteSheet = BTEngine::ResourceManager::GetInstance().LoadTexture(filename);
}

void Animation::SetSpriteSheet(std::shared_ptr<BTEngine::Texture2D> texture)
{
	m_pSpriteSheet = texture;
}

void Animation::SetAnimationSpeed(int framesPerSecond)
{
	m_AnimationFramesPerSecond = framesPerSecond;
}

void Animation::SetCellSize(int 
	width, int height)
{
	m_CellWidth = width;
	m_CellHeigth = height;
}

SDL_Rect Animation::GetCurrentFrameTexture() const 
{
	return SDL_Rect{m_CurrentCellColumn * m_CellWidth + m_AnchorPoint.x, m_CurrentCellRow * m_CellHeigth + m_AnchorPoint.y, m_CellWidth, m_CellHeigth};
}
