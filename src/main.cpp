#include "Engine.h"



//Resize
int main() {
	Engine::instance->setup(1000,800,true);

	Engine::instance->run();

	return 0;
}
