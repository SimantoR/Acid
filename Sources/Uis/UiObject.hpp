﻿#pragma once

#include <vector>
#include <memory>
#include <functional>
#include "Maths/Vector2.hpp"
#include "Maths/Vector3.hpp"
#include "Maths/Vector4.hpp"
#include "Maths/Visual/IDriver.hpp"
#include "UiBound.hpp"

namespace fl
{
	/// <summary>
	/// A representation of a object this is rendered to a screen. This object is contained in a parent and has children.
	/// The screen object has a few values that allow for it to be positioned and scaled, along with other variables that are used when rendering.
	/// This class can be extended to create a representation for GUI textures, fonts, etc.
	/// </summary>
	class FL_EXPORT UiObject :
		public std::enable_shared_from_this<UiObject>
	{
	private:
		UiObject *m_parent;
		std::vector<UiObject *> m_children;

		bool m_visible;
		UiBound m_rectangle;
		Vector4 m_scissor; // TODO: Convert to UiBound.

		Vector2 m_positionOffset;
		Vector4 m_screenTransform;

		std::shared_ptr<IDriver> m_alphaDriver;
		float m_alpha;

		std::shared_ptr<IDriver> m_scaleDriver;
		float m_scale;

		std::function<void()> m_actionLeft;
		std::function<void()> m_actionRight;
	public:
		/// <summary>
		/// Creates a new screen object.
		/// </summary>
		/// <param name="parent"> The parent screen object. </param>
		/// <param name="rectangle"> The rectangle that will represent the bounds of the ui object. </param>
		UiObject(UiObject *parent, const UiBound &rectangle);

		/// <summary>
		/// Deconstructor for the screen object.
		/// </summary>
		virtual ~UiObject();

		/// <summary>
		/// Updates this screen object and the extended object.
		/// </summary>
		void Update();

		/// <summary>
		/// Updates the implementation.
		/// </summary>
		virtual void UpdateObject();

		/// <summary>
		/// Disowns a child from this screen objects children list.
		/// </summary>
		/// <param name="child"> The child to disown. </param>
		void RemoveChild(UiObject *child);

		/// <summary>
		/// Adds this object and its children to a list.
		/// </summary>
		/// <param name="list"> The list to add to.
		/// </param>
		/// <returns> The list that has been added to. </returns>
		std::vector<UiObject *> *GetAll(std::vector<UiObject *> *list);

		/// <summary>
		/// Gets the parent object.
		/// </summary>
		/// <returns> The parent object. </returns>
		UiObject *GetParent() const { return m_parent; }

		/// <summary>
		/// Removes this object from the previous parent and attaches it to another parent.
		/// </summary>
		/// <param name="parent"> The new parent object. </param>
		void SetParent(UiObject *parent);

		std::vector<UiObject *> GetChildren() const { return m_children; }

		bool IsVisible() const;

		void SetVisible(const bool &visible) { m_visible = visible; }

		UiBound &GetRectangle() { return m_rectangle; }

		void SetRectangle(const UiBound &rectangle) { m_rectangle = rectangle; }

		Vector4 GetScissor() const { return m_scissor; }

		void SetScissor(const Vector4 &scissor) { m_scissor = scissor; }

		Vector2 GetPositionOffset() const { return m_positionOffset; }

		void SetPositionOffset(const Vector2 &positionOffset) { m_positionOffset = positionOffset; }

		/// <summary>
		/// Gets the ui object screen space transform.
		/// </summary>
		/// <returns> The screen transform. </returns>
		Vector4 GetScreenTransform() const { return m_screenTransform; }

		/// <summary>
		/// Sets the alpha driver.
		/// </summary>
		/// <param name="driver"> The new alpha driver. </param>
		void SetAlphaDriver(std::shared_ptr<IDriver> alphaDriver) { m_alphaDriver = alphaDriver; }

		/// <summary>
		/// Sets a new alpha driver from a type.
		/// </summary>
		/// <param name="T"> The type of driver to set. </param>
		/// <param name="args"> The type driver arguments. </param>
		template<typename T, typename... Args>
		void SetAlphaDriver(Args &&... args) { SetAlphaDriver(std::make_shared<T>(std::forward<Args>(args)...)); }

		float GetAlpha() const;

		/// <summary>
		/// Sets the scale driver.
		/// </summary>
		/// <param name="driver"> The new scale driver. </param>
		void SetScaleDriver(std::shared_ptr<IDriver> scaleDriver) { m_scaleDriver = scaleDriver; }

		/// <summary>
		/// Sets a new scale driver from a type.
		/// </summary>
		/// <param name="T"> The type of driver to set. </param>
		/// <param name="args"> The type driver arguments. </param>
		template<typename T, typename... Args>
		void SetScaleDriver(Args &&... args) { SetScaleDriver(std::make_shared<T>(std::forward<Args>(args)...)); }

		float GetScale() const { return m_scale; }

		void SetActionLeft(std::function<void()> action) { m_actionLeft = action; }

		void SetActionRight(std::function<void()> action) { m_actionRight = action; }
	};
}