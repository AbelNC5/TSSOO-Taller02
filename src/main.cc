#include <global.h>
#include <checkArgs.hpp>


void fillArray(size_t )

int main(int argc, char** argv){

	uint64_t totalElementos;
	uint32_t numThreads;
	uint32_t limInferior;
	uint32_t limSuperior;

	auto argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);

	totalElementos = argumentos->getArgs().tamProblema;
	numThreads     = argumentos->getArgs().numThreads;
	limInferior    = argumentos->getArgs().limInferior;
	limSuperior    = argumentos->getArgs().limSuperior;

	std::cout << "Elementos: " << totalElementos << std::endl;
	std::cout << "Threads  : " << numThreads     << std::endl;
	std::cout << "Limite inferior aleatorio: " << limInferior << std::endl;
	std::cout << "Limite superior aleatorio: " << limSuperior << std::Endl;


	//Etapa de llenado



	//Etapa de suma



	return(EXIT_SUCCESS);
}

