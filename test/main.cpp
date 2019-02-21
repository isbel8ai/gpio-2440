#include <QDebug>
#include <typeinfo>

#include <driver/gpio2440.h>
#include <driver/regs-gpio.h>

#include <access/GpioInputPin.h>
#include <access/GpioOutputPin.h>
#include <access/GpioInterruptPin.h>

#include <access/GpioInputPort.h>
#include <access/GpioOutputPort.h>

using namespace GpioAccess;

class TestClass
{
    private:
        int intrCount;

    public:
        TestClass() {
            intrCount = 0;
        }

        void action() {
            qDebug() << "Interrupt: " << ++intrCount;
        }
};

int mainInport ()
{
    GpioInputPin gpf2(S3C2410_GPF(2), true);

    while (1) {
        qDebug() << "Input port GPF2: " << (gpf2.read() ? 1 : 0);
        sleep(1);
    }

    return 0;
}

int mainOutport ()
{
    GpioOutputPin gpg5(S3C2410_GPG(5), false);
    bool enable = false;

    while (1) {
        enable = !enable;
        gpg5.write(enable);
        qDebug() << "Output port GPG5: " << (enable ? 1 : 0);
        sleep(1);
    }

    return 0;
}

int mainInbus ()
{
    int bits[] = {
    S3C2410_GPG(5),
    S3C2410_GPG(2),
    S3C2410_GPE(13),
    S3C2410_GPE(12),
    S3C2410_GPE(11),
    S3C2410_GPF(1),
    S3C2410_GPF(3),
    S3C2410_GPG(0)
    };

    GpioInputPort inbus(bits, 8, true);

    while (1) {
        qDebug() << "Input bus: " << inbus.read();
        sleep(1);
    }

    return 0;
}

int mainOutbus ()
{
    unsigned int value = 0;
    bool on = false;

    int bits[] = {
    S3C2410_GPG(5),
    S3C2410_GPG(2),
    S3C2410_GPE(13),
    S3C2410_GPE(12),
    S3C2410_GPE(11),
    S3C2410_GPF(1),
    S3C2410_GPF(3),
    S3C2410_GPG(0)
    };

    GpioOutputPort outbs(bits, 8, 0);

    while (1) {
        if (value == 0) {
            on = true;
        } else if (value == 255) {
            on = false;
        }
        value = ((value << 1) + (on ? 1 : 0)) & 0xff;
        outbs.write(value);
        usleep(100000);
    }
    return 0;
}

int mainIntr ()
{
    TestClass obj;
//    GpioInterruptPin<TestClass> gpf6(S3C2410_GPF(6), true, true,  &obj,
//            &TestClass::action, IRQF_TRIGGER_FALLING);
//    gpf6.activate();
    while (1) ;
    return 0;
}

int main() {
    return mainInport();
}
