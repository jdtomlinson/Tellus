#ifndef include_EventSystem
#define include_EventSystem
#pragma once

//-----------------------------------------------------------------------------------------------
#include <map>
#include <vector>
#include "EngineCommon.hpp"
#include "NamedProperties.hpp"


//-----------------------------------------------------------------------------------------------
class EventSubscriberBase
{
public:
	virtual void CallCallbackFunction( const NamedProperties& ) {}
};


//-----------------------------------------------------------------------------------------------
template< class T_SubscriberType >
class TypedEventSubscription : public EventSubscriberBase
{
	typedef void ( T_SubscriberType::*ObjectMemberFunctionType )( const NamedProperties& params );

public:
	TypedEventSubscription() {}
	void CallCallbackFunction( const NamedProperties& params );

	T_SubscriberType*			m_object;
	ObjectMemberFunctionType	m_function;
};


//-----------------------------------------------------------------------------------------------
template< class T_SubscriberType >
inline void TypedEventSubscription<T_SubscriberType>::CallCallbackFunction( const NamedProperties& params )
{
	( m_object->*m_function )( params );
}


//-----------------------------------------------------------------------------------------------
class EventSystem
{
public:
	~EventSystem();
	template< typename T_SubscriberType, typename T_SubscriberFuctionType >
		static void RegisterEventCallbackForObject( const std::string& eventToListenFor, T_SubscriberType* subscriber, const T_SubscriberFuctionType funcToExecute );
	template< typename T_SubscriberType >
		static void UnregisterEventCallbackForObject( T_SubscriberType* subscriber );
	template< typename T_SubscriberType >
		static void UnregisterEventCallbackForObject( const std::string& eventToListenFor, T_SubscriberType* subscriber );
	static void FireEvent( const std::string& eventToFire );
	static void FireEvent( const std::string& eventToFire, const NamedProperties& params );

private:
	static std::map< std::string, std::vector< EventSubscriberBase* > > s_subscribers;
};


//-----------------------------------------------------------------------------------------------
template< typename T_SubscriberType, typename T_SubscriberFuctionType >
inline STATIC void EventSystem::RegisterEventCallbackForObject( const std::string& eventToListenFor, T_SubscriberType* subscriber, const T_SubscriberFuctionType funcToExecute )
{	
	TypedEventSubscription< T_SubscriberType >* newSubscriber = new TypedEventSubscription< T_SubscriberType >;
	newSubscriber->m_object = subscriber;
	newSubscriber->m_function = funcToExecute;

	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter = s_subscribers.find( eventToListenFor );
	if( mapIter != s_subscribers.end() )
	{
		std::vector< EventSubscriberBase* >& subscriberVec = mapIter->second;
		subscriberVec.push_back( newSubscriber );
	}
	else
	{
		std::vector< EventSubscriberBase* > subscribersVec;
		subscribersVec.push_back( newSubscriber );
		s_subscribers[ eventToListenFor ] = subscribersVec;
	}
}


//-----------------------------------------------------------------------------------------------
template< typename T_SubscriberType >
inline STATIC void EventSystem::UnregisterEventCallbackForObject( T_SubscriberType* unsubscriber )
{
	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter;
	for( mapIter = s_subscribers.begin(); mapIter != s_subscribers.end(); ++mapIter )
	{
		std::vector< EventSubscriberBase* > oldSubscriberVec = mapIter->second;
		std::vector< EventSubscriberBase* > newSubscriberVec;

		for( unsigned int subscriberIndex = 0; subscriberIndex < oldSubscriberVec.size(); ++subscriberIndex )
		{
			EventSubscriberBase* subscriber = oldSubscriberVec[ subscriberIndex ];
			TypedEventSubscription< T_SubscriberType >* subscriberTypePtr = dynamic_cast< TypedEventSubscription< T_SubscriberType >* >( subscriber );
			if( subscriberTypePtr != nullptr && unsubscriber == subscriberTypePtr->m_object )
			{
				delete subscriberTypePtr;
			}
			else
			{
				newSubscriberVec.push_back( subscriber );
			}
		}

		mapIter->second = newSubscriberVec;
	}
}


//-----------------------------------------------------------------------------------------------
template< typename T_SubscriberType >
inline STATIC void EventSystem::UnregisterEventCallbackForObject( const std::string& eventToStopListeningFor, T_SubscriberType* unsubscriber )
{
	std::map< std::string, std::vector< EventSubscriberBase* > >::iterator mapIter = s_subscribers.find( eventToStopListeningFor );
	if( mapIter == s_subscribers.end() )
		return;

	std::vector< EventSubscriberBase* > oldSubscriberVec = mapIter->second;
	std::vector< EventSubscriberBase* > newSubscriberVec;

	for( unsigned int subscriberIndex = 0; subscriberIndex < oldSubscriberVec.size(); ++subscriberIndex )
	{
		EventSubscriberBase* subscriber = oldSubscriberVec[ subscriberIndex ];
		TypedEventSubscription< T_SubscriberType >* subscriberTypePtr = dynamic_cast< TypedEventSubscription< T_SubscriberType >* >( subscriber );
		if( unsubscriber == subscriberTypePtr->m_object )
		{
			delete subscriberTypePtr;
		}
		else
		{
			newSubscriberVec.push_back( subscriber );
		}
	}

	mapIter->second = newSubscriberVec;
}


#endif // include_EventSystem