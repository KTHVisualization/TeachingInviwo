/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Tuesday, September 19, 2017 - 15:08:24
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/ports/meshport.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/properties/eventproperty.h>
#include <inviwo/core/properties/ordinalproperty.h>
#include <labstreamlines/labstreamlinesmoduledefine.h>
#include <labutils/scalarvectorfield.h>

namespace inviwo {

/** \docpage{org.inviwo.EulerRK4Comparison, Euler RK4 Comparison}
    ![](org.inviwo.EulerRK4Comparison.png?classIdentifier=org.inviwo.EulerRK4Comparison)

    Comparison of the Euler and Runge-Kutta of 4th order integration schemes
    by computation of streamlines in a given vectorfield

    ### Inports
      * __data__ The input here is 2-dimensional vector field (with vectors of
      two components thus two values within each voxel) but it is represented
      by a 3-dimensional volume.
      This processor deals with 2-dimensional data only, therefore it is assumed
      the z-dimension will have size 1 otherwise the 0th slice of the volume
      will be processed.

    ### Outports
      * __meshOut__ The output mesh contains points and linesegments for the
      two streamlines computed with different integration schemes and both
      starting at a given start point
      * __meshBBoxOut__ Mesh with bounding box

    ### Properties
      * __propStartPoint__ Location of the start point
      * __mouseMoveStart__ Move the start point when a selected mouse button is pressed
      (default left)
*/
class IVW_MODULE_LABSTREAMLINES_API EulerRK4Comparison : public Processor {

public:
    // Construction / Deconstruction
public:
    EulerRK4Comparison();
    virtual ~EulerRK4Comparison() = default;

    // Methods
public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    /// Our main computation function
    virtual void process() override;
    void eventMoveStart(Event* event);

    // Ports
public:
    // Input data
    VolumeInport inData;

    // Output mesh
    MeshOutport meshOut;

    // Output mesh for bounding box and gridlines
    MeshOutport meshBBoxOut;

    // Properties
public:
    FloatVec2Property propStartPoint;

    EventProperty mouseMoveStart;

    // TODO: Declare additional properties
    // IntProperty properyName;
    // FloatProperty propertyName2;

// Attributes
private:
    dvec2 BBoxMin_{0, 0};
    dvec2 BBoxMax_{0, 0};
};

}  // namespace inviwo
