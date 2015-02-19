#ifndef include_World
#define include_World
#pragma once

//-----------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include "GameCommon.hpp"
#include "HeightMapVertex.hpp"
#include "../Engine/Mouse.hpp"
#include "../Engine/Button.hpp"
#include "../Engine/Camera.hpp"
#include "../Engine/Vertex.hpp"
#include "../Engine/pugixml.hpp"
#include "../Engine/TextBox.hpp"
#include "../Engine/Texture.hpp"
#include "../Engine/Vector2.hpp"
#include "../Engine/Keyboard.hpp"
#include "../Engine/Material.hpp"
#include "../Engine/BitmapFont.hpp"
#include "../Engine/DebugGraphics.hpp"
#include "../Engine/OpenGLRenderer.hpp"
#include "../Engine/NamedProperties.hpp"
#include "../Engine/ConsoleCommandArgs.hpp"
#include "../Engine/XMLParsingFunctions.hpp"


//-----------------------------------------------------------------------------------------------
const int INITIAL_NUMBER_OF_TRIANGLE_COLUMNS_ON_MESH = 128;
const int INITIAL_NUMBER_OF_TRIANGLE_ROWS_ON_MESH = INITIAL_NUMBER_OF_TRIANGLE_COLUMNS_ON_MESH * 2 + 1;
const int INITIAL_NUMBER_OF_OCTAVES = 5;
const int IMAGE_FILE_SIDE_LENGTH_PIXELS = 512;
const int LOD_MIN_VALUE = 8;
const int LOD_MAX_VALUE = 256;
const int OCTAVE_MIN_VALUE = 1;
const int OCTAVE_MAX_VALUE = 10;
const float HEIGHT_MIN_VALUE = 0.f;
const float HEIGHT_MAX_VALUE = 50.f;
const float PERSISTENCE_MIN_VALUE = 0.01f;
const float PERSISTENCE_MAX_VALUE = 1.f;
const float ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS = 1.f / IMAGE_FILE_SIDE_LENGTH_PIXELS;
const float ONE_OVER_IMAGE_SIDE_LENGTH = 1.f / (float) IMAGE_FILE_SIDE_LENGTH_PIXELS;
const float QUAD_SIDE_LENGTH = 100.f;
const float INITIAL_MESH_HEIGHT = 25.f;
const float INITIAL_PERSISTANCE = 0.5f;
const float SIDEBAR_PERCENT_SCREEN_COVER = 0.25f;
const float SIDEBAR_BORDER_WIDTH_PIXELS = 10.f;
const float APPEARANCE_TEXT_BOX_WIDTH = 150.f;
const float APPEARANCE_TEXT_BOX_HEIGHT = 30.f;
const float PERLIN_TEXT_BOX_WIDTH = 110.f;
const float PERLIN_TEXT_BOX_HEIGHT = 30.f;
const float SAVE_TEXT_BOX_WIDTH = 300.f;
const float SAVE_TEXT_BOX_HEIGHT = 30.f;
const float SAVE_BUTTON_WIDTH = 100.f;
const float SAVE_BUTTON_HEIGHT = 50.f;
const float APPLY_BUTTON_WIDTH = 128.f;
const float APPLY_BUTTON_HEIGHT = 64.f;
const float RANDOM_BUTTON_WIDTH = 128.f;
const float RANDOM_BUTTON_HEIGHT = 64.f;
const Color SIDEBAR_COLOR = Color( 0.76f, 0.76f, 0.76f );
const Vector2 HEIGHT_MAP_SAVE_BUTTON_BOTTOM_LEFT_POSITION = Vector2( 1450.f, 160.f );
const Vector2 MESH_SAVE_BUTTON_BOTTOM_LEFT_POSITION = Vector2( 1450.f, 20.f );
const Vector2 APPLY_BUTTON_BOTTOM_LEFT_POSITION = Vector2( 1434.f, 650.f );
const Vector2 RANDOM_BUTTON_BOTTOM_LEFT_POSITION = Vector2( 1434.f, 380.f );
const Vector2 HEIGHT_MAP_SAVE_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1250.f, 225.f );
const Vector2 MESH_SAVE_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1250.f, 85.f );
const Vector2 LOD_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1410.f, 800.f );
const Vector2 HEIGHT_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1410.f, 740.f );
const Vector2 OCTAVE_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1450.f, 530.f );
const Vector2 PERSISTENCE_TEXT_BOX_BOTTOM_LEFT_POSITION = Vector2( 1450.f, 470.f );
const std::string SAVE_BUTTON_UP_TEXTURE_FILE_NAME = "Data/Images/SaveButtonUp.png";
const std::string SAVE_BUTTON_OVER_TEXTURE_FILE_NAME = "Data/Images/SaveButtonOver.png";
const std::string SAVE_BUTTON_DOWN_TEXTURE_FILE_NAME = "Data/Images/SaveButtonDown.png";
const std::string APPLY_BUTTON_UP_TEXTURE_FILE_NAME = "Data/Images/ApplyButtonUp.png";
const std::string APPLY_BUTTON_OVER_TEXTURE_FILE_NAME = "Data/Images/ApplyButtonOver.png";
const std::string APPLY_BUTTON_DOWN_TEXTURE_FILE_NAME = "Data/Images/ApplyButtonDown.png";
const std::string RANDOM_BUTTON_UP_TEXTURE_FILE_NAME = "Data/Images/RandomizeButtonUp.png";
const std::string RANDOM_BUTTON_OVER_TEXTURE_FILE_NAME = "Data/Images/RandomizeButtonOver.png";
const std::string RANDOM_BUTTON_DOWN_TEXTURE_FILE_NAME = "Data/Images/RandomizeButtonDown.png";
const std::string PROGRAM_FONT_GLYPH_SHEET_FILE_NAME = "Data/Fonts/MainFont_EN_00.png";
const std::string PROGRAM_FONT_META_DATA_FILE_NAME = "Data/Fonts/MainFont_EN.FontDef.xml";
const std::string HEIGHT_MAP_VERTEX_SHADER = "Data/Shaders/Standard_Height_Map_330.vertex.glsl";
const std::string HEIGHT_MAP_FRAGMENT_SHADER = "Data/Shaders/Standard_Height_Map_330.fragment.glsl";
const std::string HEIGHT_MAP_MESH_VERTEX_SHADER = "Data/Shaders/Standard_Height_Map_330.vertex.glsl";
const std::string HEIGHT_MAP_MESH_FRAGMENT_SHADER = "Data/Shaders/Height_Map_Mesh_330.fragment.glsl";
const std::string SAVE_FILE_PATH = "Export/";


//-----------------------------------------------------------------------------------------------
class World
{
public:
	World( float worldWidth, float worldHeight );
	void Initialize();
	void SetMeshVertices();
	void ChangeMeshDimensions( int newNumberTriangleRows );
	void ChangeMeshHeight( float newMeshHeight );
	void SetRandomPosition();
	bool IsFocusedOnTextBox();
	void Update( float deltaSeconds, const Keyboard& keyboard, const Mouse& mouse );
	void RenderObjects3D();
	void RenderObjects2D();

private:
	void UpdateFromInput( const Keyboard& keyboard, const Mouse& mouse );
	void UpdateTextBoxes();
	void RenderSidebar();
	float GetRandomValue2D( float x, float y );
	float GetHeightFromPosition( const Vector2& position );
	float GetPerlinNoise2D( const Vector2& position, const Vector2& perlinDimension );
	void ApplyApperanceChanges( const NamedProperties& params );
	void SetPerlinVariablesAndRandomize( const NamedProperties& params );
	void SaveHeightMap( const NamedProperties& params );
	void SaveMapMesh( const NamedProperties& params );
	void SetHeightMapVBO( unsigned int* VBOid, const std::vector<HeightMapVertex>& vertices );
	void RenderHeightMapVerts( const std::vector<HeightMapVertex>& vertices, renderType shape );
	void SetAttribPointers( Material* material );

	Camera							m_camera;
	Vector2							m_size;
	IntVector2						m_perlinPosition;
	BitmapFont						m_font;
	bool							m_isWireframeOn;
	Material*						m_heightMapMaterial;
	Material*						m_heightMapMeshMaterial;
	float							m_meshHeight;
	int								m_numOctaves;
	int								m_numMeshTriangleRows;
	int								m_numMeshTriangleColumns;
	float							m_persistance;
	Button*							m_applyButton;
	Button*							m_randomButton;
	Button*							m_heightMapSaveButton;
	Button*							m_meshSaveButton;
	TextBox*						m_heightMapSaveTextBox;
	TextBox*						m_meshSaveTextBox;
	TextBox*						m_lodTextBox;
	TextBox*						m_heightTextBox;
	TextBox*						m_octavesTextBox;
	TextBox*						m_persistanceTextBox;
	std::vector< HeightMapVertex >	m_quadVerts;
	std::vector< HeightMapVertex >	m_meshVerts;
	unsigned int					m_quadVBOid;
	unsigned int					m_meshVBOid;
};


#endif // include_World