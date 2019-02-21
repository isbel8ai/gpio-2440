#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioInputPin_h__
#define __GpioAccess__GpioInputPin_h__

#include <access/GpioPin.h>

namespace GpioAccess
{
    /**
     * GpioInputPin es la clase que define las funcionalidades de un puerto de
     * entrada.
     */
    class GpioInputPin: public GpioAccess::GpioPin
	{
		public:           
            /**
             * Constructor de GpioInputPin.
             * @param pGpioId es un entero que contiene el identificador del
             * puerto a utilizar.
             * @param pullUp alor booleano que define la configuracion del
             * resistor pullup.
             * @throw runtime_error.
             */
            GpioInputPin(int gpioId = 0, bool pullUp = true);            

	};
}

#endif
