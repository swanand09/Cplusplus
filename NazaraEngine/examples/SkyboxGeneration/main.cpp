/*
** SkyboxGenerator - Introduction à la génération procédurale d'une skybox de l'espace
** Prérequis: Aucun
** Utilisation du noyau, du renderer, de noise
** Présente:
** - Diverses techniques pour parvenir à un rendu avancé et crédible d'images procédurales (voir Generator.cpp)
*/

#include <Nazara/Graphics.hpp>
#include <Nazara/Core/Clock.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/TerrainRenderer/TerrainRenderer.hpp>
#include <Nazara/TerrainRenderer/TerrainChunk.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include "Generator.hpp"
#include <iostream>
#include <sstream>

using namespace std;

int main()
{
	NzInitializer<NzGraphics> nazara;
	if (!nazara)
	{
		std::cout << "Failed to initialize Nazara, see NazaraLog.log for further informations" << std::endl;
		std::getchar();
		return EXIT_FAILURE;
	}

    NzScene scene;

    // La classe de génération de la skybox
    Generator G;

    NzImage generatedImage(nzImageType_2D,nzPixelFormat_RGBA8,2048,1536);
    generatedImage.Fill(NzColor::Black);
    G.Generate(generatedImage);

    NzTexture texture;
    texture.LoadCubemapFromImage(generatedImage);
    //texture.SetPersistent(false);
    NzSkyboxBackground background(&texture);
    scene.SetBackground(&background);

    ///Code classique pour ouvrir une fenêtre avec Nazara
    NzString windowTitle("Terrain Renderer example");
	NzRenderWindow window(NzVideoMode(1268,680,32),windowTitle,nzWindowStyle_Default);
	window.SetFramerateLimit(100);
	window.EnableVerticalSync(false);
	window.SetCursor(nzWindowCursor_None);

	/// Caméra
	NzVector3f camPos(-1000.f, 2300.f, 340.f);
	NzEulerAnglesf camRot(-30.f, 0.f, 0.f);
	NzCamera camera;
	camera.SetPosition(camPos);
	camera.SetRotation(camRot);
	camera.SetFOV(70.f);
	camera.SetZFar(100000.f);
	camera.SetZNear(10.f);
	camera.SetParent(scene);
	camera.SetTarget(window);

    /// Gestion du temps
    NzClock secondClock, updateClock; // Des horloges pour gérer le temps
	unsigned int fps = 0; // Compteur de FPS
	float camSpeed = 50.f;
	float sensitivity = 0.2f;

	/// Quelques variables
	bool camMode = true;
    bool drawWireframe = false;
    bool terrainUpdate = true;

	while (window.IsOpen())
	{
		NzEvent event;
		while (window.PollEvent(&event))
		{
			switch (event.type)
			{
				case nzEventType_Quit:
					window.Close();
					break;

				case nzEventType_MouseMoved:
				{
					if (!camMode)
						break;

					camRot.yaw = NzNormalizeAngle(camRot.yaw - event.mouseMove.deltaX*sensitivity);
					camRot.pitch = NzClamp(camRot.pitch - event.mouseMove.deltaY*sensitivity, -89.f, 89.f);
					camera.SetRotation(camRot);
					NzMouse::SetPosition(window.GetWidth()/2, window.GetHeight()/2, window);
					break;
				}

				case nzEventType_MouseButtonPressed:
					if (event.mouseButton.button == NzMouse::Left)
					{
						// L'utilisateur vient d'appuyer sur le bouton left de la souris
						// Nous allons inverser le mode caméra et montrer/cacher le curseur en conséquence
						if (camMode)
						{
							camMode = false;
							window.SetCursor(nzWindowCursor_Default);
						}
						else
						{
							camMode = true;
							window.SetCursor(nzWindowCursor_None);
						}
					}
                    break;

				case nzEventType_KeyPressed: // Une touche du clavier vient d'être enfoncée
				{
					switch (event.key.code)
					{
						case NzKeyboard::Escape:
							window.Close();
							break;

						default:
							break;
					}

					break;
				}
				default:
					break;
			}
		}

		// Mise à jour de la partie logique
		if (updateClock.GetMilliseconds() >= 1000/60.f)
		{
			float elapsedTime = updateClock.GetSeconds();

			// Déplacement de la caméra
			static const NzVector3f forward(NzVector3f::Forward());
			static const NzVector3f left(NzVector3f::Left());
			static const NzVector3f up(NzVector3f::Up());

            float speed2 = (NzKeyboard::IsKeyPressed(NzKeyboard::Key::LShift)) ? camSpeed*40: camSpeed;
            NzVector3f speed(speed2,speed2,speed2);

            if (NzKeyboard::IsKeyPressed(NzKeyboard::Z))
                camera.Move(forward * speed * elapsedTime);

            if (NzKeyboard::IsKeyPressed(NzKeyboard::S))
                camera.Move(-forward * speed * elapsedTime);

            if (NzKeyboard::IsKeyPressed(NzKeyboard::Q))
                camera.Move(left * speed * elapsedTime);

            if (NzKeyboard::IsKeyPressed(NzKeyboard::D))
                camera.Move(-left * speed * elapsedTime);

            // En revanche, ici la hauteur est toujours la même, peu importe notre orientation
            if (NzKeyboard::IsKeyPressed(NzKeyboard::Space))
                camera.Move(up * speed * elapsedTime, nzCoordSys_Global);

            if (NzKeyboard::IsKeyPressed(NzKeyboard::LControl))
                camera.Move(up * speed * elapsedTime, nzCoordSys_Global);

			updateClock.Restart();
		}



        camera.Activate();
		scene.Update();
		scene.Cull();
		scene.UpdateVisible();
		scene.Draw();
		window.Display();

		fps++;

		// Toutes les secondes
		if (secondClock.GetMilliseconds() >= 1000)
		{
			window.SetTitle(windowTitle + " (FPS: " + NzString::Number(fps) + ')' + "( Camera in : " + camera.GetPosition().ToString() + ")");// (Updated Nodes : " + NzString::Number(quad.GetSubdivisionsAmount()) + "/s)");
			fps = 0;
			secondClock.Restart();
		}
	}

    return 0;
}




