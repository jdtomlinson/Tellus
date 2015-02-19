#include "World.hpp"
#include <time.h>
#include <stdlib.h>
#include "../Engine/EventSystem.hpp"
#include "../Engine/DeveloperConsole.hpp"

extern "C"
{
#include "../Engine/targa.h"
};


//-----------------------------------------------------------------------------------------------
World::World( float worldWidth, float worldHeight )
	: m_size( worldWidth, worldHeight )
	, m_isWireframeOn( false )
{

}


//-----------------------------------------------------------------------------------------------
void World::Initialize()
{
	m_heightMapMaterial = new Material( HEIGHT_MAP_VERTEX_SHADER, HEIGHT_MAP_FRAGMENT_SHADER );
	m_heightMapMeshMaterial = new Material( HEIGHT_MAP_MESH_VERTEX_SHADER, HEIGHT_MAP_MESH_FRAGMENT_SHADER );

	m_font = BitmapFont( PROGRAM_FONT_GLYPH_SHEET_FILE_NAME, PROGRAM_FONT_META_DATA_FILE_NAME );

	Texture* diffuseTexture = Texture::CreateOrGetTexture( "Data/Images/Checkerboard.png" );
	m_heightMapMaterial->AddTexture( diffuseTexture, "u_diffuseTexture", TEXTURE0 );

	m_numOctaves = INITIAL_NUMBER_OF_OCTAVES;
	m_numMeshTriangleColumns = INITIAL_NUMBER_OF_TRIANGLE_COLUMNS_ON_MESH;
	m_numMeshTriangleRows = INITIAL_NUMBER_OF_TRIANGLE_ROWS_ON_MESH;
	m_meshHeight = INITIAL_MESH_HEIGHT;
	m_persistance = INITIAL_PERSISTANCE;

	m_applyButton = new Button( APPLY_BUTTON_BOTTOM_LEFT_POSITION, APPLY_BUTTON_WIDTH, APPLY_BUTTON_HEIGHT, "Apply", APPLY_BUTTON_UP_TEXTURE_FILE_NAME, APPLY_BUTTON_OVER_TEXTURE_FILE_NAME, APPLY_BUTTON_DOWN_TEXTURE_FILE_NAME );
	m_randomButton = new Button( RANDOM_BUTTON_BOTTOM_LEFT_POSITION, RANDOM_BUTTON_WIDTH, RANDOM_BUTTON_HEIGHT, "Randomize", RANDOM_BUTTON_UP_TEXTURE_FILE_NAME, RANDOM_BUTTON_OVER_TEXTURE_FILE_NAME, RANDOM_BUTTON_DOWN_TEXTURE_FILE_NAME );
	m_heightMapSaveButton = new Button( HEIGHT_MAP_SAVE_BUTTON_BOTTOM_LEFT_POSITION, SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT, "SaveHeightMap", SAVE_BUTTON_UP_TEXTURE_FILE_NAME, SAVE_BUTTON_OVER_TEXTURE_FILE_NAME, SAVE_BUTTON_DOWN_TEXTURE_FILE_NAME );
	m_meshSaveButton = new Button( MESH_SAVE_BUTTON_BOTTOM_LEFT_POSITION, SAVE_BUTTON_WIDTH, SAVE_BUTTON_HEIGHT, "SaveMesh", SAVE_BUTTON_UP_TEXTURE_FILE_NAME, SAVE_BUTTON_OVER_TEXTURE_FILE_NAME, SAVE_BUTTON_DOWN_TEXTURE_FILE_NAME );
	m_lodTextBox = new TextBox( LOD_TEXT_BOX_BOTTOM_LEFT_POSITION, APPEARANCE_TEXT_BOX_WIDTH, APPEARANCE_TEXT_BOX_HEIGHT, "128" );
	m_heightTextBox = new TextBox( HEIGHT_TEXT_BOX_BOTTOM_LEFT_POSITION, APPEARANCE_TEXT_BOX_WIDTH, APPEARANCE_TEXT_BOX_HEIGHT, "25" );
	m_octavesTextBox = new TextBox( OCTAVE_TEXT_BOX_BOTTOM_LEFT_POSITION, PERLIN_TEXT_BOX_WIDTH, PERLIN_TEXT_BOX_HEIGHT, "5" );
	m_persistanceTextBox = new TextBox( PERSISTENCE_TEXT_BOX_BOTTOM_LEFT_POSITION, PERLIN_TEXT_BOX_WIDTH, PERLIN_TEXT_BOX_HEIGHT, "0.5" );
	m_heightMapSaveTextBox = new TextBox( HEIGHT_MAP_SAVE_TEXT_BOX_BOTTOM_LEFT_POSITION, SAVE_TEXT_BOX_WIDTH, SAVE_TEXT_BOX_HEIGHT, "export.tga" );
	m_meshSaveTextBox = new TextBox( MESH_SAVE_TEXT_BOX_BOTTOM_LEFT_POSITION, SAVE_TEXT_BOX_WIDTH, SAVE_TEXT_BOX_HEIGHT, "export.obj" );

	m_lodTextBox->SetRestrictedCharacters( "0-9" );
	m_heightTextBox->SetRestrictedCharacters( "0-9." );
	m_octavesTextBox->SetRestrictedCharacters( "0-9" );
	m_persistanceTextBox->SetRestrictedCharacters( "0-9." );
	m_heightMapSaveTextBox->SetRestrictedCharacters( "A-Za-z0-9_.\\\\/" );

	EventSystem::RegisterEventCallbackForObject( "Apply", this, &World::ApplyApperanceChanges );
	EventSystem::RegisterEventCallbackForObject( "Randomize", this, &World::SetPerlinVariablesAndRandomize );
	EventSystem::RegisterEventCallbackForObject( "SaveHeightMap", this, &World::SaveHeightMap );
	EventSystem::RegisterEventCallbackForObject( "SaveMesh", this, &World::SaveMapMesh );

	srand( (unsigned int) time( NULL ) );
	m_perlinPosition.x = rand();
	m_perlinPosition.y = rand();

	SetMeshVertices();
}


//-----------------------------------------------------------------------------------------------
void World::SetMeshVertices()
{
	m_quadVerts.clear();
	m_meshVerts.clear();

	float oneOverNumColumns = 1.f / static_cast< float >( m_numMeshTriangleColumns );
	float oneOverNumRows = 1.f / static_cast< float >( m_numMeshTriangleRows );
	for( int columnIndex = 0; columnIndex < m_numMeshTriangleColumns; ++columnIndex )
	{
		for( int rowIndex = 0; rowIndex <= m_numMeshTriangleRows; ++rowIndex )
		{
			Vector3 position0;
			Vector3 position1;
			Vector3 position2;

			Vector2 texCoords0;
			Vector2 texCoords1;
			Vector2 texCoords2;

			Vector3 normal0;
			Vector3 normal1;
			Vector3 normal2;

			if( ( rowIndex & 1 ) == ( columnIndex & 1 ) )
			{
				position0 = Vector3( columnIndex * oneOverNumColumns, rowIndex * oneOverNumRows, 0.f );
				position1 = Vector3( ( columnIndex + 1 ) * oneOverNumColumns, ( rowIndex - 1 ) * oneOverNumRows, 0.f );
				position2 = Vector3( ( columnIndex + 1 ) * oneOverNumColumns, ( rowIndex + 1 ) * oneOverNumRows, 0.f );

				texCoords0 = Vector2( columnIndex * oneOverNumColumns, rowIndex * oneOverNumRows );
				texCoords1 = Vector2( ( columnIndex + 1 ) * oneOverNumColumns, ( rowIndex - 1 ) * oneOverNumRows );
				texCoords2 = Vector2( ( columnIndex + 1 ) * oneOverNumColumns, ( rowIndex + 1 ) * oneOverNumRows );

				if( rowIndex == 0 )
				{
					position1.y = 0.f;
					texCoords1.y = 0.f;
				}
				else if( rowIndex == m_numMeshTriangleRows )
				{
					position2.y = 1.f;
					texCoords2.y = 1.f;
				}
			}
			else
			{
				position0 = Vector3( ( columnIndex + 1 ) * oneOverNumColumns, rowIndex * oneOverNumRows, 0.f );
				position1 = Vector3( columnIndex * oneOverNumColumns, ( rowIndex + 1 ) * oneOverNumRows, 0.f );
				position2 = Vector3( columnIndex * oneOverNumColumns, ( rowIndex - 1 ) * oneOverNumRows, 0.f );

				texCoords0 = Vector2( ( columnIndex + 1 ) * oneOverNumColumns, rowIndex * oneOverNumRows );
				texCoords1 = Vector2( columnIndex * oneOverNumColumns, ( rowIndex + 1 ) * oneOverNumRows );
				texCoords2 = Vector2( columnIndex * oneOverNumColumns, ( rowIndex - 1 ) * oneOverNumRows );

				if( rowIndex == 0 )
				{
					position2.y = 0.f;
					texCoords2.y = 0.f;
				}
				else if( rowIndex == m_numMeshTriangleRows )
				{
					position1.y = 1.f;
					texCoords1.y = 1.f;
				}
			}

			float height0 = GetHeightFromPosition( Vector2( position0.x + m_perlinPosition.x, position0.y + m_perlinPosition.y ) );
			float height1 = GetHeightFromPosition( Vector2( position1.x + m_perlinPosition.x, position1.y + m_perlinPosition.y ) );
			float height2 = GetHeightFromPosition( Vector2( position2.x + m_perlinPosition.x, position2.y + m_perlinPosition.y ) );

			float negXPixel0 = GetHeightFromPosition( Vector2( ( position0.x - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position0.y + m_perlinPosition.y ) );
			float posXPixel0 = GetHeightFromPosition( Vector2( ( position0.x + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position0.y + m_perlinPosition.y ) );
			float negYPixel0 = GetHeightFromPosition( Vector2( position0.x + m_perlinPosition.x, ( position0.y - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );
			float posYPixel0 = GetHeightFromPosition( Vector2( position0.x + m_perlinPosition.x, ( position0.y + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );

			float negXPixel1 = GetHeightFromPosition( Vector2( ( position1.x - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position1.y + m_perlinPosition.y ) );
			float posXPixel1 = GetHeightFromPosition( Vector2( ( position1.x + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position1.y + m_perlinPosition.y ) );
			float negYPixel1 = GetHeightFromPosition( Vector2( position1.x + m_perlinPosition.x, ( position1.y - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );
			float posYPixel1 = GetHeightFromPosition( Vector2( position1.x + m_perlinPosition.x, ( position1.y + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );

			float negXPixel2 = GetHeightFromPosition( Vector2( ( position2.x - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position2.y + m_perlinPosition.y ) );
			float posXPixel2 = GetHeightFromPosition( Vector2( ( position2.x + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.x, position2.y + m_perlinPosition.y ) );
			float negYPixel2 = GetHeightFromPosition( Vector2( position2.x + m_perlinPosition.x, ( position2.y - ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );
			float posYPixel2 = GetHeightFromPosition( Vector2( position2.x + m_perlinPosition.x, ( position2.y + ONE_OVER_IMAGE_FILE_SIDE_LENGTH_PIXELS ) + m_perlinPosition.y ) );

			normal0 = Vector3( ( negXPixel0 - posXPixel0 ), ( negYPixel0 - posYPixel0 ), ( 2.f * 0.02f ) );
			normal1 = Vector3( ( negXPixel1 - posXPixel1 ), ( negYPixel1 - posYPixel1 ), ( 2.f * 0.02f ) );
			normal2 = Vector3( ( negXPixel2 - posXPixel2 ), ( negYPixel2 - posYPixel2 ), ( 2.f * 0.02f ) );

			m_quadVerts.push_back( HeightMapVertex( Vertex( position0, Color::White, texCoords0, normal0 ), height0 ) );
			m_quadVerts.push_back( HeightMapVertex( Vertex( position1, Color::White, texCoords1, normal1 ), height1 ) );
			m_quadVerts.push_back( HeightMapVertex( Vertex( position2, Color::White, texCoords2, normal2 ), height2 ) );

			m_meshVerts.push_back( HeightMapVertex( Vertex( position0, Color::Red, texCoords0, Vector3() ), height0 ) );
			m_meshVerts.push_back( HeightMapVertex( Vertex( position1, Color::Red, texCoords1, Vector3() ), height1 ) );

			m_meshVerts.push_back( HeightMapVertex( Vertex( position0, Color::Red, texCoords0, Vector3() ), height0 ) );
			m_meshVerts.push_back( HeightMapVertex( Vertex( position2, Color::Red, texCoords2, Vector3() ), height2 ) );

			m_meshVerts.push_back( HeightMapVertex( Vertex( position1, Color::Red, texCoords1, Vector3() ), height1 ) );
			m_meshVerts.push_back( HeightMapVertex( Vertex( position2, Color::Red, texCoords2, Vector3() ), height2 ) );
		}
	}

	SetHeightMapVBO( &m_quadVBOid, m_quadVerts );
	SetHeightMapVBO( &m_meshVBOid, m_meshVerts );
}


//-----------------------------------------------------------------------------------------------
void World::ChangeMeshDimensions( int newNumberTriangleRows )
{
	m_numMeshTriangleColumns = newNumberTriangleRows;
	m_numMeshTriangleRows = m_numMeshTriangleColumns * 2 + 1;
}


//-----------------------------------------------------------------------------------------------
void World::ChangeMeshHeight( float newMeshHeight )
{
	m_meshHeight = newMeshHeight;
}


//-----------------------------------------------------------------------------------------------
void World::SetRandomPosition()
{
	m_perlinPosition.x = rand();
	m_perlinPosition.y = rand();
}


//-----------------------------------------------------------------------------------------------
bool World::IsFocusedOnTextBox()
{
	bool isInFocus = m_heightMapSaveTextBox->IsInFocus();
	isInFocus |= m_meshSaveTextBox->IsInFocus();

	return isInFocus;
}


//-----------------------------------------------------------------------------------------------
void World::Update( float deltaSeconds, const Keyboard& keyboard, const Mouse& mouse )
{
	Widget::UpdateAllWidgets( deltaSeconds, mouse, keyboard );

	UpdateFromInput( keyboard, mouse );
	UpdateTextBoxes();
}


//-----------------------------------------------------------------------------------------------
void World::RenderObjects3D()
{
	OpenGLRenderer::PushMatrix();

	float angleDeg = 30.f;

	if( m_isWireframeOn )
	{
		OpenGLRenderer::BindBuffer( m_meshVBOid );
		m_heightMapMeshMaterial->Enable();
		{
			SetAttribPointers( m_heightMapMaterial );

			OpenGLRenderer::SetLineWidth( 1.f );
			m_heightMapMeshMaterial->SetUniform( "u_xScale", QUAD_SIDE_LENGTH );
			m_heightMapMeshMaterial->SetUniform( "u_yScale", QUAD_SIDE_LENGTH );
			m_heightMapMeshMaterial->SetUniform( "u_zScale", m_meshHeight );
			m_heightMapMeshMaterial->SetUniform( "u_blurAreaDimensions", m_size );
			RenderHeightMapVerts( m_meshVerts, LINES );
		}
		m_heightMapMeshMaterial->Disable();
	}
	else
	{
		OpenGLRenderer::BindBuffer( m_quadVBOid );
		m_heightMapMaterial->Enable();
		{
			SetAttribPointers( m_heightMapMaterial );

			m_heightMapMaterial->SetUniform( "u_xScale", QUAD_SIDE_LENGTH );
			m_heightMapMaterial->SetUniform( "u_yScale", QUAD_SIDE_LENGTH );
			m_heightMapMaterial->SetUniform( "u_zScale", m_meshHeight );
			m_heightMapMaterial->SetUniform( "u_lightAngle", ConvertDegreesToRadians( angleDeg ) );
			m_heightMapMaterial->SetUniform( "u_blurAreaDimensions", m_size );
			RenderHeightMapVerts( m_quadVerts, TRIANGLES );
		}
		m_heightMapMaterial->Disable();
	}

	OpenGLRenderer::PopMatrix();
}


//-----------------------------------------------------------------------------------------------
void World::RenderObjects2D()
{
	RenderSidebar();
}


//-----------------------------------------------------------------------------------------------
void World::UpdateFromInput( const Keyboard& keyboard, const Mouse& )
{
	if( keyboard.IsKeyPressedDownAndWasNotBefore( KEY_SPACE ) )
	{
		m_isWireframeOn = !m_isWireframeOn;
	}
}


//-----------------------------------------------------------------------------------------------
void World::UpdateTextBoxes()
{
	if( !m_lodTextBox->IsInFocus() )
	{
		int lodValue = atoi( m_lodTextBox->GetText().c_str() );
		int clampedLodValue = ClampInt( lodValue, LOD_MIN_VALUE, LOD_MAX_VALUE );
		m_lodTextBox->SetText( ConvertNumberToString( clampedLodValue ) );
	}


	if( !m_heightTextBox->IsInFocus() )
	{
		float heightValue = (float) atof( m_heightTextBox->GetText().c_str() );
		float clampedHeightValue = ClampFloat( heightValue, HEIGHT_MIN_VALUE, HEIGHT_MAX_VALUE );
		m_heightTextBox->SetText( ConvertNumberToString( clampedHeightValue ) );
	}
}


//-----------------------------------------------------------------------------------------------
void World::RenderSidebar()
{
	float sidebarLeftSidePositionX = m_size.x - ( m_size.x * SIDEBAR_PERCENT_SCREEN_COVER );
	OpenGLRenderer::BeginRender( QUADS );
	{
		OpenGLRenderer::SetColor4f( SIDEBAR_COLOR.r, SIDEBAR_COLOR.g, SIDEBAR_COLOR.b, SIDEBAR_COLOR.a );

		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX, 0.f );
		OpenGLRenderer::SetVertex2f( m_size.x, 0.f );
		OpenGLRenderer::SetVertex2f( m_size.x, m_size.y );
		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX, m_size.y );

		OpenGLRenderer::SetColor4f( 1.f, 1.f, 1.f, 1.f );

		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX, 0.f );
		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX + SIDEBAR_BORDER_WIDTH_PIXELS, 0.f );
		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX + SIDEBAR_BORDER_WIDTH_PIXELS, m_size.y );
		OpenGLRenderer::SetVertex2f( sidebarLeftSidePositionX, m_size.y );
	}
	OpenGLRenderer::EndRender();

	OpenGLRenderer::RenderText( "APPEARANCE", m_font, 50.f, Vector2( 1230.f, 840.f ), Color::Black );
	OpenGLRenderer::RenderText( "LOD (" + ConvertNumberToString( LOD_MIN_VALUE ) + "-" + ConvertNumberToString( LOD_MAX_VALUE ) + "):", m_font, 30.f, Vector2( 1230.f, LOD_TEXT_BOX_BOTTOM_LEFT_POSITION.y ), Color::Black );
	OpenGLRenderer::RenderText( "Height (" + ConvertNumberToString( HEIGHT_MIN_VALUE ) + "-" + ConvertNumberToString( HEIGHT_MAX_VALUE ) + "):", m_font, 30.f, Vector2( 1230.f, HEIGHT_TEXT_BOX_BOTTOM_LEFT_POSITION.y ), Color::Black );

	OpenGLRenderer::RenderText( "PERLIN NOISE", m_font, 50.f, Vector2( 1230.f, 570.f ), Color::Black );
	OpenGLRenderer::RenderText( "Octaves (" + ConvertNumberToString( OCTAVE_MIN_VALUE ) + "-" + ConvertNumberToString( OCTAVE_MAX_VALUE ) + "):", m_font, 25.f, Vector2( 1230.f, OCTAVE_TEXT_BOX_BOTTOM_LEFT_POSITION.y ), Color::Black );
	OpenGLRenderer::RenderText( "Persistence (" + ConvertNumberToString( PERSISTENCE_MIN_VALUE ) + "-" + ConvertNumberToString( PERSISTENCE_MAX_VALUE ) + "):", m_font, 25.f, Vector2( 1230.f, PERSISTENCE_TEXT_BOX_BOTTOM_LEFT_POSITION.y ), Color::Black );

	OpenGLRenderer::RenderText( "EXPORT", m_font, 50.f, Vector2( 1230.f, 300.f ), Color::Black );
	OpenGLRenderer::RenderText( "Heightmap", m_font, 30.f, Vector2( 1250.f, 260.f ), Color::Black );
	OpenGLRenderer::RenderText( "Mesh", m_font, 30.f, Vector2( 1250.f, 120.f ), Color::Black );

	Widget::RenderAllWidgets();
}


//-----------------------------------------------------------------------------------------------
float World::GetRandomValue2D( float x, float y )
{
	int n = int( x + ( y * 57 ) );
	n = ( n<<13 )^n;
	return ( 1.f - ( ( n * ( n * n * 15731 + 789221 ) + 1376312589 ) & 0x7fffffff ) / 1073741824.f );
}


//-----------------------------------------------------------------------------------------------
float World::GetHeightFromPosition( const Vector2& position )
{
	float height = 0.f;
	float scale = 0.f;
	float persistancePowerN = 1.f;

	for( int octaveIndex = 0; octaveIndex < m_numOctaves; ++octaveIndex )
	{
		float oneOverFrequency = 1.f / (float) ( 1<<( octaveIndex ) );
		float amplitude = persistancePowerN;
		scale += amplitude;
		height += amplitude * GetPerlinNoise2D( position, Vector2( oneOverFrequency, oneOverFrequency ) );

		persistancePowerN *= m_persistance;
	}

	height *= ( 1.f / scale );
	return height;
}


//-----------------------------------------------------------------------------------------------
float World::GetPerlinNoise2D( const Vector2& position, const Vector2& perlinDimension )
{
	float oneOverPerlinSampleSizeX = 1.f / perlinDimension.x;
	float oneOverPerlinSampleSizeY = 1.f / perlinDimension.y;

	float southCoord = floor( position.x * oneOverPerlinSampleSizeX );
	float northCoord = southCoord + 1.f;
	float eastCoord = floor( position.y * oneOverPerlinSampleSizeY );
	float westCoord = eastCoord + 1.f;
	float percentAcrossX = ( position.x * oneOverPerlinSampleSizeX ) - southCoord;
	float percentAcrossY = ( position.y * oneOverPerlinSampleSizeY ) - eastCoord;
	percentAcrossX = SmoothStep( percentAcrossX );
	percentAcrossY = SmoothStep( percentAcrossY );

	Vector2 posSE( southCoord, eastCoord );
	Vector2 posSW( southCoord, westCoord );
	Vector2 posNE( northCoord, eastCoord );
	Vector2 posNW( northCoord, westCoord );

	float theta0 = GetRandomValue2D( posSE.x, posSE.y );
	float theta1 = GetRandomValue2D( posSW.x, posSW.y );
	float theta2 = GetRandomValue2D( posNE.x, posNE.y );
	float theta3 = GetRandomValue2D( posNW.x, posNW.y );

	Vector2 vecSE( ( 1.f - percentAcrossX ), ( 1.f - percentAcrossY ) );
	Vector2 vecSW( ( 1.f - percentAcrossX ), percentAcrossY );
	Vector2 vecNE( percentAcrossX, ( 1.f - percentAcrossY ) );
	Vector2 vecNW( percentAcrossX, percentAcrossY );

	vecSE.Normalize();
	vecSW.Normalize();
	vecNE.Normalize();
	vecNW.Normalize();

	float se = DotProduct( Vector2( cos( theta0 ), sin( theta0 ) ), vecSE );
	float sw = DotProduct( Vector2( cos( theta1 ), sin( theta1 ) ), vecSW );
	float ne = DotProduct( Vector2( cos( theta2 ), sin( theta2 ) ), vecNE );
	float nw = DotProduct( Vector2( cos( theta3 ), sin( theta3 ) ), vecNW );

	float south = ( se * ( 1.f - percentAcrossY ) ) + ( sw * percentAcrossY );
	float north = ( ne * ( 1.f - percentAcrossY ) ) + ( nw * percentAcrossY );

	return ( south * ( 1.f - percentAcrossX ) ) + ( north * percentAcrossX );
}


//-----------------------------------------------------------------------------------------------
void World::ApplyApperanceChanges( const NamedProperties& )
{
	float heightValue = (float) atof( m_heightTextBox->GetText().c_str() );
	if( heightValue != m_meshHeight )
	{
		m_meshHeight = heightValue;
	}

	int lodValue = atoi( m_lodTextBox->GetText().c_str() );
	if( lodValue != m_numMeshTriangleColumns )
	{
		ChangeMeshDimensions( lodValue );
		SetMeshVertices();
	}
}


//-----------------------------------------------------------------------------------------------
void World::SetPerlinVariablesAndRandomize( const NamedProperties& )
{
	int octaveValue = atoi( m_octavesTextBox->GetText().c_str() );
	if( octaveValue != m_numOctaves )
	{
		m_numOctaves = octaveValue;
	}

	float persistenceValue = (float) atof( m_persistanceTextBox->GetText().c_str() );
	if( persistenceValue != m_persistance )
	{
		m_persistance = persistenceValue;
	}

	SetRandomPosition();
	SetMeshVertices();
}


//-----------------------------------------------------------------------------------------------
void World::SaveHeightMap( const NamedProperties& )
{
	std::string filePath = m_heightMapSaveTextBox->GetText();
	if( filePath == "" )
		return;

	if( filePath.size() < 5 || filePath.substr( filePath.size() - 4 ) != ".tga" )
	{
		filePath += ".tga";
	}

	unsigned int foundFolder = filePath.find( '/' );
	if( foundFolder == std::string::npos )
		filePath = SAVE_FILE_PATH + filePath;

	const int numPixels = IMAGE_FILE_SIDE_LENGTH_PIXELS * IMAGE_FILE_SIDE_LENGTH_PIXELS;
	uint8_t imageData[ numPixels ];
	for( int columnIndex = 0; columnIndex < IMAGE_FILE_SIDE_LENGTH_PIXELS; ++columnIndex )
	{
		for( int rowIndex = 0; rowIndex < IMAGE_FILE_SIDE_LENGTH_PIXELS; ++rowIndex )
		{
			Vector2 imagePosition;
			imagePosition.x = columnIndex * ONE_OVER_IMAGE_SIDE_LENGTH;
			imagePosition.y = rowIndex * ONE_OVER_IMAGE_SIDE_LENGTH;
			float pixelHeight = GetHeightFromPosition( Vector2( imagePosition.x + m_perlinPosition.x, imagePosition.y + m_perlinPosition.y ) );
			uint8_t pixelGrayscaleByte = static_cast< uint8_t >( pixelHeight * 255 );

			int pixelIndex = rowIndex + ( columnIndex * IMAGE_FILE_SIDE_LENGTH_PIXELS );
			imageData[ pixelIndex ] = pixelGrayscaleByte;
		}
	}

	tga_write_mono( filePath.c_str(), imageData, IMAGE_FILE_SIDE_LENGTH_PIXELS, IMAGE_FILE_SIDE_LENGTH_PIXELS );
}


//-----------------------------------------------------------------------------------------------
void World::SaveMapMesh( const NamedProperties& )
{
	std::string filePath = m_meshSaveTextBox->GetText();
	if( filePath == "" )
		return;

	if( filePath.size() < 5 || filePath.substr( filePath.size() - 4 ) != ".obj" )
	{
		filePath += ".obj";
	}

	unsigned int foundFolder = filePath.find( '/' );
	if( foundFolder == std::string::npos )
		filePath = SAVE_FILE_PATH + filePath;

	FILE* file;
	errno_t results = fopen_s( &file, filePath.c_str(), "w+" );
	if( results != 0 )
		return;

	for( unsigned int vertIndex = 0; vertIndex < m_quadVerts.size(); ++vertIndex )
	{
		HeightMapVertex heightMapVert = m_quadVerts[ vertIndex ];
		std::string vertLine = "v  ";
		vertLine += ConvertNumberToString( heightMapVert.m_vertex.m_position.x * QUAD_SIDE_LENGTH ) + ' ';
		vertLine += ConvertNumberToString( heightMapVert.m_vertex.m_position.y * QUAD_SIDE_LENGTH ) + ' ';
		vertLine += ConvertNumberToString( heightMapVert.m_height * m_meshHeight ) + '\n';

		fwrite( vertLine.c_str(), sizeof( char ), vertLine.size(), file );
	}

	fwrite( "\n", sizeof( char ), 1, file );

	for( unsigned int vertIndex = 0; vertIndex < m_quadVerts.size(); ++vertIndex )
	{
		HeightMapVertex heightMapVert = m_quadVerts[ vertIndex ];
		std::string normalLine = "vn ";
		normalLine += ConvertNumberToString( heightMapVert.m_vertex.m_normal.x ) + ' ';
		normalLine += ConvertNumberToString( heightMapVert.m_vertex.m_normal.y ) + ' ';
		normalLine += ConvertNumberToString( heightMapVert.m_vertex.m_normal.z ) + '\n';

		fwrite( normalLine.c_str(), sizeof( char ), normalLine.size(), file );
	}

	fwrite( "\n", sizeof( char ), 1, file );

	for( unsigned int vertIndex = 0; vertIndex < m_quadVerts.size(); ++vertIndex )
	{
		HeightMapVertex heightMapVert = m_quadVerts[ vertIndex ];
		std::string texCoordLine = "vt ";
		texCoordLine += ConvertNumberToString( heightMapVert.m_vertex.m_texCoords.x ) + ' ';
		texCoordLine += ConvertNumberToString( heightMapVert.m_vertex.m_texCoords.y ) + ' ';
		texCoordLine += "0\n";

		fwrite( texCoordLine.c_str(), sizeof( char ), texCoordLine.size(), file );
	}

	std::string objectName = "\ng map mesh\ns 1\n";
	fwrite( objectName.c_str(), sizeof( char ), objectName.size(), file );

	for( unsigned int vertIndex = 0; vertIndex < m_quadVerts.size(); vertIndex += 3 )
	{
		std::string vertNumString0 = ConvertNumberToString( (int) ( vertIndex + 1 ) );
		std::string vertNumString1 = ConvertNumberToString( (int) ( vertIndex + 2 ) );
		std::string vertNumString2 = ConvertNumberToString( (int) ( vertIndex + 3 ) );

		HeightMapVertex heightMapVert = m_quadVerts[ vertIndex ];
		std::string faceLine = "f " + vertNumString0 + "/" + vertNumString0 + "/" + vertNumString0 + " ";
		faceLine += vertNumString1 + "/" + vertNumString1 + "/" + vertNumString1 + " ";
		faceLine += vertNumString2 + "/" + vertNumString2 + "/" + vertNumString2 + "\n";

		fwrite( faceLine.c_str(), sizeof( char ), faceLine.size(), file );
	}

	fwrite( "\n", sizeof( char ), 1, file );

	fclose( file );
}


//-----------------------------------------------------------------------------------------------
void World::SetHeightMapVBO( unsigned int* VBOid, const std::vector<HeightMapVertex>& vertices )
{
	if( vertices.size() == 0 )
		return;

	glDeleteBuffers( 1, VBOid );

	glGenBuffers( 1, VBOid );
	glBindBuffer( GL_ARRAY_BUFFER, *VBOid );
	glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( HeightMapVertex ), &vertices.front(), GL_STATIC_DRAW );
}


//-----------------------------------------------------------------------------------------------
void World::RenderHeightMapVerts( const std::vector<HeightMapVertex>& vertices, renderType shape )
{
	glEnable( GL_CULL_FACE );
	glFrontFace( GL_CCW );
	glCullFace( GL_BACK );

	if( shape == LINES )
		glDrawArrays( GL_LINES, 0, vertices.size() );
	else if( shape == TRIANGLES )
		glDrawArrays( GL_TRIANGLES, 0, vertices.size() );
}


//-----------------------------------------------------------------------------------------------
void World::SetAttribPointers( Material* material )
{
	glVertexAttribPointer( VERTEX_ATTRIB_POSITIONS, 3, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_vertex.m_position ) );
	glVertexAttribPointer( VERTEX_ATTRIB_COLORS, 4, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_vertex.m_color ) );
	glVertexAttribPointer( VERTEX_ATTRIB_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_vertex.m_texCoords ) );
	glVertexAttribPointer( VERTEX_ATTRIB_NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_vertex.m_normal ) );
	glVertexAttribPointer( VERTEX_ATTRIB_TANGENTS, 3, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_vertex.m_tangent ) );

	int heightAttribLocation = glGetAttribLocation( material->GetShaderProgramID(), "a_height" );
	glVertexAttribPointer( heightAttribLocation, 1, GL_FLOAT, GL_FALSE, sizeof( HeightMapVertex ), (float*) offsetof( HeightMapVertex, m_height ) );

	glEnableVertexAttribArray( VERTEX_ATTRIB_POSITIONS );
	glEnableVertexAttribArray( VERTEX_ATTRIB_COLORS );
	glEnableVertexAttribArray( VERTEX_ATTRIB_TEX_COORDS );
	glEnableVertexAttribArray( VERTEX_ATTRIB_NORMALS );
	glEnableVertexAttribArray( VERTEX_ATTRIB_TANGENTS );
	glEnableVertexAttribArray( heightAttribLocation );
}