#include <global.h>
#include <checkArgs.hpp>

uint64_t* arreglo = nullptr;
uint64_t* arregloSecuencial = nullptr;
uint64_t* arregloParalelo = nullptr;
uint64_t sumaArreglo = 0;
std::vector<std::thread *> threads;
//std::vector<std::thread *> threadsSuma;
//std::mutex candado;


void fillArray(size_t beginIdx, size_t endIdx, size_t arrayType){
	for(size_t i = beginIdx; i < endIdx; i++){
		switch(arrayType){
			case 0:
				arregloSecuencial[i] = arreglo[i];
				break;
			case 1:
				arregloParalelo[i] = arreglo[i];
				break;
		}
	}
}


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
	std::cout << "Limite inferior: " << limInferior << std::endl;
	std::cout << "Limite superior: " << limSuperior << std::endl;


	//Etapa de llenado
	arreglo = new uint64_t[totalElementos];
	//std::srand(std::time(0));
	std::random_device device;
	std::mt19937 rng(device());
	std::uniform_int_distribution<> unif(limInferior,limSuperior);
	for(uint32_t i=0; i < totalElementos; i++){
		arreglo[i] = unif(rng);
	}

	//-------Secuencial-------
	arregloSecuencial = new uint64_t[totalElementos];

	auto start = std::chrono::high_resolution_clock::now();

	fillArray(0, totalElementos, 0);

	auto end = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto tiempoLlenadoTotal_S = elapsed.count();


	//-------Paralelo-------
	arregloParalelo = new uint64_t[totalElementos];

	for(size_t i=0; i < numThreads; i++){
		threads.push_back(new std::thread(fillArray, i*(totalElementos)/numThreads, (i+1)*(totalElementos)/numThreads, 1));
	}

	start = std::chrono::high_resolution_clock::now();

	for(auto &thFilled : threads){
		thFilled->join();
	}

	end = std::chrono::high_resolution_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
	auto tiempoLlenadoTotal_P = elapsed.count();

	std::cout << std::endl;

	//Etapa de suma

	//Secuencial

	//Paralelo

	//Etapa de Resulatados
	std::cout << "Suma total en paralelo: " << sumaArreglo << std::endl;
	std::cout << "------- Tiempos de ejecución --------" << std::endl;
	std::cout << "Tiempo Llenado Secuencial: " << tiempoLlenadoTotal_S << "[ms]" << std::endl;
	std::cout << "Tiempo Llenado Paralelo: " << tiempoLlenadoTotal_P << "[ms]" << std::endl;
	std::cout << "SpeedUp Etapa de Llenado: " << (double)tiempoLlenadoTotal_S/tiempoLlenadoTotal_P << std::endl;
	std::cout << "-------------------------------------" << std::endl;
	//std::cout << "Tiempo Suma Secuencial: " << tiempoTotalSuma_S << "[ms]" << std::endl;
	//std::cout << "Tiempo Suma Paralela: " << tiempoTotalSuma_P << "[ms]" << std::endl;
	//std::cout << "SpeedUp Etapa de Suma: " << (double)tiempoTotalSuma_S/tiempoTotalSuma_P << std::endl;

	return(EXIT_SUCCESS);
}

