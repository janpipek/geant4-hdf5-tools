#ifndef HDF5SCOREWRITER_HH
#define HDF5SCOREWRITER_HH

#include <G4VScoreWriter.hh>

namespace g4h5
{
    /**
      * @short Score writer that writes to HDF5 file.
      */
    class Hdf5ScoreWriter : public G4VScoreWriter
    {
    public:
        /**
          * @brief Dump scoring quantity to a file.
          * @param psName - HDF5 dataset of this dataset will be used (quantity)
          * @param fileName - HDF5 file of this name will be used
          * @param option
          *
          * The HDF5 group is named after the scoring world (name of the scorer).
          *
          * Several attributes are added to the dataset:
          *  - size_x, size_y, size_z: (half-)size of the scorer (in mm)
          *  - x, y, z: position of the scorer in world volume (in mm)
          *  - rotate_phi, rotate_theta, rotate_psi: rotation of the scorer in world volume (in deg)
          */
        virtual void DumpQuantityToFile(const G4String & psName, 
            const G4String & fileName, const G4String & option);
    };
}
#endif // HDF5SCOREWRITER_HH
