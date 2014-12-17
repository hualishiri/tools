#include "target.h"

namespace tools{
//TODO: something

void AirTarget::Initialize(TargetOption* option){}
bool AirTarget::Valid() const{ return true;}
void AirTarget::Next(){}
void AirTarget::Reset(){}
void AirTarget::GetState(TargetState* state){}
unsigned long AirTarget::GetSumTime() const{ return 100; }

void LandTarget::Initialize(TargetOption* option){}
bool LandTarget::Valid() const{ return true;}
void LandTarget::Next(){}
void LandTarget::Reset(){}
void LandTarget::GetState(TargetState* state){}
unsigned long LandTarget::GetSumTime() const{ return 100; }

void SurfaceSeaTarget::Initialize(TargetOption* option){}
bool SurfaceSeaTarget::Valid() const{ return true;}
void SurfaceSeaTarget::Next(){}
void SurfaceSeaTarget::Reset(){}
void SurfaceSeaTarget::GetState(TargetState* state){}
unsigned long SurfaceSeaTarget::GetSumTime() const{ return 100; }

void UnderSeaTarget::Initialize(TargetOption* option){}
bool UnderSeaTarget::Valid() const{ return true;}
void UnderSeaTarget::Next(){}
void UnderSeaTarget::Reset(){}
void UnderSeaTarget::GetState(TargetState* state){}
unsigned long UnderSeaTarget::GetSumTime() const{ return 100; }

} //namespace tools
