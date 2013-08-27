#include "Generator.hpp"

Generator::Generator()
{
    srand(123456789);
    ambient = new NzFBM3D(SIMPLEX,123456789);
    imgx = 2048;
    imgy = 1536;
    ambientLayer.Create(nzImageType_2D,nzPixelFormat_RGBA8,imgx,imgy);
    starLayer.Create(nzImageType_2D,nzPixelFormat_RGBA8,imgx,imgy);


}

Generator::~Generator()
{
    delete ambient;
}

void Generator::BlendLayers(NzImage& finalImage)
{
    NzColor c1,c2,c3;
    for(unsigned int i(0) ; i < imgx ; ++i)
        for(unsigned int j(0) ; j < imgy ; ++j)
        {
            c1 = ambientLayer.GetPixelColor(i,j);
            c2 = starLayer.GetPixelColor(i,j);
            c3 = NzColor::Blend(c1,c2,nzColorBlendingMode_Lighten);
            finalImage.SetPixelColor(c3,i,j);
        }
}

void Generator::ComputeAmbientColor(unsigned x, unsigned y, const NzVector3f& p)
{
    float ambientRes = 1/400.f;

    float lsb, density;

    // Ajouter un faible offset aléatoire ( +- 1 LSB) au calcul de bruit permet d'effacer
    // l'artéfact provoqué par un gradient très doux, à savoir des cassures très visibles
    // Il donne également un grain à l'image et la rend plus réaliste
    lsb = (rand() % 100 - 50)/(100.f * 15.f);
    // Calcul du bruit (un fbm3D), on ajuste l'intervalle à [0;1]
    density = ambient->GetValue(p.x,p.y,p.z,ambientRes) * 0.5 + 0.5 + lsb;
    // On se sert d'un gradient généré sous inkscape pour choisir une couleur associée à la densité
    ambientLayer.SetPixelColor(ambientColormap.GetPixelColor(0,static_cast<unsigned int>(density * 255.f)),x,y);
}

void Generator::ComputeForStars(const NzVector3f& p)
{

}

void Generator::DrawSingleStar(unsigned int x, unsigned int y, float innerRadius, float falloffRadius, float falloff)
{
    float distance, density, lsb;
    unsigned int xc, yc;
    NzVector2ui pixel;

    for(int i(static_cast<int>(- falloffRadius)) ; i <= static_cast<int>(falloffRadius) ; ++i)
        for(int j(static_cast<int>(- falloffRadius)) ; j <= static_cast<int>(falloffRadius) ; ++j)
        {
            if(i*i + j*j < static_cast<int>(falloffRadius * falloffRadius))
            {

                float distance = std::sqrt(static_cast<float>(i*i + j*j)) - innerRadius;
                float density = 255.f * std::exp(- falloff * distance);

                if(i*i + j*j < static_cast<int>(innerRadius * innerRadius))
                    density = 255.f;

                lsb = (rand() % 100 - 50)/(50.f);

                pixel.x = x + i;
                pixel.y = y + j;

                //pixel = IndexWrap(pixel);

                starLayer.SetPixelColor(NzColor(static_cast<nzUInt8>(density + lsb)),pixel.x,pixel.y);
            }
        }
}



void Generator::Generate(NzImage& image)
{
    NzVector3f p;

    if(!ambientColormap.LoadFromFile("resources/ambientColormap.png"))
        return;

    float offset = static_cast<float>(tileSize);
    NzVector3f center(offset/2.f);

    //FRONT
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = 0.f;
            p.y = static_cast<float>(-j) + offset;
            p.z = static_cast<float>(-i) + offset;

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i,j + tileSize,p);
        }

    //BACK
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = offset;
            p.y = static_cast<float>(-j) + offset;
            p.z = static_cast<float>(i);

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i + 2 * tileSize,j + tileSize,p);
        }


    //BOTTOM
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = static_cast<float>(i);
            p.y = 0.f;
            p.z = static_cast<float>(j);

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i + tileSize,j + 2 * tileSize,p);
        }

    //TOP
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = static_cast<float>(i);
            p.y = offset;
            p.z = static_cast<float>(-j) + offset;

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i + tileSize,j,p);
        }

    //RIGHT
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = static_cast<float>(i);
            p.y = static_cast<float>(-j) + offset;
            p.z = 0.f;

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i + tileSize,j + tileSize,p);
        }

    //LEFT
    for(int i(0) ; i < tileSize ; ++i)
        for(int j(0) ; j < tileSize ; ++j)
        {
            p.x = static_cast<float>(-i) + offset;
            p.y = static_cast<float>(-j) + offset;
            p.z = offset;

            p = (p - center).Normalize();
            p *= offset * 0.5f;

            ComputeAmbientColor(i + 3 * tileSize,j + tileSize,p);
        }
    DrawSingleStar(712,712,33.f,37.f,1.f);
    BlendLayers(image);
}

NzVector2ui Generator::IndexWrap(NzVector2ui coordinates)
{
    NzVector2ui wrap = coordinates;
    wrap /= tileSize;

    if(wrap.x > 3)
        coordinates.x -= 4 * tileSize;

    if(wrap.x < 0)
        coordinates.x += 4 * tileSize;

    if(wrap.y > 2)
        coordinates.y -= 3 * tileSize;

    if(wrap.y < 0)
        coordinates.y += 3 * tileSize;

    //if(wrap.x + wrap.y == 0)
      // (coordinates.x >= 2 * tileSize && coordinates.x < 3 * tileSize))

    return coordinates;
}

NzVector2ui FromSphereToCube(const NzVector3f& p)
{
    float R1,R2;
    NzVector2i uv;

    p.x > p.z ? R1 = p.x : p.z;
    p.x > p.y ? R2 = p.x : p.y;

    // Position par rapport au centre d'une face d'un cube de côté 2
    uv.x = static_cast<int>(std::sqrt(R1*R1 - 1));
    uv.y = static_cast<int>(std::sqrt(R2*R2 - 1));

}




