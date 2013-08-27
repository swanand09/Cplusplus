#include <Nazara/Graphics.hpp>
#include <Nazara/Core/Clock.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/DynaTerrain/DynaTerrain.hpp>
#include <Nazara/DynaTerrain/DynamicTerrain.hpp>
#include <Nazara/DynaTerrain/DynamicPlanet.hpp>
#include <Nazara/DynaTerrain/Configuration/TerrainConfiguration.hpp>
#include "MyHeightSource2D.hpp"
#include "MyHeightSource3D.hpp"
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

	NzInitializer<NzDynaTerrain> dt;
	if(!dt)
	{
	    std::cout << "Failed to initialize Nazara, see NazaraLog.log for further informations" << std::endl;
	    std::getchar();
	    return EXIT_FAILURE;
	}
    std::cout<<std::endl;
	NzDynaTerrain::ConfigurePrecisionSettings(2,5,1,200.f,3.5f);
    std::cout<<std::endl;
    for(int i(0) ; i < 200 ; ++i)
    {
        std::cout<<i * 10.f<<" : "<<NzDynaTerrain::GetPrecisionLevelFromDistance(i*100.f)<<std::endl;
    }

	NzScene scene;

    /// Initialisation du terrain
    // On instancie notre source de hauteur personnalisée, définissant la hauteur du terrain en tout point
    MyHeightSource2D source;
    NzDynamicTerrain terrain(&source);
    terrain.SetParent(scene);
    terrain.Initialize();


    //terrain.SetParent(scene);
    NzVector3f terrainPos(100.f,100.f,100.f);
    terrain.SetPosition(terrainPos);
/*
    ///-----------Initialisation de la planète-----------
    MyHeightSource3D source3;
    NzPlanetConfiguration myPlanetConfig;

    //Les paramètres de base (quasi-identiques au terrainà
    myPlanetConfig.planetRadius = 4000.f;//Le rayon de la planète
    myPlanetConfig.maxHeight = 1000.f;
    myPlanetConfig.minPrecision = 1;
    myPlanetConfig.groundTextures = "resources/debug_grid2.png";
    myPlanetConfig.higherCameraPrecision = 5;
    myPlanetConfig.cameraRadiusAmount = 3;
    myPlanetConfig.higherCameraPrecisionRadius = 100.f;
    myPlanetConfig.radiusSizeIncrement = 2.5f;

    if(!myPlanetConfig.IsValid())
        std::cout<<"Planet configuration not valid, autofix will be used."<<std::endl;

    NzDynamicPlanet planet(myPlanetConfig,&source3);
    planet.Initialize();

    planet.SetParent(scene);
    NzVector3f planetPos(8000.f,9000.f,8000.f);
    planet.SetPosition(planetPos);*/

    cout<<"Terrain initialized successfully."<<endl;

    ///Code classique pour ouvrir une fenêtre avec Nazara
    NzString windowTitle("DynaTerrain example");
	NzRenderWindow window(NzVideoMode(800,600,32),windowTitle,nzWindowStyle_Default);
	window.SetFramerateLimit(100);
	window.EnableVerticalSync(false);
	window.SetCursor(nzWindowCursor_None);
    NzRenderer::SetClearColor(25, 25, 25);

    std::cout<<"Window opened successfully."<<endl;

	/// Caméra
	//NzVector3f camPos(-2000.f, 1800.f, 2000.f);
	NzVector3f camPos(1380.f, 150.f, 2186.f);
	NzEulerAnglesf camRot(-30.f, -45.f, 0.f);
	NzCamera camera;
	camera.SetPosition(camPos);
	camera.SetRotation(camRot);
	camera.SetFOV(70.f);
	camera.SetZFar(100000.f);
	camera.SetZNear(10.f);
	camera.SetTarget(window);
	scene.SetViewer(camera);

    /// Lampe
	//NzLight spotLight(nzLightType_Spot);
	//spotLight.SetParent(camera);

    ///Gestion du temps
    NzClock secondClock, updateClock; // Des horloges pour gérer le temps
	unsigned int fps = 0; // Compteur de FPS
	float camSpeed = 50.f;
	float sensitivity = 0.2f;

	///Skybox
/*
	NzTexture* texture = new NzTexture;
	if (texture->LoadCubemapFromFile("resources/skyboxsun5deg2.png"))
	{
		texture->SetPersistent(false);
		NzSkyboxBackground* background = new NzSkyboxBackground(texture);
		scene.SetBackground(background);
		std::cout<<"Skybox loaded successfully."<<endl;
	}
	else
	{
		delete texture;
		std::cout << "Failed to load skybox." << std::endl;
	}
*/
	// Quelques variables
	bool camMode = true;
    bool drawWireframe = false;
    bool terrainUpdate = true;

    std::cout<<"Starting main loop"<<std::endl;

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

						case NzKeyboard::F1:
							if (drawWireframe)
							{
								drawWireframe = false;
								//terrain.SetFaceFilling(nzFaceFilling_Fill);//FIX ME
								//planet.SetFaceFilling(nzFaceFilling_Fill);
							}
							else
							{
								drawWireframe = true;
								//terrain.SetFaceFilling(nzFaceFilling_Line);//FIX ME
								//planet.SetFaceFilling(nzFaceFilling_Line);
							}
							break;

                        case NzKeyboard::F2:
                            terrainUpdate = !terrainUpdate;
                            break;

                        case NzKeyboard::Add:
                            //terrainPos.x += 50.f;
                            break;

                        case NzKeyboard::Subtract:
                            //terrainPos.x -= 50.f;
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

            //terrain.SetPosition(terrainPos);

			updateClock.Restart();
		}

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
