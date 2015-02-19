#include "Widget.hpp"


//-----------------------------------------------------------------------------------------------
STATIC std::vector< Widget* > Widget::s_widgetRegistry;


//-----------------------------------------------------------------------------------------------
Widget::Widget()
	: m_screenPositionBottomLeft( 0.f, 0.f )
	, m_widthPixels( 0.f )
	, m_heightPixels( 0.f )
	, m_isInFocus( false )
{
	s_widgetRegistry.push_back( this );
}


//-----------------------------------------------------------------------------------------------
Widget::~Widget()
{
	for( unsigned int widgetIndex = 0; widgetIndex < s_widgetRegistry.size(); ++widgetIndex )
	{
		Widget* widget = s_widgetRegistry[ widgetIndex ];
		if( widget == this )
		{
			s_widgetRegistry.erase( s_widgetRegistry.begin() + widgetIndex );
			break;
		}
	}
}


//-----------------------------------------------------------------------------------------------
STATIC void Widget::UpdateAllWidgets( float deltaSeconds, const Mouse& mouse, const Keyboard& keyboard )
{
	if( mouse.IsLeftButtonClicked() )
		SetAllWidgetsToOutOfFocus();

	for( unsigned int widgetIndex = 0; widgetIndex < s_widgetRegistry.size(); ++widgetIndex )
	{
		Widget* widget = s_widgetRegistry[ widgetIndex ];
		widget->Update( deltaSeconds, mouse, keyboard );
	}
}


//-----------------------------------------------------------------------------------------------
STATIC void Widget::RenderAllWidgets()
{
	for( unsigned int widgetIndex = 0; widgetIndex < s_widgetRegistry.size(); ++widgetIndex )
	{
		Widget* widget = s_widgetRegistry[ widgetIndex ];
		widget->Render();
	}
}


//-----------------------------------------------------------------------------------------------
bool Widget::IsInFocus()
{
	return m_isInFocus;
}


//-----------------------------------------------------------------------------------------------
void Widget::Update( float, const Mouse& mouse, const Keyboard& )
{
	if( mouse.IsLeftButtonClicked() )
	{
		Vector2 cursorPosition = mouse.GetCursorPositionOnWindow();
		Vector2 screenPositionTopRight( m_screenPositionBottomLeft.x + m_widthPixels, m_screenPositionBottomLeft.y + m_heightPixels );
		if( cursorPosition.x > m_screenPositionBottomLeft.x && cursorPosition.x < screenPositionTopRight.x )
		{
			if( cursorPosition.y > m_screenPositionBottomLeft.y && cursorPosition.y < screenPositionTopRight.y )
				m_isInFocus = true;
		}
	}

}


//-----------------------------------------------------------------------------------------------
STATIC void Widget::SetAllWidgetsToOutOfFocus()
{
	for( unsigned int widgetIndex = 0; widgetIndex < s_widgetRegistry.size(); ++widgetIndex )
	{
		Widget* widget = s_widgetRegistry[ widgetIndex ];
		widget->m_isInFocus = false;
	}
}