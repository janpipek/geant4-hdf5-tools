#include "Hdf5ScoreWriter.hh"

#include <stdexcept>
#include <H5Cpp.h>
#include <G4VScoringMesh.hh>
#include <fstream>

#include "hdf5functions.hh"

using namespace std;

#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

bool file_exists(const char* fileName)
{
    // Inspired by http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    std::ifstream infile(fileName);
    return infile.good();
}

namespace g4h5
{
    void Hdf5ScoreWriter::DumpQuantityToFile(const G4String& psName, 
        const G4String& fileName, const G4String& option)
    {
        // File
        H5File* file;
        if (file_exists(fileName.c_str()))
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
        else
        {
            // File does not exist
            file = new H5File(fileName, H5F_ACC_TRUNC);
        }

        // Group
        G4String groupName = fScoringMesh->GetWorldName();
        if (!H5Lexists(file->getId(), groupName.c_str(), H5P_DEFAULT))
        {
            file->createGroup(groupName);
        }
        Group group = file->openGroup(groupName);

        // DataSpace
        hsize_t dim[] = { (hsize_t)fNMeshSegments[0], (hsize_t)fNMeshSegments[1], (hsize_t)fNMeshSegments[2] };
        DataSpace fDataSpace(3, dim);

        // DataSet
        if (H5Lexists(group.getId(), psName.c_str(), H5P_DEFAULT))
        {
            group.unlink(psName.c_str());
            G4cout << "Existing data set " << psName << " deleted." << G4endl;
        }
        DataSet dataSet = group.createDataSet(psName, PredType::NATIVE_DOUBLE, fDataSpace);

        // ScoreMap
        MeshScoreMap scMap = fScoringMesh->GetScoreMap();
        MeshScoreMap::const_iterator msMapItr = scMap.find(psName);
        if(msMapItr == scMap.end()) {
            G4cerr << "ERROR : DumpToFile : Unknown quantity, \""
                 << psName << "\"." << G4endl;
            return;
        }
        std::map<G4int, G4double*> * score = msMapItr->second->GetMap();

        // Write data
        hsize_t count[] = {1, 1, 1};  // Block count

        DataSpace mDataSpace(3, dim);
        hsize_t mStart[] = {0, 0, 0};
        mDataSpace.selectHyperslab(H5S_SELECT_SET, count, mStart); // Always just the address

        for(int x = 0; x < fNMeshSegments[0]; x++) {
            for(int y = 0; y < fNMeshSegments[1]; y++) {
                for(int z = 0; z < fNMeshSegments[2]; z++) {
                    G4int idx = GetIndex(x, y, z);
                    std::map<G4int, G4double*>::iterator value = score->find(idx);
                    if (value != score->end())
                    {
                        double quantity = *(value->second);
                        hsize_t start[] = { (hsize_t)x, (hsize_t)y, (hsize_t)z }; // Start of hyperslab
                        fDataSpace.selectHyperslab( H5S_SELECT_SET, count, start);
                        dataSet.write(&quantity, PredType::NATIVE_DOUBLE, mDataSpace, fDataSpace);
                    }
                }
            }
        }

        // Add descriptory attributes
        G4ThreeVector size = fScoringMesh->GetSize();
        addAttribute(dataSet, "size_x", size.x() / mm);
        addAttribute(dataSet, "size_y", size.y() / mm);
        addAttribute(dataSet, "size_z", size.z() / mm);

        G4ThreeVector position = fScoringMesh->GetTranslation();
        addAttribute(dataSet, "x", position.x() / mm);
        addAttribute(dataSet, "y", position.y() / mm);
        addAttribute(dataSet, "z", position.z() / mm);

        G4RotationMatrix matrix = fScoringMesh->GetRotationMatrix();
        addAttribute(dataSet, "rotate_phi", matrix.phi() / deg);
        addAttribute(dataSet, "rotate_theta", matrix.theta() / deg);
        addAttribute(dataSet, "rotate_psi", matrix.psi() / deg);

        // Close file and we're done
        delete file;
    }
}
