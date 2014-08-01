#ifndef HDF5SCOREWRITER_HH
#define HDF5SCOREWRITER_HH

#include <G4VScoreWriter.hh>

namespace g4h5
{
    class Hdf5ScoreWriter : public G4VScoreWriter
    {
    public:
        virtual void DumpQuantityToFile(const G4String & psName, 
            const G4String & fileName, const G4String & option);
    };
}
#endif // HDF5SCOREWRITER_HH