#include <exception>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdexcept>

using namespace std;

#include <driver/gpio2440.h>
#include <access/GpioOutputPin.h>


GpioAccess::GpioOutputPin::GpioOutputPin(int gpioId, bool initState)
        :GpioPin(gpioId) {
    int ret = ioctlCmd(GPIOD_IOC_SETCFG, GPIOD_OUTP);
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
    write(initState);
}

void GpioAccess::GpioOutputPin::write(bool state) {
    int ret = ioctlCmd(GPIOD_IOC_SETDAT, (state ? GPIOD_ON : GPIOD_OFF));
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
}

void GpioAccess::GpioOutputPin::operator =(bool state) {
    write(state);
}

