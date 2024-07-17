// Jolt Physics Library (https://github.com/jrouwe/JoltPhysics)
// SPDX-FileCopyrightText: 2021 Jorrit Rouwe
// SPDX-License-Identifier: MIT

#pragma once

#include <vendor/Jolt/ObjectStream/SerializableObject.h>
#include <vendor/Jolt/Core/Color.h>
#include <vendor/Jolt/Geometry/AABox.h>
#include <vendor/Jolt/Geometry/Triangle.h>
#include <vendor/Jolt/Geometry/IndexedTriangle.h>

JPH_NAMESPACE_BEGIN

JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, uint8);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, uint16);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, int);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, uint32);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, uint64);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, float);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, double);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, bool);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, String);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Float3);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Double3);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Vec3);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, DVec3);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Vec4);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Quat);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, Mat44);
JPH_DECLARE_RTTI_OUTSIDE_CLASS(JPH_EXPORT, DMat44);
JPH_DECLARE_SERIALIZABLE_OUTSIDE_CLASS(JPH_EXPORT, Color);
JPH_DECLARE_SERIALIZABLE_OUTSIDE_CLASS(JPH_EXPORT, AABox);
JPH_DECLARE_SERIALIZABLE_OUTSIDE_CLASS(JPH_EXPORT, Triangle);
JPH_DECLARE_SERIALIZABLE_OUTSIDE_CLASS(JPH_EXPORT, IndexedTriangle);

JPH_NAMESPACE_END

// These need to be added after all types have been registered or else clang under linux will not find GetRTTIOfType for the type
#include <vendor/Jolt/ObjectStream/SerializableAttributeTyped.h>
#include <vendor/Jolt/ObjectStream/SerializableAttributeEnum.h>
