/**
 *	This file contains structures and classes belonging to the system itself
 * 
 */

#ifndef _PRPS_SYSTEM_H_
	#define _PRPS_SYSTEM_H_

// #include <stdio.h>
// #include <stdlib.h>
// #include <iterator>
// #include<fstream>
// #include<sstream>
// #include<string>
// #include <iostream>
// #include <algorithm>
// #include <array>

namespace PRPSEvolution {

	struct Constants {
		double a_1;
		double a_2;

		double lambda;
		double f_mess;
		double c_0;

		Constants() {
			a_1 = a_2 = lambda = f_mess = c_0 = 0.0;
			
		}

		Constants( const PRPSEvolution::Constants &c ) : a_1(c.a_1 ),
														a_2( c.a_2 ),
														lambda( c.lambda ),
														f_mess( c.f_mess ),
														c_0( c.c_0 ) { }
		
	};

	struct System {
		PRPSEvolution::Constants constants;
		std::string fn;

		/**
		 * 
		 */
		System() {
			fn = "PRPS/PRPS.ini";
			if( rPRPSIniFile() < 0 )
				std::cout << "Error while loading PRPS.ini" << std::endl;
			
		}

		/** copy constructor */
		System( const PRPSEvolution::System &s ) : fn(s.fn), constants(s.constants){
// 				fn = s.fn;
// 				constants = s.constants;

		}
		
		/**
		 *
		 */
		int rPRPSIniFile() {
			std::ifstream	file ( fn );
			std::string		line;
			int				valuesRead;
			int				linesRead;

			valuesRead = linesRead = 0;

			/* read out the file **************************************************/
			while( getline( file,line ) ) {
				std::stringstream   linestream( line );
				std::string         value;

				valuesRead = 0;
				while( getline( linestream, value, ',' ) ) {

						/* ignore the first line */
						if( linesRead == 0 ) continue;

						/* the constants */
						constants.c_0 = ( valuesRead == 0 ) ? std::stod( value ):( constants.c_0 ) ;
						constants.f_mess = ( valuesRead == 1 ) ? std::stod( value ):( constants.f_mess ) ;

						valuesRead++;

				}
				linesRead++;

			}
			file.close();

			/* check the input */
			if( linesRead != PRPSEvolution::EXPECTED_LINES_SYSTEM_INI_FILE )
				return PRPSError::FileIO::inputmalformed;

			/* caluculate the constants */
			if( constants.f_mess != 0.0 )
				constants.lambda = constants.c_0 / constants.f_mess;
			
			constants.a_1 = ( constants.lambda * constants.lambda ) / 8;
			constants.a_2 = constants.a_1 / M_PI;

			std::cout << "** INIT-System:: read the following values from: '" << fn << "'" << std::endl;
			std::cout << "c_0: " << constants.c_0 <<'\t'
						<< "f_mess: " << constants.f_mess <<'\t'
						<< "lambda: " << constants.lambda
						<< std::endl;
			std::cout << "a_1: " << constants.a_1 <<'\t'<< "a_2: " << constants.a_2 << std::endl;
			
			std::cout << "** Init complete" << std::endl << std::endl;
			
			return PRPSError::okay;

		}
		
	};
	
} /* !namespace N*/

#endif /* !PRPS_SYSTEM_ H_ */