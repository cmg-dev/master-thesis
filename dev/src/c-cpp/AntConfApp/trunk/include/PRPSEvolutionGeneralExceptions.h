/**
 * @file PRPSEvolutionGeneralExeptions.h
 * Contains the exeption used in the PRPSEvolution - Project
 * 
 */

#ifndef __PRPS_EVOLUTION_GENERAL_EXEPTIONS_H_
	#define __PRPS_EVOLUTION_GENERAL_EXEPTIONS_H_

#include <iostream>
#include <exception>
#include <string>

namespace PRPSEvolution {
	namespace Exceptions {
		namespace General {
	
			/**
			 * Throw this if a Method is not implemented
			 *
			 */
			struct NotImplemented : std::exception {
				const char* what() const noexcept { return "Not implemented!\n"; }
				
			};

		}
	}
}

#endif /* !__PRPS_EVOLUTION_GENERAL_EXEPTIONS_H_ */