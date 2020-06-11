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

void InitExamples() {
  ADD_EXAMPLE(Ex_DepthTest);
  ADD_EXAMPLE(Ex_StencilTest);
  ADD_EXAMPLE(Ex_Blending);
  ADD_EXAMPLE(Ex_FrameBuffer);

}