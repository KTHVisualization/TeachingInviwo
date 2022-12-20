/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Monday, October 02, 2017 - 13:31:36
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <lablic/noisetexturegenerator.h>
#include <labutils/rgbaimage.h>

namespace inviwo {

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo NoiseTextureGenerator::processorInfo_{
    "org.inviwo.NoiseTextureGenerator",  // Class identifier
    "Noise Texture Generator",           // Display name
    "KTH Labs",                          // Category
    CodeState::Experimental,             // Code state
    Tags::None,                          // Tags
};

const ProcessorInfo NoiseTextureGenerator::getProcessorInfo() const { return processorInfo_; }

NoiseTextureGenerator::NoiseTextureGenerator()
    : Processor()
    , texOut_("texOut")
    , texSize_("texSize", "Texture Size", vec2(512, 512), vec2(1, 1), vec2(2048, 2048), vec2(1, 1))
// TODO: Register additional properties
{
    // Register ports
    addPort(texOut_);

    // Register properties
    addProperty(texSize_);

    // TODO: Register additional properties
}

void NoiseTextureGenerator::process() {
    // The output of the generation process is an Image
    // With the given dimensions
    // With the data format DataVec4UInt8, this means values for RGB-alpha range between 0 and 255
    auto outImage =
        std::make_shared<Image>(size2_t(texSize_.get().x, texSize_.get().y), DataVec4UInt8::get());

    // Similar to ScalarField and VectorField, the RGBAImage has some methods to sample from and set
    // values
    RGBAImage noiseTexture(outImage);

    // Setting pixels in the image/texture
    // setPixelGrayScale will set the value to (val,val,val,255) at the pixel with indices (i,j)
    int val = 4;
    noiseTexture.setPixelGrayScale(size2_t(0, 0), val);
    // setPixel allows to set all color components (red,green,blue,alpha) at the pixel with indices
    // (i,j)
    noiseTexture.setPixel(size2_t(0, 0), vec4(val, val, val, 255));

    // Reading from the image
    // readPixelGrayScale returns the average of the three colors (red+green+blue)/3 at the pixel
    // with indices (i,j)
    double value = noiseTexture.readPixelGrayScale(size2_t(0, 0));
    // readPixel returns all color components (red,green,blue,alpha) at the pixel with indices (i,j)
    dvec4 color = noiseTexture.readPixel(size2_t(0, 0));
    LogProcessorInfo("The color at index (0,0) is " << color << " with grayscale value " << value
                                                    << ".");
    // sample performs bilinear interpolation. For (0.5,0.5) this would involve the values at pixels
    // (0,0), (1,0), (0,1), and (1,1)
    color = noiseTexture.sample(dvec2(0.5, 0.5));
    // The grayscale version again does the same but returns an average of the three color values
    value = noiseTexture.sampleGrayScale(dvec2(0.5, 0.5));
    LogProcessorInfo("The interpolated color at (0.5,0.5) is " << color << " with grayscale value "
                                                               << value << ".");

    for (int j = 0; j < texSize_.get().y; j++) {
        for (int i = 0; i < texSize_.get().x; i++) {

            val = 256 / 2;
            // TODO: Randomly sample values for the texture, this produces the same gray value for
            // all pixels
            // A value within the output image is set by specifying pixel position and color
            noiseTexture.setPixelGrayScale(size2_t(i, j), val);
            // Alternatively, the entire color can be specified
            // noiseTexture.setPixel(size2_t(i, j), vec4(val, val, val, 255));
        }
    }

    texOut_.setData(outImage);
}

}  // namespace inviwo
