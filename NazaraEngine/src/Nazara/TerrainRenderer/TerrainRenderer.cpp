// Copyright (C) 2013 Rémi Bèges
// This file is part of the "Nazara Engine - Terrain renderer module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/TerrainRenderer/TerrainRenderer.hpp>
#include <Nazara/Core/Core.hpp>
#include <Nazara/Core/Error.hpp>
#include <Nazara/Core/Log.hpp>
#include <Nazara/Utility/IndexBuffer.hpp>
#include <Nazara/Renderer/ShaderProgram.hpp>
#include <Nazara/TerrainRenderer/Config.hpp>
#include <iostream>
#include <Nazara/Utility/BufferMapper.hpp>
#include <Nazara/TerrainRenderer/Debug.hpp>

namespace
{
    static NzIndexBuffer m_indexBuffer;
    //Même shader pour tous les terrains pour l'instant
    static NzShaderProgram* m_shader;
}

void NzTerrainRenderer::DrawTerrainChunk(const NzTerrainChunk& chunk)
{
    auto itBuffers = chunk.m_vertexBuffers.begin();
    unsigned int i = 0;
    unsigned int count;
    unsigned int offset;

    for( ; itBuffers != chunk.m_vertexBuffers.end() ; ++itBuffers)
    {
        // Pour itérer sur les lots de maillage dans un même vertexBuffer
        auto itBatches = chunk.m_vertexBuffersMap.at(i).GetFilledIntervals().cbegin();

        // On envoie le vertexBuffer entier au renderer Nazara
        NzRenderer::SetVertexBuffer(&(*itBuffers));

        // On itère sur l'ensemble des lots d'un même buffer
        for(; itBatches != chunk.m_vertexBuffersMap.at(i).GetFilledIntervals().cend() ; ++itBatches)
        {
            // On fait le rendu
                //(*it).x -> firstIndex;
                //(*it).y -> vertexCount;
            //Pour dessiner 1 patch (25 vertex) il nous faut 48 index (pas 96 ??)
            offset = itBatches->Start() * 48;
            count = itBatches->Count() * 96;

            NzRenderer::DrawIndexedPrimitives(nzPrimitiveMode_TriangleList,offset,count);
        }
        ++i;
    }
}

const NzIndexBuffer* NzTerrainRenderer::GetIndexBuffer()
{
    return &m_indexBuffer;
}

const NzShaderProgram* NzTerrainRenderer::GetShader()
{
    return m_shader;
}

bool NzTerrainRenderer::Initialize()
{
	if (s_moduleReferenceCounter++ != 0)
		return true;

	// Initialisation des dépendances
	if (!NzRenderer::Initialize())
	{
		NazaraError("Failed to initialize renderer module");
		return false;
	}

	// Initialisation du module

	///L'index buffer
    unsigned int rowIndex[24];

    for(int i(0) ; i < 4 ; ++i)
    {
        rowIndex[i*6] = i;
        rowIndex[i*6+1] = i + 1;
        rowIndex[i*6+2] = i + 6;
        rowIndex[i*6+3] = i;
        rowIndex[i*6+4] = i + 5;
        rowIndex[i*6+5] = i + 6;
    }

    unsigned int indexes[96];

    for(unsigned int i(0) ; i < 4 ; ++i)
        for(unsigned int j(0) ; j < 24 ; ++j)
        {
            indexes[i*24+j] = rowIndex[j] + i*5;
        }

    std::vector<nzUInt16> allIndexes;
    allIndexes.reserve(VERTEX_BUFFER_SLOT_AMOUNT * 96);

    for(int i(0) ; i < VERTEX_BUFFER_SLOT_AMOUNT ; ++i)
        for(int j(0) ; j < 96 ; ++j)
        {
            allIndexes.push_back(static_cast<nzUInt16>(indexes[j] + 25 * i));
        }

	try
    {
        m_indexBuffer.Reset(false, VERTEX_BUFFER_SLOT_AMOUNT * 96, nzBufferStorage_Hardware);
    }
    catch (const std::exception& e)
    {
        NazaraError("Failed to create buffer: " + NzString(e.what()));

        Uninitialize();
        return false;
    }

	if (!m_indexBuffer.Fill(allIndexes.data(), 0, VERTEX_BUFFER_SLOT_AMOUNT * 96))
	{
		NazaraError("Failed to initialize terrain renderer module : Failed to create/fill index buffer");
		m_indexBuffer.Reset();
		return false;
	}

	/// Le shader par défaut du terrain
	const char* vertexSource =
    "#version 140\n"
    "in vec3 VertexPosition;\n"
    "in vec3 VertexNormal;\n"
    "uniform mat4 WorldViewProjMatrix;\n"
    "out vec3 normal;\n"
    "out vec3 position;\n"

    "void main()\n"
    "{\n"
	"normal = VertexNormal;\n"
	"position = VertexPosition;\n"
    "gl_Position = WorldViewProjMatrix * vec4(VertexPosition, 1.0);\n"
    "}\n";

    const char* fragmentSource =
    "#version 140\n"
    "out vec4 out_Color;\n"
    "in vec3 normal;\n"
    "in vec3 position;\n"

    "void main()\n"
    "{\n"
    "/*out_Color = vec4(0.0,1.0,0.0,1.0);*/\n"
    "out_Color = vec4(normal.x,normal.y,normal.z,1.0);\n"
    "}\n";

    m_shader = new NzShaderProgram(nzShaderLanguage_GLSL);

    if (!m_shader->LoadShader(nzShaderType_Fragment, fragmentSource))
    {
        NazaraError("Failed to initialize terrain renderer module : Failed to load fragment shader");
        m_indexBuffer.Reset();
        delete m_shader;
        return false;
    }

    if (!m_shader->LoadShader(nzShaderType_Vertex, vertexSource))
    {
        NazaraError("Failed to initialize terrain renderer module : Failed to load vertex shader");
        m_indexBuffer.Reset();
        delete m_shader;
        return false;
    }

    if (!m_shader->Compile())
    {
        NazaraError("Failed to initialize terrain renderer module : Failed to compile shader");
        m_indexBuffer.Reset();
        delete m_shader;
        return false;
    }

	NazaraNotice("Initialized: TerrainRenderer module");

	return true;
}

bool NzTerrainRenderer::IsInitialized()
{
	return s_moduleReferenceCounter != 0;
}

void NzTerrainRenderer::Uninitialize()
{
	if (s_moduleReferenceCounter != 1)
	{
		// Le module est soit encore utilisé, soit pas initialisé
		if (s_moduleReferenceCounter > 1)
			s_moduleReferenceCounter--;

		return;
	}

	// Libération du module
	s_moduleReferenceCounter = 0;
	m_indexBuffer.Reset();
    delete m_shader;

	NazaraNotice("Uninitialized: TerrainRenderer module");

	// Libération des dépendances
	NzRenderer::Uninitialize();
}

unsigned int NzTerrainRenderer::s_moduleReferenceCounter = 0;
