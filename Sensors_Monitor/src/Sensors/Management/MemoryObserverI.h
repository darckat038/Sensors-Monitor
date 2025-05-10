#ifndef MEMORYOBSERVERI_H
#define MEMORYOBSERVERI_H

namespace Sensors {
namespace Management {

class SensorsMemory;

class MemoryObserverI {

public:
    virtual ~MemoryObserverI() = default;

    //Metodo di notifica
    virtual void notify(SensorsMemory &sMemory) = 0;

    //Metodo di notifica eliminazione
    virtual void notifyDeletion() = 0;
};

}
}

#endif // MEMORYOBSERVERI_H
