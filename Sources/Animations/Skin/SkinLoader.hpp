#pragma once

#include <vector>
#include "Files/LoadedValue.hpp"
#include "VertexSkinData.hpp"

namespace fl
{
	class FL_EXPORT SkinLoader
	{
	private:
		std::shared_ptr<LoadedValue> m_skinData;

		int m_maxWeights;

		std::vector<std::string> m_jointOrder;
		std::vector<VertexSkinData *> m_verticesSkinData;
	public:
		SkinLoader(std::shared_ptr<LoadedValue> libraryControllers, const int &maxWeights);

		~SkinLoader();

		std::vector<std::string> GetJointOrder() const { return m_jointOrder; }

		std::vector<VertexSkinData *> GetVerticesSkinData() const { return m_verticesSkinData; }

	private:
		void LoadJointsList();

		std::vector<float> LoadWeights();

		std::vector<int> GetEffectiveJointsCounts(std::shared_ptr<LoadedValue> weightsDataNode);

		void GetSkinData(std::shared_ptr<LoadedValue> weightsDataNode, const std::vector<int> &counts, const std::vector<float> &weights);
	};
}