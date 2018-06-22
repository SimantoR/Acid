#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Files/Files.hpp"
#include "Helpers/FormatString.hpp"
#include "Resources/Resources.hpp"
#include "Files/Json/FileJson.hpp"

namespace fl
{
	class GameObject;

	/// <summary>
	/// Class that represents a entity prefab.
	/// </summary>
	class FL_EXPORT PrefabObject :
		public IResource
	{
	private:
		std::string m_filename;
		FileJson m_fileJson;
	public:
		static std::shared_ptr<PrefabObject> Resource(const std::string &filename)
		{
			std::string realFilename = Files::Get()->SearchFile(filename);
			auto resource = Resources::Get()->Get(realFilename);

			if (resource != nullptr)
			{
				return std::dynamic_pointer_cast<PrefabObject>(resource);
			}

			auto result = std::make_shared<PrefabObject>(realFilename);
			Resources::Get()->Add(std::dynamic_pointer_cast<IResource>(result));
			return result;
		}

		/// <summary>
		/// Creates a new entity prefab.
		/// </summary>
		/// <param name="filename"> The file name. </param>
		PrefabObject(const std::string &filename);

		~PrefabObject();

		void Write(const GameObject &gameObject);

		void Save();

		std::string GetFilename() override { return m_filename; }

		std::shared_ptr<LoadedValue> GetParent() const { return m_fileJson.GetParent(); }
	};
}