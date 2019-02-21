#include <stdexcept>

using namespace std;

#include <access/GpioInputPin.h>
#include <access/GpioInputPort.h>

GpioAccess::GpioInputPort::GpioInputPort(int* bitsIds, int bitCount,bool pullUp):
        GpioPort(bitCount) {
    inputBits = new GpioInputPin[bitCount];
    for (int i = 0; i < bitCount; ++i) {
        inputBits[i] = GpioAccess::GpioInputPin(bitsIds[i], pullUp);
    }
}

GpioAccess::GpioInputPort::~GpioInputPort() {
    delete [] inputBits;
}

unsigned int GpioAccess::GpioInputPort::read() {
    unsigned int tmpData = 0;
    bool bit = false;
    int power = 1;

    /* Convirtiendo de binario a decimal */
    for (unsigned int i = 0; i < bitCount; ++i) {
        bit = inputBits[i].read();
        tmpData += bit * power;
        power *= 2;
    }

    return tmpData;
}

bool GpioAccess::GpioInputPort::operator [](unsigned int pos) {
    if (pos >= bitCount) {
        throw new runtime_error("Error: posición fuera de rango.");
    }
    return inputBits[pos].read();
}

