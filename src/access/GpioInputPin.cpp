#include <sys/ioctl.h>
#include <unistd.h>
#include <stdexcept>

using namespace std;

#include <driver/gpio2440.h>
#include <access/GpioInputPin.h>

GpioAccess::GpioInputPin::GpioInputPin(int gpioId, bool pullUp)
        :GpioPin(gpioId) {
    int ret = ioctlCmd(GPIOD_IOC_CONFIG, GPIOD_INP);
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
    ret = ioctlCmd(GPIOD_IOC_SETPUP, (pullUp ? GPIOD_PUPON : GPIOD_PUPOFF));
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
}

