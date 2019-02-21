#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioInputPort_h__
#define __GpioAccess__GpioInputPort_h__

#include <access/GpioPort.h>

namespace GpioAccess
{
    class GpioInputPin;
}

namespace GpioAccess
{
    /**
     * GpioInputPort es la clase que define las funcionalidades de un bus de
     * entrada.
     */
    class GpioInputPort: public GpioAccess::GpioPort
	{
        public:
            /**
             * Constructor de GpioInputPort.
             * @param bitsIds es un arreglo de enteros los cuales corresponden
             * con los identificadores de los puertos que conforman el bus de
             * entrada.
             * @param pBitCount cantidad de bits del bus de entrada.
             * @param pullUp valor booleano que define la configuracion del
             * resistor pullup.
             */
            GpioInputPort(int* bitsIds, int bitCount, bool pullUp = true);
            ~GpioInputPort();

            /**
             * La función read lee el valor presente en el bus.
             * @return Devuelve un valor entero positivo correspondiente a la
             * lectura del bus de entrada.
             * @throw runtime_error.
             */
             unsigned int read();
             bool operator [] (unsigned int pos);

        protected:
             /**
             * inputBits es un arreglo donde se almacenan los puertos que
             * componen el bus de entrada.
             */
            GpioAccess::GpioInputPin* inputBits;

	};
}

#endif
