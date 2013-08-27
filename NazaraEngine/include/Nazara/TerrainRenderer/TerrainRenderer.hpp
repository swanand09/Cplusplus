// Copyright (C) 2013 Rémi Bèges
// This file is part of the "Nazara Engine - Module name"
// For conditions of distribution and use, see copyright notice in Config.hpp

#pragma once

#ifndef NAZARA_TERRAINRENDERER_HPP
#define NAZARA_TERRAINRENDERER_HPP

#include <Nazara/Prerequesites.hpp>
#include <Nazara/Core/Initializer.hpp>
#include <Nazara/TerrainRenderer/TerrainChunk.hpp>
#include <Nazara/Renderer/Renderer.hpp>
#include <vector>

class NAZARA_API NzTerrainRenderer
{
	public:
		NzTerrainRenderer() = delete;
		~NzTerrainRenderer() = delete;

        static void DrawTerrainChunk(const NzTerrainChunk& chunk);

        static const NzIndexBuffer* GetIndexBuffer();
        static const NzShaderProgram* GetShader();

		static bool Initialize();

		static bool IsInitialized();

		static void Uninitialize();

	private:
		static unsigned int s_moduleReferenceCounter;
};

#endif // NAZARA_TERRAINRENDERER_HPP
