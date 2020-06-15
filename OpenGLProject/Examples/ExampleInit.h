#pragma once

#include "ExampleFactory.h"

#include "Triangle.h"
#include "ColorTriangle.h"
#include "Ex1_1.h"
#include "Ex2_1.h"
#include "Ex2_2.h"
#include "Ex3_1.h"
#include "Ex3_2.h"
#include "FaceBox.h"
#include "Ex_Cyclender.h"
#include "Ex_DynamicPolygon.h"
#include "Ex_ModelImport.h"


#include "Ex_Lighting.h"
#include "Ex_Lighting_Tex.h"
#include "Ex_Lighting_Cast.h"

#include "Ex_DepthTest.h"
#include "Ex_StencilTest.h"
#include "Ex_Blending.h"
#include "Ex_FrameBuffer.h"
#include "Ex_Skybox.h"
#include "Ex_EnvReflectAndRefract.h"

#include "Ex_Instancing.h"
#include "Ex_PlanetInstancing.h"
#include "Ex_AntiAlising.h"
void InitExamples() {
  //ADD_EXAMPLE(Ex_DepthTest);
  //ADD_EXAMPLE(Ex_StencilTest);
  //ADD_EXAMPLE(Ex_Blending);
  //ADD_EXAMPLE(Ex_FrameBuffer);
  //ADD_EXAMPLE(Ex_Skybox);
  //ADD_EXAMPLE(Ex_EnvReflectAndRefract);
  //ADD_EXAMPLE(Ex_DynamicPolygon);
  //ADD_EXAMPLE(Ex_Instancing);
  //ADD_EXAMPLE(Ex_PlanetInstancing);
  ADD_EXAMPLE(Ex_AntiAlising);

}