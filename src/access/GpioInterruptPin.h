#include <stdexcept>

using namespace std;

#ifndef __GpioAccess__GpioInterruptPin_h__
#define __GpioAccess__GpioInterruptPin_h__

#include <driver/gpio2440.h>
#include <access/GpioPin.h>

namespace GpioAccess
{
    template <class T>
    /**
     * SignalAction es una estructura donde se almacena un puntero a objeto de
     * tipo T y un puntero a una funcion miembro de la misma clase del objeto.
     */
    struct SignalAction {
        T *object;
        void (T::*function)();
    };

    template <class T>
    /**
     * GpioInterruptPin es la clase que permite procesar las intrrupciones que
     * se generan en un puerto.
     */
    class GpioInterruptPin: public GpioAccess::GpioPin
    {
        public:
            /**
             * Constructor de GpioInterruptPin.
             * @param pGpioId es un entero que contiene el identificador del
             * puerto a utilizar.
             * @param pullUp es un valor booleano que define la configuración
             * del resistor pullup.
             * @param glitchFilter es un valor booleano que define la activación
             * del filtro de ruido.
             * @param object es un puntero a un objeto de tipo Tsobre el cual se
             * ejecutará la función action.
             * @param action es un puntero a una funcion miembro de la clase T.
             * Es la función que se ejecutará en caso de ocurrir la interrupción
             * externa correspondiente.
             * @param flags es un entero positivo el cual contiene las banderas
             * de configuración de detección de la interrupción externa.
             * @throw runtime_error.
             */
            GpioInterruptPin(int gpioId, bool pullUp = true,
                    bool glitchFilter = true, T *object = 0,
                    void (T::*action)() = 0, unsigned int flags = 0);

            /**
             * La función activate activa la deteccón de interrupción.
             * @throw runtime_error.
             */
            void activate();

            /**
             * La función deactivate desactiva la deteccón de interrupción.
             * @throw runtime_error.
             */
            void deactivate();           

        protected:
            /**
             * signalNumber es un entero positivo que almacena el número de la
             * señal que se recibirá en caso de ocurrir la interrupción
             * correspondiente.
             */
            int signalNumber;

            /**
             * flags es un entero positivo el cual almacena las banderas de
             * configuración de detección de la interrupción externa.
             */
            unsigned int eintFlags;

            /**
             * sigActions es un arreglo estático donde se almacena la
             * información necesaria para procesar las señales del resibidas del
             * sistema operativo.
             */
            static SignalAction<T> sigActions[GPIOD_SIGMAX];

             /**
             * La función handleSignal será ejecutada de forma estática al
             * recibir las señales del sistema operativo.
             * @param signum es un entero positivo que contendrá el número de la
             * señal recibida del sistema operativo.
             */
            static void handleSignal(int signum);

	};
}

#endif

#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

template <class T>
GpioAccess::SignalAction<T>
        GpioAccess::GpioInterruptPin<T>::sigActions[GPIOD_SIGMAX];

template <class T>
GpioAccess::GpioInterruptPin<T>::GpioInterruptPin(int gpioId, bool pullUp,
        bool glitchFilter, T *object, void (T::*action)(), unsigned int flags)
        :GpioPin(gpioId) {
    int ret = ioctlCmd(GPIOD_IOC_SETCFG, GPIOD_EINT);
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }

    /* Obteniendo número de señal desde el espacio kernel. */
    int signum = ioctlCmd(GPIOD_IOC_GETSIG, 0);
    if (signum < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
    signalNumber = signum;

    /* Mapeando la función correspondiente a al señal. */
    sigActions[GPIOD_SIG2EINT(signalNumber)].object = object;
    sigActions[GPIOD_SIG2EINT(signalNumber)].function = action;

    /* Configurando resistor pull up. */
    ioctlCmd(GPIOD_IOC_SETPUP, (pullUp ? GPIOD_PUPON : GPIOD_PUPOFF));

    /* Configurando filtro de ruido. */
    ioctlCmd(GPIOD_IOC_SETFLT,
            (glitchFilter ? GPIOD_IRQFLT_ON : GPIOD_IRQFLT_OFF));
    eintFlags = flags;
}

template <class T>
void GpioAccess::GpioInterruptPin<T>::activate() {

    /* Configurando captura de señal del sistema en el espacio usuario. */
    struct sigaction drvsig;
    drvsig.sa_handler = handleSignal;
    sigemptyset(&drvsig.sa_mask);
    drvsig.sa_flags = 0;
    drvsig.sa_flags |= SA_RESTART;
    sigaction(signalNumber, &drvsig, NULL);

    /* Configurando detección de interrupción en el espacio kernel. */
    int err = ioctlCmd(GPIOD_IOC_SETIRQ, eintFlags);
    if (err < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
}

template <class T>
void GpioAccess::GpioInterruptPin<T>::deactivate() {

    /* Desactivando detección de interrupcion en el espacio kernel. */
    int err = ioctlCmd(GPIOD_IOC_CLRIRQ, 0);
    if (err < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }

    /* Desactivando captura de señal del sistema en el espacio usuario. */
    struct sigaction drvsig;
    drvsig.sa_handler = SIG_DFL;
    sigemptyset(&drvsig.sa_mask);
    drvsig.sa_flags = 0;
    drvsig.sa_flags |= SA_RESTART;
    sigaction(signalNumber, &drvsig, NULL);
}

template <class T>
void GpioAccess::GpioInterruptPin<T>::handleSignal(int signum) {
    T *obj = sigActions[GPIOD_SIG2EINT(signum)].object;
    void (T::*func)() = sigActions[GPIOD_SIG2EINT(signum)].function;
    (obj->*func)();
}
