/*********************************************************************
 *  Author  : Himangshu Saikia, Wiebke Koepp, Anke Friederici
 *  Init    : Monday, September 11, 2017 - 12:58:42
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#pragma once

#include <labmarchingsquares/labmarchingsquaresmoduledefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/processors/processor.h>
#include <inviwo/core/ports/volumeport.h>
#include <inviwo/core/ports/meshport.h>
#include <inviwo/core/properties/boolproperty.h>
#include <inviwo/core/properties/optionproperty.h>
#include <inviwo/core/properties/ordinalproperty.h>
#include <inviwo/core/properties/transferfunctionproperty.h>
#include <inviwo/core/datastructures/volume/volumeram.h>
#include <inviwo/core/datastructures/geometry/basicmesh.h>
#include <labutils/scalarvectorfield.h>

#include <random>

namespace inviwo {

/** \docpage{org.inviwo.MarchingSquares, Marching Squares}
    ![](org.inviwo.MarchingSquares.png?classIdentifier=org.inviwo.MarchingSquares)

    Extraction of isocontours in 2D with the marching squares algorithm.

    ### Inports
      * __data__ The input is a 2-dimensional scalar field (with a single value at each position
      represented in a 2-dimension uniform structured grid.

    ### Outports
      * __isolinesmesh__ Mesh with (possibly multiple) iso contours
      * __gridmesh__ Mesh with bounding box and potentially grid lines

    ### Properties
      * __propShowGrid__ Display grid lines if true, do not display grid lines if false.
      * __propGridColor__ Color of the grid lines
      * __propDeciderType__ Type of decider for ambiguities in marching squares
	  * __propSeed__ Seed for random decision
      * __propMultiple__ Display of one iso contour or multiple
      * __propIsoValue__ Iso value for one iso contour
      * __propIsoColor__ Color for iso contour(s)
      * __propNumContours__ Number of isocontours to be displayed between minimum and maximum data
   value
      * __propIsoTransferFunc__ Transfer function to be used to color those multiple contours
*/
class IVW_MODULE_LABMARCHINGSQUARES_API MarchingSquares : public Processor {
    // Friends
    // Types
public:
    // Construction / Deconstruction
public:
    MarchingSquares();
    virtual ~MarchingSquares() = default;

    // Methods
public:
    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    /// Our main computation function
    virtual void process() override;

    // (TODO: Helper functions can be defined here and then implemented in the .cpp)

    // Draw a line segment from v1 to v2 with a color
    void drawLineSegment(const vec2& v1, const vec2& v2, const vec4& color,
                         IndexBufferRAM* indexBuffer, std::vector<BasicMesh::Vertex>& vertices);

	float randomValue(const float min, const float max) const;
    // Ports
public:
    // Input data
    VolumeInport inData;

    // Output mesh for isolines
    MeshOutport meshIsoOut;

    // Output mesh for bounding box and gridlines
    MeshOutport meshGridOut;

    // Properties
public:
    // Basic settings
    BoolProperty propShowGrid;
    FloatVec4Property propGridColor;
    TemplateOptionProperty<int> propDeciderType;
    Int64Property propRandomSeed;
    TemplateOptionProperty<int> propMultiple;
    // Properties for choosing a single iso contour by value
    DoubleProperty propIsoValue;
    FloatVec4Property propIsoColor;
    // Properties for multiple iso contours
    IntProperty propNumContours;
    TransferFunctionProperty propIsoTransferFunc;

    // Attributes
private:
    mutable std::mt19937 randGenerator;
    mutable std::uniform_real_distribution<float> uniformReal;

};

}  // namespace inviwo
