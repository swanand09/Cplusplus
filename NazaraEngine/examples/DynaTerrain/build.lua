kind "ConsoleApp"

files {"main.cpp","MyHeightSource2D.hpp","MyHeightSource2D.cpp","MyHeightSource3D.hpp","MyHeightSource3D.cpp"}

if (_OPTIONS["united"]) then
	configuration "DebugStatic"
		links "NazaraEngine-s-d"

	configuration "ReleaseStatic"
		links "NazaraEngine-s"

	configuration "DebugDLL"
		links "NazaraEngine-d"

	configuration "ReleaseDLL"
		links "NazaraEngine"
else
	configuration "DebugStatic"
		links "Nazara3D-s-d"
		links "NazaraRenderer-s-d"
		links "NazaraUtility-s-d"
		links "NazaraCore-s-d"
		links "NazaraNoise-s-d"
		links "NazaraGraphics-s-d"
		links "NazaraDynaTerrain-s-d"

	configuration "ReleaseStatic"
		links "Nazara3D-s"
		links "NazaraRenderer-s"
		links "NazaraUtility-s"
		links "NazaraCore-s"
		links "NazaraNoise-s"
		links "NazaraGraphics-s"
		links "NazaraDynaTerrain-s"

	configuration "DebugDLL"
		links "Nazara3D-d"
		links "NazaraRenderer-d"
		links "NazaraUtility-d"
		links "NazaraCore-d"
		links "NazaraNoise-d"
		links "NazaraGraphics-d"
		links "NazaraDynaTerrain-d"

	configuration "ReleaseDLL"
		links "Nazara3D"
		links "NazaraRenderer"
		links "NazaraUtility"
		links "NazaraCore"
		links "NazaraNoise"
		links "NazaraGraphics"
		links "NazaraDynaTerrain"
end
