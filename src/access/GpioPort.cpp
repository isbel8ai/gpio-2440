#include <stdexcept>

using namespace std;

#include <access/GpioPort.h>

GpioAccess::GpioPort::GpioPort(unsigned int bitCount) {
    if (bitCount > MAX_PORT_SIZE) {
        throw new runtime_error("Error al establecer longitud del puerto.");
    }    
    this->bitCount = bitCount;
}

