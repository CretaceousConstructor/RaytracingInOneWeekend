#include "renderer.h"


renderer::renderer() :
     result("Picture.ppm", std::ofstream::out)
{
}

void renderer::startToRender()
{
	first_scene.render(result);
	//cam->render_scence(w, result);
}

void renderer::cleanUp()
{
	result.close();
	system("OpenPic.bat");
}