#include "Engine.h"



//Resize
int main() {
	Engine::instance->setup(1000,800,true);

	Engine::instance->run();

	return 0;
}


/* TODO
 *
 * Classe Renderer
 * Classe Material
 * Classe Light
 * Classe Scene
 *
 * */
