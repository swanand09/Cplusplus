// Copyright (C) 2013 Jérôme Leclercq
// This file is part of the "Nazara Engine - Utility module"
// For conditions of distribution and use, see copyright notice in Config.hpp

#include <Nazara/Utility/Loaders/MD2/Constants.hpp>
#include <Nazara/Utility/Debug.hpp>

const nzUInt32 md2Ident = 'I' + ('D'<<8) + ('P'<<16) + ('2'<<24);

const NzVector3f md2Normals[162] =
{
	NzVector3f(-0.525731f, 0.000000f, 0.850651f),
	NzVector3f(-0.442863f, 0.238856f, 0.864188f),
	NzVector3f(-0.295242f, 0.000000f, 0.955423f),
	NzVector3f(-0.309017f, 0.500000f, 0.809017f),
	NzVector3f(-0.162460f, 0.262866f, 0.951056f),
	NzVector3f(0.000000f, 0.000000f, 1.000000f),
	NzVector3f(0.000000f, 0.850651f, 0.525731f),
	NzVector3f(-0.147621f, 0.716567f, 0.681718f),
	NzVector3f(0.147621f, 0.716567f, 0.681718f),
	NzVector3f(0.000000f, 0.525731f, 0.850651f),
	NzVector3f(0.309017f, 0.500000f, 0.809017f),
	NzVector3f(0.525731f, 0.000000f, 0.850651f),
	NzVector3f(0.295242f, 0.000000f, 0.955423f),
	NzVector3f(0.442863f, 0.238856f, 0.864188f),
	NzVector3f(0.162460f, 0.262866f, 0.951056f),
	NzVector3f(-0.681718f, 0.147621f, 0.716567f),
	NzVector3f(-0.809017f, 0.309017f, 0.500000f),
	NzVector3f(-0.587785f, 0.425325f, 0.688191f),
	NzVector3f(-0.850651f, 0.525731f, 0.000000f),
	NzVector3f(-0.864188f, 0.442863f, 0.238856f),
	NzVector3f(-0.716567f, 0.681718f, 0.147621f),
	NzVector3f(-0.688191f, 0.587785f, 0.425325f),
	NzVector3f(-0.500000f, 0.809017f, 0.309017f),
	NzVector3f(-0.238856f, 0.864188f, 0.442863f),
	NzVector3f(-0.425325f, 0.688191f, 0.587785f),
	NzVector3f(-0.716567f, 0.681718f, -0.147621f),
	NzVector3f(-0.500000f, 0.809017f, -0.309017f),
	NzVector3f(-0.525731f, 0.850651f, 0.000000f),
	NzVector3f(0.000000f, 0.850651f, -0.525731f),
	NzVector3f(-0.238856f, 0.864188f, -0.442863f),
	NzVector3f(0.000000f, 0.955423f, -0.295242f),
	NzVector3f(-0.262866f, 0.951056f, -0.162460f),
	NzVector3f(0.000000f, 1.000000f, 0.000000f),
	NzVector3f(0.000000f, 0.955423f, 0.295242f),
	NzVector3f(-0.262866f, 0.951056f, 0.162460f),
	NzVector3f(0.238856f, 0.864188f, 0.442863f),
	NzVector3f(0.262866f, 0.951056f, 0.162460f),
	NzVector3f(0.500000f, 0.809017f, 0.309017f),
	NzVector3f(0.238856f, 0.864188f, -0.442863f),
	NzVector3f(0.262866f, 0.951056f, -0.162460f),
	NzVector3f(0.500000f, 0.809017f, -0.309017f),
	NzVector3f(0.850651f, 0.525731f, 0.000000f),
	NzVector3f(0.716567f, 0.681718f, 0.147621f),
	NzVector3f(0.716567f, 0.681718f, -0.147621f),
	NzVector3f(0.525731f, 0.850651f, 0.000000f),
	NzVector3f(0.425325f, 0.688191f, 0.587785f),
	NzVector3f(0.864188f, 0.442863f, 0.238856f),
	NzVector3f(0.688191f, 0.587785f, 0.425325f),
	NzVector3f(0.809017f, 0.309017f, 0.500000f),
	NzVector3f(0.681718f, 0.147621f, 0.716567f),
	NzVector3f(0.587785f, 0.425325f, 0.688191f),
	NzVector3f(0.955423f, 0.295242f, 0.000000f),
	NzVector3f(1.000000f, 0.000000f, 0.000000f),
	NzVector3f(0.951056f, 0.162460f, 0.262866f),
	NzVector3f(0.850651f, -0.525731f, 0.000000f),
	NzVector3f(0.955423f, -0.295242f, 0.000000f),
	NzVector3f(0.864188f, -0.442863f, 0.238856f),
	NzVector3f(0.951056f, -0.162460f, 0.262866f),
	NzVector3f(0.809017f, -0.309017f, 0.500000f),
	NzVector3f(0.681718f, -0.147621f, 0.716567f),
	NzVector3f(0.850651f, 0.000000f, 0.525731f),
	NzVector3f(0.864188f, 0.442863f, -0.238856f),
	NzVector3f(0.809017f, 0.309017f, -0.500000f),
	NzVector3f(0.951056f, 0.162460f, -0.262866f),
	NzVector3f(0.525731f, 0.000000f, -0.850651f),
	NzVector3f(0.681718f, 0.147621f, -0.716567f),
	NzVector3f(0.681718f, -0.147621f, -0.716567f),
	NzVector3f(0.850651f, 0.000000f, -0.525731f),
	NzVector3f(0.809017f, -0.309017f, -0.500000f),
	NzVector3f(0.864188f, -0.442863f, -0.238856f),
	NzVector3f(0.951056f, -0.162460f, -0.262866f),
	NzVector3f(0.147621f, 0.716567f, -0.681718f),
	NzVector3f(0.309017f, 0.500000f, -0.809017f),
	NzVector3f(0.425325f, 0.688191f, -0.587785f),
	NzVector3f(0.442863f, 0.238856f, -0.864188f),
	NzVector3f(0.587785f, 0.425325f, -0.688191f),
	NzVector3f(0.688191f, 0.587785f, -0.425325f),
	NzVector3f(-0.147621f, 0.716567f, -0.681718f),
	NzVector3f(-0.309017f, 0.500000f, -0.809017f),
	NzVector3f(0.000000f, 0.525731f, -0.850651f),
	NzVector3f(-0.525731f, 0.000000f, -0.850651f),
	NzVector3f(-0.442863f, 0.238856f, -0.864188f),
	NzVector3f(-0.295242f, 0.000000f, -0.955423f),
	NzVector3f(-0.162460f, 0.262866f, -0.951056f),
	NzVector3f(0.000000f, 0.000000f, -1.000000f),
	NzVector3f(0.295242f, 0.000000f, -0.955423f),
	NzVector3f(0.162460f, 0.262866f, -0.951056f),
	NzVector3f(-0.442863f, -0.238856f, -0.864188f),
	NzVector3f(-0.309017f, -0.500000f, -0.809017f),
	NzVector3f(-0.162460f, -0.262866f, -0.951056f),
	NzVector3f(0.000000f, -0.850651f, -0.525731f),
	NzVector3f(-0.147621f, -0.716567f, -0.681718f),
	NzVector3f(0.147621f, -0.716567f, -0.681718f),
	NzVector3f(0.000000f, -0.525731f, -0.850651f),
	NzVector3f(0.309017f, -0.500000f, -0.809017f),
	NzVector3f(0.442863f, -0.238856f, -0.864188f),
	NzVector3f(0.162460f, -0.262866f, -0.951056f),
	NzVector3f(0.238856f, -0.864188f, -0.442863f),
	NzVector3f(0.500000f, -0.809017f, -0.309017f),
	NzVector3f(0.425325f, -0.688191f, -0.587785f),
	NzVector3f(0.716567f, -0.681718f, -0.147621f),
	NzVector3f(0.688191f, -0.587785f, -0.425325f),
	NzVector3f(0.587785f, -0.425325f, -0.688191f),
	NzVector3f(0.000000f, -0.955423f, -0.295242f),
	NzVector3f(0.000000f, -1.000000f, 0.000000f),
	NzVector3f(0.262866f, -0.951056f, -0.162460f),
	NzVector3f(0.000000f, -0.850651f, 0.525731f),
	NzVector3f(0.000000f, -0.955423f, 0.295242f),
	NzVector3f(0.238856f, -0.864188f, 0.442863f),
	NzVector3f(0.262866f, -0.951056f, 0.162460f),
	NzVector3f(0.500000f, -0.809017f, 0.309017f),
	NzVector3f(0.716567f, -0.681718f, 0.147621f),
	NzVector3f(0.525731f, -0.850651f, 0.000000f),
	NzVector3f(-0.238856f, -0.864188f, -0.442863f),
	NzVector3f(-0.500000f, -0.809017f, -0.309017f),
	NzVector3f(-0.262866f, -0.951056f, -0.162460f),
	NzVector3f(-0.850651f, -0.525731f, 0.000000f),
	NzVector3f(-0.716567f, -0.681718f, -0.147621f),
	NzVector3f(-0.716567f, -0.681718f, 0.147621f),
	NzVector3f(-0.525731f, -0.850651f, 0.000000f),
	NzVector3f(-0.500000f, -0.809017f, 0.309017f),
	NzVector3f(-0.238856f, -0.864188f, 0.442863f),
	NzVector3f(-0.262866f, -0.951056f, 0.162460f),
	NzVector3f(-0.864188f, -0.442863f, 0.238856f),
	NzVector3f(-0.809017f, -0.309017f, 0.500000f),
	NzVector3f(-0.688191f, -0.587785f, 0.425325f),
	NzVector3f(-0.681718f, -0.147621f, 0.716567f),
	NzVector3f(-0.442863f, -0.238856f, 0.864188f),
	NzVector3f(-0.587785f, -0.425325f, 0.688191f),
	NzVector3f(-0.309017f, -0.500000f, 0.809017f),
	NzVector3f(-0.147621f, -0.716567f, 0.681718f),
	NzVector3f(-0.425325f, -0.688191f, 0.587785f),
	NzVector3f(-0.162460f, -0.262866f, 0.951056f),
	NzVector3f(0.442863f, -0.238856f, 0.864188f),
	NzVector3f(0.162460f, -0.262866f, 0.951056f),
	NzVector3f(0.309017f, -0.500000f, 0.809017f),
	NzVector3f(0.147621f, -0.716567f, 0.681718f),
	NzVector3f(0.000000f, -0.525731f, 0.850651f),
	NzVector3f(0.425325f, -0.688191f, 0.587785f),
	NzVector3f(0.587785f, -0.425325f, 0.688191f),
	NzVector3f(0.688191f, -0.587785f, 0.425325f),
	NzVector3f(-0.955423f, 0.295242f, 0.000000f),
	NzVector3f(-0.951056f, 0.162460f, 0.262866f),
	NzVector3f(-1.000000f, 0.000000f, 0.000000f),
	NzVector3f(-0.850651f, 0.000000f, 0.525731f),
	NzVector3f(-0.955423f, -0.295242f, 0.000000f),
	NzVector3f(-0.951056f, -0.162460f, 0.262866f),
	NzVector3f(-0.864188f, 0.442863f, -0.238856f),
	NzVector3f(-0.951056f, 0.162460f, -0.262866f),
	NzVector3f(-0.809017f, 0.309017f, -0.500000f),
	NzVector3f(-0.864188f, -0.442863f, -0.238856f),
	NzVector3f(-0.951056f, -0.162460f, -0.262866f),
	NzVector3f(-0.809017f, -0.309017f, -0.500000f),
	NzVector3f(-0.681718f, 0.147621f, -0.716567f),
	NzVector3f(-0.681718f, -0.147621f, -0.716567f),
	NzVector3f(-0.850651f, 0.000000f, -0.525731f),
	NzVector3f(-0.688191f, 0.587785f, -0.425325f),
	NzVector3f(-0.587785f, 0.425325f, -0.688191f),
	NzVector3f(-0.425325f, 0.688191f, -0.587785f),
	NzVector3f(-0.425325f, -0.688191f, -0.587785f),
	NzVector3f(-0.587785f, -0.425325f, -0.688191f),
	NzVector3f(-0.688191f, -0.587785f, -0.425325f)
};