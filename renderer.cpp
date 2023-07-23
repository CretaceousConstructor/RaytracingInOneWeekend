#include "Renderer.h"


Renderer::Renderer() :
     result("Picture.ppm", std::ofstream::out)
{

}


void Renderer::StartToRender()
{
	first_scene.render(result);
	//cam->render_scence(world, result);
}


Renderer::~Renderer()
{

	result.close();
	system("OpenPic.bat");


}
