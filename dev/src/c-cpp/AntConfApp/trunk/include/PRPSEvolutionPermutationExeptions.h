/**
 * @file PRPSEvolutionExeptions.h
 * Contains the exeption used during permutation in the PRPSEvolution - Project
 *
 */
#ifndef __PRPS_EVOLUTION_PERMUTATION_EXEPTIONS_H_
	#define __PRPS_EVOLUTION_PERMUTATION_EXEPTIONS_H_

	#include <iostream>
	#include <exception>

namespace PRPSEvolution {
	namespace Exeptions {
		namespace Permutation {

			class Init: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "Expetion during initialization of Permutation class";

				}
			} InitExeption;

			class Calculation: public std::exception
			{
				virtual const char* what() const throw()
				{
					return "Something went wrong during calculation";

				}
			} CalculationExeption;

		}
	}
}

#endif /* !_ __PRPS_EVOLUTION_PERMUTATION_EXEPTIONS_H_ */