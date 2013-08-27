#include <Nazara/Graphics.hpp>
#include <Nazara/Core/Clock.hpp>
#include <Nazara/Renderer.hpp>
#include <Nazara/Utility.hpp>
#include <Nazara/TerrainRenderer/TerrainRenderer.hpp>
#include <Nazara/TerrainRenderer/TerrainChunksManager.hpp>
#include <Nazara/Math/Matrix4.hpp>
#include <Nazara/Renderer/OpenGL.hpp>
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

	NzInitializer<NzTerrainRenderer> nzTerrainRender;
	if (!nzTerrainRender)
	{
		std::cout << "Failed to initialize Terrain Renderer, see NazaraLog.log for further informations" << std::endl;
		std::getchar();
		return EXIT_FAILURE;
	}

	NzDebugDrawer::Initialize();

    NzScene scene;

    ///Un manager de chunks pour un carré de 500 m de côté et un total de 5*5 = 25 chunks
    NzTerrainChunksManager chunksManager(500.f,5);

    //NzTerrainChunk c1,c2,c3;

    NzBoundingVolumef box(0.f,0.f,0.f,100.f,50.f,100.f);
    box.Update(NzMatrix4f::Identity());
    NzBoundingVolumef box2(0.f,0.f,0.f,100.f,50.f,100.f);
    box2.Update(NzMatrix4f::Identity());

    NzTerrainNodeID id(1,0,0);
    NzTerrainNodeID id2(1,1,0);
    NzTerrainNodeID id3(1,1,1);
    NzTerrainNodeID id4(1,0,1);

    unsigned int index;
    std::array<float,150> data;
    for(int y(0) ; y < 5 ; ++y)
        for(int x(0) ; x < 5 ; ++x)
        {
            index = (x + 5 * y)*6;
            //On génère une grille
            data.at(index) = x * 25.f;
            data.at(index + 1) = 0.f;
            data.at(index + 2) = y * 25.f;
            //Normales vers le haut
            data.at(index + 3) = 0.f;
            data.at(index + 4) = 1.f;
            data.at(index + 5) = 0.f;
        }

    if(!chunksManager.AddMesh(data,box,id))
            std::cout<<"Impossible d'ajouter le mesh 1"<<std::endl;

    //if(!c1.AddMesh(data,box,id))
      //  std::cout<<"Impossible d'ajouter le mesh 1"<<std::endl;

    for(int y(0) ; y < 5 ; ++y)
        for(int x(0) ; x < 5 ; ++x)
        {
            index = (x + 5 * y)*6;
            //On génère une grille
            data.at(index) = x * 25.f + 150.f;
            data.at(index + 1) = 0.f;
            data.at(index + 2) = y * 25.f;
            //Normales vers le haut
            data.at(index + 3) = 0.f;
            data.at(index + 4) = 1.f;
            data.at(index + 5) = 0.f;
        }
    if(!chunksManager.AddMesh(data,box,id2))
            std::cout<<"Impossible d'ajouter le mesh 1"<<std::endl;
    //if(!c1.AddMesh(data,box,id2))
      //  std::cout<<"Impossible d'ajouter le mesh 2"<<std::endl;

    for(int y(0) ; y < 5 ; ++y)
        for(int x(0) ; x < 5 ; ++x)
        {
            index = (x + 5 * y)*6;
            //On génère une grille
            data.at(index) = x * 25.f + 300.f;
            data.at(index + 1) = (rand() % 5) * 10.f;
            data.at(index + 2) = y * 25.f;
            //Normales vers le haut
            data.at(index + 3) = 0.f;
            data.at(index + 4) = 1.f;
            data.at(index + 5) = 0.f;
        }
    if(!chunksManager.AddMesh(data,box,id3))
            std::cout<<"Impossible d'ajouter le mesh 1"<<std::endl;
    //if(!c1.AddMesh(data,box,id3))
      //  std::cout<<"Impossible d'ajouter le mesh 2"<<std::endl;

    for(int y(0) ; y < 5 ; ++y)
        for(int x(0) ; x < 5 ; ++x)
        {
            index = (x + 5 * y)*6;
            //On génère une grille
            data.at(index) = x * 25.f + 450.f;
            data.at(index + 1) = 0.f;
            data.at(index + 2) = y * 25.f;
            //Normales vers le haut
            data.at(index + 3) = 0.f;
            data.at(index + 4) = 1.f;
            data.at(index + 5) = 0.f;
        }
    if(!chunksManager.AddMesh(data,box,id4))
            std::cout<<"Impossible d'ajouter le mesh 1"<<std::endl;

    //if(!c1.AddMesh(data,box,id4))
    //    std::cout<<"Impossible d'ajouter le mesh 3"<<std::endl;

    //if(!chunksManager.RemoveMesh(box,id))
    //    std::cout<<"Impossible de supprimer le mesh 3"<<std::endl;

    //if(!c1.RemoveMesh(id2))
    //    std::cout<<"Impossible de supprimer le mesh3"<<std::endl;

    //if(!c1.RemoveMesh(id3))
     //   std::cout<<"Impossible de supprimer le mesh 2"<<std::endl;


    ////////////////////////////

    ///Code classique pour ouvrir une fenêtre avec Nazara
    NzString windowTitle("Terrain Renderer example");
	NzRenderWindow window(NzVideoMode(800,600,32),windowTitle,nzWindowStyle_Default);
	window.SetFramerateLimit(100);
	window.EnableVerticalSync(false);
	window.SetCursor(nzWindowCursor_None);

	/// Caméra
	//NzVector3f camPos(-2000.f, 1800.f, 2000.f);
	//NzVector3f camPos(7241.f, 12618.f, 3130.f);
	NzVector3f camPos(-100.f, 230.f, 34.f);
	NzEulerAnglesf camRot(-30.f, -90.f, 0.f);
	NzCamera camera;
	camera.SetPosition(camPos);
	camera.SetRotation(camRot);
	camera.SetFOV(70.f);
	camera.SetZFar(10000.f);
	camera.SetZNear(0.5f);
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

    NzRenderStates renderStates;
    renderStates.parameters[nzRendererParameter_DepthBuffer] = true;

    NzClock deformationClock;





	///L'index buffer
   /* unsigned int rowIndex[24];

    for(int i(0) ; i < 4 ; ++i)
    {
        rowIndex[i*6] = i;
        rowIndex[i*6+1] = i + 1;
        rowIndex[i*6+2] = i + 6;
        rowIndex[i*6+3] = i;
        rowIndex[i*6+4] = i + 5;
        rowIndex[i*6+5] = i + 6;
    }

    std::array<nzUInt16,96> indexdata;

    NzIndexBuffer indexBuf(false, 384, nzBufferStorage_Hardware);
    for(unsigned int k(0) ; k < 4 ; ++k)
    {
        for(unsigned int i(0) ; i < 4 ; ++i)
            for(unsigned int j(0) ; j < 24 ; ++j)
            {
                indexdata[i*24+j] = static_cast<nzUInt16>(rowIndex[j] + i*5 + 25 *k);
            }
        indexBuf.Fill(indexdata.data(), k*96, 96);
    }

	/// Le vertex buffer
	//std::array<float,150> data;
    //int index = 0;

    NzVertexBuffer buf(NzVertexDeclaration::Get(nzVertexLayout_XYZ_Normal),100,nzBufferStorage_Hardware,nzBufferUsage_Static);

    for(int k(0) ; k < 4 ; ++k)
    {
        for(int y(0) ; y < 5 ; ++y)
            for(int x(0) ; x < 5 ; ++x)
            {
                index = (x + 5 * y)*6;
                //On génère une grille
                data.at(index) = x * 100.f + 500.f * k;
                data.at(index + 1) = 0.f;
                data.at(index + 2) = y * 100.f;
                //Normales vers le haut
                data.at(index + 3) = 0.f;
                data.at(index + 4) = 1.f;
                data.at(index + 5) = 0.f;
            }
        buf.Fill(data.data(),k*25,25);
    }*/







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

            float speed2 = (NzKeyboard::IsKeyPressed(NzKeyboard::Key::LShift)) ? camSpeed*5: camSpeed;
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



        camera.Activate();

        //NzRenderer::SetClearColor(25, 25, 25);
        //NzRenderer::Clear(nzRendererClear_Color | nzRendererClear_Depth);
		scene.Update();
		scene.Cull();
		scene.UpdateVisible();
		scene.Draw();

		//NzRenderer::SetMatrix(nzMatrixType_World, NzMatrix4f::Identity());
		//NzBoxf bbox(-10.f,10.f,10.f,100.f,100.f,100.f);
		//NzDebugDrawer::Draw(bbox);

      /*  NzRenderer::SetRenderStates(renderStates);
        NzRenderer::SetFaceFilling(nzFaceFilling_Line);
        NzRenderer::SetShaderProgram(NzTerrainRenderer::GetShader());
		NzRenderer::SetVertexBuffer(&buf);
		NzRenderer::SetIndexBuffer(&indexBuf);
        NzRenderer::DrawIndexedPrimitives(nzPrimitiveMode_TriangleList,48,288);*/

		// Dessin des chunks
		NzRenderer::SetMatrix(nzMatrixType_World, NzMatrix4f::Identity());

		NzRenderer::SetFaceFilling(nzFaceFilling_Line);
		NzRenderer::SetShaderProgram(NzTerrainRenderer::GetShader());
        NzRenderer::SetIndexBuffer(NzTerrainRenderer::GetIndexBuffer());
//        NzTerrainRenderer::DrawTerrainChunk(c1);
        //NzTerrainRenderer::DrawTerrainChunk(c2);
        //NzTerrainRenderer::DrawTerrainChunk(chunk3);

        chunksManager.DrawChunks();

        //On teste la maj du chunk
        for(int y(0) ; y < 5 ; ++y)
            for(int x(0) ; x < 5 ; ++x)
            {
                index = (x + 5 * y)*6;
                //On génère une grille
                data.at(index) = x * 25.f;
                data.at(index + 1) = sin(x * deformationClock.GetMilliseconds() / 1000.f) * 25.f + 25.f;
                data.at(index + 2) = y * 25.f;
                //Normales vers le haut
                data.at(index + 3) = 0.f;
                data.at(index + 4) = 1.f;
                data.at(index + 5) = 0.f;
            }

       chunksManager.UpdateMesh(data,box,id);

		// Nous mettons à jour l'écran
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
/*
	NzBufferMapper<NzVertexBuffer> mapper(buf,nzBufferAccess_ReadOnly);
	const float* vertices = reinterpret_cast<const float*>(mapper.GetPointer());

	for(int i(0) ; i < 75 ; ++i)
        std::cout<<vertices[i*6]<<" ; "<<vertices[i*6+1]<<" ; "<<vertices[i*6+2]<<" | "
                 <<vertices[i*6+3]<<" ; "<<vertices[i*6+4]<<" ; "<<vertices[i*6+5]<<std::endl;*/

	NzDebugDrawer::Uninitialize();

    return 0;
}
