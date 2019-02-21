#include <exception>

using namespace std;

#ifndef __GpioAccess__GpioPin_h__
#define __GpioAccess__GpioPin_h__

namespace GpioAccess
{
    /**
     * GpioPin es la clase base para los puertos GPIO
     */
    class GpioPin
    {        
        public:
            /**
             * Constructor de GpioPin.
             * @param pGpioId es un entero que contiene el identificador del
             * puerto a utilizar.
             * @throw runtime_error.
             */
            GpioPin(int pGpioId);

            /**
             * La función read lee el valor presente en un puerto.
             * @return Devuelve un valor booleano positivo correspondiente a la
             * lectura del bus de entrada.
             * @throw runtime_error.
             */
            bool read();

        protected:
            /**
             * La función ioctlCmd es la encargada de hacer el llamado ioctl al
             * driver.
             * @param cmd es un valor entero positivo que corresponde el comando
             * a ejecutar.
             * @param value es un valor entero positivo el cual va a utilizar el
             * comando si es necesario.
             * @return Devuelve el valor entero retornado por la ejecución del
             * comando ioctl cmd.
             */
            int ioctlCmd(unsigned int cmd, unsigned int value = 0);

            /**
             * gpioId es un entero que contiene el identificador del puerto.
             */
            int gpioId;

            /**
             * file es un entero que elmacena del descriptor del fichero de
             * acceso al driver gpio (en linux /dev/gpio2440).
             */
            static int file;

	};
}

#endif
