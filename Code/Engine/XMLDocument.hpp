#ifndef include_XMLDocument
#define include_XMLDocument
#pragma once

//-----------------------------------------------------------------------------------------------
#include "pugixml.hpp"
#include "XMLNode.hpp"


//-----------------------------------------------------------------------------------------------
class XMLDocument
{
public:
	XMLDocument() {}
	XMLDocument( const std::string xmlFileName );
	std::string GetFileName() const;
	XMLNode GetRootNode() const;
	XMLNode GetCurrentNode() const;
	void SetCurrentNode( const XMLNode& node );
	void SetCurrentNodeToRoot();
	void SetCurrentNodeToPreviousNode();
	void SetCurrentNodeToParent();
	void SetCurrentNodeToChild( const std::string& childName );
	void SetCurrentNodeToFirstChild();
	void SetCurrentNodeToNextSibling();

private:
	std::string			m_fileName;
	pugi::xml_document	m_document;
	XMLNode				m_currentNode;
	XMLNode				m_previousNode;
};


//-----------------------------------------------------------------------------------------------
inline XMLDocument::XMLDocument( const std::string xmlFileName )
	: m_fileName( xmlFileName )
{
	pugi::xml_parse_result result = m_document.load_file( xmlFileName.c_str() );
	if( result.status != pugi::status_ok )
		return;

	m_currentNode = XMLNode( m_document.root() );
	m_previousNode = m_currentNode;
}


//-----------------------------------------------------------------------------------------------
inline std::string XMLDocument::GetFileName() const
{
	return m_fileName;
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLDocument::GetRootNode() const
{
	return m_document.root();
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLDocument::GetCurrentNode() const
{
	return m_currentNode;
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNode( const XMLNode& node )
{
	m_previousNode = m_currentNode;
	m_currentNode = node;
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToRoot()
{
	m_previousNode = m_currentNode;
	m_currentNode = m_document.root();
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToPreviousNode()
{
	XMLNode tempNode = m_previousNode;
	m_previousNode = m_currentNode;
	m_currentNode = tempNode;
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToParent()
{
	m_previousNode = m_currentNode;
	m_currentNode = m_currentNode.GetParent();
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToChild( const std::string& childName )
{
	m_previousNode = m_currentNode;
	m_currentNode = m_currentNode.GetChild( childName );
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToFirstChild()
{
	m_previousNode = m_currentNode;
	m_currentNode = m_currentNode.GetFirstChild();
}


//-----------------------------------------------------------------------------------------------
inline void XMLDocument::SetCurrentNodeToNextSibling()
{
	m_previousNode = m_currentNode;
	m_currentNode = m_currentNode.GetNextSibling();
}


#endif // include_XMLDocument