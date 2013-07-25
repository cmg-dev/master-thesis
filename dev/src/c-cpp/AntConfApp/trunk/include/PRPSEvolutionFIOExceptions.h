/**
 * @file PRPSEvolutionFIOExeptions.h
 * Exeptions of file IO
 *
 */
#ifndef __PRPS_EVOLUTION_FIO_EXEPTIONS_H_
	#define __PRPS_EVOLUTION_FIO_EXEPTIONS_H_

#include <iostream>
#include <exception>

namespace PRPSEvolution {
	namespace Exceptions {
		namespace FileIO {

			/**
			 *
			 */
			struct FileNotFound : std::exception {
				const char* what() const noexcept { return "File not Found\n"; }

			};

			/**
			 *
			 */
			struct MalformedInput : std::exception {
				const char* what() const noexcept { return "Input is not formed properly\n"; }

			};

			/**
			 *
			 */
			struct OutputFailure : std::exception {
				const char* what() const noexcept { return "Output to file failed\n"; }

			};
		}
	}
}

#endif /* !_ __PRPS_EVOLUTION_FIO_EXEPTIONS_H_ */