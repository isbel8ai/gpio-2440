#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioOutputPin_h__
#define __GpioAccess__GpioOutputPin_h__

#include <access/GpioPin.h>

namespace GpioAccess
{
    /**
     * GpioInputPin es la clase que define las funcionalidades de un puerto de
     * salida.
     */
    class GpioOutputPin: public GpioAccess::GpioPin
	{
		public:
            /**
             * Constructor de GpioOutputPin.
             * @param pGpioId es un entero que contiene el identificador del
             * puerto a utilizar.
             * @param initState es un valor booleano que define el estado
             * inicial del puerto de salida.
             * @throw runtime_error.
             */
            GpioOutputPin(int gpioId = 0, bool initState = false);

            /**
             * La función write establece el estado del puerto de salida.
             * @param state es un valor booleano el cual se establecerá como
             * salida del puerto.
             * @throw runtime_error.
             */
            void write(bool state);
            void operator =(bool state);

	};
}

#endif
