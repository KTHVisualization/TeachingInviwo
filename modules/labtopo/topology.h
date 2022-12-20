/*********************************************************************
 *  Author  : Anke Friederici
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 **********************************************************************/

#pragma once

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/ports/meshport.h>
#include <inviwo/core/datastructures/geometry/basicmesh.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/properties/eventproperty.h>
#include <inviwo/core/properties/ordinalproperty.h>
#include <inviwo/core/properties/boolproperty.h>
#include <labtopo/labtopomoduledefine.h>
#include <labutils/scalarvectorfield.h>

namespace inviwo {

/** \docpage{org.inviwo.Topology, Vector Field Topology}
    ![](org.inviwo.Topology.png?classIdentifier=org.inviwo.Topology)

    Generate the topological skeleton of a vector field.

    ### Inports
      * __data__ The input here is 2-dimensional vector field (with vectors of
      two components thus two values within each voxel) but it is represented
      by a 3-dimensional volume.
      This processor deals with 2-dimensional data only, therefore it is assumed
      the z-dimension will have size 1 otherwise the 0th slice of the volume
      will be processed.

    ### Outports
      * __outMesh__ The output mesh contains points and linesegments that make up
      the topological skeleton.
      * __meshBBoxOut__ Mesh with bounding box
*/
class IVW_MODULE_LABTOPO_API Topology : public Processor {
public:
    // All possible first order critical points in 2D vector fields.
    enum class TypeCP {
        Saddle = 0,
        AttractingNode = 1,
        RepellingNode = 2,
        AttractingFocus = 3,
        RepellingFocus = 4,
        Center = 5
    };

    // Colors according to the TypeCP enum.
    static const vec4 ColorsCP[6];

    // Construction / Deconstruction
public:
    Topology();
    virtual ~Topology() = default;

    // Methods
public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    // Our main computation function
    virtual void process() override;

    // TODO: You may want to declare additional functions here, e.g., extractCriticalPoints.

    static void drawLineSegment(const dvec2& v1, const dvec2& v2, const vec4& color,
                                IndexBufferRAM* indexBuffer,
                                std::vector<BasicMesh::Vertex>& vertices);

    // Ports
public:
    // Input data
    VolumeInport inData;

    // Output mesh
    MeshOutport outMesh;

	// Output mesh for bounding box and gridlines
    MeshOutport meshBBoxOut;

};  // namespace inviwo

}  // namespace inviwo
