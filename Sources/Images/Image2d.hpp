#pragma once

#include "Helpers/NonCopyable.hpp"
#include "Resources/Resource.hpp"
#include "Image.hpp"

namespace acid
{
/// <summary>
/// Class that represents a loaded texture.
/// </summary>
class ACID_EXPORT Image2d :
	public NonCopyable, public Descriptor, public Resource
{
public:
	/// <summary>
	/// Will find an existing texture with the same values, or create a new texture.
	/// </summary>
	/// <param name="metadata"> The metadata to decode values from. </param>
	static std::shared_ptr<Image2d> Create(const Metadata &metadata);

	/// <summary>
	/// Will find an existing texture with the same values, or create a new texture.
	/// </summary>
	/// <param name="filename"> The file to load the texture from. </param>
	/// <param name="filter"> The type of filtering will be use on the texture. </param>
	/// <param name="addressMode"> The sampler address mode to use. </param>
	/// <param name="anisotropic"> If anisotropic filtering will be use on the texture. </param>
	/// <param name="mipmap"> If mipmaps will be generated for the texture. </param>
	static std::shared_ptr<Image2d> Create(const std::string &filename, const VkFilter &filter = VK_FILTER_LINEAR, const VkSamplerAddressMode &addressMode = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE,
		const bool &anisotropic = true, const bool &mipmap = true);

	/// <summary>
	/// A new texture object.
	/// </summary>
	/// <param name="filename"> The file to load the texture from. </param>
	/// <param name="filter"> The type of filtering will be use on the texture. </param>
	/// <param name="addressMode"> The sampler address mode to use. </param>
	/// <param name="anisotropic"> If anisotropic filtering will be use on the texture. </param>
	/// <param name="mipmap"> If mipmaps will be generated for the texture. </param>
	/// <param name="load"> If this resource will load immediately, otherwise <seealso cref="#Load()"/> can be called. </param>
	explicit Image2d(std::string filename, const VkFilter &filter = VK_FILTER_LINEAR, const VkSamplerAddressMode &addressMode = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, const bool &anisotropic = true,
		const bool &mipmap = true, const bool &load = true);

	/// <summary>
	/// A new texture object from a array of pixels.
	/// </summary>
	/// <param name="width"> The textures width. </param>
	/// <param name="height"> The textures height. </param>
	/// <param name="pixels"> The initial pixels to use in the texture. <seealso cref="#GetPixels()"/> to get a copy of the pixels, and <seealso cref="#SetPixels()"/> to set the pixels. </param>
	/// <param name="format"> The textures format. </param>
	/// <param name="layout"> The textures image layout </param>
	/// <param name="usage"> The textures image usage </param>
	/// <param name="filter"> The type of filtering will be use on the texture. </param>
	/// <param name="addressMode"> The sampler address mode to use. </param>
	/// <param name="samples"> The amount of MSAA samples to use. </param>
	/// <param name="anisotropic"> If anisotropic filtering will be use on the texture. </param>
	/// <param name="mipmap"> If mipmaps will be generated for the texture. </param>
	Image2d(const uint32_t &width, const uint32_t &height, std::unique_ptr<uint8_t[]> pixels = nullptr, const VkFormat &format = VK_FORMAT_R8G8B8A8_UNORM,
		const VkImageLayout &layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, const VkImageUsageFlags &usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_STORAGE_BIT,
		const VkFilter &filter = VK_FILTER_LINEAR, const VkSamplerAddressMode &addressMode = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE, const VkSampleCountFlagBits &samples = VK_SAMPLE_COUNT_1_BIT,
		const bool &anisotropic = false, const bool &mipmap = false);

	~Image2d();

	static VkDescriptorSetLayoutBinding GetDescriptorSetLayout(const uint32_t &binding, const VkDescriptorType &descriptorType, const VkShaderStageFlags &stage, const uint32_t &count);

	WriteDescriptorSet GetWriteDescriptor(const uint32_t &binding, const VkDescriptorType &descriptorType, const VkDescriptorSet &descriptorSet,
		const std::optional<OffsetSize> &offsetSize) const override;

	void Load() override;

	void Decode(const Metadata &metadata) override;

	void Encode(Metadata &metadata) const override;

	/// <summary>
	/// Gets a copy of the textures pixels from memory.
	/// </summary>
	/// <param name="width"> The value sampled width is stored to. </param>
	/// <param name="height"> The value sampled height is stored to. </param>
	/// <param name="mipLevel"> The mipmap level index to get the pixels from. </param>
	/// <returns> A copy of the textures pixels. </returns>
	std::unique_ptr<uint8_t[]> GetPixels(uint32_t &width, uint32_t &height, const uint32_t &mipLevel = 1) const;

	/// <summary>
	/// Copies the pixels into this textures memory.
	/// </summary>
	/// <param name="pixels"> The pixels to copy to the image. </param>
	void SetPixels(const uint8_t *pixels);

	const std::string &GetFilename() const { return m_filename; };

	const VkFilter &GetFilter() const { return m_filter; }

	const VkSamplerAddressMode &GetAddressMode() const { return m_addressMode; }

	const bool &IsAnisotropic() const { return m_anisotropic; }

	const bool &IsMipmap() const { return m_mipmap; }

	const VkSampleCountFlagBits &GetSamples() const { return m_samples; }

	const VkImageLayout &GetLayout() const { return m_layout; }

	const VkImageUsageFlags &GetUsage() const { return m_usage; }

	const uint32_t &GetComponents() const { return m_components; }

	const uint32_t &GetWidth() const { return m_width; }

	const uint32_t &GetHeight() const { return m_height; }

	const uint32_t &GetMipLevels() const { return m_mipLevels; }

	const VkImage &GetImage() { return m_image; }

	const VkDeviceMemory &GetMemory() { return m_memory; }

	const VkImageView &GetView() const { return m_view; }

	const VkSampler &GetSampler() const { return m_sampler; }

	const VkFormat &GetFormat() const { return m_format; }

private:
	std::string m_filename;

	VkFilter m_filter;
	VkSamplerAddressMode m_addressMode;
	bool m_anisotropic;
	bool m_mipmap;
	VkSampleCountFlagBits m_samples;
	VkImageLayout m_layout;
	VkImageUsageFlags m_usage;

	uint32_t m_components;
	uint32_t m_width, m_height;
	std::unique_ptr<uint8_t[]> m_loadPixels;
	uint32_t m_mipLevels;

	VkImage m_image;
	VkDeviceMemory m_memory;
	VkImageView m_view;
	VkSampler m_sampler;
	VkFormat m_format;
};
}
