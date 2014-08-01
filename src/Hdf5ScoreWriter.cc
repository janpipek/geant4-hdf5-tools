#include "Hdf5ScoreWriter.hh"

#include <stdexcept>
#include <H5Cpp.h>
#include <G4VScoringMesh.hh>

using namespace std;

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

namespace g4h5
{
    void Hdf5ScoreWriter::DumpQuantityToFile(const G4String& psName, 
        const G4String& fileName, const G4String& option)
    {
        H5File* file;
        try 
        {
            if (H5File::isHdf5(fileName))
            {
                file = new H5File(fileName, H5F_ACC_RDWR);
            }
            else
            {
                throw new runtime_error("File has invalid format.");
            }
        }
        catch (H5::FileIException)
        {
            // File does not exist
            file = new H5File(fileName, H5F_ACC_TRUNC);
        }

        MeshScoreMap scoreMap = fScoringMesh->GetScoreMap();
        // scoreMap.
        delete file;
    }
}
