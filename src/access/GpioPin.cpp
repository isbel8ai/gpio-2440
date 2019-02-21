#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <stdexcept>

using namespace std;

#include <access/GpioPin.h>
#include <driver/gpio2440.h>

int GpioAccess::GpioPin::file = 0;

GpioAccess::GpioPin::GpioPin(int pGpioId) {
    gpioId = pGpioId;
    if (file == 0) {
        file = open(GPIOD_DEVPATH, O_RDWR);
        if (file == -1) {
            throw new runtime_error("Error al abrir el fichero" GPIOD_DEVPATH);
        }
    }
}

int GpioAccess::GpioPin::ioctlCmd(unsigned int cmd, unsigned int value) {
    struct gpiod_ioc_args cmdargs;
    cmdargs.pid = getpid();
    cmdargs.pin = gpioId;
    cmdargs.value = value;
    return ioctl(file, cmd, &cmdargs);
}

bool GpioAccess::GpioPin::read() {
    int ret = ioctlCmd(GPIOD_IOC_GETDAT, 0);
    if (ret < 0) {
        throw new runtime_error("Error al ejecutar comando ioctl.");
    }
    return ret;
}
