#ifndef include_Widget
#define include_Widget
#pragma once

//-----------------------------------------------------------------------------------------------
#include <vector>
#include "Mouse.hpp"
#include "Vector2.hpp"
#include "Keyboard.hpp"
#include "EngineCommon.hpp"


//-----------------------------------------------------------------------------------------------
class Widget
{
public:
	Widget();
	virtual ~Widget();
	static void UpdateAllWidgets( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard );
	static void RenderAllWidgets();
	bool IsInFocus();

protected:
	virtual void Update( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard );
	virtual void Render() {}

	Vector2							m_screenPositionBottomLeft;
	float							m_widthPixels;
	float							m_heightPixels;
	bool							m_isInFocus;

private:
	static void SetAllWidgetsToOutOfFocus();

	static std::vector< Widget* >	s_widgetRegistry;
};


#endif // include_Widget