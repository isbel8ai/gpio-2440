#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioPort_h__
#define __GpioAccess__GpioPort_h__


#define MAX_PORT_SIZE sizeof(int) * 8

namespace GpioAccess
{	
    /**
     * GpioPort es la clase base para los bus de datos de entrada y salida.
     */
    class GpioPort
	{
		public:
            /**
             * Constructor de GpioPort.
             * @param pBitCount es la cantidad de bits del bus datos.
             * @throw runtime_error.
             */
            GpioPort(unsigned int bitCount);

        protected:
            /**
             * bitCount almacena la cantidad de bits del bus de datos.
             */
            unsigned int bitCount;

	};
}

#endif
