#pragma once
#define DISALLOW_CTOR(TypeName) \
   TypeName() = delete; 

#define DISALLOW_CTOR_MOVECTOR_COPYCTOR(TypeName) \
   private:                       \
   TypeName() = delete;           \
   TypeName(const TypeName&) = delete;           \
   TypeName(const TypeName&&) = delete;     


#define NO_INSTANCE(TypeName)   DISALLOW_CTOR_MOVECTOR_COPYCTOR(TypeName)