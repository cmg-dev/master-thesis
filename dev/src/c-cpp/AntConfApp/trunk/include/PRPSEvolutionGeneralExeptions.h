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
	namespace Exeptions {
		namespace General {

// 			struct MyException : public std::exception
// 			{
// 				std::string s;
// 				MyException(std::string ss) : s(ss) {}
// 				virtual const char* what() const noexcept { return s.c_str(); }
// 			}
// 
// 			/**
// 			 * Throw this if a Method is not implemented
// 			 * 
// 			 */
// 			class NotImplemented: public std::exception
// 			{
// 				virtual const char* what() const noexcept
// 				{
// 					return "Not implemented";
// 
// 				}
// 			} NotImplementedExeption;
// 
// // 			class MalformedInput: public std::exception
// // 			{
// // 				virtual const char* what() const throw()
// // 				{
// // 					return "Input is not formed properly";
// // 
// // 				}
// // 			} MalformedInputExeption;
			
		}
	}
}

#endif /* !__PRPS_EVOLUTION_GENERAL_EXEPTIONS_H_ */