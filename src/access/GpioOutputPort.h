#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioOutputPort_h__
#define __GpioAccess__GpioOutputPort_h__

#include <access/GpioPort.h>

namespace GpioAccess
{
    class GpioOutputPin;
}

namespace GpioAccess
{
    /**
     * GpioInputPort es la clase que define las funcionalidades de un bus de
     * salida.
     */
    class GpioOutputPort: public GpioAccess::GpioPort
	{
        public:
            /**
             * Constructor de GpioOutputPort.
             * @param bitsIds es un arreglo de enteros los cuales corresponden
             * con los identificadores de los puertos que conforman el bus de
             * salida.
             * @param pBitCount cantidad de bits del bus de salida.
             * @param initState es un entero positivo que define el estado
             * inicial del bus de salida.
             * @throw runtime_error.
             */
            GpioOutputPort(int* bitsIds, int bitCount,
                    unsigned int initState = 0);
            ~GpioOutputPort();

            /**
             * La función write establece el estado del bus de salida.
             * @param state es un entero positivo el cual se establecerá como
             * salida del bus.
             * @throw runtime_error.
             */
            void write(unsigned int state);
            GpioAccess::GpioOutputPin operator [](unsigned int pos);

        protected:
            /**
             * outputBits es un arreglo GpioOutputPort que almacena los puertos
             * de salida que conforman el bus.
             */
            GpioAccess::GpioOutputPin* outputBits;

	};
}

#endif
