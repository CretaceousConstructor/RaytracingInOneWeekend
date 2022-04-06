#include "renderer.h"
//#include <map>

std::mt19937 TrekMath::generator(12);

int main()
{
	//using iner_map  = std::map<std::string, int>;
	//using outer_map = std::map<iner_map, std::string>;
	//outer_map b;
	//b.insert(std::pair<iner_map, std::string>(iner_map{std::pair<std::string, int>("hello", 1)}, "null"));

	//iner_map::const_iterator  it_iner;
	//outer_map::iterator it_outer;
	//it_outer = b.begin();
	//it_iner = (it_outer->first).begin();

	renderer TrekRay;

	TrekRay.startToRender();

	TrekRay.cleanUp();
}

//void printVec4(glm::vec3 v) {
//
//	std::cout << v.x << " ";
//	std::cout << v.y << " ";
//	std::cout << v.z << " ";
//	std::cout << std::endl;
//
//}
