#include "Engine.h"



//Resize
int main() {
	Engine::instance->setup(1000,800,true);

	Engine::instance->run();

	return 0;
}


/* TODO
 * 1) Lire des .obj ou .fbx
 * 1.5) DSA
 * 2) Classe Renderer : Classe qui parcours tous les objets afin de leurs appliquer leurs matériaux et de les rendre
 * 3) Classe Material : Une classe ou struct qui contient les parametres à passer au shader correspondant
 * 4) Classe Light : comme object, une pos et des parametres d'éclairage
 * 5) Classe Scene : contient une light et n objets à rendre
 *
 * */
