#ifndef include_XMLNode
#define include_XMLNode
#pragma once

//-----------------------------------------------------------------------------------------------
#include <vector>
#include "pugixml.hpp"
#include "XMLAttribute.hpp"


//-----------------------------------------------------------------------------------------------
class XMLNode
{
public:
	XMLNode() {}
	XMLNode( const pugi::xml_node& node ) : m_node( node ) {}
	std::string GetNodeName() const;
	XMLNode GetParent() const;
	XMLNode GetChild( const std::string childName ) const;
	XMLNode GetFirstChild() const;
	int GetNumberOfChildNodes() const;
	XMLNode GetNextSibling() const;
	XMLAttribute GetAttributeByName( const std::string& attributeName ) const;
	std::vector<XMLAttribute> GetAllAttributes() const;
	std::vector<XMLNode> GetAllChildren() const;
	bool IsNull() const;

private:
	pugi::xml_node	m_node;
};


//-----------------------------------------------------------------------------------------------
inline std::string XMLNode::GetNodeName() const
{
	return m_node.name();
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLNode::GetParent() const
{
	return XMLNode( m_node.parent() );
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLNode::GetChild( const std::string childName ) const
{
	return XMLNode( m_node.child( childName.c_str() ) );
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLNode::GetFirstChild() const
{
	return XMLNode( m_node.first_child() );
}


//-----------------------------------------------------------------------------------------------
inline int XMLNode::GetNumberOfChildNodes() const
{
	return std::distance( m_node.begin(), m_node.end() );
}


//-----------------------------------------------------------------------------------------------
inline XMLNode XMLNode::GetNextSibling() const
{
	return XMLNode( m_node.next_sibling() );
}


//-----------------------------------------------------------------------------------------------
inline XMLAttribute XMLNode::GetAttributeByName( const std::string& attributeName ) const
{
	XMLAttribute attribute( m_node.attribute( attributeName.c_str() ) );
	return attribute;
}


//-----------------------------------------------------------------------------------------------
inline std::vector<XMLAttribute> XMLNode::GetAllAttributes() const
{
	pugi::xml_object_range<pugi::xml_attribute_iterator> attributeList = m_node.attributes();
	std::vector<XMLAttribute> returnVec;

	for( pugi::xml_attribute_iterator attribIter = attributeList.begin(); attribIter != attributeList.end(); ++attribIter )
	{
		returnVec.push_back( *attribIter );
	}

	return returnVec;
}


//-----------------------------------------------------------------------------------------------
inline std::vector<XMLNode> XMLNode::GetAllChildren() const
{
	pugi::xml_object_range<pugi::xml_node_iterator> childList = m_node.children();
	std::vector<XMLNode> returnVec;

	for( pugi::xml_node_iterator childIter = childList.begin(); childIter != childList.end(); ++childIter )
	{
		returnVec.push_back( *childIter );
	}

	return returnVec;
}


//-----------------------------------------------------------------------------------------------
inline bool XMLNode::IsNull() const
{
	return m_node == nullptr;
}


#endif // include_XMLNode