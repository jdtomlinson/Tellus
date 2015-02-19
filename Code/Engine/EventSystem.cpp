#include "EventSystem.hpp"


//-----------------------------------------------------------------------------------------------
STATIC std::map< std::string, std::vector< EventSubscriberBase* > > EventSystem::s_subscribers;


//-----------------------------------------------------------------------------------------------
EventSystem::~EventSystem()
{
	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter;
	for( mapIter = s_subscribers.begin(); mapIter != s_subscribers.end(); ++mapIter )
	{
		std::vector< EventSubscriberBase* >& subscriberVec = mapIter->second;
		for( unsigned int subscriberIndex = 0; subscriberIndex < subscriberVec.size(); ++subscriberIndex )
		{
			EventSubscriberBase* tempSubscriber = subscriberVec[ subscriberIndex ];
			delete tempSubscriber;
			tempSubscriber = nullptr;
		}

		subscriberVec.clear();
	}
}


//-----------------------------------------------------------------------------------------------
STATIC void EventSystem::FireEvent( const std::string& eventToFire )
{
	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter = s_subscribers.find( eventToFire );
	if( mapIter == s_subscribers.end() )
		return;

	std::vector<EventSubscriberBase*> subscriberVec = mapIter->second;
	for( unsigned int subscriberIndex = 0; subscriberIndex < subscriberVec.size(); ++subscriberIndex )
	{
		EventSubscriberBase* subscriber = subscriberVec[ subscriberIndex ];
		subscriber->CallCallbackFunction( NamedProperties() );
	}
}


//-----------------------------------------------------------------------------------------------
STATIC void EventSystem::FireEvent( const std::string& eventToFire, const NamedProperties& params )
{
	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter = s_subscribers.find( eventToFire );
	if( mapIter == s_subscribers.end() )
		return;

	std::vector<EventSubscriberBase*> subscriberVec = mapIter->second;
	for( unsigned int subscriberIndex = 0; subscriberIndex < subscriberVec.size(); ++subscriberIndex )
	{
		EventSubscriberBase* subscriber = subscriberVec[ subscriberIndex ];
		subscriber->CallCallbackFunction( params );
	}
}