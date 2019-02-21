#include <stdexcept>

using namespace std;

#include <access/GpioOutputPin.h>
#include <access/GpioOutputPort.h>

GpioAccess::GpioOutputPort::GpioOutputPort(int* bitsIds, int bitCount,
        unsigned int initState):GpioPort(bitCount) {
    if (initState >= (unsigned int)(1 << bitCount)) {
        throw new runtime_error("Error: valor fuera de rango.");
    }
    unsigned int tmpData = initState;
    bool bit = false;
    outputBits = new GpioOutputPin[bitCount];
    for (int i = 0; i < bitCount; ++i) {
        bit = (tmpData % 2);
        tmpData /= 2;
        outputBits[i] = GpioAccess::GpioOutputPin(bitsIds[i], bit);
    }
}

GpioAccess::GpioOutputPort::~GpioOutputPort() {    
    delete [] outputBits;
}

void GpioAccess::GpioOutputPort::write(unsigned int state) {
    if (state >= (unsigned int)(1 << bitCount)) {
        throw new runtime_error("Error: valor fuera de rango.");
    }
    unsigned int tmpData = state;
    bool bit = false;

    /* Convirtiendo de decimal a binario */
    for (unsigned int i = 0; i < bitCount; ++i) {
        bit = (tmpData % 2);
        tmpData /= 2;        
        outputBits[i].write(bit);
    }
}

GpioAccess::GpioOutputPin GpioAccess::GpioOutputPort::operator [](unsigned int pos) {
    if (pos >= bitCount) {
        throw new runtime_error("Error: posición fuera de rango.");
    }
    return outputBits[pos];
}

